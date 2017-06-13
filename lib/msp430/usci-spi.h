#pragma once
#include "usci.h"
namespace usci {
	template<uint32_t fclk, uint32_t fcpu>
	constexpr uint16_t spi_ucbr() {
		return fcpu / fclk;
	}
	template<usci::module_t module, uint32_t fclk, uint32_t fcpu>
	struct spi;
	// B0
	template<uint32_t fclk, uint32_t fcpu>
	struct spi<usci::B0, fclk, fcpu> {
		static void init_master() {
			constexpr auto CS = BIT4;
			constexpr auto CLK = BIT5;
			constexpr auto MISO = BIT6;
			constexpr auto MOSI = BIT7;
			P1SEL |= CS + CLK + MISO + MOSI;
			P1SEL2 |= CS + CLK + MISO + MOSI;
			P1DIR &= ~MISO;
			P1DIR |= CS + CLK + MOSI;
			UCB0CTL1 |= UCSSEL_2 + UCSWRST; // SMCLK
			UCB0CTL0 = UCCKPH + UCMSB + UCMST + UCSYNC; // 3-pin, 8-bit SPI master
			UCB0BR0 = static_cast<uint8_t>(spi_ucbr<fclk, fcpu>());
			UCB0BR1 = static_cast<uint8_t>(spi_ucbr<fclk, fcpu>() >> 8);
			UCB0CTL1 &= ~UCSWRST; // Initialize USCI state machine
			IE2 &= ~(UCB0TXIE + UCB0RXIE); // Disable interrupts
		}
		static void write(uint8_t data) {
			while(!(IFG2 & UCB0TXIFG));
			UCB0TXBUF = data;
		}
		static uint8_t read(void) {
			while(!(IFG2 & UCB0RXIFG));
			return UCB0RXBUF;
		}
	};
}
