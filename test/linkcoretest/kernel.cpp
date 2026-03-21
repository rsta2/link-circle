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
#include <assert.h>

#define CATCH_CONFIG_MAIN
#define main _main
#include <ableton/test/CatchWrapper.hpp>

extern int _main (int argc, char *argv[]);

namespace
{

char *_strdup (const char *pString)
{
	char *p = new char[strlen (pString)+1];
	assert (p);
	return strcpy (p, pString);
}

}

CKernel::CKernel(void)
:	CStdlibAppNetwork ("linkcoretest")
{
}

CStdlibApp::TShutdownMode CKernel::Run(void)
{
	char *ArgV[2];
	ArgV[0] = _strdup (GetKernelName ());
	ArgV[1] = nullptr;

	_main (1, ArgV);

	return ShutdownHalt;
}
