#pragma once
#include "msp430/usci-uart.h"
namespace uart {
	template<usci::module_t module, uint32_t baud = 9600, uint32_t fcpu = F_CPU>
	struct uart : public usci::uart<module, baud, fcpu> {
		using uart_t = usci::uart<module, baud, fcpu>;
		static void putc(char c) { uart_t::write(c); }
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
