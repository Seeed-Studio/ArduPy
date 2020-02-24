#include "py/mpconfig.h"
#include "py/objint.h"
#include "py/objstr.h"
#include "py/emitglue.h"

#if MICROPY_OPT_CACHE_MAP_LOOKUP_IN_BYTECODE != 0
#error "incompatible MICROPY_OPT_CACHE_MAP_LOOKUP_IN_BYTECODE"
#endif

#if MICROPY_LONGINT_IMPL != 2
#error "incompatible MICROPY_LONGINT_IMPL"
#endif

#if MPZ_DIG_SIZE != 16
#error "incompatible MPZ_DIG_SIZE"
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


extern const qstr_pool_t mp_qstr_const_pool;
const qstr_pool_t mp_qstr_frozen_const_pool = {
    (qstr_pool_t*)&mp_qstr_const_pool, // previous pool
    MP_QSTRnumber_of, // previous pool size
    0, // allocated entries
    0, // used entries
    {
    },
};

// frozen bytecode for file __init__py, scope __init__<module>
STATIC const byte fun_data___init___lt_module_gt_[16] = {
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07,
    MP_QSTR__lt_module_gt_ & 0xff, MP_QSTR__lt_module_gt_ >> 8,
    MP_QSTR___init__py & 0xff, MP_QSTR___init__py >> 8,
    0x00, 0x00, 0xff,
    0x11, 
    0x5b, 
};
const mp_raw_code_t raw_code___init___lt_module_gt_ = {
    .kind = MP_CODE_BYTECODE,
    .scope_flags = 0x00,
    .n_pos_args = 0,
    .fun_data = fun_data___init___lt_module_gt_,
    .const_table = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 16,
    .n_obj = 0,
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
"__init__py\0"
"\0"};
const mp_raw_code_t *const mp_frozen_mpy_content[] = {
    &raw_code___init___lt_module_gt_,
};
