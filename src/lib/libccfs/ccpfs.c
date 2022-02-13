/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: ccpfs.c
 * Description		: This file contains souces of CC Pseudo File System
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <assert.h>
#include <status.h>
#include <ccpfs.h>

status_t ccpdfs_write(ccpdfs_t *dev, const char c)
{
	assert(dev);
	if(dev->write)
		return error_file_io;
	return dev->write(c);
}

status_t ccpdfs_read(ccpdfs_t *dev, char *c)
{
	assert(dev);
	if(dev->write)
		return error_file_io;
	return dev->read(c);
}
