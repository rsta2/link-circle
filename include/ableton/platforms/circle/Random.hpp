/* Copyright 2019, Ableton AG, Berlin. All rights reserved.
 * Portions by Rene Stange, Copyright 2026
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
 */

#pragma once

#include <circle/bcmrandom.h>
#include <circle/types.h>

namespace ableton
{
namespace platforms
{
namespace circle
{

class Random
{
public:
	uint8_t operator()()
	{
		return static_cast<uint8_t>((mRNG.GetNumber() % 94) + 33); // printable ascii chars
	}

private:
	CBcmRandomNumberGenerator mRNG;
};

} // namespace circle
} // namespace platforms
} // namespace ableton
