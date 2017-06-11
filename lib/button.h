#pragma once
#include "msp430/btn.h"
namespace gpio {
	using port_t = msp430::gpio::port_t;
	template<port_t port, const uint8_t bval>
	struct button : public msp430::gpio::btn<port, bval> {
		using btn_t = msp430::gpio::btn<port, bval>;
		using cb_t = void (*)(void);
		button() : press_cb(nullptr), release_cb(nullptr) {
			btn_t::init();
			state = btn_t::is_push();
		}
		void on_press(void (*cb)(void) = nullptr) { press_cb = cb; }
		void on_release(void (*cb)(void) = nullptr) { release_cb = cb; }
		void update() {
			bool cur = btn_t::is_push();
			if(cur == true && state == false) {
				if(press_cb) press_cb();
			}
			else if(cur == false && state == true) {
				if(release_cb) release_cb();
			}
			state = cur; // update state
		}
		private:
			bool state;
			cb_t press_cb;
			cb_t release_cb;
	};
}
