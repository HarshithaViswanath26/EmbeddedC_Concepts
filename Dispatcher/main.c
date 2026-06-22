/*
 * main.c
 *
 *  Created on: Jun 22, 2026
 *      Author: 49157
 */

/* Description: The code shows the underneath working of a dispatcher in CLI
 * For implementation, concepts of structs, array of structs & function pointers has been used.
 * It also shows why flag needs to be used for the edge case and not an "Else" part.*/

#include <stdint.h>
#include <stdio.h>
#include <string.h>

void Led_On(void)
{
	printf("Led ON\n");
}

void Led_Off(void)
{
	printf("Led OFF\n");
}

void Led_Toggle(void)
{
	printf("Led Toggle\n");
}

typedef struct
{
	const char* inputName;
	void (*handler)(void);
}Command;

static const Command cmd_lut[] = {
	{"Led_On", Led_On},
	{"Led_Off", Led_Off},
	{"Led_Toggle", Led_Toggle},
	{NULL, NULL}
};

void Dispatcher(const char *userInput)
{
	uint8_t flag = 0;
	for(int i = 0; cmd_lut[i].inputName != NULL; i++)
	{
		if(strcmp(cmd_lut[i].inputName, userInput) == 0)
		{
			cmd_lut[i].handler();
			flag = 1;
			break;
		}

	}

	if(!flag)
	{
		printf("No match found!\n");
	}

	return;

}
int main(void)
{
	Dispatcher("Led_on");  // No match
	Dispatcher("Led_Off");
	return 0;
}

