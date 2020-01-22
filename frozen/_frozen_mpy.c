#include "py/mpconfig.h"
#include "py/objint.h"
#include "py/objstr.h"
#include "py/emitglue.h"
#include "py/nativeglue.h"

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

enum {
    MP_QSTR_frozen_slash_adafruit_bus_device_slash_i2c_device_dot_py = MP_QSTRnumber_of,
    MP_QSTR___version__,
    MP_QSTR___repo__,
    MP_QSTR_I2CDevice,
    MP_QSTR_write_then_readinto,
    MP_QSTR_i2c,
    MP_QSTR_device_address,
    MP_QSTR_buf,
    MP_QSTR_writeto_then_readfrom,
    MP_QSTR_out_buffer,
    MP_QSTR_in_buffer,
    MP_QSTR_frozen_slash_adafruit_bus_device_slash___init___dot_py,
    MP_QSTR_frozen_slash_adafruit_bus_device_slash_spi_device_dot_py,
    MP_QSTR_SPIDevice,
    MP_QSTR_extra_clocks,
    MP_QSTR_spi,
    MP_QSTR_chip_select,
};

extern const qstr_pool_t mp_qstr_const_pool;
const qstr_pool_t mp_qstr_frozen_const_pool = {
    (qstr_pool_t*)&mp_qstr_const_pool, // previous pool
    MP_QSTRnumber_of, // previous pool size
    10, // allocated entries
    17, // used entries
    {
        (const byte*)"\x13\x28" "frozen/adafruit_bus_device/i2c_device.py",
        (const byte*)"\x3f\x0b" "__version__",
        (const byte*)"\x8d\x08" "__repo__",
        (const byte*)"\x45\x09" "I2CDevice",
        (const byte*)"\x61\x13" "write_then_readinto",
        (const byte*)"\x5d\x03" "i2c",
        (const byte*)"\x14\x0e" "device_address",
        (const byte*)"\x74\x03" "buf",
        (const byte*)"\x70\x15" "writeto_then_readfrom",
        (const byte*)"\xf4\x0a" "out_buffer",
        (const byte*)"\x1d\x09" "in_buffer",
        (const byte*)"\x76\x26" "frozen/adafruit_bus_device/__init__.py",
        (const byte*)"\x81\x28" "frozen/adafruit_bus_device/spi_device.py",
        (const byte*)"\x37\x09" "SPIDevice",
        (const byte*)"\x1b\x0c" "extra_clocks",
        (const byte*)"\xcf\x03" "spi",
        (const byte*)"\x60\x0b" "chip_select",
    },
};

// frozen bytecode for file frozen/adafruit_bus_device/i2c_device.py, scope frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice___init__
STATIC const byte fun_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice___init__[133] = {
    0xe7, 0x02, 0x28,
    MP_QSTR___init__ & 0xff, MP_QSTR___init__ >> 8,
    MP_QSTR_frozen_slash_adafruit_bus_device_slash_i2c_device_dot_py & 0xff, MP_QSTR_frozen_slash_adafruit_bus_device_slash_i2c_device_dot_py >> 8,
    0x80, 0x3c, 0x60, 0x20, 0x23, 0x29, 0x26, 0x76, 0x20, 0x23, 0x27, 0x55, 0x53, 0x48, 0x25, 0x00,
    0x42, 0x00, 0x80, 
    0xb1, 
    0x14, MP_QSTR_try_lock & 0xff, MP_QSTR_try_lock >> 8, 
    0x36, 0x00, 
    0x44, 0xf7, 0x7f, 
    0x49, 0x4b, 0x00, 
    0x48, 0x0d, 0x00, 
    0xb1, 
    0x14, MP_QSTR_writeto & 0xff, MP_QSTR_writeto >> 8, 
    0xb2, 
    0x23, 0x03, 
    0x36, 0x02, 
    0x59, 
    0x4a, 0x3a, 0x00, 
    0x57, 
    0x12, MP_QSTR_OSError & 0xff, MP_QSTR_OSError >> 8, 
    0xdf, 
    0x44, 0x31, 0x80, 
    0x59, 
    0x48, 0x13, 0x00, 
    0x12, MP_QSTR_bytearray & 0xff, MP_QSTR_bytearray >> 8, 
    0x81, 
    0x34, 0x01, 
    0xc3, 
    0xb1, 
    0x14, MP_QSTR_readfrom_into & 0xff, MP_QSTR_readfrom_into >> 8, 
    0xb2, 
    0xb3, 
    0x36, 0x02, 
    0x59, 
    0x4a, 0x17, 0x00, 
    0x57, 
    0x12, MP_QSTR_OSError & 0xff, MP_QSTR_OSError >> 8, 
    0xdf, 
    0x44, 0x0e, 0x80, 
    0x59, 
    0x12, MP_QSTR_ValueError & 0xff, MP_QSTR_ValueError >> 8, 
    0x23, 0x04, 
    0xb2, 
    0xf8, 
    0x34, 0x01, 
    0x65, 
    0x4a, 0x01, 0x00, 
    0x5d, 
    0x4a, 0x01, 0x00, 
    0x5d, 
    0x51, 
    0xb1, 
    0x14, MP_QSTR_unlock & 0xff, MP_QSTR_unlock >> 8, 
    0x36, 0x00, 
    0x59, 
    0x5d, 
    0xb1, 
    0xb0, 
    0x18, MP_QSTR_i2c & 0xff, MP_QSTR_i2c >> 8, 
    0xb2, 
    0xb0, 
    0x18, MP_QSTR_device_address & 0xff, MP_QSTR_device_address >> 8, 
    0x51, 
    0x63, 
};
STATIC const mp_obj_str_t const_obj_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice___init___0 = {{&mp_type_bytes}, 5, 0, (const byte*)""};
STATIC const mp_obj_str_t const_obj_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice___init___1 = {{&mp_type_str}, 96, 28, (const byte*)"\x4e\x6f\x20\x49\x32\x43\x20\x64\x65\x76\x69\x63\x65\x20\x61\x74\x20\x61\x64\x64\x72\x65\x73\x73\x3a\x20\x25\x78"};
STATIC const mp_rom_obj_t const_table_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice___init__[5] = {
    MP_ROM_QSTR(MP_QSTR_self),
    MP_ROM_QSTR(MP_QSTR_i2c),
    MP_ROM_QSTR(MP_QSTR_device_address),
    MP_ROM_PTR(&const_obj_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice___init___0),
    MP_ROM_PTR(&const_obj_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice___init___1),
};
STATIC const mp_raw_code_t raw_code_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice___init__ = {
    .kind = MP_CODE_BYTECODE,
    .scope_flags = 0x00,
    .n_pos_args = 3,
    .fun_data = fun_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice___init__,
    .const_table = (mp_uint_t*)const_table_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice___init__,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 133,
    .n_obj = 2,
    .n_raw_code = 0,
    #if MICROPY_PY_SYS_SETTRACE
    .prelude = {
        .n_state = 13,
        .n_exc_stack = 3,
        .scope_flags = 0,
        .n_pos_args = 3,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name = MP_QSTR___init__,
        .qstr_source_file = MP_QSTR_frozen_slash_adafruit_bus_device_slash_i2c_device_dot_py,
        .line_info = fun_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice___init__ + 0,
        .opcodes = fun_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice___init__ + 23,
    },
    .line_of_definition = 0,
    #endif
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    .n_qstr = 0,
    .qstr_link = NULL,
    #endif
    #endif
    #if MICROPY_EMIT_MACHINE_CODE
    .type_sig = 0,
    #endif
};

