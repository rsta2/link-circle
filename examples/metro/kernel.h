//
// kernel.h
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
#ifndef _kernel_h
#define _kernel_h

#include <circle_stdlib_app.h>
#include <ableton/Link.hpp>
#include <circle/gpiopin.h>
#include <circle/sound/pwmsoundbasedevice.h>

class CKernel : public CStdlibAppNetwork
{
public:
	CKernel (void);

	TShutdownMode Run (void);

private:
	void TickTask (void);

	static void PrintTask (CKernel *pThis);

private:
	ableton::Link *m_pLink;

	CGPIOPin m_LEDPin;
	CSoundBaseDevice *m_pSound;

	static short s_ClickSound[];
};

#endif
