/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <misc/printk.h>
#include <console.h>
#include "app/ihp_cli.h"

void main(void)
{
	console_init();
	//printk("Hello World! %s\n", CONFIG_BOARD);
	run_shell_cli();

}
