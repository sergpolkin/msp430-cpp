#include <msp430.h>
#include "gpio.h"
#include "uart.h"
#include "spi.h"
namespace {
	constexpr auto port1 = msp430::gpio::P1;
	gpio::led<port1, BIT0> led_red;
	// gpio::led<port1, BIT6> led_green;
	gpio::button<port1, BIT3> btn;
	uart::uart<usci::A0> uart0;
	spi::spi<usci::B0> spi0;
}
static void init(void) {
	DCOCTL = CALDCO_12MHZ;
	BCSCTL1 = CALBC1_12MHZ;
	WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
	__delay_cycles(F_CPU * 1); // 1s
}
int main(void) {
	init();
	led_red.toggle();
	spi0.init_master();
	uart0.init();
	uart0.print("\n\033[31mmsp430launchpad\033[0m\n");
	btn.on_press([](){
		led_red.on();
		uart0.println("> btn pressed");
	});
	btn.on_release([](){
		led_red.off();
		uart0.println("| btn released");
		spi0.write(0x55);
		uart0.putc(spi0.read());
	});
	led_red.toggle();
	while(1) {
		__delay_cycles(F_CPU * 0.01); // 10ms
		btn.update();
	}
}
