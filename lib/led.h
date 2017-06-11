#pragma once
#include "msp430/led.h"
namespace gpio {
	using port_t = msp430::gpio::port_t;
	template<port_t port, const uint8_t bval>
	struct led : public msp430::gpio::led<port, bval> {
		using led_t = msp430::gpio::led<port, bval>;
		led() { led_t::init(); }
	};
}
