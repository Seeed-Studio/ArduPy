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

DWORD get_fattime(void) {
	// TODO: Implement this function. For now, fake it.
    return ((2016 - 1980) << 25) | ((12) << 21) | ((4) << 16) | ((00) << 11) | ((18) << 5) | (23 / 2);
}
