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

#pragma once

#include "AudioEngine.hpp"
#include <circle/sched/task.h>
#include <circle/sound/soundbasedevice.h>
#include <circle/i2cmaster.h>
#include <ableton/link/HostTimeFilter.hpp>
#include <atomic>

namespace ableton
{
namespace linkaudio
{

class AudioTask;

class AudioPlatform
{
public:
  AudioPlatform(Link &rLink, CI2CMaster *pI2CMaster = nullptr);
  ~AudioPlatform();

  AudioEngine mEngine;

private:
  AudioTask *mpAudioTask;
};

class AudioTask : public CTask
{
public:
  static const unsigned SampleRate = 44100;
  static const unsigned ChunkSize = 256;
  static const unsigned QueueSizeMillis = 20;

public:
  AudioTask(AudioEngine &rEngine, CI2CMaster *pI2CMaster);

  void Stop();

private:
  void Run();

private:
  AudioEngine &mrEngine;
  CI2CMaster *mpI2CMaster;
  CSoundBaseDevice *mpSoundDevice;
  link::HostTimeFilter<platforms::circle::Clock> mHostTimeFilter;
  double mSampleTime;
  std::atomic<bool> mIsRunning;
};

} // namespace linkaudio
} // namespace ableton
