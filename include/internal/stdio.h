/*
   Copyright (c) 2020-2021 Sibi Siddharthan

   Distributed under the MIT license.
   Refer to the LICENSE file at the root directory for details.
*/

#ifndef WLIBC_STDIO_INTERNAL_H
#define WLIBC_STDIO_INTERNAL_H

#include <Windows.h>
#include <sys/types.h>

typedef struct WLIBC_FILE
{
	unsigned int magic;
	int fd;
	int buf_mode;
	int error;
	char *buffer;
	size_t buf_size;
	size_t start;
	size_t end;
	size_t pos; // ftell
	int prev_op;
	HANDLE phandle;
	CRITICAL_SECTION critical;
	struct WLIBC_FILE *prev;
	struct WLIBC_FILE *next;
} FILE;

/* Buffer options */

#define FILE_STREAM_MAGIC 0x1
#define VALIDATE_FILE_STREAM(stream, ret)                     \
	if (stream == NULL || stream->magic != FILE_STREAM_MAGIC) \
	{                                                         \
		errno = EINVAL;                                       \
		return ret;                                           \
	}

#define LOCK_FILE_STREAM(stream)   EnterCriticalSection(&(stream->critical))
#define UNLOCK_FILE_STREAM(stream) LeaveCriticalSection(&(stream->critical))

#define _IOBUFFER_INTERNAL  0x1
#define _IOBUFFER_EXTERNAL  0x2
#define _IOBUFFER_NONE      0x4
#define _IOBUFFER_ALLOCATED 0x8

#define _IOBUFFER_RDONLY 0x100 // reads are buffered
#define _IOBUFFER_WRONLY 0x200 // writes are buffered
#define _IOBUFFER_RDWR   0x400 // both reads and writes are unbuffered
//#define _IOBUFFER_WRRD   0x800 // writes are buffered, reads are unbuffered

// Same as public stdio.h
#define _IOFBF 0x0010 // Full buffering
#define _IOLBF 0x0020 // line buffering
#define _IONBF 0x0040 // no buffering

#define _IOEOF   0x1 // End of file reached
#define _IOERROR 0x2 // Error while read/writing file

#define OP_READ  0x1
#define OP_WRITE 0x2

#define FD_MEMSTREAM -1

extern FILE *_wlibc_stdio_head;
extern CRITICAL_SECTION _wlibc_stdio_critical;

void initialize_stdio();
void cleanup_stdio();
FILE *create_stream(int fd, int buf_mode, int buf_size);
void delete_stream(FILE *stream);

#endif
