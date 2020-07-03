/**
 * The MIT License (MIT)
 *
 * Author: Baozhu Zuo (baozhu.zuo@gmail.com)
 *
 * Copyright (C) 2019  Seeed Technology Co.,Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stdint.h>
#include <string.h>

#include "lib/oofatfs/ff.h"
#include "extmod/vfs.h"
#include "extmod/vfs_fat.h"
#include "py/runtime.h"
#include "mpconfigport.h"
#include "ardupy_storage.h"
#include "mphalport.h"
#if MICROPY_HW_ENABLE_STORAGE

// static int32_t intenal_free_start_addr;
// static int32_t block_count;

static int32_t convert_block_to_flash_addr(uint32_t block)
{
    if (0 <= block && block < INTERNAL_FLASH_PART1_NUM_BLOCKS)
    {
        // a block in partition 1
        return INTERNAL_FLASH_MEM_SEG1_START_ADDR + block * FILESYSTEM_BLOCK_SIZE;
    }
    // bad block
    return -1;
}

uint32_t storage_get_block_size(void) { return FILESYSTEM_BLOCK_SIZE; }

uint32_t storage_get_block_count(void)
{
    return INTERNAL_FLASH_PART1_NUM_BLOCKS;
}

bool storage_read_block(uint8_t *dest, uint32_t block)
{
    // non-MBR block, get data from flash memory
    int32_t src = convert_block_to_flash_addr(block);
    if (src == -1)
    {
        // bad block number
        return false;
    }
    int32_t error_code = board_flash_read(src, dest, FILESYSTEM_BLOCK_SIZE);
    return error_code == 0;
}

bool storage_write_block(const uint8_t *src, uint32_t block)
{
    // non-MBR block, copy to cache
    int32_t dest = convert_block_to_flash_addr(block);
    if (dest == -1)
    {
        // bad block number
        return false;
    }
    int32_t error_code = board_flash_write(dest, src, FILESYSTEM_BLOCK_SIZE);
    return error_code == 0;
}

mp_uint_t storage_read_blocks(uint8_t *dest, uint32_t block_num, uint32_t num_blocks)
{

    for (size_t i = 0; i < num_blocks; i++)
    {
        if (!storage_read_block(dest + i * FILESYSTEM_BLOCK_SIZE, block_num + i))
        {
            return 1; // error
        }
    }
    return 0; // success
}

mp_uint_t storage_write_blocks(const uint8_t *src, uint32_t block_num, uint32_t num_blocks)
{

    for (size_t i = 0; i < num_blocks; i++)
    {
        if (!storage_write_block(src + i * FILESYSTEM_BLOCK_SIZE, block_num + i))
        {
            return 1; // error
        }
    }

    return 0; // success
}
void storage_init(void)
{
    board_flash_init();
}
void storage_flush(void)
{
    board_flash_flush();
}

/******************************************************************************/
// MicroPython bindings
//
// Expose the flash as an object with the block protocol.

// there is a singleton Flash object
STATIC const mp_obj_base_t ardupy_flash_obj = {&ardupy_flash_type};

STATIC mp_obj_t ardupy_flash_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args)
{
    // check arguments
    mp_arg_check_num(n_args, n_kw, 0, 0, false);

    // return singleton object
    return MP_OBJ_FROM_PTR(&ardupy_flash_obj);
}

