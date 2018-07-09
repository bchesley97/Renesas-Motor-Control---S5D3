/* generated pin source file - do not edit */
#include "r_ioport.h"
#if defined(__ICCARM__)
#pragma diag_suppress=Pa089
#endif
const ioport_pin_cfg_t g_bsp_pin_cfg_data[] = {
	{
		.pin = IOPORT_PORT_00_PIN_00,
		.pin_cfg = (IOPORT_CFG_ANALOG_ENABLE),
	},
	{
		.pin = IOPORT_PORT_00_PIN_01,
		.pin_cfg = (IOPORT_CFG_ANALOG_ENABLE),
	},
	{
		.pin = IOPORT_PORT_00_PIN_02,
		.pin_cfg = (IOPORT_CFG_ANALOG_ENABLE),
	},
	{
		.pin = IOPORT_PORT_00_PIN_04,
		.pin_cfg = (IOPORT_CFG_ANALOG_ENABLE),
	},
	{
		.pin = IOPORT_PORT_00_PIN_05,
		.pin_cfg = (IOPORT_CFG_ANALOG_ENABLE),
	},
	{
		.pin = IOPORT_PORT_00_PIN_06,
		.pin_cfg = (IOPORT_CFG_ANALOG_ENABLE),
	},
	{
		.pin = IOPORT_PORT_01_PIN_00,
		.pin_cfg = (IOPORT_CFG_PERIPHERAL_PIN | IOPORT_PERIPHERAL_RSPI),
	},
	{
		.pin = IOPORT_PORT_01_PIN_01,
		.pin_cfg = (IOPORT_CFG_PERIPHERAL_PIN | IOPORT_PERIPHERAL_RSPI),
	},
	{
		.pin = IOPORT_PORT_01_PIN_02,
		.pin_cfg = (IOPORT_CFG_PERIPHERAL_PIN | IOPORT_PERIPHERAL_RSPI),
	},
	{
		.pin = IOPORT_PORT_01_PIN_03,
		.pin_cfg = (IOPORT_CFG_PERIPHERAL_PIN | IOPORT_PERIPHERAL_RSPI),
	},
	{
		.pin = IOPORT_PORT_01_PIN_04,
		.pin_cfg = (IOPORT_CFG_PERIPHERAL_PIN | IOPORT_PERIPHERAL_SCI0_2_4_6_8),
	},
	{
		.pin = IOPORT_PORT_01_PIN_05,
		.pin_cfg = (IOPORT_CFG_PERIPHERAL_PIN | IOPORT_PERIPHERAL_SCI0_2_4_6_8),
	},
	{
		.pin = IOPORT_PORT_01_PIN_06,
		.pin_cfg = (IOPORT_CFG_PORT_DIRECTION_OUTPUT | IOPORT_CFG_PORT_OUTPUT_LOW),
	},
	{
		.pin = IOPORT_PORT_01_PIN_07,
		.pin_cfg = (IOPORT_CFG_PORT_DIRECTION_OUTPUT | IOPORT_CFG_PORT_OUTPUT_LOW),
	},
	{
		.pin = IOPORT_PORT_01_PIN_08,
		.pin_cfg = (IOPORT_CFG_PERIPHERAL_PIN | IOPORT_PERIPHERAL_DEBUG),
	},
	{
		.pin = IOPORT_PORT_01_PIN_09,
		.pin_cfg = (IOPORT_CFG_PERIPHERAL_PIN | IOPORT_PERIPHERAL_DEBUG),
	},
	{
		.pin = IOPORT_PORT_01_PIN_10,
		.pin_cfg = (IOPORT_CFG_PERIPHERAL_PIN | IOPORT_PERIPHERAL_DEBUG),
	},
	{
		.pin = IOPORT_PORT_01_PIN_12,
		.pin_cfg = (IOPORT_CFG_PORT_DIRECTION_OUTPUT | IOPORT_CFG_PORT_OUTPUT_LOW),
	},
	{
		.pin = IOPORT_PORT_01_PIN_13,
		.pin_cfg = (IOPORT_CFG_PERIPHERAL_PIN | IOPORT_PERIPHERAL_GPT1),
	},
	{
		.pin = IOPORT_PORT_01_PIN_14,
		.pin_cfg = (IOPORT_CFG_PERIPHERAL_PIN | IOPORT_PERIPHERAL_GPT1),
	},
	{
		.pin = IOPORT_PORT_02_PIN_01,
		.pin_cfg = (IOPORT_CFG_PORT_DIRECTION_INPUT),
	},
	{
		.pin = IOPORT_PORT_02_PIN_05,
		.pin_cfg = (IOPORT_CFG_PERIPHERAL_PIN | IOPORT_PERIPHERAL_CTSU),
	},
	{
		.pin = IOPORT_PORT_02_PIN_07,
		.pin_cfg = (IOPORT_CFG_PERIPHERAL_PIN | IOPORT_PERIPHERAL_CTSU),
	},
	{
		.pin = IOPORT_PORT_03_PIN_00,
		.pin_cfg = (IOPORT_CFG_PERIPHERAL_PIN | IOPORT_PERIPHERAL_DEBUG),
	},
	{
		.pin = IOPORT_PORT_04_PIN_05,
		.pin_cfg = (IOPORT_CFG_PERIPHERAL_PIN | IOPORT_PERIPHERAL_GPT1),
	},
	{
		.pin = IOPORT_PORT_04_PIN_06,
		.pin_cfg = (IOPORT_CFG_PERIPHERAL_PIN | IOPORT_PERIPHERAL_GPT1),
	},
	{
		.pin = IOPORT_PORT_04_PIN_07,
		.pin_cfg = (IOPORT_CFG_PERIPHERAL_PIN | IOPORT_PERIPHERAL_USB_FS),
	},
	{
		.pin = IOPORT_PORT_04_PIN_14,
		.pin_cfg = (IOPORT_CFG_PERIPHERAL_PIN | IOPORT_PERIPHERAL_GPT1),
	},
	{
		.pin = IOPORT_PORT_04_PIN_15,
		.pin_cfg = (IOPORT_CFG_PERIPHERAL_PIN | IOPORT_PERIPHERAL_GPT1),
	},
	{
		.pin = IOPORT_PORT_05_PIN_00,
		.pin_cfg = (IOPORT_CFG_PORT_DIRECTION_OUTPUT | IOPORT_CFG_PORT_OUTPUT_LOW),
	},
};
const ioport_cfg_t g_bsp_pin_cfg = {
	.number_of_pins = sizeof(g_bsp_pin_cfg_data)/sizeof(ioport_pin_cfg_t),
	.p_pin_cfg_data = &g_bsp_pin_cfg_data[0],
};
#if defined(__ICCARM__)
#pragma diag_default=Pa089
#endif
