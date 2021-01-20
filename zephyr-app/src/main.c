/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <misc/printk.h>
#include <console.h>
#include "app/ihp_cli.h"
#include "common.h"

K_THREAD_DEFINE(cli_thread, STACK_SIZE,
	run_shell_cli, NULL, NULL, NULL,
	THREAD_PRIORITY, 0, K_FOREVER);

void main(void)
{
	console_init();
	//printk("Hello World! %s\n", CONFIG_BOARD);
	k_thread_start(cli_thread);

	// run_coap_server();
}
