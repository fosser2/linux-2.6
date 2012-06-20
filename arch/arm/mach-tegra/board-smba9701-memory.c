/* OK, info extracted from a running .32 kernel */
/*
 * Copyright (C) 2011 Eduardo Jos� Tagle <ejtagle@tutopia.com>
 * Copyright (C) 2010 Google, Inc.
 *
 * Authors:
 *	Colin Cross <ccross@google.com>
 *	Eduardo Jos� Tagle <ejtagle@tutopia.com>
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

/* Tegra2 external memory controller initialization */
 
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/init.h>

#include "board-smba9701.h"
#include "tegra2_emc.h"

/* This is the LPDDR2 sdram used in SMBA_1002: Hynax HY5PS1G831C-S6  //Shuttle was S5 speed bin
				    Malata_a02_12Mhz_H5PS1G83EFR-S6C_333Mhz_1GB_emmc_THGBM1G6D4EBAI4_x8.bct
	Tck  = 2.5ns -> DDR2-800   //Same as Shuttle
	CL	 = 6 Clk          // Shuttle was 5  
	tRCD = 6 Clk              //Shuttle was 5
	tRP  = 6 Clk              //Shuttle was 5

	VDD = 1.8 +/- 0.1V
	VDDQ = 1.8 +/- 0.1V
	
	4 chips x 128Mx8
	
	Programmable CAS latency 3, 4, 5 and 6 supported
	Programmable additive latency 0, 1, 2, 3, 4 and 5 supported
	Programmable burst length 4/8 with both nibble sequential and interleave mode
	Internal eight bank operations with single pulsed RAS
	Auto refresh and self refresh supported
	tRAS lockout supported
	8K refresh cycles /64ms	
	
	Page size = 1kbyte

	*/

