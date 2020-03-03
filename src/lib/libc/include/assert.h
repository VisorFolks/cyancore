#pragma once

#define assert(X)	(X ? (void)0 : __assert(__FILE__, __LINE__, #X))

void __assert(const char *file, unsigned int line, const char *assertion);
