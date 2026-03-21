//
// kernel.cpp
//
// Ported from link/examples/esp32
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#include "kernel.h"
#include <thread>
#include <cassert>

//#define GPIO_LED		18	// LED connected here, instead of Act LED
#define PRINT_LINK_STATE	true

short CKernel::s_ClickSound[] =
{
	#include "click-sound.h"
};

CKernel::CKernel(void)
:	CStdlibAppNetwork ("metro")
#ifdef GPIO_LED
	, m_LEDPin (GPIO_LED, GPIOModeOutput)
#endif
{
}

CStdlibApp::TShutdownMode CKernel::Run(void)
{
	m_pLink = new ableton::Link (120.0f);
	assert (m_pLink);
	m_pLink->enable(true);

	m_pSound = new CPWMSoundBaseDevice (&mInterrupt, 44100, 256);
	assert (m_pSound);
	m_pSound->AllocateQueue (500);
	m_pSound->SetWriteFormat (SoundFormatSigned16, 2);
	m_pSound->Start ();

	TickTask ();

	return ShutdownHalt;
}

void CKernel::TickTask (void)
{
	assert (m_pLink);

	if (PRINT_LINK_STATE)
	{
		new std::thread (PrintTask, this);
	}

	bool bSoundActive = false;
	while (true)
	{
		const auto state = m_pLink->captureAudioSessionState();
		const auto phase = state.phaseAtTime(m_pLink->clock().micros(), 1.);
		bool bLEDOn = fmodf(phase, 1.) < 0.1;

#ifdef GPIO_LED
		m_LEDPin.Write (bLEDOn ? HIGH : LOW);
#else
		if (bLEDOn)
		{
			mActLED.On ();
		}
		else
		{
			mActLED.Off ();
		}
#endif

		if (bLEDOn)
		{
			if (!bSoundActive)
			{
				m_pSound->Write (s_ClickSound, sizeof s_ClickSound);
				bSoundActive = true;
			}
		}
		else
		{
			bSoundActive = false;
		}

		mScheduler.MsSleep (1);
	}
}

void CKernel::PrintTask (CKernel *pThis)
{
	assert (pThis);

	const auto quantum = 4.0;

	while (true)
	{
		const auto sessionState = pThis->m_pLink->captureAppSessionState();
		const auto numPeers = pThis->m_pLink->numPeers();
		const auto time = pThis->m_pLink->clock().micros();
		const auto beats = sessionState.beatAtTime(time, quantum);

		std::cout << std::defaultfloat << "| peers: " << numPeers << " | "
			  << "tempo: " << sessionState.tempo() << " | " << std::fixed
			  << "beats: " << beats << " |" << std::endl;

		pThis->mScheduler.MsSleep (800);
	}
}
