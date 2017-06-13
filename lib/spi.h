#pragma once
#include "msp430/usci-spi.h"
namespace spi {
	template<usci::module_t module, uint32_t fclk = 100000, uint32_t fcpu = F_CPU>
	struct spi : public usci::spi<module, fclk, fcpu> {
	};
}
