#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <status.h>
#include <driver/console.h>
#include <hal/gpio.h>

void project_setup()
{
	gpio_pin_config(0, 5, out);
	gpio_pin_clear(0, 5);
	printf("Demo Program!\n");
	return;
}

void project_loop()
{
	char c, arr[20];
	uint8_t i;
	printf("Enter Password: ");
	i = 0;
	do
	{
		c = getch();
		gpio_pin_toggle(0, 5);
		if(c == '\b')
		{
			printf("\b \b");
			i--;
		}
		else if(c != '\r')
		{
			printf("*");
			arr[i++] = c;
		}
		
		if(i > 18)
		{
			i = 19;
			break;
		}
	}
	while(c != '\r');
	arr[i] = '\0';
	printf("\nYou Entered: %s\n", arr);
	return;
}
