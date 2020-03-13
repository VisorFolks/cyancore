#pragma once
#define _MACHINE_CALL_H_

typedef struct mret
{
	uintptr_t p;
	size_t size;
	status_t status;
} mret_t;

// Machine call IDs

#define FETCH_DP		0x0001
#define SET_SLEEP_MODE		0x0002
