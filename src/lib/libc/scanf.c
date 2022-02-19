/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: scanf.c
 * Description		: This file contains sources of libc-scanf
 *			  inspired from gnu-libc
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stddef.h>
#include <stdint.h>
#include <status.h>
#include <ccpfs.h>
#include <stdio.h>
#include <stddev.h>

int __fgetc(const FILE *dev, char *c)
{
	return ccpdfs_read(dev, c);
}

char getch()
{
    char c;
    __fgetc(stdin, &c);
    return c;
}

char getchar()
{
    char c = 0, temp;
    do
    {
        temp = getch();
        if(c == 0)
            c = temp;
        fputc(stdout, temp);
    }
    while(temp != '\r');
    return c;
}
