#pragma once
#include "gpio.h"
namespace msp430 { namespace gpio {
	template<port_t port, const uint8_t bval>
	struct led;
	// P1 spec
	template<const uint8_t bval>
	struct led<P1, bval> {
		static void init() {
			// Set digital io
			P1SEL &= ~bval;
			P1SEL2 &= ~bval;
			P1REN &= ~bval; // Disable pull-up resistor
			P1OUT &= ~bval; // Set the LEDs off
			P1DIR |= bval; // Set output direction
		}
		static void on() { P1OUT |= bval; }
		static void off() { P1OUT &= ~bval; }
		static void toggle() { P1OUT ^= bval; }
	};
	// P2 spec
	template<const uint8_t bval>
	struct led<P2, bval> {
		static void init() {
			// Set digital io
			P2SEL &= ~bval;
			P2SEL2 &= ~bval;
			P2REN &= ~bval; // Disable pull-up resistor
			P2OUT &= ~bval; // Set the LEDs off
			P2DIR |= bval; // Set output direction
		}
		static void on() { P2OUT |= bval; }
		static void off() { P2OUT &= ~bval; }
		static void toggle() { P2OUT ^= bval; }
	};
}} // msp430::gpio
