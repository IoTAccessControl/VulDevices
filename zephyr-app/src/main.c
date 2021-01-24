/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <misc/printk.h>
#include <console.h>
#include <stdio.h>
#include <string.h>

#include "include/patch_service.h"
#include "include/iotpatch.h"
#include "libebpf/include/ebpf_allocator.h"
#include "include/utils.h"

#include "hotpatch/include/profiling.h"

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

	profile_add_event("micro profile dynamic start");
	profile_add_event("micro profile fixed start");

	// run_coap_server();
	start_patch_service();
	load_fixed_patch_0();

}

static uint8_t fixed_patch_0[64] = ""
"\x01\x00\x38\x00\x00\x00\x00\x00\x61\x11\x04\x00\x00\x00\x00\x00\x67\x01\x00\x00\x20\x00\x00\x00\xc7"
"\x01\x00\x00\x20\x00\x00\x00\xb7\x00\x00\x00\x01\x00\x00\x00\x65\x01\x01\x00\x13\x00\x00\x00\xb7\x00"
"\x00\x00\x00\x00\x00\x00\x95\x00\x00\x00\x00\x00\x00\x00"
"";

static uint8_t sign_0[16] = "\x73\x73\x73\x73\x73\x73\x73\x73\x73\x73\x73\x73\x73\x73\x73\x73";

void load_fixed_patch_0(void) {
	patch_payload paylod;
	int pkt_len = 64;
	paylod.pkt = ebpf_malloc(pkt_len);
	memcpy(paylod.sign, sign_0, 16);
	memcpy(paylod.pkt, fixed_patch_0, pkt_len);
	patch_desc *patch = (patch_desc*) (paylod.pkt);
	DEBUG_LOG("packet size: %d patch type:%d code_len:%d addr:0x%08x\n", pkt_len, patch->type, patch->code_len, patch->inst_addr);
	// DEBUG_LOG("%d %hu\n", &(patch->type), patch->type);
	// DEBUG_LOG("%d %hu\n", &(patch->code_len), patch->code_len);
	// DEBUG_LOG("%d\n", *(uint8_t*)(fixed_patch_0+1));
	// DEBUG_LOG("%d\n", patch);
	notify_new_patch(patch);
}

// static uint8_t fixed_patch_0[24] = ""
// "\x01\x00\x10\x00\x00\x00\x00\x00\xb7\x00\x00\x00\x00\x00\x00\x00\x95\x00\x00\x00\x00\x00\x00\x00"
// "";

// static uint8_t sign_0[16] = "\x73\x73\x73\x73\x73\x73\x73\x73\x73\x73\x73\x73\x73\x73\x73\x73";

// void load_fixed_patch_0(void) {
// 	patch_payload paylod;
// 	int pkt_len = 24;
// 	paylod.pkt = ebpf_malloc(pkt_len);
// 	memcpy(paylod.sign, sign_0, 16);
// 	memcpy(paylod.pkt, fixed_patch_0, pkt_len);
// 	patch_desc *patch = (patch_desc*) (paylod.pkt);
// 	DEBUG_LOG("packet size: %d patch type:%d code_len:%d addr:0x%08x\n", pkt_len, patch->type, patch->code_len, patch->inst_addr);
// 	// DEBUG_LOG("%d %hu\n", &(patch->type), patch->type);
// 	// DEBUG_LOG("%d %hu\n", &(patch->code_len), patch->code_len);
// 	// DEBUG_LOG("%d\n", *(uint8_t*)(fixed_patch_0+1));
// 	// DEBUG_LOG("%d\n", patch);
// 	notify_new_patch(patch);
// }
