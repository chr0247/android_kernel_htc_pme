/* arch/arm/mach-msm/htc_footprint.h
 * Copyright (C) 2013 HTC Corporation.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
#ifndef __MACH_HTC_FOOTPRINT_H
#define __MACH_HTC_FOOTPRINT_H

#define CPU_FOOT_PRINT_MAGIC				0xACBDCC00
#define CPU_FOOT_PRINT_MAGIC_FROM_IDLE			0xACBDCF00
#define CPU_FOOT_PRINT_MAGIC_FPC			0xACBDAA00
#define CPU_FOOT_PRINT_MAGIC_FPC_FROM_IDLE		0xACBDAF00
#define CPU_FOOT_PRINT_MAGIC_HOTPLUG			0xACBDBB00
#define PSCI_FOOT_PRINT_SUSPEND_ENTRY			0xACBDEF01
#define PSCI_FOOT_PRINT_SUSPEND_EXIT			0xACBDEF0B
#define PSCI_FOOT_PRINT_OFF_ENTRY			0xACBDFF01
#define PSCI_FOOT_PRINT_OFF_EXIT			0xACBDFF0B
#define RESET_VECTOR_CLEAN_MAGIC			0xDCBAABCD
#define MAGIC_NUM_FOR_BATT_SAVE		0xFEDCBA00 
#define HTC_BATT_SAVE_CC			(1)
#define HTC_BATT_SAVE_OCV_UV		(1<<1)
#define BATT_SAVE_MASK		(HTC_BATT_SAVE_CC|HTC_BATT_SAVE_OCV_UV)

#ifndef __ASSEMBLY__
#include <linux/clk.h>

#ifdef CONFIG_HTC_DEBUG_FOOTPRINT

enum ACPU_STATE_FOOTPRINT {
	ACPU_ENTER = 0x1,		
	ACPU_BEFORE_SAFE_PARENT_INIT,
	ACPU_BEFORE_SET_SAFE_RATE,
	ACPU_BEFORE_SET_PARENT_RATE,
	ACPU_BEFORE_ERR_SET_RATE,
	ACPU_BEFORE_CLK_PREPARE,
	ACPU_BEFORE_ERR_SET_PARENT_RATE,
	ACPU_BEFORE_SET_RATE,
	ACPU_BEFORE_ERR_CLK_UNPREPARE,
	ACPU_BEFORE_CLK_UNPREPARE,
	ACPU_BEFORE_RETURN,
	ACPU_BEFORE_ERR_RETURN,
	ACPU_BEFORE_UPDATE_L2_BW,	
	ACPU_LEAVE = 0xff,		
};

enum FREQ_TYPE {
	FT_PREV_RATE,
	FT_CUR_RATE,
	FT_NEW_RATE,
};

enum HOTPLUG_ON_FOOTPRINT {
	HOF_ENTER,
	HOF_AFTER_PREPARE_ENABLE_L2,
	HOF_AFTER_PREPARE_ENABLE_CPU,
	HOF_BEFORE_UPDATE_L2_BW,
	HOF_LEAVE,
};

int read_backup_cc_uah(void);
void write_backup_cc_uah(int cc_reading);
int read_backup_ocv_uv(void);
void write_backup_ocv_uv(int ocv_backup);
void set_msm_watchdog_en_footprint(int enable);
void set_msm_watchdog_pet_time_utc(void);
void set_msm_watchdog_pet_footprint(void __iomem *sleep_clk_base);
void set_acpuclk_footprint(unsigned cpu, unsigned state);
void set_acpuclk_footprint_by_clk(struct clk *c, unsigned state);
void set_acpuclk_cpu_freq_footprint(enum FREQ_TYPE type, unsigned cpu, unsigned khz);
void set_acpuclk_cpu_freq_footprint_by_clk(enum FREQ_TYPE type, struct clk *c, unsigned khz);
void set_acpuclk_l2_freq_footprint(enum FREQ_TYPE type, unsigned khz);
void set_acpuclk_l2_freq_footprint_by_clk(enum FREQ_TYPE type, struct clk *c, unsigned khz);
void inc_kernel_exit_counter_from_pc(unsigned cpu);
void init_cpu_foot_print(unsigned cpu, bool from_idle, bool notify_rpm);
void set_cpu_foot_print(unsigned cpu, unsigned state);
void clean_reset_vector_debug_info(unsigned cpu);
void set_reset_vector(unsigned cpu);
void set_reset_vector_address_after_pc(unsigned cpu);
void set_reset_vector_value_after_pc(unsigned cpu);
void store_pm_boot_entry_addr(void);
void store_pm_boot_vector_addr(u64 value);
void set_hotplug_on_footprint(unsigned cpu, unsigned value);
#endif

#endif

#endif