// frozen bytecode for file frozen/adafruit_bus_device/i2c_device.py, scope frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice_readinto
STATIC const byte fun_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice_readinto[32] = {
    0xc2, 0x80, 0x40, 0x12,
    MP_QSTR_readinto & 0xff, MP_QSTR_readinto >> 8,
    MP_QSTR_frozen_slash_adafruit_bus_device_slash_i2c_device_dot_py & 0xff, MP_QSTR_frozen_slash_adafruit_bus_device_slash_i2c_device_dot_py >> 8,
    0x80, 0x53, 0x80, 0x0c, 0x00,
    0xb0, 
    0x13, MP_QSTR_i2c & 0xff, MP_QSTR_i2c >> 8, 
    0x14, MP_QSTR_readfrom_into & 0xff, MP_QSTR_readfrom_into >> 8, 
    0xb0, 
    0x13, MP_QSTR_device_address & 0xff, MP_QSTR_device_address >> 8, 
    0xb1, 
    0x53, 
    0xb2, 
    0x37, 0x02, 
    0x59, 
    0x51, 
    0x63, 
};
STATIC const mp_rom_obj_t const_table_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice_readinto[2] = {
    MP_ROM_QSTR(MP_QSTR_self),
    MP_ROM_QSTR(MP_QSTR_buf),
};
STATIC const mp_raw_code_t raw_code_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice_readinto = {
    .kind = MP_CODE_BYTECODE,
    .scope_flags = 0x02,
    .n_pos_args = 2,
    .fun_data = fun_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice_readinto,
    .const_table = (mp_uint_t*)const_table_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice_readinto,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 32,
    .n_obj = 0,
    .n_raw_code = 0,
    #if MICROPY_PY_SYS_SETTRACE
    .prelude = {
        .n_state = 9,
        .n_exc_stack = 0,
        .scope_flags = 2,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name = MP_QSTR_readinto,
        .qstr_source_file = MP_QSTR_frozen_slash_adafruit_bus_device_slash_i2c_device_dot_py,
        .line_info = fun_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice_readinto + 0,
        .opcodes = fun_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice_readinto + 13,
    },
    .line_of_definition = 0,
    #endif
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    .n_qstr = 0,
    .qstr_link = NULL,
    #endif
    #endif
    #if MICROPY_EMIT_MACHINE_CODE
    .type_sig = 0,
    #endif
};

// frozen bytecode for file frozen/adafruit_bus_device/i2c_device.py, scope frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice_write
STATIC const byte fun_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice_write[32] = {
    0xc2, 0x80, 0x40, 0x12,
    MP_QSTR_write & 0xff, MP_QSTR_write >> 8,
    MP_QSTR_frozen_slash_adafruit_bus_device_slash_i2c_device_dot_py & 0xff, MP_QSTR_frozen_slash_adafruit_bus_device_slash_i2c_device_dot_py >> 8,
    0x80, 0x62, 0x80, 0x0d, 0x00,
    0xb0, 
    0x13, MP_QSTR_i2c & 0xff, MP_QSTR_i2c >> 8, 
    0x14, MP_QSTR_writeto & 0xff, MP_QSTR_writeto >> 8, 
    0xb0, 
    0x13, MP_QSTR_device_address & 0xff, MP_QSTR_device_address >> 8, 
    0xb1, 
    0x53, 
    0xb2, 
    0x37, 0x02, 
    0x59, 
    0x51, 
    0x63, 
};
STATIC const mp_rom_obj_t const_table_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice_write[2] = {
    MP_ROM_QSTR(MP_QSTR_self),
    MP_ROM_QSTR(MP_QSTR_buf),
};
STATIC const mp_raw_code_t raw_code_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice_write = {
    .kind = MP_CODE_BYTECODE,
    .scope_flags = 0x02,
    .n_pos_args = 2,
    .fun_data = fun_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice_write,
    .const_table = (mp_uint_t*)const_table_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice_write,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 32,
    .n_obj = 0,
    .n_raw_code = 0,
    #if MICROPY_PY_SYS_SETTRACE
    .prelude = {
        .n_state = 9,
        .n_exc_stack = 0,
        .scope_flags = 2,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name = MP_QSTR_write,
        .qstr_source_file = MP_QSTR_frozen_slash_adafruit_bus_device_slash_i2c_device_dot_py,
        .line_info = fun_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice_write + 0,
        .opcodes = fun_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice_write + 13,
    },
    .line_of_definition = 0,
    #endif
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    .n_qstr = 0,
    .qstr_link = NULL,
    #endif
    #endif
    #if MICROPY_EMIT_MACHINE_CODE
    .type_sig = 0,
    #endif
};

