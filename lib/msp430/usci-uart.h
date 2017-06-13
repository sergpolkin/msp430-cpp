#pragma once
#include "usci.h"
namespace usci {
	template<uint32_t baud, uint32_t fcpu>
	constexpr uint16_t uart_ucbr() {
		return fcpu / baud;
	}
	template<uint32_t baud, uint32_t fcpu>
	constexpr uint8_t uart_ucbrs() {
		return (static_cast<double>(fcpu) / baud - fcpu / baud) * 8;
	}
	template<usci::module_t module, uint32_t baud, uint32_t fcpu>
	struct uart;
	// A0
	template<uint32_t baud, uint32_t fcpu>
	struct uart<usci::A0, baud, fcpu> {
		static void init() {
			constexpr auto RXD = BIT1;
			constexpr auto TXD = BIT2;
			P1SEL |= RXD + TXD;
			P1SEL2 |= RXD + TXD;
			P1DIR &= ~RXD;
			P1DIR |= TXD;
			UCA0CTL1 |= UCSSEL_2 + UCSWRST; // SMCLK
			UCA0CTL0 = UCMODE_0; // UART mode
			UCA0BR0 = static_cast<uint8_t>(uart_ucbr<baud, fcpu>());
			UCA0BR1 = static_cast<uint8_t>(uart_ucbr<baud, fcpu>() >> 8);
			UCA0MCTL = (uart_ucbrs<baud, fcpu>() & 7) << 1;
			UCA0CTL1 &= ~UCSWRST; // Initialize USCI state machine
			IE2 &= ~(UCA0TXIE + UCA0RXIE); // Disable interrupts
		}
		static void write(uint8_t data) {
			// while (!(IFG2 & UCA0TXIFG)); // TX buffer ready?
			while(UCA0STAT & UCBUSY);
			UCA0TXBUF = data;
		}
	};
}
