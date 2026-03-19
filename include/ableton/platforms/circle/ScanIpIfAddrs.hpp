/* Copyright 2020, Ableton AG, Berlin and 2019, Mathias Bredholt, Torso Electronics,
 * Copenhagen. All rights reserved. Portions by Rene Stange, Copyright 2026
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

#include <ableton/discovery/AsioTypes.hpp>
#include <circle/net/netsubsystem.h>
#include <circle/net/netconfig.h>
#include <circle/net/ipaddress.h>
#include <arpa/inet.h>
#include <vector>

namespace ableton
{
namespace platforms
{
namespace circle
{

struct ScanIpIfAddrs
{
	std::vector<discovery::IpAddress> operator()()
	{
		std::vector<discovery::IpAddress> addrs;
		CNetSubSystem *pNet = CNetSubSystem::Get();
		// Check if interface is active
		if (pNet->IsRunning())
		{
			// There is only one network interface in Circle
			const CNetConfig *pNetConfig = pNet->GetConfig();
			addrs.emplace_back(
				::asio::ip::address_v4(ntohl(*pNetConfig->GetIPAddress())));
		}
		return addrs;
	}
};

} // namespace circle
} // namespace platforms
} // namespace ableton
