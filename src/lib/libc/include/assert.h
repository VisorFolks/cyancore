#pragma once

#define assert(X)	(X ? (void)0 : __assert(__func__, __LINE__))
#define assert_ndbg(X)	(X ? (void)0 : __assert_nodbg())

void __assert(const char *, unsigned int);
void __assert_nodbg();
