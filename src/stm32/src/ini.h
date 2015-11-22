/* inih -- simple .INI file parser

inih is released under the New BSD license (see LICENSE.txt). Go to the project
home page for more info:

https://github.com/benhoyt/inih

*/

#ifndef __INI_H__
#define __INI_H__

/* Make this header file easier to include in C++ code */
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

/* Typedef for prototype of handler function. */
typedef int (*ini_handler)(void* user, const char* section,
                           const char* name, const char* value);

/* Typedef for prototype of fgets-style reader function. */
typedef char* (*ini_reader)(char* str, int num, void* stream);

/* Same as ini_parse(), but takes an ini_reader function pointer instead of
   filename. Used for implementing custom or string-based I/O. */
int ini_parse_stream(ini_reader reader, void* stream, ini_handler handler,
                     void* user);

/* Nonzero to allow multi-line value parsing, in the style of Python's
   ConfigParser. If allowed, ini_parse() will call the handler with the same
   name for each subsequent line parsed. */
#ifndef INI_ALLOW_MULTILINE
#define INI_ALLOW_MULTILINE 1
#endif

/* Nonzero to allow a UTF-8 BOM sequence (0xEF 0xBB 0xBF) at the start of
   the file. See http://code.google.com/p/inih/issues/detail?id=21 */
#ifndef INI_ALLOW_BOM
#define INI_ALLOW_BOM 1
#endif

/* Nonzero to use stack, zero to use heap (malloc/free). */
#ifndef INI_USE_STACK
#define INI_USE_STACK 1
#endif

/* Stop parsing on first error (default is to keep parsing). */
#ifndef INI_STOP_ON_FIRST_ERROR
#define INI_STOP_ON_FIRST_ERROR 0
#endif

/* Maximum line length for any line in INI file. */
#ifndef INI_MAX_LINE
#define INI_MAX_LINE 200
#endif

#ifdef __cplusplus
}
#endif

#endif /* __INI_H__ */