// frozen bytecode for file frozen/adafruit_bus_device/i2c_device.py, scope frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice_write_then_readinto
STATIC const byte fun_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice_write_then_readinto[144] = {
    0xb3, 0x98, 0x80, 0x88, 0x40, 0x24,
    MP_QSTR_write_then_readinto & 0xff, MP_QSTR_write_then_readinto >> 8,
    MP_QSTR_frozen_slash_adafruit_bus_device_slash_i2c_device_dot_py & 0xff, MP_QSTR_frozen_slash_adafruit_bus_device_slash_i2c_device_dot_py >> 8,
    0x80, 0x74, 0x80, 0x18, 0x26, 0x27, 0x26, 0x27, 0x4e, 0x1f, 0x69, 0x60, 0x35, 0x00,
    0xb4, 
    0x51, 
    0xde, 
    0x44, 0x07, 0x80, 
    0x12, MP_QSTR_len & 0xff, MP_QSTR_len >> 8, 
    0xb1, 
    0x34, 0x01, 
    0xc4, 
    0xb6, 
    0x51, 
    0xde, 
    0x44, 0x07, 0x80, 
    0x12, MP_QSTR_len & 0xff, MP_QSTR_len >> 8, 
    0xb2, 
    0x34, 0x01, 
    0xc6, 
    0x12, MP_QSTR_hasattr & 0xff, MP_QSTR_hasattr >> 8, 
    0xb0, 
    0x13, MP_QSTR_i2c & 0xff, MP_QSTR_i2c >> 8, 
    0x23, 0x08, 
    0x34, 0x02, 
    0x44, 0x28, 0x80, 
    0xb0, 
    0x13, MP_QSTR_i2c & 0xff, MP_QSTR_i2c >> 8, 
    0x14, MP_QSTR_writeto_then_readfrom & 0xff, MP_QSTR_writeto_then_readfrom >> 8, 
    0xb0, 
    0x13, MP_QSTR_device_address & 0xff, MP_QSTR_device_address >> 8, 
    0xb1, 
    0xb2, 
    0x10, MP_QSTR_out_start & 0xff, MP_QSTR_out_start >> 8, 
    0xb3, 
    0x10, MP_QSTR_out_end & 0xff, MP_QSTR_out_end >> 8, 
    0xb4, 
    0x10, MP_QSTR_in_start & 0xff, MP_QSTR_in_start >> 8, 
    0xb5, 
    0x10, MP_QSTR_in_end & 0xff, MP_QSTR_in_end >> 8, 
    0xb6, 
    0x10, MP_QSTR_stop & 0xff, MP_QSTR_stop >> 8, 
    0xb7, 
    0x36, 0x8a, 0x03, 
    0x59, 
    0x42, 0x26, 0x80, 
    0xb0, 
    0x14, MP_QSTR_write & 0xff, MP_QSTR_write >> 8, 
    0xb1, 
    0x10, MP_QSTR_start & 0xff, MP_QSTR_start >> 8, 
    0xb3, 
    0x10, MP_QSTR_end & 0xff, MP_QSTR_end >> 8, 
    0xb4, 
    0x10, MP_QSTR_stop & 0xff, MP_QSTR_stop >> 8, 
    0xb7, 
    0x36, 0x86, 0x01, 
    0x59, 
    0xb0, 
    0x14, MP_QSTR_readinto & 0xff, MP_QSTR_readinto >> 8, 
    0xb2, 
    0x10, MP_QSTR_start & 0xff, MP_QSTR_start >> 8, 
    0xb5, 
    0x10, MP_QSTR_end & 0xff, MP_QSTR_end >> 8, 
    0xb6, 
    0x36, 0x84, 0x01, 
    0x59, 
    0x51, 
    0x63, 
};
STATIC const mp_obj_str_t const_obj_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice_write_then_readinto_0 = {{&mp_type_str}, 112, 21, (const byte*)"\x77\x72\x69\x74\x65\x74\x6f\x5f\x74\x68\x65\x6e\x5f\x72\x65\x61\x64\x66\x72\x6f\x6d"};
STATIC const mp_rom_obj_t const_table_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice_write_then_readinto[9] = {
    MP_ROM_QSTR(MP_QSTR_self),
    MP_ROM_QSTR(MP_QSTR_out_buffer),
    MP_ROM_QSTR(MP_QSTR_in_buffer),
    MP_ROM_QSTR(MP_QSTR_out_start),
    MP_ROM_QSTR(MP_QSTR_out_end),
    MP_ROM_QSTR(MP_QSTR_in_start),
    MP_ROM_QSTR(MP_QSTR_in_end),
    MP_ROM_QSTR(MP_QSTR_stop),
    MP_ROM_PTR(&const_obj_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice_write_then_readinto_0),
};
STATIC const mp_raw_code_t raw_code_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice_write_then_readinto = {
    .kind = MP_CODE_BYTECODE,
    .scope_flags = 0x08,
    .n_pos_args = 3,
    .fun_data = fun_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice_write_then_readinto,
    .const_table = (mp_uint_t*)const_table_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice_write_then_readinto,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 144,
    .n_obj = 1,
    .n_raw_code = 0,
    #if MICROPY_PY_SYS_SETTRACE
    .prelude = {
        .n_state = 23,
        .n_exc_stack = 0,
        .scope_flags = 8,
        .n_pos_args = 3,
        .n_kwonly_args = 5,
        .n_def_pos_args = 0,
        .qstr_block_name = MP_QSTR_write_then_readinto,
        .qstr_source_file = MP_QSTR_frozen_slash_adafruit_bus_device_slash_i2c_device_dot_py,
        .line_info = fun_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice_write_then_readinto + 0,
        .opcodes = fun_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice_write_then_readinto + 24,
    },
    .line_of_definition = 0,
    #endif
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    .n_qstr = 0,
    .qstr_link = NULL,
    #endif
    #endif
    #if MICROPY_EMIT_MACHINE_CODE
    .type_sig = 0,
    #endif
};

// frozen bytecode for file frozen/adafruit_bus_device/i2c_device.py, scope frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice___enter__
STATIC const byte fun_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice___enter__[28] = {
    0x11, 0x12,
    MP_QSTR___enter__ & 0xff, MP_QSTR___enter__ >> 8,
    MP_QSTR_frozen_slash_adafruit_bus_device_slash_i2c_device_dot_py & 0xff, MP_QSTR_frozen_slash_adafruit_bus_device_slash_i2c_device_dot_py >> 8,
    0x80, 0x9e, 0x23, 0x2c, 0x00,
    0x42, 0x00, 0x80, 
    0xb0, 
    0x13, MP_QSTR_i2c & 0xff, MP_QSTR_i2c >> 8, 
    0x14, MP_QSTR_try_lock & 0xff, MP_QSTR_try_lock >> 8, 
    0x36, 0x00, 
    0x44, 0xf4, 0x7f, 
    0xb0, 
    0x63, 
};
STATIC const mp_rom_obj_t const_table_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice___enter__[1] = {
    MP_ROM_QSTR(MP_QSTR_self),
};
STATIC const mp_raw_code_t raw_code_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice___enter__ = {
    .kind = MP_CODE_BYTECODE,
    .scope_flags = 0x00,
    .n_pos_args = 1,
    .fun_data = fun_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice___enter__,
    .const_table = (mp_uint_t*)const_table_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice___enter__,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 28,
    .n_obj = 0,
    .n_raw_code = 0,
    #if MICROPY_PY_SYS_SETTRACE
    .prelude = {
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name = MP_QSTR___enter__,
        .qstr_source_file = MP_QSTR_frozen_slash_adafruit_bus_device_slash_i2c_device_dot_py,
        .line_info = fun_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice___enter__ + 0,
        .opcodes = fun_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice___enter__ + 11,
    },
    .line_of_definition = 0,
    #endif
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    .n_qstr = 0,
    .qstr_link = NULL,
    #endif
    #endif
    #if MICROPY_EMIT_MACHINE_CODE
    .type_sig = 0,
    #endif
};

