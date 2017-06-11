#include <msp430.h>
#include "gpio.h"
#include "uart.h"
namespace {
	constexpr auto port1 = msp430::gpio::P1;
	gpio::led<port1, BIT0> led_red;
	gpio::led<port1, BIT6> led_green;
	gpio::button<port1, BIT3> btn;
	uart::uart<usci::A0, F_CPU, 9600> uart0;
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
	uart0.init();
	uart0.print("\nmsp430launchpad\n");
	btn.on_press([](){
		led_green.on();
		uart0.println("> btn pressed");
	});
	btn.on_release([](){
		led_green.off();
		uart0.println("| btn released");
	});
	led_red.toggle();
	while(1) {
		__delay_cycles(F_CPU * 0.01); // 10ms
		btn.update();
	}
}
