/*
 * Copyright (C) 2017 MediaTek Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See http://www.gnu.org/licenses/gpl-2.0.html for more details.
 */

#ifndef __IMGSENSOR_I2C_H__
#define __IMGSENSOR_I2C_H__

#include <linux/i2c.h>
#include <linux/mutex.h>

#include "i2c-mtk.h"

#include "imgsensor_custom.h"
#include "imgsensor_common.h"

#define IMGSENSOR_I2C_MSG_SIZE_READ      2
#define IMGSENSOR_I2C_BURST_WRITE_LENGTH MAX_DMA_TRANS_SIZE
#define IMGSENSOR_I2C_CMD_LENGTH_MAX     255

#define IMGSENSOR_I2C_BUFF_MODE_DEV      IMGSENSOR_I2C_DEV_2

#ifdef IMGSENSOR_I2C_1000K
#define IMGSENSOR_I2C_SPEED              1000000
#else
#define IMGSENSOR_I2C_SPEED              400000
#endif

struct IMGSENSOR_I2C_STATUS {
	u8 reserved:7;
	u8 is_buff_mode:1;
};

struct IMGSENSOR_I2C_INST {
	struct i2c_client   *pi2c_client;
	struct i2c_msg       msg[IMGSENSOR_I2C_CMD_LENGTH_MAX];
};

struct IMGSENSOR_I2C_CFG {
    struct IMGSENSOR_I2C_INST *pinst;
	struct i2c_driver         *pi2c_driver;
	struct mutex               i2c_mutex;
};

struct IMGSENSOR_I2C {
	struct IMGSENSOR_I2C_INST inst[IMGSENSOR_I2C_DEV_MAX_NUM];
};

enum IMGSENSOR_RETURN imgsensor_i2c_init(
	struct IMGSENSOR_I2C_CFG *pi2c_cfg,
	enum IMGSENSOR_I2C_DEV device);
enum IMGSENSOR_RETURN imgsensor_i2c_delete(struct IMGSENSOR_I2C_CFG *pi2c_cfg);
int imgsensor_i2c_buffer_mode(int enable);
int imgsensor_i2c_read(
	struct IMGSENSOR_I2C_CFG *pi2c_cfg,
	u8 *pwrite_data,
	u16 write_length,
	u8 *pread_data,
	u16 read_length,
	u16 id,
	int speed);
int imgsensor_i2c_write(
	struct IMGSENSOR_I2C_CFG *pi2c_cfg,
	u8 *pwrite_data,
	u16 write_length,
	u16 write_per_cycle,
	u16 id,
	int speed);

#ifdef IMGSENSOR_LEGACY_COMPAT
void imgsensor_i2c_set_device(struct IMGSENSOR_I2C_CFG *pi2c_cfg);
#endif

#endif
