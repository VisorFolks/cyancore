#pragma once

#define _PRAGMA(x)	_Pragma (#x)
#define INFO(x)		_PRAGMA(message (#x))
#define WARN(x)		_PRAGMA(GCC warning #x)
#define ERROR(x)	_PRAGMA(GCC error #x)
#define TODO(x)		INFO(TODO: x)

#define _WEAK		__attribute__((weak))
#define _UNUSED		__attribute__((unused))
