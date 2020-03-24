#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <status.h>
#include <driver/console.h>

char getch()
{
    char c;
    console_getc(&c);
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
        console_putc(temp);
    }
    while(temp != '\r');
    return c;
}