#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>

#define FRONT_LEFT_EN TIM_OC1
#define FRONT_RIGHT_EN TIM_OC2
#define REAR_LEFT_EN TIM_OC3
#define REAR_RIGHT_EN TIM_OC4

#define ENGINE_TIM TIM2
#define SERVO_TIM TIM3

void TIMER_SERVO_SETUP(void);
void TIMER_ENGINE_SETUP(void);
void GPIO_SETUP(void);
void set_servo_angle(uint8_t angle, enum tim_oc_id type);
void set_engine_speed(uint8_t speed, enum tim_oc_id type);

typedef enum {
    FORWARD,
    REVERSE
}Direction;

typedef enum {
    FRONT_LEFT_EN,
    FRONT_RIGHT_EN,
    REAR_LEFT_EN,
    REAR_RIGHT_EN
}Wheel;
