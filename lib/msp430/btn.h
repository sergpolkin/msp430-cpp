#pragma once
#include "gpio.h"
namespace msp430 { namespace gpio {
	template<port_t port, const uint8_t bval>
	struct btn;
	// P1 spec
	template<const uint8_t bval>
	struct btn<P1, bval> {
		static void init() {
			// Set digital io
			P1SEL &= ~bval;
			P1SEL2 &= ~bval;
			P1DIR &= ~bval; // Set input direction
			P1REN = bval; // Enable pull-up resistor
			P1OUT |= bval;
		}
		static bool is_push() { return !(P1IN & bval); }
	};
	// P2 spec
	template<const uint8_t bval>
	struct btn<P2, bval> {
		static void init() {
			// Set digital io
			P2SEL &= ~bval;
			P2SEL2 &= ~bval;
			P2DIR &= ~bval; // Set input direction
			P2REN = bval; // Enable pull-up resistor
			P2OUT |= bval;
		}
		static bool is_push() { return !(P2IN & bval); }
	};
}} // msp430::gpio
