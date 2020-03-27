

#ifdef LCD_SUPPORT
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
#include "py/objtype.h"
#include "shared-bindings/util.h"
#ifdef MICROPY_PY_LVGL
#include "Seeed_Ardupy_LvGL/lvgl/lvgl.h"
#include "Seeed_Ardupy_LvGL/driver/include/common.h"
common_hal_lcd_monitor_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);
#endif

void common_hal_lcd_construct(abstract_module_t *self);
void common_hal_lcd_deinit(abstract_module_t *self);
void common_hal_lcd_fillScreen(abstract_module_t *self, uint32_t color);
int16_t common_hal_lcd_width(abstract_module_t *self);
int16_t common_hal_lcd_height(abstract_module_t *self);
void common_hal_lcd_setRotation(abstract_module_t *self, uint8_t r);
void common_hal_lcd_invertDisplay(abstract_module_t *self, bool i);

#ifdef __cplusplus
}
#endif
#endif