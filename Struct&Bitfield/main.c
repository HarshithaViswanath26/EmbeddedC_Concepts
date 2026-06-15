/*
 * main.c
 *
 *  Created on: Jun 15, 2026
 *      Author: 49157
 */
/*
 * Fake UART Register using Bitfield Struct in C
Simulates a memory-mapped UART control register using C bitfields.
Models TX, RX, parity enable bits and a 2-bit baud rate selector packed into a 32-bit register.
Includes driver-style API functions with input validation and compile-time size assertion to catch struct padding issues.
Concepts covered: bitfield structs, volatile, memory-mapped register simulation, compile-time assertions, embedded driver patterns.*/

#include <stdint.h>
#include <stdio.h>

#define UART_DISABLE				0
#define UART_ENABLE 				1

#define BAUD0				0
#define BAUD1				1
#define BAUD2				2
#define BAUD3				3

typedef struct
{
	uint32_t TX_ENABLE : 1;
	uint32_t RX_ENABLE : 1;
	uint32_t PARITY_ENABLE : 1;
	uint32_t BAUD_RATE_SELECTOR : 2;
	uint32_t RESERVED : 27;

}UART_RegDef_t;
typedef char assert_uart_reg_size[(sizeof(UART_RegDef_t) == 4) ? 1 : -1];

/*#define REG_ADDR		((volatile uint32_t*)0x20000004)
#define UART_REG		((volatile UART_RegDef_t*) REG_ADDR)
*/
UART_RegDef_t UART_REG = {0};

void UART_SetTX(uint8_t EnOrDi)
{
	if(EnOrDi == UART_ENABLE)
		UART_REG.TX_ENABLE = 1;
	else
		UART_REG.TX_ENABLE = 0;
}

void UART_SetRX(uint8_t EnOrDi)
{
	if(EnOrDi == UART_ENABLE)
		UART_REG.RX_ENABLE = 1;
	else
		UART_REG.RX_ENABLE = 0;

}

void UART_SetParity(uint8_t EnOrDi)
{
	if(EnOrDi == UART_ENABLE)
		UART_REG.PARITY_ENABLE = 1;
	else
		UART_REG.PARITY_ENABLE = 0;

}

void UART_SetBaudRate(uint8_t baud)
{
	if(baud > 3) return;
	UART_REG.BAUD_RATE_SELECTOR = baud;
}


int main(void)
{
	UART_SetTX(UART_ENABLE);
	UART_SetRX(UART_DISABLE);
	UART_SetParity(UART_ENABLE);
	UART_SetBaudRate(BAUD2);

	printf("TX ENABLE bit: %u \n", UART_REG.TX_ENABLE);
	printf("RX ENABLE bit: %u \n", UART_REG.RX_ENABLE);
	printf("Parity ENABLE bit: %u \n", UART_REG.PARITY_ENABLE);
	printf("Baudrate Selector: %u \n", UART_REG.BAUD_RATE_SELECTOR);

	return 0;
}
