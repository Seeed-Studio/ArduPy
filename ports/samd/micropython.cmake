
set(MP ${ARDUPY_ROOT_PATH}/MicroPython)

set(GENHDR ${CMAKE_BINARY_DIR}/genhdr)
include_directories(${MP} 
                    ${CMAKE_CURRENT_LIST_DIR}/boards/${BOARD}
                    ${GENHDR}/..
                    ${MP}/lib/lwip/src/include
                    ${MP}/extmod/lwip-include
                    ${CMAKE_CURRENT_LIST_DIR}
                    )


FILE(GLOB_RECURSE MICROPYTHON_SRC
    "${MP}/py/*.c"
    "${ARDUPY_ROOT_PATH}/shared-bindings/*.c"
    "${ARDUPY_ROOT_PATH}/shared-bindings/*.cpp"
)
 
set(MICROPYTHON_SRC ${MICROPYTHON_SRC}             
        ${MP}/extmod/moductypes.c
        ${MP}/extmod/modujson.c
        ${MP}/extmod/modure.c
        ${MP}/extmod/moduzlib.c
        ${MP}/extmod/moduheapq.c
        ${MP}/extmod/modutimeq.c
        ${MP}/extmod/moduhashlib.c
        ${MP}/extmod/moducryptolib.c
        ${MP}/extmod/modubinascii.c
        ${MP}/extmod/virtpin.c
        ${MP}/extmod/machine_mem.c
        ${MP}/extmod/modurandom.c
        ${MP}/extmod/moduselect.c
        ${MP}/extmod/modframebuf.c
        ${MP}/extmod/vfs.c
        ${MP}/extmod/vfs_reader.c
        ${MP}/extmod/vfs_posix.c
        ${MP}/extmod/vfs_posix_file.c
        ${MP}/extmod/vfs_fat.c
        ${MP}/extmod/vfs_fat_diskio.c
        ${MP}/extmod/vfs_fat_file.c
        ${MP}/extmod/utime_mphal.c
        ${MP}/extmod/uos_dupterm.c
        ${MP}/lib/embed/abort_.c
        ${MP}/lib/timeutils/timeutils.c 
        ${MP}/lib/utils/stdout_helpers.c 
        ${MP}/lib/utils/sys_stdio_mphal.c
        ${MP}/lib/utils/pyexec.c 
        ${MP}/lib/utils/printf.c
        ${MP}/lib/mp-readline/readline.c 
        ${MP}/lib/oofatfs/ff.c 
        ${MP}/lib/oofatfs/ffunicode.c 
        ${CMAKE_CURRENT_LIST_DIR}/ardupy_init.c
        ${CMAKE_CURRENT_LIST_DIR}/ardupy_storage.c
        ${CMAKE_CURRENT_LIST_DIR}/frozen/_frozen_mpy.c
        ${CMAKE_CURRENT_LIST_DIR}/boards/${BOARD}/mod_machine_map.c
        )

set(micropython_CFLAGS
        ${micropython_CFLAGS}
        -I.
	-I${ARDUPY_ROOT_PATH}/
        -I${ARDUINO_CORE_PATH}/cores/arduino
        -I${ARDUINO_CORE_PATH}/libraries/Wire
        -I${ARDUINO_CORE_PATH}/libraries/SPI
        -I${ARDUINO_CORE_PATH}/libraries/Adafruit_ZeroDMA
        -I${VARIANT}/
        -I${CMAKE_CURRENT_LIST_DIR}/boards/${BOARD}
        -I${ARDUINO_CORE_PATH}/cores/arduino/TinyUSB
        -I${ARDUINO_CORE_PATH}/cores/arduino/TinyUSB/Adafruit_TinyUSB_ArduinoCore
        -I${ARDUINO_CORE_PATH}/cores/arduino/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src
        -I${MP}/
        -I${CMAKE_CURRENT_LIST_DIR}
        -I${CMAKE_CURRENT_LIST_DIR}/ArduinoLibrarys
        -Wall
        -Werror
        -Wpointer-arith
        -Wuninitialized
        -Wno-unused-label
        -U_FORTIFY_SOURCE
        -Os
        ) 

