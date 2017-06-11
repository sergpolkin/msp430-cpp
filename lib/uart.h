#pragma once
#include "msp430/usci-uart.h"
namespace uart {
	template<usci::module_t module, uint32_t fclk, uint16_t baud>
	struct uart : public usci::uart<module, fclk, baud> {
		using uart_t = usci::uart<module, fclk, baud>;
		static void write(const void* buf, uint16_t size) {
			auto p = reinterpret_cast<const uint8_t*>(buf);
			while(size--) uart_t::write(*p++);
		}
		static void print(const char* str) {
			char c;
			while((c = *str++) != 0) {
				if(c == '\n') uart_t::write('\r');
				uart_t::write(c);
			}
		}
		static void println(const char* str) {
			print(str);
			uart_t::write('\r');
			uart_t::write('\n');
		}
	};
}