static const struct tegra_emc_table smba_emc_tables[] = {
  	{
		.rate =  18000,   /* SDRAM frequency : 950mV emc core voltage*/
		.regs = {
            0x00000002,   /* RC */
            0x00000006,   /* RFC */
            0x00000003,   /* RAS */
            0x00000003,   /* RP */
            0x00000006,   /* R2W */
            0x00000004,   /* W2R */
            0x00000002,   /* R2P */
            0x0000000B,   /* W2P */
            0x00000003,   /* RD_RCD */
            0x00000003,   /* WR_RCD */
            0x00000002,   /* RRD */
            0x00000002,   /* REXT */
            0x00000003,   /* WDV */
            0x00000005,   /* QUSE */
            0x00000004,   /* QRST */
            0x00000008,   /* QSAFE */
            0x0000000C,   /* RDV */
            0x00000070,   /* REFRESH */
            0x00000000,   /* BURST_REFRESH_NUM */
            0x00000003,   /* PDEX2WR */
            0x00000003,   /* PDEX2RD */
            0x00000003,   /* PCHG2PDEN */
            0x00000003,   /* ACT2PDEN */
            0x00000001,   /* AR2PDEN */
            0x0000000B,   /* RW2PDEN */
            0x00000003,   /* TXSR */
            0x00000003,   /* TCKE */
            0x00000008,   /* TFAW */
            0x00000004,   /* TRPAB */
            0x00000008,   /* TCLKSTABLE */
            0x00000002,   /* TCLKSTOP */
            0x0000004B,   /* TREFBW */
            0x00000000,   /* QUSE_EXTRA */
            0x00000003,   /* FBIO_CFG6 */
            0x00000000,   /* ODT_WRITE */
            0x00000000,   /* ODT_READ */
            0x00000082,   /* FBIO_CFG5 */
            0x00780006,   /* CFG_DIG_DLL */
            0x00000010,   /* DLL_XFORM_DQS */
            0x00000008,   /* DLL_XFORM_QUSE */
            0x00000000,   /* ZCAL_REF_CNT */
            0x00000002,   /* ZCAL_WAIT_CNT */
            0x00000000,   /* AUTO_CAL_INTERVAL */
            0x00000000,   /* CFG_CLKTRIM_0 */
            0x00000000,   /* CFG_CLKTRIM_1 */
            0x00000000,   /* CFG_CLKTRIM_2 */
        }
    },
    {
		.rate =  27000,   /* SDRAM frequency : 950mV emc core voltage*/
		.regs = {
            0x00000002,   /* RC */
            0x00000006,   /* RFC */
            0x00000003,   /* RAS */
            0x00000003,   /* RP */
            0x00000006,   /* R2W */
            0x00000004,   /* W2R */
            0x00000002,   /* R2P */
            0x0000000B,   /* W2P */
            0x00000003,   /* RD_RCD */
            0x00000003,   /* WR_RCD */
            0x00000002,   /* RRD */
            0x00000002,   /* REXT */
            0x00000003,   /* WDV */
            0x00000005,   /* QUSE */
            0x00000004,   /* QRST */
            0x00000008,   /* QSAFE */
            0x0000000C,   /* RDV */
            0x000000A8,   /* REFRESH */
            0x00000000,   /* BURST_REFRESH_NUM */
            0x00000003,   /* PDEX2WR */
            0x00000003,   /* PDEX2RD */
            0x00000003,   /* PCHG2PDEN */
            0x00000003,   /* ACT2PDEN */
            0x00000001,   /* AR2PDEN */
            0x0000000B,   /* RW2PDEN */
            0x00000004,   /* TXSR */
            0x00000003,   /* TCKE */
            0x00000008,   /* TFAW */
            0x00000004,   /* TRPAB */
            0x00000008,   /* TCLKSTABLE */
            0x00000002,   /* TCLKSTOP */
            0x00000071,   /* TREFBW */
            0x00000000,   /* QUSE_EXTRA */
            0x00000003,   /* FBIO_CFG6 */
            0x00000000,   /* ODT_WRITE */
            0x00000000,   /* ODT_READ */
            0x00000082,   /* FBIO_CFG5 */
            0x00780006,   /* CFG_DIG_DLL */
            0x00000010,   /* DLL_XFORM_DQS */
            0x00000008,   /* DLL_XFORM_QUSE */
            0x00000000,   /* ZCAL_REF_CNT */
            0x00000003,   /* ZCAL_WAIT_CNT */
            0x00000000,   /* AUTO_CAL_INTERVAL */
            0x00000000,   /* CFG_CLKTRIM_0 */
            0x00000000,   /* CFG_CLKTRIM_1 */
            0x00000000,   /* CFG_CLKTRIM_2 */
        }
    },
    {
		.rate =  54000,   /* SDRAM frequency : 1000mV emc core voltage*/
		.regs = {
            0x00000004,   /* RC */
            0x00000008,   /* RFC */
            0x00000003,   /* RAS */
            0x00000003,   /* RP */
            0x00000006,   /* R2W */
            0x00000004,   /* W2R */
            0x00000002,   /* R2P */
            0x0000000B,   /* W2P */
            0x00000003,   /* RD_RCD */
            0x00000003,   /* WR_RCD */
            0x00000002,   /* RRD */
            0x00000002,   /* REXT */
            0x00000003,   /* WDV */
            0x00000006,   /* QUSE */
            0x00000004,   /* QRST */
            0x00000008,   /* QSAFE */
            0x0000000C,   /* RDV */
            0x0000017F,   /* REFRESH */
            0x00000000,   /* BURST_REFRESH_NUM */
            0x00000003,   /* PDEX2WR */
            0x00000003,   /* PDEX2RD */
            0x00000003,   /* PCHG2PDEN */
            0x00000003,   /* ACT2PDEN */
            0x00000001,   /* AR2PDEN */
            0x0000000B,   /* RW2PDEN */
            0x00000008,   /* TXSR */
            0x00000003,   /* TCKE */
            0x00000008,   /* TFAW */
            0x00000004,   /* TRPAB */
            0x00000008,   /* TCLKSTABLE */
            0x00000002,   /* TCLKSTOP */
            0x000000E1,   /* TREFBW */
            0x00000000,   /* QUSE_EXTRA */
            0x00000000,   /* FBIO_CFG6 */
            0x00000000,   /* ODT_WRITE */
            0x00000000,   /* ODT_READ */
            0x00000082,   /* FBIO_CFG5 */
            0x00780006,   /* CFG_DIG_DLL */
            0x00000010,   /* DLL_XFORM_DQS */
            0x00000008,   /* DLL_XFORM_QUSE */
            0x00000000,   /* ZCAL_REF_CNT */
            0x00000005,   /* ZCAL_WAIT_CNT */
            0x00000000,   /* AUTO_CAL_INTERVAL */
            0x00000000,   /* CFG_CLKTRIM_0 */
            0x00000000,   /* CFG_CLKTRIM_1 */
            0x00000000,   /* CFG_CLKTRIM_2 */
        }
    },
    {
		.rate = 108000,   /* SDRAM frequency : 1000mV emc core voltage*/
		.regs = {
            0x00000007,   /* RC */
            0x0000000F,   /* RFC */
            0x00000005,   /* RAS */
            0x00000003,   /* RP */
            0x00000006,   /* R2W */
            0x00000004,   /* W2R */
            0x00000002,   /* R2P */
            0x0000000B,   /* W2P */
            0x00000003,   /* RD_RCD */
            0x00000003,   /* WR_RCD */
            0x00000002,   /* RRD */
            0x00000002,   /* REXT */
            0x00000003,   /* WDV */
            0x00000006,   /* QUSE */
            0x00000004,   /* QRST */
            0x00000008,   /* QSAFE */
            0x0000000C,   /* RDV */
            0x0000031F,   /* REFRESH */
            0x00000000,   /* BURST_REFRESH_NUM */
            0x00000003,   /* PDEX2WR */
            0x00000003,   /* PDEX2RD */
            0x00000003,   /* PCHG2PDEN */
            0x00000003,   /* ACT2PDEN */
            0x00000001,   /* AR2PDEN */
            0x0000000B,   /* RW2PDEN */
            0x00000010,   /* TXSR */
            0x00000003,   /* TCKE */
            0x00000008,   /* TFAW */
            0x00000004,   /* TRPAB */
            0x00000008,   /* TCLKSTABLE */
            0x00000002,   /* TCLKSTOP */
            0x000001C2,   /* TREFBW */
            0x00000000,   /* QUSE_EXTRA */
            0x00000000,   /* FBIO_CFG6 */
            0x00000000,   /* ODT_WRITE */
            0x00000000,   /* ODT_READ */
            0x00000082,   /* FBIO_CFG5 */
            0xD0780323,   /* CFG_DIG_DLL */
            0x007FD010,   /* DLL_XFORM_DQS */
            0x00000010,   /* DLL_XFORM_QUSE */
            0x00000000,   /* ZCAL_REF_CNT */
            0x0000000A,   /* ZCAL_WAIT_CNT */
            0x00000000,   /* AUTO_CAL_INTERVAL */
            0x00000000,   /* CFG_CLKTRIM_0 */
            0x00000000,   /* CFG_CLKTRIM_1 */
            0x00000000,   /* CFG_CLKTRIM_2 */
        }
    },
    {
		.rate = 150000,   /* SDRAM frequency : 1000mV emc core voltage*/
		.regs = {
            0x00000009,   /* RC */
            0x00000014,   /* RFC */
            0x00000007,   /* RAS */
            0x00000003,   /* RP */
            0x00000006,   /* R2W */
            0x00000004,   /* W2R */
            0x00000002,   /* R2P */
            0x0000000B,   /* W2P */
            0x00000003,   /* RD_RCD */
            0x00000003,   /* WR_RCD */
            0x00000002,   /* RRD */
            0x00000002,   /* REXT */
            0x00000003,   /* WDV */
            0x00000006,   /* QUSE */
            0x00000004,   /* QRST */
            0x00000008,   /* QSAFE */
            0x0000000C,   /* RDV */
            0x0000045F,   /* REFRESH */
            0x00000000,   /* BURST_REFRESH_NUM */
            0x00000003,   /* PDEX2WR */
            0x00000003,   /* PDEX2RD */
            0x00000003,   /* PCHG2PDEN */
            0x00000003,   /* ACT2PDEN */
            0x00000001,   /* AR2PDEN */
            0x0000000B,   /* RW2PDEN */
            0x00000015,   /* TXSR */
            0x00000003,   /* TCKE */
            0x00000008,   /* TFAW */
            0x00000004,   /* TRPAB */
            0x00000008,   /* TCLKSTABLE */
            0x00000002,   /* TCLKSTOP */
            0x00000270,   /* TREFBW */
            0x00000000,   /* QUSE_EXTRA */
            0x00000001,   /* FBIO_CFG6 */
            0x00000000,   /* ODT_WRITE */
            0x00000000,   /* ODT_READ */
            0x00000082,   /* FBIO_CFG5 */
            0xD05E0323,   /* CFG_DIG_DLL */
            0x007FD010,   /* DLL_XFORM_DQS */
            0x00000010,   /* DLL_XFORM_QUSE */
            0x00000000,   /* ZCAL_REF_CNT */
            0x0000000E,   /* ZCAL_WAIT_CNT */
            0x00000000,   /* AUTO_CAL_INTERVAL */
            0x00000000,   /* CFG_CLKTRIM_0 */
            0x00000000,   /* CFG_CLKTRIM_1 */
            0x00000000,   /* CFG_CLKTRIM_2 */
        }
    },
    {
		.rate = 166500,   /* SDRAM frequency : 1000mV emc core voltage*/
		.regs = {
            0x0000000a,   /* RC */
            0x00000016,   /* RFC */
            0x00000008,   /* RAS */
            0x00000003,   /* RP */
            0x00000004,   /* R2W */
            0x00000004,   /* W2R */
            0x00000002,   /* R2P */
            0x0000000c,   /* W2P */
            0x00000003,   /* RD_RCD */
            0x00000003,   /* WR_RCD */
            0x00000002,   /* RRD */
            0x00000001,   /* REXT */
            0x00000004,   /* WDV */
            0x00000005,   /* QUSE */
            0x00000004,   /* QRST */
            0x00000009,   /* QSAFE */
            0x0000000d,   /* RDV */
            0x000004df,   /* REFRESH */
            0x00000000,   /* BURST_REFRESH_NUM */
            0x00000003,   /* PDEX2WR */
            0x00000003,   /* PDEX2RD */
            0x00000003,   /* PCHG2PDEN */
            0x00000003,   /* ACT2PDEN */
            0x00000001,   /* AR2PDEN */
            0x0000000a,   /* RW2PDEN */
            0x000000c8,   /* TXSR */
            0x00000003,   /* TCKE */
            0x00000006,   /* TFAW */
            0x00000004,   /* TRPAB */
            0x00000008,   /* TCLKSTABLE */
            0x00000002,   /* TCLKSTOP */
            0x00000000,   /* TREFBW */
            0x00000000,   /* QUSE_EXTRA */
            0x00000002,   /* FBIO_CFG6 */
            0x00000000,   /* ODT_WRITE */
            0x00000000,   /* ODT_READ */
            0x00000083,   /* FBIO_CFG5 */
            0xa06e04ae,//0xa05c04ae,   /* CFG_DIG_DLL */
            0x007fb010,   /* DLL_XFORM_DQS */
            0x00078000,   /* DLL_XFORM_QUSE */
            0x00000000,   /* ZCAL_REF_CNT */
            0x00000000,   /* ZCAL_WAIT_CNT */
            0x00000000,   /* AUTO_CAL_INTERVAL */
            0x00000000,   /* CFG_CLKTRIM_0 */
            0x00000000,   /* CFG_CLKTRIM_1 */
            0x00000000,   /* CFG_CLKTRIM_2 */
	       }
  	 },
    	{
		.rate = 300000,   /* SDRAM frequency : 1100mV emc core voltage*/
		.regs = {
            0x00000012,   /* RC */
            0x00000027,   /* RFC */
            0x0000000D,   /* RAS */
            0x00000006,   /* RP */
            0x00000007,   /* R2W */
            0x00000005,   /* W2R */
            0x00000003,   /* R2P */
            0x0000000B,   /* W2P */
            0x00000006,   /* RD_RCD */
            0x00000006,   /* WR_RCD */
            0x00000003,   /* RRD */
            0x00000003,   /* REXT */
            0x00000003,   /* WDV */
            0x00000006,   /* QUSE */
            0x00000004,   /* QRST */
            0x00000009,   /* QSAFE */
            0x0000000D,   /* RDV */
            0x000008FF,   /* REFRESH */
            0x00000000,   /* BURST_REFRESH_NUM */
            0x00000004,   /* PDEX2WR */
            0x00000004,   /* PDEX2RD */
            0x00000006,   /* PCHG2PDEN */
            0x00000006,   /* ACT2PDEN */
            0x00000001,   /* AR2PDEN */
            0x0000000F,   /* RW2PDEN */
            0x0000002A,   /* TXSR */
            0x00000003,   /* TCKE */
            0x0000000F,   /* TFAW */
            0x00000007,   /* TRPAB */
            0x00000007,   /* TCLKSTABLE */
            0x00000002,   /* TCLKSTOP */
            0x000004E0,   /* TREFBW */
            0x00000000,   /* QUSE_EXTRA */
            0x00000002,   /* FBIO_CFG6 */
            0x00000000,   /* ODT_WRITE */
            0x00000000,   /* ODT_READ */
            0x00000282,   /* FBIO_CFG5 */
            0xE03A0303,   /* CFG_DIG_DLL */
            0x007FD010,   /* DLL_XFORM_DQS */
            0x00000010,   /* DLL_XFORM_QUSE */
            0x00000000,   /* ZCAL_REF_CNT */
            0x0000001B,   /* ZCAL_WAIT_CNT */
            0x00000000,   /* AUTO_CAL_INTERVAL */
            0x00000000,   /* CFG_CLKTRIM_0 */
            0x00000000,   /* CFG_CLKTRIM_1 */
            0x00000000,   /* CFG_CLKTRIM_2 */
        }
    },
    {
		.rate = 333000,   /* SDRAM frequency : 1100mV emc core voltage*/
		.regs = {
            0x00000014,   /* RC */
            0x0000002B,   /* RFC */
            0x0000000F,   /* RAS */
            0x00000005,   /* RP */
            0x00000004,   /* R2W */
            0x00000005,   /* W2R */
            0x00000003,   /* R2P */
            0x0000000C,   /* W2P */
            0x00000005,   /* RD_RCD */
            0x00000005,   /* WR_RCD */
            0x00000003,   /* RRD */
            0x00000001,   /* REXT */
            0x00000004,   /* WDV */
            0x00000005,   /* QUSE */
            0x00000004,   /* QRST */
            0x00000009,   /* QSAFE */
            0x0000000D,   /* RDV */
            0x000009ff,   /* REFRESH */
            0x00000000,   /* BURST_REFRESH_NUM */
            0x00000003,   /* PDEX2WR */
            0x00000003,   /* PDEX2RD */
            0x00000005,   /* PCHG2PDEN */
            0x00000005,   /* ACT2PDEN */
            0x00000001,   /* AR2PDEN */
            0x0000000f,   /* RW2PDEN */
            0x000000C8,   /* TXSR */
            0x00000003,   /* TCKE */
            0x0000000C,   /* TFAW */
            0x00000006,   /* TRPAB */
            0x00000008,   /* TCLKSTABLE */
            0x00000002,   /* TCLKSTOP */
            0x00000000,   /* TREFBW */
            0x00000000,   /* QUSE_EXTRA */
            0x00000002,   /* FBIO_CFG6 */
            0x00000000,   /* ODT_WRITE */
            0x00000000,   /* ODT_READ */
            0x00000083,   /* FBIO_CFG5 */
            0xe04e048b,//0xe044048b,   /* CFG_DIG_DLL */
            0x007fa010,//0x007f9010,   /* DLL_XFORM_DQS */
            0x00028014,//0x00023014,   /* DLL_XFORM_QUSE */
            0x00000000,   /* ZCAL_REF_CNT */
            0x00000000,   /* ZCAL_WAIT_CNT */
            0x00000000,   /* AUTO_CAL_INTERVAL */
            0x00000000,   /* CFG_CLKTRIM_0 */
            0x00000000,   /* CFG_CLKTRIM_1 */
            0x00000000,   /* CFG_CLKTRIM_2 */
        }
    }, 
};

static const struct tegra_emc_chip smba_emc_chips[] = {
	{
		.description = "smba9701 memory",
		.mem_manufacturer_id = -1,
		.mem_revision_id1 = -1,
		.mem_revision_id2 = -1,
		.mem_pid = -1,
		.table = smba_emc_tables,
		.table_size = ARRAY_SIZE(smba_emc_tables),
	},
};


void __init smba_init_emc(void)
{
	tegra_init_emc(smba_emc_chips, ARRAY_SIZE(smba_emc_chips));
}