// frozen bytecode for file frozen/adafruit_bus_device/i2c_device.py, scope frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice___exit__
STATIC const byte fun_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice___exit__[25] = {
    0x99, 0x80, 0x80, 0x40, 0x10,
    MP_QSTR___exit__ & 0xff, MP_QSTR___exit__ >> 8,
    MP_QSTR_frozen_slash_adafruit_bus_device_slash_i2c_device_dot_py & 0xff, MP_QSTR_frozen_slash_adafruit_bus_device_slash_i2c_device_dot_py >> 8,
    0x80, 0xa3, 0x2a, 0x00,
    0xb0, 
    0x13, MP_QSTR_i2c & 0xff, MP_QSTR_i2c >> 8, 
    0x14, MP_QSTR_unlock & 0xff, MP_QSTR_unlock >> 8, 
    0x36, 0x00, 
    0x59, 
    0x50, 
    0x63, 
};
STATIC const mp_rom_obj_t const_table_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice___exit__[1] = {
    MP_ROM_QSTR(MP_QSTR_self),
};
STATIC const mp_raw_code_t raw_code_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice___exit__ = {
    .kind = MP_CODE_BYTECODE,
    .scope_flags = 0x04,
    .n_pos_args = 1,
    .fun_data = fun_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice___exit__,
    .const_table = (mp_uint_t*)const_table_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice___exit__,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 25,
    .n_obj = 0,
    .n_raw_code = 0,
    #if MICROPY_PY_SYS_SETTRACE
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 4,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name = MP_QSTR___exit__,
        .qstr_source_file = MP_QSTR_frozen_slash_adafruit_bus_device_slash_i2c_device_dot_py,
        .line_info = fun_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice___exit__ + 0,
        .opcodes = fun_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice___exit__ + 13,
    },
    .line_of_definition = 0,
    #endif
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    .n_qstr = 0,
    .qstr_link = NULL,
    #endif
    #endif
    #if MICROPY_EMIT_MACHINE_CODE
    .type_sig = 0,
    #endif
};

// frozen bytecode for file frozen/adafruit_bus_device/i2c_device.py, scope frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice
STATIC const byte fun_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice[94] = {
    0x18, 0x28,
    MP_QSTR_I2CDevice & 0xff, MP_QSTR_I2CDevice >> 8,
    MP_QSTR_frozen_slash_adafruit_bus_device_slash_i2c_device_dot_py & 0xff, MP_QSTR_frozen_slash_adafruit_bus_device_slash_i2c_device_dot_py >> 8,
    0x8c, 0x1f, 0x80, 0x1c, 0x85, 0x17, 0x85, 0x0f, 0x85, 0x11, 0x1f, 0x82, 0x2b, 0x65, 0x40, 0x00,
    0x11, MP_QSTR___name__ & 0xff, MP_QSTR___name__ >> 8, 
    0x16, MP_QSTR___module__ & 0xff, MP_QSTR___module__ >> 8, 
    0x10, MP_QSTR_I2CDevice & 0xff, MP_QSTR_I2CDevice >> 8, 
    0x16, MP_QSTR___qualname__ & 0xff, MP_QSTR___qualname__ >> 8, 
    0x32, 0x00, 
    0x16, MP_QSTR___init__ & 0xff, MP_QSTR___init__ >> 8, 
    0x32, 0x01, 
    0x16, MP_QSTR_readinto & 0xff, MP_QSTR_readinto >> 8, 
    0x32, 0x02, 
    0x16, MP_QSTR_write & 0xff, MP_QSTR_write >> 8, 
    0x53, 
    0x2c, 0x00, 
    0x80, 
    0x10, MP_QSTR_out_start & 0xff, MP_QSTR_out_start >> 8, 
    0x62, 
    0x51, 
    0x10, MP_QSTR_out_end & 0xff, MP_QSTR_out_end >> 8, 
    0x62, 
    0x80, 
    0x10, MP_QSTR_in_start & 0xff, MP_QSTR_in_start >> 8, 
    0x62, 
    0x51, 
    0x10, MP_QSTR_in_end & 0xff, MP_QSTR_in_end >> 8, 
    0x62, 
    0x52, 
    0x10, MP_QSTR_stop & 0xff, MP_QSTR_stop >> 8, 
    0x62, 
    0x33, 0x03, 
    0x16, MP_QSTR_write_then_readinto & 0xff, MP_QSTR_write_then_readinto >> 8, 
    0x32, 0x04, 
    0x16, MP_QSTR___enter__ & 0xff, MP_QSTR___enter__ >> 8, 
    0x32, 0x05, 
    0x16, MP_QSTR___exit__ & 0xff, MP_QSTR___exit__ >> 8, 
    0x51, 
    0x63, 
};
STATIC const mp_rom_obj_t const_table_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice[6] = {
    MP_ROM_PTR(&raw_code_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice___init__),
    MP_ROM_PTR(&raw_code_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice_readinto),
    MP_ROM_PTR(&raw_code_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice_write),
    MP_ROM_PTR(&raw_code_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice_write_then_readinto),
    MP_ROM_PTR(&raw_code_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice___enter__),
    MP_ROM_PTR(&raw_code_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice___exit__),
};
STATIC const mp_raw_code_t raw_code_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice = {
    .kind = MP_CODE_BYTECODE,
    .scope_flags = 0x00,
    .n_pos_args = 0,
    .fun_data = fun_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice,
    .const_table = (mp_uint_t*)const_table_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 94,
    .n_obj = 0,
    .n_raw_code = 6,
    #if MICROPY_PY_SYS_SETTRACE
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name = MP_QSTR_I2CDevice,
        .qstr_source_file = MP_QSTR_frozen_slash_adafruit_bus_device_slash_i2c_device_dot_py,
        .line_info = fun_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice + 0,
        .opcodes = fun_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice + 22,
    },
    .line_of_definition = 0,
    #endif
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    .n_qstr = 0,
    .qstr_link = NULL,
    #endif
    #endif
    #if MICROPY_EMIT_MACHINE_CODE
    .type_sig = 0,
    #endif
};

