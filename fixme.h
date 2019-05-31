#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>

typedef char CHAR;
typedef unsigned char UCHAR;
typedef uint8_t  BYTE;
typedef uint8_t *LPBYTE;
typedef uint16_t WORD;
typedef WORD *LPWORD;
typedef uint16_t USHORT;
typedef uint32_t DWORD;
typedef uint32_t UINT32;
typedef DWORD   *LPDWORD;
typedef int32_t LONG;
typedef uint32_t ULONG;
typedef int BOOL;
#define FALSE 0
#define TRUE (!FALSE)
typedef char *LPSTR;
typedef char *LPCSTR;
typedef void *PVOID;
typedef void *LPVOID;
typedef size_t SIZE_T;
typedef int32_t INT;
typedef uint32_t UINT;
typedef PVOID HANDLE;

#define FILE_ATTRIBUTE_NORMAL 1
#define FILE_SHARE_WRITE 1
#define FILE_SHARE_READ 1
#define GENERIC_WRITE 1
#define GENERIC_READ 1
#define INVALID_HANDLE_VALUE NULL
#define CREATE_ALWAYS 1
#define OPEN_EXISTING 1
#define OPEN_ALWAYS 1
#define MAX_PATH 255

typedef struct _WIN32_FIND_DATA {
	int dummy;
} WIN32_FIND_DATA;

static HANDLE CreateFile(...)    { assert(0); }
static BOOL WriteFile(...)       { assert(0); return TRUE; }
static void CloseHandle(...)     { assert(0); }
static HANDLE FindFirstFile(...) { assert(0); return NULL; }
static BOOL ReadFile(...)        { assert(0); return TRUE; }
static DWORD GetFileSize(...)    { assert(0); return 0; }

#define ZeroMemory(d,l) memset(d,0,l)
#define min(x,y) ((x)<=(y)?(x):(y))

static char *strupr(char *str)
{
	for (int i = 0; i < strlen(str); i++)
		str[i] = toupper(str[i]);
	return str;
}

// FIXME: Unsafe if sizeof(str) < 9!
static char *itoa(int value, char *str, int base)
{
	assert(base == 16);
	sprintf(str, "%x", value);
	return str;
}
