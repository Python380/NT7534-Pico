#include "pico/stdlib.h"
#include "hardware/uart.h"
#include <stdio.h>
#include "../lib/NT7534.h"
#include "../lib/parallelInterface.h"

int main()
{
	stdio_init_all();
	sleep_ms(10000);

	gpio_init(23);
	gpio_set_dir(23, GPIO_OUT);
	gpio_put(23, 1); // set power supply PS pin high

	Parallel8Bit interface(15, 22, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4);
	NT7534 nt7534(interface);
	nt7534.begin(0x19);
	nt7534.clear();

	while (1)
	{
		printf("Drawing rect\n");
		nt7534.fillrect(10, 10, 118, 54, 0xFF);
	}
}
