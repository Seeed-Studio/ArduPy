#include <stdint.h>
#include "mpconfigcommon.h"
#include "mpconfigboard.h"

// fatfs configuration
#define MICROPY_PY_BUILTINS_COMPLEX (1)
#define MICROPY_HW_ENABLE_STORAGE (1)
#define MICROPY_HW_HAS_FLASH    (1)
#define FILESYSTEM_BLOCK_SIZE       (512)
#define MICROPY_FATFS_USE_LABEL        (1)
#define MICROPY_FATFS_ENABLE_LFN            (1)
#define MICROPY_FATFS_RPATH                 (2)
#define MICROPY_FATFS_LFN_CODE_PAGE         437 /* 1=SFN/ANSI 437=LFN/U.S.(OEM) */
#define MICROPY_VFS                         (1)
#define MICROPY_VFS_FAT                     (1)
#define MICROPY_READER_VFS          (MICROPY_VFS)
#define MICROPY_HW_FLASH_FS_LABEL "ardupy"
 
#define mp_type_fileio                      mp_type_vfs_fat_fileio
#define mp_type_textio                      mp_type_vfs_fat_textio

// use vfs's functions for import stat and builtin open
#define mp_import_stat mp_vfs_import_stat
#define mp_builtin_open mp_vfs_open
#define mp_builtin_open_obj mp_vfs_open_obj

#define MICROPY_MAKE_POINTER_CALLABLE(p) ((void*)((mp_uint_t)(p) | 1))
 
#define UINT_FMT "%lu"
#define INT_FMT "%ld"


#define mp_hal_pin_obj_t uint32_t

typedef int32_t mp_int_t; // must be pointer size
typedef uint32_t mp_uint_t; // must be pointer size
typedef long mp_off_t;
typedef uint32_t sys_prot_t; // for modlwip
// ssize_t, off_t as required by POSIX-signatured functions in stream.h
#include <sys/types.h> 


#if MICROPY_PY_THREAD 
#define MICROPY_EVENT_POLL_HOOK \
    do { \
        extern void mp_handle_pending(void); \
        mp_handle_pending(); \
        if (pyb_thread_enabled) { \
            MP_THREAD_GIL_EXIT(); \
            pyb_thread_yield(); \
            MP_THREAD_GIL_ENTER(); \
        } else { \
            __WFI(); \
        } \
    } while (0);

#define MICROPY_THREAD_YIELD() pyb_thread_yield()
#else
#define MICROPY_EVENT_POLL_HOOK \
    do { \
        extern void mp_handle_pending(void); \
        mp_handle_pending(); \
        __WFI(); \
    } while (0);

#define MICROPY_THREAD_YIELD()
#endif 

extern const struct _mp_obj_module_t ardupy_module;
extern const struct _mp_obj_module_t mp_module_uos;
extern const struct _mp_obj_module_t mp_module_utime;
extern const struct _mp_obj_module_t math_module;
extern const struct _mp_obj_module_t random_module;
extern const struct _mp_obj_module_t uheap_module;
extern const struct _mp_obj_module_t ustack_module;

#ifdef ARDUPY_MODULE
extern const struct _mp_obj_module_t mp_module_arduino;
#endif
// extern const struct _mp_obj_module_t supervisor_module;


// dummy print
#define MP_PLAT_PRINT_STRN(str, len) mp_hal_stdout_tx_strn_cooked(str, len)


#if MICROPY_PY_URE
#define RE_MODULE { MP_ROM_QSTR(MP_QSTR_re), MP_ROM_PTR(&mp_module_ure) },
#else
#define RE_MODULE
#endif

// These modules are not yet in shared-bindings, but we prefer the non-uxxx names.
#if MICROPY_PY_UERRNO
#define ERRNO_MODULE           { MP_ROM_QSTR(MP_QSTR_errno), MP_ROM_PTR(&mp_module_uerrno) },
#else
#define ERRNO_MODULE
#endif

