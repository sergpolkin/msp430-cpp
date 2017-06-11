#pragma once
#include "usci.h"
namespace usci {
	template<uint32_t fclk, uint16_t baud>
	constexpr uint16_t ucbr() {
		return fclk / baud;
	}
	template<uint32_t fclk, uint16_t baud>
	constexpr uint8_t ucbrs() {
		return (static_cast<double>(fclk) / baud - fclk / baud) * 8;
	}
	template<usci::module_t module, uint32_t fclk, uint16_t baud>
	struct uart;
	// A0
	template<uint32_t fclk, uint16_t baud>
	struct uart<usci::A0, fclk, baud> {
		static void init() {
			constexpr auto RXD = BIT1;
			constexpr auto TXD = BIT2;
			P1SEL |= RXD + TXD;
			P1SEL2 |= RXD + TXD;
			P1DIR &= ~RXD;
			P1DIR |= TXD;
			UCA0CTL1 |= UCSSEL_2 + UCSWRST; // SMCLK
			UCA0CTL0 = UCMODE_0; // UART mode
			UCA0BR0 = static_cast<uint8_t>(ucbr<fclk, baud>());
			UCA0BR1 = static_cast<uint8_t>(ucbr<fclk, baud>() >> 8);
			UCA0MCTL = (ucbrs<fclk, baud>() & 7) << 1;
			UCA0CTL1 &= ~UCSWRST; // Initialize USCI state machine
			IE2 = 0; // Disable interrupts
		}
		static void write(uint8_t data) {
			// while (!(IFG2 & UCA0TXIFG)); // TX buffer ready?
			while(UCA0STAT & UCBUSY);
			UCA0TXBUF = data;
		}
	};
}
