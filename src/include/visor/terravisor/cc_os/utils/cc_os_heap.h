#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <terravisor/cc_os/cc_os.h>

void * cc_os_malloc(size_t size);
void * cc_os_free(const void *addr);