#if MICROPY_PY_UJSON
#define JSON_MODULE            { MP_ROM_QSTR(MP_QSTR_json), MP_ROM_PTR(&mp_module_ujson) },
#else 
#define JSON_MODULE
#endif

#ifdef ARDUPY_MODULE
#define ARDUPY_PY_MODULE  { MP_OBJ_NEW_QSTR(MP_QSTR_arduino), (mp_obj_t)&mp_module_arduino },                   
#else
#define ARDUPY_PY_MODULE
#endif


// extra built in names to add to the global namespace
#define MICROPY_PORT_BUILTINS                                            \
    { MP_OBJ_NEW_QSTR(MP_QSTR_open), MP_ROM_PTR(&mp_builtin_open_obj) }, \
    { MP_OBJ_NEW_QSTR(MP_QSTR_help), (mp_obj_t)&mp_builtin_help_obj },   \
    { MP_OBJ_NEW_QSTR(MP_QSTR_input), (mp_obj_t)&mp_builtin_input_obj }, \

    // { MP_OBJ_NEW_QSTR(MP_QSTR_uhashlib), (mp_obj_t)&mp_module_uhashlib }, 


#define EXTRA_BUILTIN_MODULES                                                        \
    { MP_OBJ_NEW_QSTR(MP_QSTR_math), (mp_obj_t)&math_module },                       \
    { MP_OBJ_NEW_QSTR(MP_QSTR_random), (mp_obj_t)&random_module },                   \
    { MP_OBJ_NEW_QSTR(MP_QSTR_binascii), (mp_obj_t)&mp_module_ubinascii },           \
    { MP_OBJ_NEW_QSTR(MP_QSTR_collections), (mp_obj_t)&mp_module_collections },      \
    { MP_OBJ_NEW_QSTR(MP_QSTR_hashlib), (mp_obj_t)&mp_module_uhashlib },             \
    { MP_OBJ_NEW_QSTR(MP_QSTR_heapq), (mp_obj_t)&mp_module_uheapq },                 \
    { MP_OBJ_NEW_QSTR(MP_QSTR_io), (mp_obj_t)&mp_module_io },                        \
    { MP_OBJ_NEW_QSTR(MP_QSTR_select), (mp_obj_t)&mp_module_uselect },               \
    { MP_OBJ_NEW_QSTR(MP_QSTR_zlib), (mp_obj_t)&mp_module_uzlib },                   \
     { MP_OBJ_NEW_QSTR(MP_QSTR_machine), (mp_obj_t)&mp_module_machine },             \
    JSON_MODULE                                                                      \
    ERRNO_MODULE                                                                     \
    RE_MODULE                                                                        \
    ARDUPY_PY_MODULE                                                                 \

    


#define MICROPY_PORT_BUILTIN_MODULES                              \
    { MP_ROM_QSTR(MP_QSTR_ardupy), MP_ROM_PTR(&ardupy_module) },  \
    { MP_ROM_QSTR(MP_QSTR_os), MP_ROM_PTR(&mp_module_uos) },      \
    { MP_ROM_QSTR(MP_QSTR_time), MP_ROM_PTR(&mp_module_utime) },  \
    { MP_ROM_QSTR(MP_QSTR_array), MP_ROM_PTR(&mp_module_array) }, \
    EXTRA_BUILTIN_MODULES                                         \
    

#define MICROPY_PORT_BUILTIN_MODULE_WEAK_LINKS \



#define MICROPY_PORT_CONSTANTS  \
    { MP_ROM_QSTR(MP_QSTR_ardupy), MP_ROM_PTR(&ardupy_module) }, 

#define MICROPY_PORT_ROOT_POINTERS \
    const char *readline_hist[8]; \
    mp_obj_t shared_uart_bus; \
    mp_obj_t shared_i2c_bus; \
    mp_obj_t shared_spi_bus; \



// We need to provide a declaration/definition of alloca()
#include <alloca.h>  

