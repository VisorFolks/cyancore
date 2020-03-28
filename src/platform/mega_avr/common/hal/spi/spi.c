#include <status.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include <mmio.h>
#include <mega_avr_platform.h>
#include <interrupt.h>
#include <hal/spi.h>
#include "spi-private.h"


status_t spi_master_setup(spi_port_t *port, dataframe_format_t df_format, clk_pol_t cpol, clk_ph_t cpha)
{
}

status_t spi_slave_setup(spi_port_t *port, dataframe_format_t df_format, clk_pol_t cpol, clk_ph_t cpha)
{
}

bool spi_wcol_error(spi_port_t *port)
{
	assert(port);
	return (MMIO8(port->baddr + SPSR_OFFSET) & (1 << WCOL)) ? true : false;
}

bool spi_trx_done(spi_port_t *port)
{
	assert(port);
	return (MMIO8(port->baddr + SPSR_OFFSET) & (1 << SPIF)) ? true : false;
}

status_t spi_int_en(spi_port_t *port)
{
	assert(port);
	MMIO8(port->baddr + SPCR_OFFSET) |= (1 << SPIE);
	return success;
}

status_t spi_int_dis(spi_port_t * port)
{
	assert(port);
	MMIO8(port->baddr + SPCR_OFFSET) &= ~(1 << SPIE);
	return success;
}

status_t spi_tx(spi_port_t *port, char data)
{
	assert(port);
}

status_t spi_rx(spi_port_t *port, char *data)
{
	assert(port);
}