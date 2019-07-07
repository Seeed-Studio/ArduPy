#include "py/mpconfig.h"
#include "py/objint.h"
#include "py/objstr.h"
#include "py/emitglue.h"

#if MICROPY_OPT_CACHE_MAP_LOOKUP_IN_BYTECODE != 0
#error "incompatible MICROPY_OPT_CACHE_MAP_LOOKUP_IN_BYTECODE"
#endif

#if MICROPY_LONGINT_IMPL != 0
#error "incompatible MICROPY_LONGINT_IMPL"
#endif

#if MICROPY_PY_BUILTINS_FLOAT
typedef struct _mp_obj_float_t {
    mp_obj_base_t base;
    mp_float_t value;
} mp_obj_float_t;
#endif

#if MICROPY_PY_BUILTINS_COMPLEX
typedef struct _mp_obj_complex_t {
    mp_obj_base_t base;
    mp_float_t real;
    mp_float_t imag;
} mp_obj_complex_t;
#endif

enum {
    MP_QSTR_uPy = MP_QSTRnumber_of,
    MP_QSTR_i,
    MP_QSTR__slash_home_slash_baozhu_slash_workspace_slash_GroveForMCU_slash_arduino_slash_mpy_slash_modules_slash_frozentest_dot_py,
};

extern const qstr_pool_t mp_qstr_const_pool;
const qstr_pool_t mp_qstr_frozen_const_pool = {
    (qstr_pool_t*)&mp_qstr_const_pool, // previous pool
    MP_QSTRnumber_of, // previous pool size
    3, // allocated entries
    3, // used entries
    {
        (const byte*)"\xf9\x03" "uPy",
        (const byte*)"\xcc\x01" "i",
        (const byte*)"\xd1\x44" "/home/baozhu/workspace/GroveForMCU/arduino/mpy/modules/frozentest.py",
    },
};

