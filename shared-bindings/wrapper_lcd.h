

#ifdef LCD_SUPPORT

#include <stdint.h>
#ifdef __cplusplus
extern "C"
{
#endif
#include "py/objtype.h"
#include "shared-bindings/util.h"
#ifdef MICROPY_PY_LVGL
#include "Seeed_Ardupy_LvGL/lvgl/lvgl.h"
#include "Seeed_Ardupy_LvGL/driver/include/common.h"
    common_hal_lcd_monitor_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p);
#endif

    void common_hal_lcd_construct(abstract_module_t *self);
    void common_hal_lcd_deinit(abstract_module_t *self);
    void common_hal_lcd_fillScreen(abstract_module_t *self, uint32_t color);
    int16_t common_hal_lcd_width(abstract_module_t *self);
    int16_t common_hal_lcd_height(abstract_module_t *self);
    void common_hal_lcd_setRotation(abstract_module_t *self, uint8_t r);
    void common_hal_lcd_invertDisplay(abstract_module_t *self, bool i);
    void common_hal_lcd_drawPixel(abstract_module_t *self, int32_t x, int32_t y, uint32_t color);
    void common_hal_lcd_setTextFont(abstract_module_t *self, uint8_t font);
    uint8_t common_hal_lcd_getTextFont(abstract_module_t *self);
    void common_hal_lcd_drawChar(abstract_module_t *self, uint16_t uniCode, int32_t x, int32_t y, uint8_t font);
    void common_hal_lcd_drawString(abstract_module_t *self, const char *string, int32_t poX, int32_t poY, uint8_t font);
    void common_hal_lcd_drawCentreString(abstract_module_t *self, const char *string, int32_t dX, int32_t poY, uint8_t font);
    void common_hal_lcd_drawRightString(abstract_module_t *self, const char *string, int32_t dX, int32_t poY, uint8_t font);
    void common_hal_lcd_drawNumber(abstract_module_t *self, long long_num, int32_t poX, int32_t poY, uint8_t font);
    void common_hal_lcd_drawFloat(abstract_module_t *self, float floatNumber, uint8_t decimal, int32_t poX, int32_t poY, uint8_t font);
    int16_t common_hal_lcd_fontHeight(abstract_module_t *self, uint8_t font);
    int16_t common_hal_lcd_textWidth(abstract_module_t *self, const char *string, uint8_t font);
    int16_t common_hal_lcd_fontHeight(abstract_module_t *self, uint8_t font);
    void common_hal_lcd_setTextColor(abstract_module_t *self, uint16_t fgcolor, uint16_t bgcolor);
    void common_hal_lcd_setTextSize(abstract_module_t *self, uint8_t size);
    void common_hal_lcd_setTextWrap(abstract_module_t *self, boolean wrapX, boolean wrapY);
    void common_hal_lcd_setTextDatum(abstract_module_t *self, uint8_t datum);
    void common_hal_lcd_setTextPadding(abstract_module_t *self, uint16_t x_width);
    uint8_t  common_hal_lcd_getRotation(abstract_module_t *self);
    uint8_t  common_hal_lcd_getTextDatum(abstract_module_t *self);
#ifdef __cplusplus
}
#endif

#endif