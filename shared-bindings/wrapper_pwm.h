


#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
void wrapper_pwm(uint32_t _pin, uint32_t frequency, uint32_t duty);
void wrapper_noPwm(uint32_t _pin);
#ifdef __cplusplus
}
#endif