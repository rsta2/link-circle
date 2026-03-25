/* Copyright 2016, Ableton AG, Berlin. All rights reserved.
 * Circle support by Rene Stange, Copyright 2026
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  If you would like to incorporate Link into a proprietary software application,
 *  please contact <link-devs@ableton.com>.
 */

#include "AudioPlatform_Circle.hpp"
#include <circle/sound/pwmsoundbasedevice.h>
#include <circle/sched/scheduler.h>
#include <circle/interrupt.h>
#include <chrono>
#include <cassert>

namespace ableton
{
namespace linkaudio
{

AudioPlatform::AudioPlatform(Link &rLink)
  : mEngine(rLink)
  , mpAudioTask(new AudioTask (mEngine))
{
  assert (mpAudioTask);
}

AudioPlatform::~AudioPlatform()
{
  assert (mpAudioTask);
  mpAudioTask->Stop();
  CScheduler::Get()->MsSleep (10);
  mpAudioTask->WaitForTermination();
}

AudioTask::AudioTask(AudioEngine &rEngine)
  : mrEngine(rEngine)
  , mpSoundDevice(nullptr)
  , mSampleTime(0)
  , mIsRunning(true)
{
  SetName("linkaudio");
}

void AudioTask::Stop()
{
  mIsRunning = false;
}

void AudioTask::Run()
{
  mpSoundDevice = new CPWMSoundBaseDevice(CInterruptSystem::Get(), SampleRate, ChunkSize);
  assert (mpSoundDevice);
  mpSoundDevice->AllocateQueue(QueueSizeMillis);
  mpSoundDevice->SetWriteFormat(SoundFormatSigned16, 2);
  mpSoundDevice->Start();

  unsigned nQueueSizeFrames = mpSoundDevice->GetQueueSizeFrames();

  mrEngine.setBufferSize(nQueueSizeFrames);
  mrEngine.setSampleRate(SampleRate);

  while (mIsRunning)
  {
    // Get the amount of padding, which basically is the amount of data in the driver's
    // ring buffer that is filled with unread data. Thus, subtracting this amount from
    // the buffer size gives the effective buffer size, which is the amount of frames
    // that can be safely written to the driver.
    unsigned paddingFrames = mpSoundDevice->GetQueueFramesAvail();
    const unsigned numSamples = nQueueSizeFrames - paddingFrames;

    const auto hostTime = mHostTimeFilter.sampleTimeToHostTime(mSampleTime);
    mSampleTime += numSamples;

    const auto bufferBeginAtOutput = hostTime + mrEngine.mOutputLatency.load();
    mrEngine.audioCallback(bufferBeginAtOutput, numSamples);

    short Buffer[numSamples][2];
    for (unsigned i = 0; i < numSamples; ++i)
    {
      if (i >= mrEngine.mBuffer.size())
      {
        break;
      }
      for (unsigned j = 0; j < 2; ++j)
      {
        Buffer[i][j] = static_cast<short>(mrEngine.mBuffer[i] * 32767);
      }
    }

    mpSoundDevice->Write(Buffer, sizeof Buffer);

    CScheduler::Get()->MsSleep (1);
  }

  mpSoundDevice->Cancel();
  while (mpSoundDevice->IsActive())
  {
    CScheduler::Get()->Yield ();
  }

  delete mpSoundDevice;
  mpSoundDevice = nullptr;
}

} // namespace linkaudio
} // namespace ableton
