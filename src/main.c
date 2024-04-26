/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/logging/log_ctrl.h>
#include <stdio.h>
#include <string.h>

#include <nrfx_pdm.h>
#include <hal/nrf_gpio.h>
#include <nrf52840.h>

LOG_MODULE_REGISTER(main);

#define PDM_BUF_SIZE 495
int16_t pdm_buf[PDM_BUF_SIZE];

void nrfx_pdm_event_handler(nrfx_pdm_evt_t const *const p_evt)
{
	if (p_evt->buffer_requested)
	{
		nrfx_pdm_buffer_set(pdm_buf, PDM_BUF_SIZE);
	}
	if (p_evt->buffer_released != 0)
	{
		LOG_INF("buffer released: pdm_buf[0] = %d\n", (int16_t)pdm_buf[0]);
	}
}

static void pdm_init(void)
{
	nrfx_pdm_config_t pdm_config =
		{
			.mode = NRF_PDM_MODE_MONO,
			.edge = NRF_PDM_EDGE_LEFTFALLING,
			.pin_clk = NRF_GPIO_PIN_MAP(0, 3),
			.pin_din = NRF_GPIO_PIN_MAP(0, 2),
			.clock_freq = NRF_PDM_FREQ_1032K,
			.gain_l = NRF_PDM_GAIN_DEFAULT,
			.gain_r = NRF_PDM_GAIN_DEFAULT,
			.interrupt_priority = 	NRFX_PDM_DEFAULT_CONFIG_IRQ_PRIORITY,
									NRFX_PDM_DEFAULT_EXTENDED_RATIO_CONFIG
									NRFX_PDM_DEFAULT_EXTENDED_MCLKSRC_CONFIG
		};
	nrfx_pdm_init(&pdm_config, nrfx_pdm_event_handler);
}

/*ISR workaround given by Nordic*/
ISR_DIRECT_DECLARE(pdm_isr_handler)
{
	nrfx_pdm_irq_handler();
	ISR_DIRECT_PM(); /* PM done after servicing interrupt for best latency
					  */

	return 1; /* We should check if scheduling decision should be made */
}

void main(void)
{
	IRQ_DIRECT_CONNECT(PDM_IRQn, 0, pdm_isr_handler, 0); // workaround line
	LOG_INF("Starting PDM program!\n");
	LOG_INF("PDM Buffer size: %d in int16\n", PDM_BUF_SIZE);

	/*
	bool enabled = nrfx_pdm_enable_check();
	LOG_INF(enabled ? "true/n" : "false\n");
	*/

	pdm_init();
	LOG_INF("PDM init done, pdm_buf[0] = %d\n", pdm_buf[0]);
	nrfx_pdm_start();
	for (;;)
	{
		// Forever
		k_sleep(K_SECONDS(2));
	}
	nrfx_pdm_stop();
	LOG_ERR("PDM stopped\n");
}
