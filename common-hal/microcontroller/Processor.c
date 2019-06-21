/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Dan Halbert for Adafruit Industries
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

/*
 * Includes code from ASF sample code adc_temp.h and adc_temp.c,
 * and so includes this license:
 *
 * Copyright (C) 2015 Atmel Corporation. All rights reserved.
 *
 * License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "common-hal/microcontroller/Processor.h"


float common_hal_mcu_processor_get_temperature(void) {
//     struct adc_sync_descriptor adc;

//     static Adc* adc_insts[] = ADC_INSTS;
//     samd_peripherals_adc_setup(&adc, adc_insts[0]);

// #ifdef SAMD21
//     // The parameters chosen here are from the temperature example in:
//     // http://www.atmel.com/images/Atmel-42645-ADC-Configurations-with-Examples_ApplicationNote_AT11481.pdf
//     // That note also recommends in general:
//     // "Discard the first conversion result whenever there is a change
//     // in ADC configuration like voltage reference / ADC channel change."

//     adc_sync_set_resolution(&adc, ADC_CTRLB_RESSEL_12BIT_Val);
//     adc_sync_set_reference(&adc, ADC_REFCTRL_REFSEL_INT1V_Val);
//     // Channel passed in adc_sync_enable_channel is actually ignored (!).
//     adc_sync_enable_channel(&adc, ADC_INPUTCTRL_MUXPOS_TEMP_Val);
//     adc_sync_set_inputs(&adc,
//                         ADC_INPUTCTRL_MUXPOS_TEMP_Val,   // pos_input
//                         ADC_INPUTCTRL_MUXNEG_GND_Val,    // neg_input
//                         ADC_INPUTCTRL_MUXPOS_TEMP_Val);  // channel channel (this arg is ignored (!))

//     adc_sync_set_resolution(&adc, ADC_CTRLB_RESSEL_12BIT_Val);

//     hri_adc_write_CTRLB_PRESCALER_bf(adc.device.hw, ADC_CTRLB_PRESCALER_DIV32_Val);
//     hri_adc_write_SAMPCTRL_SAMPLEN_bf(adc.device.hw, ADC_TEMP_SAMPLE_LENGTH);

//     hri_sysctrl_set_VREF_TSEN_bit(SYSCTRL);

//     // Oversample and decimate. A higher samplenum produces a more stable result.
//     hri_adc_write_AVGCTRL_SAMPLENUM_bf(adc.device.hw, ADC_AVGCTRL_SAMPLENUM_4_Val);
//     hri_adc_write_AVGCTRL_ADJRES_bf(adc.device.hw, 2);

//     volatile uint16_t value;

//     // Read twice and discard first result, as recommended in section 14 of
//     // http://www.atmel.com/images/Atmel-42645-ADC-Configurations-with-Examples_ApplicationNote_AT11481.pdf
//     // "Discard the first conversion result whenever there is a change in ADC configuration
//     // like voltage reference / ADC channel change"
//     // Empirical observation shows the first reading is quite different than subsequent ones.

//     // The channel listed in adc_sync_read_channel is actually ignored(!).
//     // Must be set as above with adc_sync_set_inputs.
//     adc_sync_read_channel(&adc, ADC_INPUTCTRL_MUXPOS_TEMP_Val, ((uint8_t*) &value), 2);
//     adc_sync_read_channel(&adc, ADC_INPUTCTRL_MUXPOS_TEMP_Val, ((uint8_t*) &value), 2);

//     adc_sync_deinit(&adc);
//     return calculate_temperature(value);
// #endif // SAMD21

// #ifdef SAMD51
//     adc_sync_set_resolution(&adc, ADC_CTRLB_RESSEL_12BIT_Val);
//     // Reference voltage choice is a guess. It's not specified in the datasheet that I can see.
//     // INTVCC1 seems to read a little high.
//     // INTREF doesn't work: ADC hangs BUSY.
//     adc_sync_set_reference(&adc, ADC_REFCTRL_REFSEL_INTVCC0_Val);

//     // If ONDEMAND=1, we don't need to use the VREF.TSSEL bit to choose PTAT and CTAT.
//     hri_supc_set_VREF_ONDEMAND_bit(SUPC);
//     hri_supc_set_VREF_TSEN_bit(SUPC);

//     // Channel passed in adc_sync_enable_channel is actually ignored (!).
//     adc_sync_enable_channel(&adc, ADC_INPUTCTRL_MUXPOS_PTAT_Val);
//     adc_sync_set_inputs(&adc,
//                         ADC_INPUTCTRL_MUXPOS_PTAT_Val,   // pos_input
//                         ADC_INPUTCTRL_MUXNEG_GND_Val,    // neg_input
//                         ADC_INPUTCTRL_MUXPOS_PTAT_Val);  // channel (this arg is ignored (!))

//     // Read both temperature sensors.
//     volatile uint16_t ptat;
//     volatile uint16_t ctat;

//     // The channel listed in adc_sync_read_channel is actually ignored(!).
//     // Must be set as above with adc_sync_set_inputs.
//     // Read twice for stability (necessary?)
//     adc_sync_read_channel(&adc, ADC_INPUTCTRL_MUXPOS_PTAT_Val, ((uint8_t*) &ptat), 2);
//     adc_sync_read_channel(&adc, ADC_INPUTCTRL_MUXPOS_PTAT_Val, ((uint8_t*) &ptat), 2);

//     adc_sync_set_inputs(&adc,
//                         ADC_INPUTCTRL_MUXPOS_CTAT_Val,   // pos_input
//                         ADC_INPUTCTRL_MUXNEG_GND_Val,    // neg_input
//                         ADC_INPUTCTRL_MUXPOS_CTAT_Val);  // channel (this arg is ignored (!))

//     // Channel passed in adc_sync_enable_channel is actually ignored (!).
//     adc_sync_enable_channel(&adc, ADC_INPUTCTRL_MUXPOS_CTAT_Val);
//     // The channel listed in adc_sync_read_channel is actually ignored(!).
//     // Must be set as above with adc_sync_set_inputs.
//     // Read twice for stability (necessary?)
//     adc_sync_read_channel(&adc, ADC_INPUTCTRL_MUXPOS_CTAT_Val, ((uint8_t*) &ctat), 2);
//     adc_sync_read_channel(&adc, ADC_INPUTCTRL_MUXPOS_CTAT_Val, ((uint8_t*) &ctat), 2);
//     hri_supc_set_VREF_ONDEMAND_bit(SUPC);

//     adc_sync_deinit(&adc);
//     return calculate_temperature(ptat, ctat);
// #endif // SAMD51
}


uint32_t common_hal_mcu_processor_get_frequency(void) {
    // TODO(tannewt): Determine this dynamically.
    // return CONF_CPU_FREQUENCY;
    return 0;
}

void common_hal_mcu_processor_get_uid(uint8_t raw_id[]) {
    // #ifdef SAMD21
    uint32_t* id_addresses[4] = {(uint32_t *) 0x0080A00C, (uint32_t *) 0x0080A040,
                                 (uint32_t *) 0x0080A044, (uint32_t *) 0x0080A048};
    // #endif
    // #ifdef SAMD51
    // uint32_t* id_addresses[4] = {(uint32_t *) 0x008061FC, (uint32_t *) 0x00806010,
    //                              (uint32_t *) 0x00806014, (uint32_t *) 0x00806018};
    // #endif

    for (int i=0; i<4; i++) {
        for (int k=0; k<4; k++) {
            raw_id[4 * i + k] = (*(id_addresses[i]) >> k * 8) & 0xff;
        }
    }
}