// frozen bytecode for file frozen/adafruit_bus_device/i2c_device.py, scope frozen_adafruit_bus_device_i2c_device_<module>
STATIC const byte fun_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt_[36] = {
    0x10, 0x16,
    MP_QSTR__lt_module_gt_ & 0xff, MP_QSTR__lt_module_gt_ >> 8,
    MP_QSTR_frozen_slash_adafruit_bus_device_slash_i2c_device_dot_py & 0xff, MP_QSTR_frozen_slash_adafruit_bus_device_slash_i2c_device_dot_py >> 8,
    0x80, 0x16, 0x60, 0x40, 0x25, 0x45, 0x00,
    0x23, 0x00, 
    0x16, MP_QSTR___version__ & 0xff, MP_QSTR___version__ >> 8, 
    0x23, 0x01, 
    0x16, MP_QSTR___repo__ & 0xff, MP_QSTR___repo__ >> 8, 
    0x54, 
    0x32, 0x02, 
    0x10, MP_QSTR_I2CDevice & 0xff, MP_QSTR_I2CDevice >> 8, 
    0x34, 0x02, 
    0x16, MP_QSTR_I2CDevice & 0xff, MP_QSTR_I2CDevice >> 8, 
    0x51, 
    0x63, 
};
STATIC const mp_obj_str_t const_obj_frozen_adafruit_bus_device_i2c_device__lt_module_gt__0 = {{&mp_type_str}, 41, 12, (const byte*)"\x30\x2e\x30\x2e\x30\x2d\x61\x75\x74\x6f\x2e\x30"};
STATIC const mp_obj_str_t const_obj_frozen_adafruit_bus_device_i2c_device__lt_module_gt__1 = {{&mp_type_str}, 209, 64, (const byte*)"\x68\x74\x74\x70\x73\x3a\x2f\x2f\x67\x69\x74\x68\x75\x62\x2e\x63\x6f\x6d\x2f\x61\x64\x61\x66\x72\x75\x69\x74\x2f\x41\x64\x61\x66\x72\x75\x69\x74\x5f\x43\x69\x72\x63\x75\x69\x74\x50\x79\x74\x68\x6f\x6e\x5f\x42\x75\x73\x44\x65\x76\x69\x63\x65\x2e\x67\x69\x74"};
STATIC const mp_rom_obj_t const_table_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt_[3] = {
    MP_ROM_PTR(&const_obj_frozen_adafruit_bus_device_i2c_device__lt_module_gt__0),
    MP_ROM_PTR(&const_obj_frozen_adafruit_bus_device_i2c_device__lt_module_gt__1),
    MP_ROM_PTR(&raw_code_frozen_adafruit_bus_device_i2c_device__lt_module_gt__I2CDevice),
};
const mp_raw_code_t raw_code_frozen_adafruit_bus_device_i2c_device__lt_module_gt_ = {
    .kind = MP_CODE_BYTECODE,
    .scope_flags = 0x00,
    .n_pos_args = 0,
    .fun_data = fun_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt_,
    .const_table = (mp_uint_t*)const_table_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt_,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 36,
    .n_obj = 2,
    .n_raw_code = 1,
    #if MICROPY_PY_SYS_SETTRACE
    .prelude = {
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name = MP_QSTR__lt_module_gt_,
        .qstr_source_file = MP_QSTR_frozen_slash_adafruit_bus_device_slash_i2c_device_dot_py,
        .line_info = fun_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt_ + 0,
        .opcodes = fun_data_frozen_adafruit_bus_device_i2c_device__lt_module_gt_ + 13,
    },
    .line_of_definition = 0,
    #endif
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    .n_qstr = 0,
    .qstr_link = NULL,
    #endif
    #endif
    #if MICROPY_EMIT_MACHINE_CODE
    .type_sig = 0,
    #endif
};

// frozen bytecode for file frozen/adafruit_bus_device/__init__.py, scope frozen_adafruit_bus_device___init___<module>
STATIC const byte fun_data_frozen_adafruit_bus_device___init____lt_module_gt_[9] = {
    0x00, 0x0a,
    MP_QSTR__lt_module_gt_ & 0xff, MP_QSTR__lt_module_gt_ >> 8,
    MP_QSTR_frozen_slash_adafruit_bus_device_slash___init___dot_py & 0xff, MP_QSTR_frozen_slash_adafruit_bus_device_slash___init___dot_py >> 8,
    0x00,
    0x51, 
    0x63, 
};
const mp_raw_code_t raw_code_frozen_adafruit_bus_device___init____lt_module_gt_ = {
    .kind = MP_CODE_BYTECODE,
    .scope_flags = 0x00,
    .n_pos_args = 0,
    .fun_data = fun_data_frozen_adafruit_bus_device___init____lt_module_gt_,
    .const_table = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 9,
    .n_obj = 0,
    .n_raw_code = 0,
    #if MICROPY_PY_SYS_SETTRACE
    .prelude = {
        .n_state = 1,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name = MP_QSTR__lt_module_gt_,
        .qstr_source_file = MP_QSTR_frozen_slash_adafruit_bus_device_slash___init___dot_py,
        .line_info = fun_data_frozen_adafruit_bus_device___init____lt_module_gt_ + 0,
        .opcodes = fun_data_frozen_adafruit_bus_device___init____lt_module_gt_ + 7,
    },
    .line_of_definition = 0,
    #endif
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    .n_qstr = 0,
    .qstr_link = NULL,
    #endif
    #endif
    #if MICROPY_EMIT_MACHINE_CODE
    .type_sig = 0,
    #endif
};

