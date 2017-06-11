#pragma once
#include "msp430/btn.h"
namespace gpio {
	using port_t = msp430::gpio::port_t;
	template<port_t port, const uint8_t bval>
	struct simple_button : public msp430::gpio::btn<port, bval> {
		using btn_t = msp430::gpio::btn<port, bval>;
		simple_button() { btn_t::init(); }
	};
}
