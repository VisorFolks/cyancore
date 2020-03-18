#pragma once

#define assert_dbg(X)	(X ? (void)0 : __assert_dbg(__func__, __LINE__))
#define assert(X)	(X ? (void)0 : __assert())

void __assert_dbg(const char *, unsigned int);
void __assert();