// frozen bytecode for file frozen/adafruit_bus_device/spi_device.py, scope frozen_adafruit_bus_device_spi_device__lt_module_gt__SPIDevice___init__
STATIC const byte fun_data_frozen_adafruit_bus_device_spi_device__lt_module_gt__SPIDevice___init__[74] = {
    0xd3, 0x81, 0x80, 0x88, 0x40, 0x1c,
    MP_QSTR___init__ & 0xff, MP_QSTR___init__ >> 8,
    MP_QSTR_frozen_slash_adafruit_bus_device_slash_spi_device_dot_py & 0xff, MP_QSTR_frozen_slash_adafruit_bus_device_slash_spi_device_dot_py >> 8,
    0x80, 0x45, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x27, 0x00,
    0xb1, 
    0xb0, 
    0x18, MP_QSTR_spi & 0xff, MP_QSTR_spi >> 8, 
    0xb3, 
    0xb0, 
    0x18, MP_QSTR_baudrate & 0xff, MP_QSTR_baudrate >> 8, 
    0xb4, 
    0xb0, 
    0x18, MP_QSTR_polarity & 0xff, MP_QSTR_polarity >> 8, 
    0xb5, 
    0xb0, 
    0x18, MP_QSTR_phase & 0xff, MP_QSTR_phase >> 8, 
    0xb6, 
    0xb0, 
    0x18, MP_QSTR_extra_clocks & 0xff, MP_QSTR_extra_clocks >> 8, 
    0xb2, 
    0xb0, 
    0x18, MP_QSTR_chip_select & 0xff, MP_QSTR_chip_select >> 8, 
    0xb0, 
    0x13, MP_QSTR_chip_select & 0xff, MP_QSTR_chip_select >> 8, 
    0x44, 0x0f, 0x80, 
    0xb0, 
    0x13, MP_QSTR_chip_select & 0xff, MP_QSTR_chip_select >> 8, 
    0x14, MP_QSTR_switch_to_output & 0xff, MP_QSTR_switch_to_output >> 8, 
    0x10, MP_QSTR_value & 0xff, MP_QSTR_value >> 8, 
    0x52, 
    0x36, 0x82, 0x00, 
    0x59, 
    0x51, 
    0x63, 
};
STATIC const mp_rom_obj_t const_table_data_frozen_adafruit_bus_device_spi_device__lt_module_gt__SPIDevice___init__[7] = {
    MP_ROM_QSTR(MP_QSTR_self),
    MP_ROM_QSTR(MP_QSTR_spi),
    MP_ROM_QSTR(MP_QSTR_chip_select),
    MP_ROM_QSTR(MP_QSTR_baudrate),
    MP_ROM_QSTR(MP_QSTR_polarity),
    MP_ROM_QSTR(MP_QSTR_phase),
    MP_ROM_QSTR(MP_QSTR_extra_clocks),
};
STATIC const mp_raw_code_t raw_code_frozen_adafruit_bus_device_spi_device__lt_module_gt__SPIDevice___init__ = {
    .kind = MP_CODE_BYTECODE,
    .scope_flags = 0x08,
    .n_pos_args = 3,
    .fun_data = fun_data_frozen_adafruit_bus_device_spi_device__lt_module_gt__SPIDevice___init__,
    .const_table = (mp_uint_t*)const_table_data_frozen_adafruit_bus_device_spi_device__lt_module_gt__SPIDevice___init__,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 74,
    .n_obj = 0,
    .n_raw_code = 0,
    #if MICROPY_PY_SYS_SETTRACE
    .prelude = {
        .n_state = 11,
        .n_exc_stack = 0,
        .scope_flags = 8,
        .n_pos_args = 3,
        .n_kwonly_args = 4,
        .n_def_pos_args = 1,
        .qstr_block_name = MP_QSTR___init__,
        .qstr_source_file = MP_QSTR_frozen_slash_adafruit_bus_device_slash_spi_device_dot_py,
        .line_info = fun_data_frozen_adafruit_bus_device_spi_device__lt_module_gt__SPIDevice___init__ + 0,
        .opcodes = fun_data_frozen_adafruit_bus_device_spi_device__lt_module_gt__SPIDevice___init__ + 20,
    },
    .line_of_definition = 0,
    #endif
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    .n_qstr = 0,
    .qstr_link = NULL,
    #endif
    #endif
    #if MICROPY_EMIT_MACHINE_CODE
    .type_sig = 0,
    #endif
};

// frozen bytecode for file frozen/adafruit_bus_device/spi_device.py, scope frozen_adafruit_bus_device_spi_device__lt_module_gt__SPIDevice___enter__
STATIC const byte fun_data_frozen_adafruit_bus_device_spi_device__lt_module_gt__SPIDevice___enter__[82] = {
    0x41, 0x1a,
    MP_QSTR___enter__ & 0xff, MP_QSTR___enter__ >> 8,
    MP_QSTR_frozen_slash_adafruit_bus_device_slash_spi_device_dot_py & 0xff, MP_QSTR_frozen_slash_adafruit_bus_device_slash_spi_device_dot_py >> 8,
    0x80, 0x4f, 0x23, 0x2c, 0x38, 0x28, 0x27, 0x28, 0x00,
    0x42, 0x00, 0x80, 
    0xb0, 
    0x13, MP_QSTR_spi & 0xff, MP_QSTR_spi >> 8, 
    0x14, MP_QSTR_try_lock & 0xff, MP_QSTR_try_lock >> 8, 
    0x36, 0x00, 
    0x44, 0xf4, 0x7f, 
    0xb0, 
    0x13, MP_QSTR_spi & 0xff, MP_QSTR_spi >> 8, 
    0x14, MP_QSTR_configure & 0xff, MP_QSTR_configure >> 8, 
    0x10, MP_QSTR_baudrate & 0xff, MP_QSTR_baudrate >> 8, 
    0xb0, 
    0x13, MP_QSTR_baudrate & 0xff, MP_QSTR_baudrate >> 8, 
    0x10, MP_QSTR_polarity & 0xff, MP_QSTR_polarity >> 8, 
    0xb0, 
    0x13, MP_QSTR_polarity & 0xff, MP_QSTR_polarity >> 8, 
    0x10, MP_QSTR_phase & 0xff, MP_QSTR_phase >> 8, 
    0xb0, 
    0x13, MP_QSTR_phase & 0xff, MP_QSTR_phase >> 8, 
    0x36, 0x86, 0x00, 
    0x59, 
    0xb0, 
    0x13, MP_QSTR_chip_select & 0xff, MP_QSTR_chip_select >> 8, 
    0x44, 0x08, 0x80, 
    0x50, 
    0xb0, 
    0x13, MP_QSTR_chip_select & 0xff, MP_QSTR_chip_select >> 8, 
    0x18, MP_QSTR_value & 0xff, MP_QSTR_value >> 8, 
    0xb0, 
    0x13, MP_QSTR_spi & 0xff, MP_QSTR_spi >> 8, 
    0x63, 
};
STATIC const mp_rom_obj_t const_table_data_frozen_adafruit_bus_device_spi_device__lt_module_gt__SPIDevice___enter__[1] = {
    MP_ROM_QSTR(MP_QSTR_self),
};
STATIC const mp_raw_code_t raw_code_frozen_adafruit_bus_device_spi_device__lt_module_gt__SPIDevice___enter__ = {
    .kind = MP_CODE_BYTECODE,
    .scope_flags = 0x00,
    .n_pos_args = 1,
    .fun_data = fun_data_frozen_adafruit_bus_device_spi_device__lt_module_gt__SPIDevice___enter__,
    .const_table = (mp_uint_t*)const_table_data_frozen_adafruit_bus_device_spi_device__lt_module_gt__SPIDevice___enter__,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 82,
    .n_obj = 0,
    .n_raw_code = 0,
    #if MICROPY_PY_SYS_SETTRACE
    .prelude = {
        .n_state = 9,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name = MP_QSTR___enter__,
        .qstr_source_file = MP_QSTR_frozen_slash_adafruit_bus_device_slash_spi_device_dot_py,
        .line_info = fun_data_frozen_adafruit_bus_device_spi_device__lt_module_gt__SPIDevice___enter__ + 0,
        .opcodes = fun_data_frozen_adafruit_bus_device_spi_device__lt_module_gt__SPIDevice___enter__ + 15,
    },
    .line_of_definition = 0,
    #endif
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    .n_qstr = 0,
    .qstr_link = NULL,
    #endif
    #endif
    #if MICROPY_EMIT_MACHINE_CODE
    .type_sig = 0,
    #endif
};