if ("${MACHINE_LCD}" EQUAL 1)
   set(micropython_CFLAGS
        ${micropython_CFLAGS}
        -I${ARDUINO_CORE_PATH}/libraries/Seeed_Arduino_LCD
   )
endif()


#TODO: verify that this works
set_source_files_properties(${MP}/py/gc.c PROPERTIES COMPILE_FLAGS -Os)
set_source_files_properties(${MP}/py/vm.c PROPERTIES COMPILE_FLAGS -Os) 

#
set_source_files_properties(${MICROPYTHON_SRC} PROPERTIES COMPILE_FLAGS "'-DFFCONF_H=\"${MP}/lib/oofatfs/ffconf.h\"' -Wall -Werror -Wpointer-arith -Wuninitialized -Wno-unused-label -std=gnu99 -U_FORTIFY_SOURCE -Os")
#add_library(micropython ${micropython_regular_SOURCE} ${GENHDR}/qstrdefs.generated.h)
#target_compile_options(micropython PRIVATE ${micropython_CFLAGS})
#target_compile_definitions(micropython PRIVATE FFCONF_H=\"${MP}/lib/oofatfs/ffconf.h\")
set(MPY_LIST
    "${CMAKE_CURRENT_LIST_DIR}/frozen/seeed_device/__init__.mpy"
)
add_custom_command(OUTPUT ${GENHDR}/qstrdefs.generated.h
        COMMAND echo "=======================start========================="
        COMMAND mkdir -p ${GENHDR}
        COMMAND python3 ${MP}/py/makeversionhdr.py ${GENHDR}/mpversion.h
	COMMAND python3 ${MP}/py/makemoduledefs.py --vpath="., .., ${ARDUPY_ROOT_DIR}/, ${CMAKE_CURRENT_LIST_DIR}/boards/${BOARD}," ${MICROPYTHON_SRC} ${GENHDR}/moduledefs.h > ${GENHDR}/moduledefs.h
        COMMAND ${CMAKE_C_COMPILER} -E -DNO_QSTR ${BOARD_DEF} ${micropython_CFLAGS} -DFFCONF_H='\"${MP}/lib/oofatfs/ffconf.h\"' ${MICROPYTHON_SRC} ${CMAKE_CURRENT_LIST_DIR}/mpconfigport.h > ${GENHDR}/qstr.i.last
        COMMAND python3 ${MP}/py/makeqstrdefs.py split ${GENHDR}/qstr.i.last ${GENHDR}/qstr ${GENHDR}/qstrdefs.collected.h
        COMMAND python3 ${MP}/py/makeqstrdefs.py cat ${GENHDR}/qstr.i.last ${GENHDR}/qstr ${GENHDR}/qstrdefs.collected.h
        COMMAND cat ${MP}/py/qstrdefs.h ${CMAKE_CURRENT_LIST_DIR}/qstrdefsport.h ${GENHDR}/qstrdefs.collected.h | sed [=['s/^Q(.*)/"&"/']=] | ${CMAKE_C_COMPILER} -E ${micropython_CFLAGS} -DFFCONF_H='\"${MP}/lib/oofatfs/ffconf.h\"' - | sed [=['s/^"\(Q(.*)\)"/\1/']=] > ${GENHDR}/qstrdefs.preprocessed.h
        COMMAND python3 ${MP}/py/makeqstrdata.py ${GENHDR}/qstrdefs.preprocessed.h > ${GENHDR}/qstrdefs.generated.h
        COMMAND make -C ${MP}/mpy-cross
        # COMMAND cd ${CMAKE_CURRENT_LIST_DIR}/frozen
        # COMMAND ${MP}/mpy-cross/mpy-cross -march=armv7m seeed_device/__init__.py
        # COMMAND cd -
        COMMAND python3  ${MP}/tools/mpy-tool.py -f -q  ${GENHDR}/qstrdefs.preprocessed.h  ${MPY_LIST}  > ${CMAKE_CURRENT_LIST_DIR}/frozen/_frozen_mpy.c
        COMMAND echo "=======================end========================="
        DEPENDS ${MICROPYTHON_SRC}  ${CMAKE_CURRENT_LIST_DIR}/mpconfigport.h
        )
        
