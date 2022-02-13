/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: ccpfs.h
 * Description		: This file contains prototypes and macros of
 *			  CC Pseudo File System
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _CCPFS_H_

typedef struct ccpdfs
{
	status_t (*write)(const char);
	status_t (*read)(char *);
} ccpdfs_t;

status_t ccpdfs_write(ccpdfs_t *, const char);
status_t ccpdfs_read(ccpdfs_t *, char *);
