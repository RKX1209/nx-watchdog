/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2016        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include <string.h>
#include "diskio.h"		/* FatFs lower layer API */
#include "sdmmc.h"

extern sdmmc_storage_t sd_storage;

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	return 0;
}

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	return 0;
}

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	if ((u32)buff >= 0x90000000)
		return sdmmc_storage_read(&sd_storage, sector, count, buff) ? RES_OK : RES_ERROR;
	u8 *buf = (u8 *)0x98000000; //TODO: define this somewhere.
	if (sdmmc_storage_read(&sd_storage, sector, count, buf))
	{
		memcpy(buff, buf, 512 * count);
		return RES_OK;
	}
	return RES_ERROR;
}

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	if ((u32)buff >= 0x90000000)
		return sdmmc_storage_write(&sd_storage, sector, count, (void *)buff) ? RES_OK : RES_ERROR;
	u8 *buf = (u8 *)0x98000000; //TODO: define this somewhere.
	memcpy(buf, buff, 512 * count);
	if (sdmmc_storage_write(&sd_storage, sector, count, buf))
		return RES_OK;
	return RES_ERROR;
}

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	return RES_OK;
}
