//
// kernel.cpp
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

extern int _main (CI2CMaster *pI2CMaster);

CKernel::CKernel(void)
:	CStdlibAppNetwork ("linkhut",
			   CSTDLIBAPP_DEFAULT_PARTITION,
			   0, 0, 0, 0,
			   NetDeviceTypeEthernet),	// or: NetDeviceTypeWLAN
	m_I2CMaster (CMachineInfo::Get ()->GetDevice (DeviceI2CMaster), FALSE)
{
}

boolean CKernel::Initialize (void)
{
	if (!CStdlibAppNetwork::Initialize ())
	{
		return false;
	}

	return m_I2CMaster.Initialize ();
}

CStdlibApp::TShutdownMode CKernel::Run(void)
{
	mConsole.SetOptions (  mConsole.GetOptions ()
			     & ~(  CONSOLE_OPTION_ICANON
			         | CONSOLE_OPTION_ECHO));

	_main (&m_I2CMaster);

	return ShutdownHalt;
}
