/* Copyright (c) 2012-2013, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef __BMS_BATTERYDATA_H
#define __BMS_BATTERYDATA_H

#include <linux/errno.h>

#define FCC_CC_COLS		5
#define FCC_TEMP_COLS		8

#if defined(CONFIG_MACH_MSM8226_E9WIFI) || defined(CONFIG_MACH_MSM8226_E9WIFIN) || \
    defined(CONFIG_MACH_MSM8226_E7WIFI) || defined(CONFIG_MACH_MSM8226_E8WIFI) || \
    defined(CONFIG_MACH_MSM8926_E8LTE) || defined (CONFIG_MACH_MSM8926_E8LTE_KR) || defined(CONFIG_MACH_MSM8926_E7LTE_ATT_US) || \
    defined(CONFIG_MACH_MSM8926_E7LTE_VZW_US) || defined (CONFIG_MACH_MSM8926_E7LTE_USC_US)
#define PC_CC_ROWS             30
#define PC_CC_COLS             13

#define PC_TEMP_ROWS		31
#define PC_TEMP_COLS		8
#else
#define PC_CC_ROWS             31
#define PC_CC_COLS             13

#define PC_TEMP_ROWS		31
#define PC_TEMP_COLS		8
#endif

#define MAX_SINGLE_LUT_COLS	20

#define MAX_BATT_ID_NUM		4

struct single_row_lut {
	int x[MAX_SINGLE_LUT_COLS];
	int y[MAX_SINGLE_LUT_COLS];
	int cols;
};

/**
 * struct sf_lut -
 * @rows:	number of percent charge entries should be <= PC_CC_ROWS
 * @cols:	number of charge cycle entries should be <= PC_CC_COLS
 * @row_entries:	the charge cycles/temperature at which sf data
 *			is available in the table.
 *		The charge cycles must be in increasing order from 0 to rows.
 * @percent:	the percent charge at which sf data is available in the table
 *		The  percentcharge must be in decreasing order from 0 to cols.
 * @sf:		the scaling factor data
 */
struct sf_lut {
	int rows;
	int cols;
	int row_entries[PC_CC_COLS];
	int percent[PC_CC_ROWS];
	int sf[PC_CC_ROWS][PC_CC_COLS];
};

/**
 * struct pc_temp_ocv_lut -
 * @rows:	number of percent charge entries should be <= PC_TEMP_ROWS
 * @cols:	number of temperature entries should be <= PC_TEMP_COLS
 * @temp:	the temperatures at which ocv data is available in the table
 *		The temperatures must be in increasing order from 0 to rows.
 * @percent:	the percent charge at which ocv data is available in the table
 *		The  percentcharge must be in decreasing order from 0 to cols.
 * @ocv:	the open circuit voltage
 */
struct pc_temp_ocv_lut {
	int rows;
	int cols;
	int temp[PC_TEMP_COLS];
	int percent[PC_TEMP_ROWS];
	int ocv[PC_TEMP_ROWS][PC_TEMP_COLS];
};

struct batt_ids {
	int kohm[MAX_BATT_ID_NUM];
	int num;
};

enum battery_type {
	BATT_UNKNOWN = 0,
	BATT_PALLADIUM,
	BATT_DESAY,
	BATT_OEM,
	BATT_QRD_4V35_2000MAH,
	BATT_QRD_4V2_1300MAH,
#ifdef CONFIG_LGE_PM
	BATT_4600_LGE
#endif
};

/**
 * struct bms_battery_data -
 * @fcc:		full charge capacity (mAmpHour)
 * @fcc_temp_lut:	table to get fcc at a given temp
 * @pc_temp_ocv_lut:	table to get percent charge given batt temp and cycles
 * @pc_sf_lut:		table to get percent charge scaling factor given cycles
 *			and percent charge
 * @rbatt_sf_lut:	table to get battery resistance scaling factor given
 *			temperature and percent charge
 * @default_rbatt_mohm:	the default value of battery resistance to use when
 *			readings from bms are not available.
 * @delta_rbatt_mohm:	the resistance to be added towards lower soc to
 *			compensate for battery capacitance.
 * @rbatt_capacitve_mohm: the resistance to be added to compensate for
 *				battery capacitance
 * @flat_ocv_threshold_uv: the voltage where the battery's discharge curve
 *				starts flattening out.
 * @max_voltage_uv:	max voltage of the battery
 * @cutoff_uv:		cutoff voltage of the battery
 * @iterm_ua:		termination current of the battery when charging
 *			to 100%
 * @batt_id_kohm:	the best matched battery id resistor value
 */

struct bms_battery_data {
	unsigned int		fcc;
	struct single_row_lut	*fcc_temp_lut;
	struct single_row_lut	*fcc_sf_lut;
	struct pc_temp_ocv_lut	*pc_temp_ocv_lut;
	struct sf_lut		*pc_sf_lut;
	struct sf_lut		*rbatt_sf_lut;
	int			default_rbatt_mohm;
	int			delta_rbatt_mohm;
	int			rbatt_capacitive_mohm;
	int			flat_ocv_threshold_uv;
	int			max_voltage_uv;
	int			cutoff_uv;
	int			iterm_ua;
	int			batt_id_kohm;
};

#if defined(CONFIG_PM8921_BMS) || \
	defined(CONFIG_PM8921_BMS_MODULE) || \
	defined(CONFIG_QPNP_BMS)

#if defined(CONFIG_LGE_PM_BATTERY_CAPACITY_2100mAh) && defined(CONFIG_MACH_MSM8X10_W5C_VZW)
#define CONFIG_LGE_PM_BATTERY_HITACI_2100mAh
#endif