// frozen bytecode for file frozen/adafruit_bus_device/spi_device.py, scope frozen_adafruit_bus_device_spi_device__lt_module_gt__SPIDevice___exit__
STATIC const byte fun_data_frozen_adafruit_bus_device_spi_device__lt_module_gt__SPIDevice___exit__[122] = {
    0xc9, 0x80, 0x80, 0x40, 0x24,
    MP_QSTR___exit__ & 0xff, MP_QSTR___exit__ >> 8,
    MP_QSTR_frozen_slash_adafruit_bus_device_slash_spi_device_dot_py & 0xff, MP_QSTR_frozen_slash_adafruit_bus_device_slash_spi_device_dot_py >> 8,
    0x80, 0x58, 0x27, 0x28, 0x29, 0x27, 0x26, 0x27, 0x2b, 0x24, 0x27, 0x35, 0x2a, 0x00,
    0xb0, 
    0x13, MP_QSTR_chip_select & 0xff, MP_QSTR_chip_select >> 8, 
    0x44, 0x08, 0x80, 
    0x52, 
    0xb0, 
    0x13, MP_QSTR_chip_select & 0xff, MP_QSTR_chip_select >> 8, 
    0x18, MP_QSTR_value & 0xff, MP_QSTR_value >> 8, 
    0xb0, 
    0x13, MP_QSTR_extra_clocks & 0xff, MP_QSTR_extra_clocks >> 8, 
    0x80, 
    0xd8, 
    0x44, 0x3f, 0x80, 
    0x12, MP_QSTR_bytearray & 0xff, MP_QSTR_bytearray >> 8, 
    0x81, 
    0x34, 0x01, 
    0xc2, 
    0x22, 0x81, 0x7f, 
    0xb2, 
    0x80, 
    0x56, 
    0xb0, 
    0x13, MP_QSTR_extra_clocks & 0xff, MP_QSTR_extra_clocks >> 8, 
    0x88, 
    0xf6, 
    0xc3, 
    0xb0, 
    0x13, MP_QSTR_extra_clocks & 0xff, MP_QSTR_extra_clocks >> 8, 
    0x88, 
    0xf8, 
    0x80, 
    0xdc, 
    0x44, 0x04, 0x80, 
    0xb3, 
    0x81, 
    0xe5, 
    0xc3, 
    0xb3, 
    0x80, 
    0x42, 0x0f, 0x80, 
    0x57, 
    0xc4, 
    0xb0, 
    0x13, MP_QSTR_spi & 0xff, MP_QSTR_spi >> 8, 
    0x14, MP_QSTR_write & 0xff, MP_QSTR_write >> 8, 
    0xb2, 
    0x36, 0x01, 
    0x59, 
    0x81, 
    0xe5, 
    0x58, 
    0x5a, 
    0xd7, 
    0x43, 0xeb, 0x7f, 
    0x59, 
    0x59, 
    0xb0, 
    0x13, MP_QSTR_spi & 0xff, MP_QSTR_spi >> 8, 
    0x14, MP_QSTR_unlock & 0xff, MP_QSTR_unlock >> 8, 
    0x36, 0x00, 
    0x59, 
    0x50, 
    0x63, 
};
STATIC const mp_rom_obj_t const_table_data_frozen_adafruit_bus_device_spi_device__lt_module_gt__SPIDevice___exit__[1] = {
    MP_ROM_QSTR(MP_QSTR_self),
};
STATIC const mp_raw_code_t raw_code_frozen_adafruit_bus_device_spi_device__lt_module_gt__SPIDevice___exit__ = {
    .kind = MP_CODE_BYTECODE,
    .scope_flags = 0x04,
    .n_pos_args = 1,
    .fun_data = fun_data_frozen_adafruit_bus_device_spi_device__lt_module_gt__SPIDevice___exit__,
    .const_table = (mp_uint_t*)const_table_data_frozen_adafruit_bus_device_spi_device__lt_module_gt__SPIDevice___exit__,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 122,
    .n_obj = 0,
    .n_raw_code = 0,
    #if MICROPY_PY_SYS_SETTRACE
    .prelude = {
        .n_state = 10,
        .n_exc_stack = 0,
        .scope_flags = 4,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name = MP_QSTR___exit__,
        .qstr_source_file = MP_QSTR_frozen_slash_adafruit_bus_device_slash_spi_device_dot_py,
        .line_info = fun_data_frozen_adafruit_bus_device_spi_device__lt_module_gt__SPIDevice___exit__ + 0,
        .opcodes = fun_data_frozen_adafruit_bus_device_spi_device__lt_module_gt__SPIDevice___exit__ + 23,
    },
    .line_of_definition = 0,
    #endif
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    .n_qstr = 0,
    .qstr_link = NULL,
    #endif
    #endif
    #if MICROPY_EMIT_MACHINE_CODE
    .type_sig = 0,
    #endif
};

