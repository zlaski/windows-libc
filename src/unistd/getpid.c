/*
   Copyright (c) 2020 Sibi Siddharthan

   Distributed under the MIT license.
   Refer to the LICENSE file at the root directory for details.
*/

#include <unistd.h>
#include <Windows.h>

pid_t wlibc_getpid()
{
	return GetCurrentProcessId();
}