#ifdef CONFIG_LGE_PM_BATTERY_PROFILE_DATA

#ifdef CONFIG_LGE_PM_BATTERY_CAPACITY_1540mAh
extern struct bms_battery_data LGC_BL44JR_1540_data;
#elif defined(CONFIG_LGE_PM_BATTERY_CAPACITY_1700mAh)
#ifdef CONFIG_MACH_MSM8926_VFP_KR
extern struct bms_battery_data LGE_BL_44JH_1700mAh_LG_Chem_data;
#else
extern struct bms_battery_data LGC_BL44JH_1700_data;
extern struct bms_battery_data LG_LGC_BL44JH_1700_data;
extern struct bms_battery_data LG_TOCAD_BL44JH_1700_data;
#endif
#elif defined(CONFIG_LGE_PM_BATTERY_CAPACITY_1900mAh)
extern struct bms_battery_data LGE_L70_TOCAD_1900mAh_data;
extern struct bms_battery_data LGE_L70_CHEM_1900mAh_data;
#elif defined(CONFIG_LGE_PM_BATTERY_CAPACITY_2440mAh)
extern struct bms_battery_data LGE_BL_59UH_2440mAh_LG_Chem_data;
extern struct bms_battery_data LGE_BL_59UH_2440mAh_TOCAD_data;
#elif defined(CONFIG_LGE_PM_BATTERY_CAPACITY_2540mAh)
extern struct bms_battery_data LGE_BL_54SH_2540mAh_LG_Chem_data;
extern struct bms_battery_data LGE_BL_54SH_2540mAh_LG_Sanyo_data;
#elif defined(CONFIG_LGE_PM_BATTERY_CAPACITY_3000mAh)
extern struct bms_battery_data LGE_BL_64SH_3000mAh_LG_Chem_data;
extern struct bms_battery_data LGE_BL_64SH_3000mAh_Technohill_data;
#elif defined(CONFIG_LGE_PM_BATTERY_CAPACITY_2100mAh)
extern struct bms_battery_data LGE_LGC_2040mAH_data;
extern struct bms_battery_data LGE_Tocad_2040mAh_data;
extern struct bms_battery_data LGE_BL41A1H_1527783_2100mAh_BMS_data;
#if defined(CONFIG_LGE_PM_BATTERY_HITACI_2100mAh)
extern struct bms_battery_data LGE_Hitaci_2040mAh_data;
#endif
#elif defined(CONFIG_LGE_PM_BATTERY_CAPACITY_3200mAh)
extern struct bms_battery_data LGE_BL_47TH_3200mAh_LG_Chem_data;
extern struct bms_battery_data LGE_BL_47TH_3200mAh_Tocad_data;
#elif defined(CONFIG_LGE_PM_BATTERY_CAPACITY_4000mAh)
extern struct bms_battery_data LGE_BL_T12_4000mAh_TOCAD_data;
extern struct bms_battery_data LGE_BL_T12_4000mAh_LG_Chem_data;
#elif defined(CONFIG_LGE_PM_BATTERY_CAPACITY_4200mAh)
extern struct bms_battery_data LGE_LGC_4200mAh_data;
#elif defined(CONFIG_LGE_PM_BATTERY_CAPACITY_4600mAh)
extern struct bms_battery_data LGE_LGC_4600mAH_data;
#elif defined(CONFIG_LGE_PM_BATTERY_CAPACITY_8000mAh)
extern struct bms_battery_data LGE_BL_T13_8000mAh_TOCAD_data;
extern struct bms_battery_data LGE_BL_T13_8000mAh_LG_Chem_data;
#else
extern struct bms_battery_data LGE_BL_54SH_2540mAh_LG_Chem_data;
#endif

#else
extern struct bms_battery_data  palladium_1500_data;
extern struct bms_battery_data  desay_5200_data;
extern struct bms_battery_data  oem_batt_data;
extern struct bms_battery_data QRD_4v35_2000mAh_data;
extern struct bms_battery_data  qrd_4v2_1300mah_data;
#endif

int interpolate_fcc(struct single_row_lut *fcc_temp_lut, int batt_temp);
int interpolate_scalingfactor(struct sf_lut *sf_lut, int row_entry, int pc);
int interpolate_scalingfactor_fcc(struct single_row_lut *fcc_sf_lut,
				int cycles);
int interpolate_pc(struct pc_temp_ocv_lut *pc_temp_ocv,
				int batt_temp_degc, int ocv);
int interpolate_ocv(struct pc_temp_ocv_lut *pc_temp_ocv,
				int batt_temp_degc, int pc);
int linear_interpolate(int y0, int x0, int y1, int x1, int x);
int is_between(int left, int right, int value);
#else
static inline int interpolate_fcc(struct single_row_lut *fcc_temp_lut,
			int batt_temp)
{
	return -EINVAL;
}
static inline int interpolate_scalingfactor(struct sf_lut *sf_lut,
			int row_entry, int pc)
{
	return -EINVAL;
}
static inline int interpolate_scalingfactor_fcc(
			struct single_row_lut *fcc_sf_lut, int cycles)
{
	return -EINVAL;
}
static inline int interpolate_pc(struct pc_temp_ocv_lut *pc_temp_ocv,
			int batt_temp_degc, int ocv)
{
	return -EINVAL;
}
static inline int interpolate_ocv(struct pc_temp_ocv_lut *pc_temp_ocv,
			int batt_temp_degc, int pc)
{
	return -EINVAL;
}
static inline int linear_interpolate(int y0, int x0, int y1, int x1, int x)
{
	return -EINVAL;
}
static inline int is_between(int left, int right, int value)
{
	return -EINVAL;
}
#endif

#endif
