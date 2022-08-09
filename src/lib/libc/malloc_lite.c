/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: malloc_lite.c
 * Description		: This file contains sources of libc-malloc
 *			  functions
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <status.h>
#include <string.h>
#include <stdlib.h>

typedef struct chunk
{
	size_t size;
	int free;
	struct chunk *next;
} chunk_t;

extern uint8_t _heap_start, _heap_end;
static chunk_t *freeList;

static void split(chunk_t *fit_slot, size_t size)
{
	chunk_t *new = (void *)((void *) fit_slot + size + sizeof(chunk_t));
	new->size = fit_slot->size - size - sizeof(chunk_t);
	new->free = 1;
	new->next = fit_slot->next;
	fit_slot->size = size;
	fit_slot->free = 0;
	fit_slot->next = new;
	return;
}

static void merge()
{
	chunk_t *cur;
	cur = freeList;
	while(cur->next != NULL)
	{
		if(cur->free && cur->next->free)
		{
			cur->size += cur->next->size + sizeof(chunk_t);
			cur->next = cur->next->next;
		}
		cur = cur->next;
	}
}

status_t platform_init_heap()
{
	memset(&_heap_start, 0, (size_t)(&_heap_end - &_heap_start));
	freeList = (void *)&_heap_start;
	freeList->size = (size_t)(&_heap_end - &_heap_start) - sizeof(chunk_t);
	freeList->free = 1;
	freeList->next = NULL;
	return success;
}

void *malloc(size_t n_bytes)
{
	chunk_t *cur;

	if(!freeList->size)
		return NULL;
	cur = freeList;
	while(cur->size < n_bytes || (!cur->free && cur->next))
		cur = cur->next;
	if(cur->size == n_bytes)
		cur->free = 0;
	else if(cur->size > (n_bytes + sizeof(chunk_t)))
		split(cur, n_bytes);
	else
		return NULL;
	return (void *)(++cur);
}

void free(void *ptr)
{
	if((void *)&_heap_start <= ptr && ptr <= (void *)&_heap_end)
	{
		chunk_t *cur = ptr;
		cur->free = 1;
		merge();
	}
	return;
}
