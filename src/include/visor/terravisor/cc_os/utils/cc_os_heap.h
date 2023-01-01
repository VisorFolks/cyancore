/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: cc_os_heap.h
 * Description		: CC OS Heap declaration (Placeholder)
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <terravisor/cc_os/cc_os.h>

void * cc_os_malloc(size_t size);
void cc_os_free(void *addr);