// frozen bytecode for file frozen/adafruit_bus_device/spi_device.py, scope frozen_adafruit_bus_device_spi_device__lt_module_gt__SPIDevice
STATIC const byte fun_data_frozen_adafruit_bus_device_spi_device__lt_module_gt__SPIDevice[73] = {
    0x18, 0x1c,
    MP_QSTR_SPIDevice & 0xff, MP_QSTR_SPIDevice >> 8,
    MP_QSTR_frozen_slash_adafruit_bus_device_slash_spi_device_dot_py & 0xff, MP_QSTR_frozen_slash_adafruit_bus_device_slash_spi_device_dot_py >> 8,
    0x8c, 0x20, 0x80, 0x23, 0x1f, 0x82, 0x0b, 0x85, 0x09, 0x00,
    0x11, MP_QSTR___name__ & 0xff, MP_QSTR___name__ >> 8, 
    0x16, MP_QSTR___module__ & 0xff, MP_QSTR___module__ >> 8, 
    0x10, MP_QSTR_SPIDevice & 0xff, MP_QSTR_SPIDevice >> 8, 
    0x16, MP_QSTR___qualname__ & 0xff, MP_QSTR___qualname__ >> 8, 
    0x51, 
    0x2a, 0x01, 
    0x2c, 0x00, 
    0x22, 0x86, 0x8d, 0x20, 
    0x10, MP_QSTR_baudrate & 0xff, MP_QSTR_baudrate >> 8, 
    0x62, 
    0x80, 
    0x10, MP_QSTR_polarity & 0xff, MP_QSTR_polarity >> 8, 
    0x62, 
    0x80, 
    0x10, MP_QSTR_phase & 0xff, MP_QSTR_phase >> 8, 
    0x62, 
    0x80, 
    0x10, MP_QSTR_extra_clocks & 0xff, MP_QSTR_extra_clocks >> 8, 
    0x62, 
    0x33, 0x00, 
    0x16, MP_QSTR___init__ & 0xff, MP_QSTR___init__ >> 8, 
    0x32, 0x01, 
    0x16, MP_QSTR___enter__ & 0xff, MP_QSTR___enter__ >> 8, 
    0x32, 0x02, 
    0x16, MP_QSTR___exit__ & 0xff, MP_QSTR___exit__ >> 8, 
    0x51, 
    0x63, 
};
STATIC const mp_rom_obj_t const_table_data_frozen_adafruit_bus_device_spi_device__lt_module_gt__SPIDevice[3] = {
    MP_ROM_PTR(&raw_code_frozen_adafruit_bus_device_spi_device__lt_module_gt__SPIDevice___init__),
    MP_ROM_PTR(&raw_code_frozen_adafruit_bus_device_spi_device__lt_module_gt__SPIDevice___enter__),
    MP_ROM_PTR(&raw_code_frozen_adafruit_bus_device_spi_device__lt_module_gt__SPIDevice___exit__),
};
STATIC const mp_raw_code_t raw_code_frozen_adafruit_bus_device_spi_device__lt_module_gt__SPIDevice = {
    .kind = MP_CODE_BYTECODE,
    .scope_flags = 0x00,
    .n_pos_args = 0,
    .fun_data = fun_data_frozen_adafruit_bus_device_spi_device__lt_module_gt__SPIDevice,
    .const_table = (mp_uint_t*)const_table_data_frozen_adafruit_bus_device_spi_device__lt_module_gt__SPIDevice,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 73,
    .n_obj = 0,
    .n_raw_code = 3,
    #if MICROPY_PY_SYS_SETTRACE
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name = MP_QSTR_SPIDevice,
        .qstr_source_file = MP_QSTR_frozen_slash_adafruit_bus_device_slash_spi_device_dot_py,
        .line_info = fun_data_frozen_adafruit_bus_device_spi_device__lt_module_gt__SPIDevice + 0,
        .opcodes = fun_data_frozen_adafruit_bus_device_spi_device__lt_module_gt__SPIDevice + 16,
    },
    .line_of_definition = 0,
    #endif
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    .n_qstr = 0,
    .qstr_link = NULL,
    #endif
    #endif
    #if MICROPY_EMIT_MACHINE_CODE
    .type_sig = 0,
    #endif
};

// frozen bytecode for file frozen/adafruit_bus_device/spi_device.py, scope frozen_adafruit_bus_device_spi_device_<module>
STATIC const byte fun_data_frozen_adafruit_bus_device_spi_device__lt_module_gt_[36] = {
    0x10, 0x16,
    MP_QSTR__lt_module_gt_ & 0xff, MP_QSTR__lt_module_gt_ >> 8,
    MP_QSTR_frozen_slash_adafruit_bus_device_slash_spi_device_dot_py & 0xff, MP_QSTR_frozen_slash_adafruit_bus_device_slash_spi_device_dot_py >> 8,
    0x80, 0x17, 0x60, 0x40, 0x25, 0x45, 0x00,
    0x23, 0x00, 
    0x16, MP_QSTR___version__ & 0xff, MP_QSTR___version__ >> 8, 
    0x23, 0x01, 
    0x16, MP_QSTR___repo__ & 0xff, MP_QSTR___repo__ >> 8, 
    0x54, 
    0x32, 0x02, 
    0x10, MP_QSTR_SPIDevice & 0xff, MP_QSTR_SPIDevice >> 8, 
    0x34, 0x02, 
    0x16, MP_QSTR_SPIDevice & 0xff, MP_QSTR_SPIDevice >> 8, 
    0x51, 
    0x63, 
};
STATIC const mp_obj_str_t const_obj_frozen_adafruit_bus_device_spi_device__lt_module_gt__0 = {{&mp_type_str}, 41, 12, (const byte*)"\x30\x2e\x30\x2e\x30\x2d\x61\x75\x74\x6f\x2e\x30"};
STATIC const mp_obj_str_t const_obj_frozen_adafruit_bus_device_spi_device__lt_module_gt__1 = {{&mp_type_str}, 209, 64, (const byte*)"\x68\x74\x74\x70\x73\x3a\x2f\x2f\x67\x69\x74\x68\x75\x62\x2e\x63\x6f\x6d\x2f\x61\x64\x61\x66\x72\x75\x69\x74\x2f\x41\x64\x61\x66\x72\x75\x69\x74\x5f\x43\x69\x72\x63\x75\x69\x74\x50\x79\x74\x68\x6f\x6e\x5f\x42\x75\x73\x44\x65\x76\x69\x63\x65\x2e\x67\x69\x74"};
STATIC const mp_rom_obj_t const_table_data_frozen_adafruit_bus_device_spi_device__lt_module_gt_[3] = {
    MP_ROM_PTR(&const_obj_frozen_adafruit_bus_device_spi_device__lt_module_gt__0),
    MP_ROM_PTR(&const_obj_frozen_adafruit_bus_device_spi_device__lt_module_gt__1),
    MP_ROM_PTR(&raw_code_frozen_adafruit_bus_device_spi_device__lt_module_gt__SPIDevice),
};
const mp_raw_code_t raw_code_frozen_adafruit_bus_device_spi_device__lt_module_gt_ = {
    .kind = MP_CODE_BYTECODE,
    .scope_flags = 0x00,
    .n_pos_args = 0,
    .fun_data = fun_data_frozen_adafruit_bus_device_spi_device__lt_module_gt_,
    .const_table = (mp_uint_t*)const_table_data_frozen_adafruit_bus_device_spi_device__lt_module_gt_,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 36,
    .n_obj = 2,
    .n_raw_code = 1,
    #if MICROPY_PY_SYS_SETTRACE
    .prelude = {
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name = MP_QSTR__lt_module_gt_,
        .qstr_source_file = MP_QSTR_frozen_slash_adafruit_bus_device_slash_spi_device_dot_py,
        .line_info = fun_data_frozen_adafruit_bus_device_spi_device__lt_module_gt_ + 0,
        .opcodes = fun_data_frozen_adafruit_bus_device_spi_device__lt_module_gt_ + 13,
    },
    .line_of_definition = 0,
    #endif
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    .n_qstr = 0,
    .qstr_link = NULL,
    #endif
    #endif
    #if MICROPY_EMIT_MACHINE_CODE
    .type_sig = 0,
    #endif
};

const char mp_frozen_mpy_names[] = {
"frozen/adafruit_bus_device/i2c_device.py\0"
"frozen/adafruit_bus_device/__init__.py\0"
"frozen/adafruit_bus_device/spi_device.py\0"
"\0"};
const mp_raw_code_t *const mp_frozen_mpy_content[] = {
    &raw_code_frozen_adafruit_bus_device_i2c_device__lt_module_gt_,
    &raw_code_frozen_adafruit_bus_device___init____lt_module_gt_,
    &raw_code_frozen_adafruit_bus_device_spi_device__lt_module_gt_,
};
