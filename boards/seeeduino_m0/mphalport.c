#include "mphalport.h"
#include "py/runtime.h"
#include "lib/oofatfs/ff.h"

const char grove_help_text[] = "Welcome to MicroPython!\n"
                                "For online help please visit http://micropython.org/help/.\n"
                                "  _____                    _    _____ _             _ _       \n"
                                " / ____|                  | |  / ____| |           | (_)      \n"
                                "| (___   ___  ___  ___  __| | | (___ | |_ _   _  __| |_  ___  \n"
                                " \\___ \\ / _ \\/ _ \\/ _ \\/ _` |  \\___ \\| __| | | |/ _` | |/ _ \\ \n"
                                " ____) |  __/  __/  __/ (_| |  ____) | |_| |_| | (_| | | (_) |\n"
                                "|_____/ \\___|\\___|\\___|\\__,_| |_____/ \\__|\\__,_|\\__,_|_|\\___/ \n"                              
                                "For further help on a specific object, type help(obj)\n";

#if 0
mp_lexer_t *mp_lexer_new_from_file(const char *filename) {
    mp_raise_OSError(MP_ENOENT);
}
#endif

mp_import_stat_t mp_import_stat(const char *path) {
    return MP_IMPORT_STAT_NO_EXIST;
}

mp_obj_t mp_builtin_open(size_t n_args, const mp_obj_t *args, mp_map_t *kwargs) {
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_KW(mp_builtin_open_obj, 1, mp_builtin_open);

uint32_t mp_hal_ticks_ms(void) {
    return micros();
}

void mp_hal_init(){
    mp_init();
    mp_obj_list_init(MP_OBJ_TO_PTR(mp_sys_path), 0);
    mp_obj_list_append(mp_sys_path, MP_OBJ_NEW_QSTR(MP_QSTR_)); // current dir (or base dir of the script)
    mp_obj_list_init(MP_OBJ_TO_PTR(mp_sys_argv), 0);
    readline_init0();
}

static inline uint32_t flash_read_unaligned_uint32(const void *data)
{
  union {
    uint32_t u32;
    uint8_t u8[4];
  } res;
  const uint8_t *d = (const uint8_t *)data;
  res.u8[0] = d[0];
  res.u8[1] = d[1];
  res.u8[2] = d[2];
  res.u8[3] = d[3];
  return res.u32;
}

static inline uint32_t flash_get_page_size(){
    const uint32_t pageSizes[] = { 8, 16, 32, 64, 128, 256, 512, 1024 };
    return pageSizes[NVMCTRL->PARAM.bit.PSZ];
}

void flash_write(const volatile void *flash_ptr, const void *data, uint32_t size){
  // Calculate data boundaries
  size = (size + 3) / 4;
  volatile uint32_t *dst_addr = (volatile uint32_t *)flash_ptr;
  const uint8_t *src_addr = (uint8_t *)data;

  // Disable automatic page write
  NVMCTRL->CTRLB.bit.MANW = 1;

  // Do writes in pages
  while (size) {
    // Execute "PBC" Page Buffer Clear
    NVMCTRL->CTRLA.reg = NVMCTRL_CTRLA_CMDEX_KEY | NVMCTRL_CTRLA_CMD_PBC;
    while (NVMCTRL->INTFLAG.bit.READY == 0) { }

    // Fill page buffer
    uint32_t i;
    for (i=0; i<(flash_get_page_size()/4) && size; i++) {
      *dst_addr = flash_read_unaligned_uint32(src_addr);
      src_addr += 4;
      dst_addr++;
      size--;
    }

    // Execute "WP" Write Page
    NVMCTRL->CTRLA.reg = NVMCTRL_CTRLA_CMDEX_KEY | NVMCTRL_CTRLA_CMD_WP;
    while (NVMCTRL->INTFLAG.bit.READY == 0) { }
  }
}
static void flash_erase_wait(const volatile void *flash_ptr){
  NVMCTRL->ADDR.reg = ((uint32_t)flash_ptr) / 2;
  NVMCTRL->CTRLA.reg = NVMCTRL_CTRLA_CMDEX_KEY | NVMCTRL_CTRLA_CMD_ER;
  while (!NVMCTRL->INTFLAG.bit.READY) { }
}

void flash_erase(const volatile void *flash_ptr, uint32_t size){
  const uint8_t *ptr = (const uint8_t *)flash_ptr;
  const uint32_t ROW_SIZE = flash_get_page_size() * 4;
  while (size > ROW_SIZE) {
    flash_erase_wait(ptr);
    ptr += ROW_SIZE;
    size -= ROW_SIZE;
  }
  flash_erase_wait(ptr);
}

void flash_read(const volatile void *flash_ptr, void *data, uint32_t size){
    memcpy(data, (const void *)flash_ptr, size);
}


uint32_t get_free_workspace(){

}
DWORD get_fattime(void) {
	// TODO: Implement this function. For now, fake it.
    return ((2016 - 1980) << 25) | ((12) << 21) | ((4) << 16) | ((00) << 11) | ((18) << 5) | (23 / 2);
}