// frozen bytecode for file /home/baozhu/workspace/GroveForMCU/arduino/mpy/modules/frozentest.py, scope _home_baozhu_workspace_GroveForMCU_arduino_mpy_modules_frozentest_<module>
STATIC const byte fun_data__home_baozhu_workspace_GroveForMCU_arduino_mpy_modules_frozentest__lt_module_gt_[92] = {
    0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0d,
    MP_QSTR__lt_module_gt_ & 0xff, MP_QSTR__lt_module_gt_ >> 8,
    MP_QSTR__slash_home_slash_baozhu_slash_workspace_slash_GroveForMCU_slash_arduino_slash_mpy_slash_modules_slash_frozentest_dot_py & 0xff, MP_QSTR__slash_home_slash_baozhu_slash_workspace_slash_GroveForMCU_slash_arduino_slash_mpy_slash_modules_slash_frozentest_dot_py >> 8,
    0x2a, 0x28, 0x28, 0x28, 0x2b, 0x28, 0x00, 0x00, 0xff,
    0x1b, MP_QSTR_print & 0xff, MP_QSTR_print >> 8, 
    0x16, MP_QSTR_uPy & 0xff, MP_QSTR_uPy >> 8, 
    0x64, 0x01, 
    0x32, 
    0x1b, MP_QSTR_print & 0xff, MP_QSTR_print >> 8, 
    0x17, 0x00, 
    0x64, 0x01, 
    0x32, 
    0x1b, MP_QSTR_print & 0xff, MP_QSTR_print >> 8, 
    0x17, 0x01, 
    0x64, 0x01, 
    0x32, 
    0x1b, MP_QSTR_print & 0xff, MP_QSTR_print >> 8, 
    0x17, 0x02, 
    0x64, 0x01, 
    0x32, 
    0x1b, MP_QSTR_print & 0xff, MP_QSTR_print >> 8, 
    0x14, 0xba, 0xef, 0x9a, 0x15, 
    0x64, 0x01, 
    0x32, 
    0x80, 
    0x35, 0x0f, 0x80, 
    0x30, 
    0x24, MP_QSTR_i & 0xff, MP_QSTR_i >> 8, 
    0x1b, MP_QSTR_print & 0xff, MP_QSTR_print >> 8, 
    0x1b, MP_QSTR_i & 0xff, MP_QSTR_i >> 8, 
    0x64, 0x01, 
    0x32, 
    0x81, 
    0xe5, 
    0x30, 
    0x84, 
    0xd7, 
    0x36, 0xeb, 0x7f, 
    0x32, 
    0x11, 
    0x5b, 
};
STATIC const mp_obj_str_t const_obj__home_baozhu_workspace_GroveForMCU_arduino_mpy_modules_frozentest__lt_module_gt__0 = {{&mp_type_str}, 246, 34, (const byte*)"\x61\x20\x6c\x6f\x6e\x67\x20\x73\x74\x72\x69\x6e\x67\x20\x74\x68\x61\x74\x20\x69\x73\x20\x6e\x6f\x74\x20\x69\x6e\x74\x65\x72\x6e\x65\x64"};
STATIC const mp_obj_str_t const_obj__home_baozhu_workspace_GroveForMCU_arduino_mpy_modules_frozentest__lt_module_gt__1 = {{&mp_type_str}, 200, 38, (const byte*)"\x61\x20\x73\x74\x72\x69\x6e\x67\x20\x74\x68\x61\x74\x20\x68\x61\x73\x20\x75\x6e\x69\x63\x6f\x64\x65\x20\xce\xb1\xce\xb2\xce\xb3\x20\x63\x68\x61\x72\x73"};
STATIC const mp_obj_str_t const_obj__home_baozhu_workspace_GroveForMCU_arduino_mpy_modules_frozentest__lt_module_gt__2 = {{&mp_type_bytes}, 57, 11, (const byte*)"\x62\x79\x74\x65\x73\x20\x31\x32\x33\x34\x01"};
STATIC const mp_rom_obj_t const_table_data__home_baozhu_workspace_GroveForMCU_arduino_mpy_modules_frozentest__lt_module_gt_[3] = {
    MP_ROM_PTR(&const_obj__home_baozhu_workspace_GroveForMCU_arduino_mpy_modules_frozentest__lt_module_gt__0),
    MP_ROM_PTR(&const_obj__home_baozhu_workspace_GroveForMCU_arduino_mpy_modules_frozentest__lt_module_gt__1),
    MP_ROM_PTR(&const_obj__home_baozhu_workspace_GroveForMCU_arduino_mpy_modules_frozentest__lt_module_gt__2),
};
const mp_raw_code_t raw_code__home_baozhu_workspace_GroveForMCU_arduino_mpy_modules_frozentest__lt_module_gt_ = {
    .kind = MP_CODE_BYTECODE,
    .scope_flags = 0x00,
    .n_pos_args = 0,
    .fun_data = fun_data__home_baozhu_workspace_GroveForMCU_arduino_mpy_modules_frozentest__lt_module_gt_,
    .const_table = (mp_uint_t*)const_table_data__home_baozhu_workspace_GroveForMCU_arduino_mpy_modules_frozentest__lt_module_gt_,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 92,
    .n_obj = 3,
    .n_raw_code = 0,
    #if MICROPY_EMIT_NATIVE || MICROPY_EMIT_INLINE_ASM
    .prelude_offset = 0,
    .n_qstr = 0,
    .qstr_link = NULL,
    #endif
    #endif
    #if MICROPY_EMIT_NATIVE || MICROPY_EMIT_INLINE_ASM
    .type_sig = 0,
    #endif
};

const char mp_frozen_mpy_names[] = {
"/home/baozhu/workspace/GroveForMCU/arduino/mpy/modules/frozentest.py\0"
"\0"};
const mp_raw_code_t *const mp_frozen_mpy_content[] = {
    &raw_code__home_baozhu_workspace_GroveForMCU_arduino_mpy_modules_frozentest__lt_module_gt_,
};