STATIC mp_obj_t ardupy_flash_readblocks(mp_obj_t self, mp_obj_t block_num, mp_obj_t buf)
{
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(buf, &bufinfo, MP_BUFFER_WRITE);
    mp_uint_t ret = storage_read_blocks(bufinfo.buf, mp_obj_get_int(block_num), bufinfo.len / FLASH_BLOCK_SIZE);
    return MP_OBJ_NEW_SMALL_INT(ret);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_3(ardupy_flash_readblocks_obj, ardupy_flash_readblocks);

STATIC mp_obj_t ardupy_flash_writeblocks(mp_obj_t self, mp_obj_t block_num, mp_obj_t buf)
{
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(buf, &bufinfo, MP_BUFFER_READ);
    mp_uint_t ret = storage_write_blocks(bufinfo.buf, mp_obj_get_int(block_num), bufinfo.len / FLASH_BLOCK_SIZE);
    return MP_OBJ_NEW_SMALL_INT(ret);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_3(ardupy_flash_writeblocks_obj, ardupy_flash_writeblocks);

STATIC mp_obj_t ardupy_flash_ioctl(mp_obj_t self, mp_obj_t cmd_in, mp_obj_t arg_in)
{
    mp_int_t cmd = mp_obj_get_int(cmd_in);
    switch (cmd)
    {
    case BP_IOCTL_INIT:
        storage_init();
        return MP_OBJ_NEW_SMALL_INT(0);
    case BP_IOCTL_DEINIT:
        storage_flush();
        return MP_OBJ_NEW_SMALL_INT(0); // TODO properly
    case BP_IOCTL_SYNC:
        storage_flush();
        return MP_OBJ_NEW_SMALL_INT(0);
    case BP_IOCTL_SEC_COUNT:
        return MP_OBJ_NEW_SMALL_INT(storage_get_block_count());
    case BP_IOCTL_SEC_SIZE:
        return MP_OBJ_NEW_SMALL_INT(storage_get_block_size());
    default:
        return mp_const_none;
    }
}
STATIC MP_DEFINE_CONST_FUN_OBJ_3(ardupy_flash_ioctl_obj, ardupy_flash_ioctl);

STATIC const mp_rom_map_elem_t ardupy_flash_locals_dict_table[] = {
    {MP_ROM_QSTR(MP_QSTR_readblocks), MP_ROM_PTR(&ardupy_flash_readblocks_obj)},
    {MP_ROM_QSTR(MP_QSTR_writeblocks), MP_ROM_PTR(&ardupy_flash_writeblocks_obj)},
    {MP_ROM_QSTR(MP_QSTR_ioctl), MP_ROM_PTR(&ardupy_flash_ioctl_obj)},
};

STATIC MP_DEFINE_CONST_DICT(ardupy_flash_locals_dict, ardupy_flash_locals_dict_table);

const mp_obj_type_t ardupy_flash_type = {
    {&mp_type_type},
    .name = MP_QSTR_Flash,
    .make_new = ardupy_flash_make_new,
    .locals_dict = (mp_obj_dict_t *)&ardupy_flash_locals_dict,
};

void ardupy_flash_init_vfs(fs_user_mount_t *vfs)
{
    vfs->base.type = &mp_fat_vfs_type;
    vfs->flags |= FSUSER_NATIVE | FSUSER_HAVE_IOCTL;
    vfs->fatfs.drv = vfs;
    vfs->readblocks[0] = MP_OBJ_FROM_PTR(&ardupy_flash_readblocks_obj);
    vfs->readblocks[1] = MP_OBJ_FROM_PTR(&ardupy_flash_obj);
    vfs->readblocks[2] = MP_OBJ_FROM_PTR(storage_read_blocks); // native version
    vfs->writeblocks[0] = MP_OBJ_FROM_PTR(&ardupy_flash_writeblocks_obj);
    vfs->writeblocks[1] = MP_OBJ_FROM_PTR(&ardupy_flash_obj);
    vfs->writeblocks[2] = MP_OBJ_FROM_PTR(storage_write_blocks); // native version
    vfs->u.ioctl[0] = MP_OBJ_FROM_PTR(&ardupy_flash_ioctl_obj);
    vfs->u.ioctl[1] = MP_OBJ_FROM_PTR(&ardupy_flash_obj);
}

static void make_empty_file(FATFS *fatfs, const char *path)
{
    FIL fp;
    f_open(fatfs, &fp, path, FA_WRITE | FA_CREATE_ALWAYS);
    f_close(&fp);
}

#include "py/gc.h"

static fs_user_mount_t static_vfs_fat;
void protect_main_py()
{
    FIL fp;
    fs_user_mount_t *vfs_fat = &static_vfs_fat;
    f_open(&vfs_fat->fatfs, &fp, "main.py", FA_READ);
    f_close(&fp);
}
// avoid inlining to avoid stack usage within main()
MP_NOINLINE bool init_flash_fs()
{
    // init the vfs object
    fs_user_mount_t *vfs_fat = &static_vfs_fat;
    memset(vfs_fat, 0, sizeof(fs_user_mount_t));

    vfs_fat->flags = FSUSER_FREE_OBJ;
    storage_init();
    ardupy_flash_init_vfs(vfs_fat);

    // try to mount the flash
    FRESULT res = f_mount(&vfs_fat->fatfs);
    
    if (res == FR_NO_FILESYSTEM)
    {
        // HINT: DON'T USE THE STACK BUFFER, IS MAYBE RESULT STACK OVERFLOW.
        // no filesystem, or asked to reset it, so create a fresh one
        uint8_t *working_buf = m_new(uint8_t, FF_MAX_SS);
        res = f_mkfs(&vfs_fat->fatfs, FM_FAT | FM_SFD, 0, working_buf, FF_MAX_SS);
        if (res != FR_OK)
        {
            printf("MPY: can't create flash filesystem\n");
            return false;
        }

        // set label
        res = f_setlabel(&vfs_fat->fatfs, MICROPY_HW_FLASH_FS_LABEL);
        if (res != FR_OK)
        {
            printf("MPY: can't set flash filesystem label\n");
            return false;
        }

        make_empty_file(&vfs_fat->fatfs, "main.py");
    }
    else if (res == FR_OK)
    {
        // mount sucessful
    }
    else
    {
    fail:
        printf("MPY: can't mount flash\n");
        return false;
    }

    // mount the flash device (there should be no other devices mounted at this point)
    // we allocate this structure on the heap because vfs->next is a root pointer
    mp_vfs_mount_t *vfs = m_new_obj_maybe(mp_vfs_mount_t);
    if (vfs == NULL)
    {
        goto fail;
    }
    vfs->str = "/";
    vfs->len = 1;
    vfs->obj = MP_OBJ_FROM_PTR(vfs_fat);
    vfs->next = NULL;
    MP_STATE_VM(vfs_mount_table) = vfs;

    // The current directory is used as the boot up directory.
    // It is set to the internal flash filesystem by default.
    MP_STATE_PORT(vfs_cur) = vfs;
    return true;
}

#endif //MICROPY_HW_ENABLE_STORAGE
