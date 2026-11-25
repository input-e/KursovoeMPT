#include "main.h"

int main (void){
    rcc_clock_setup_pll(&rcc_hse_configs[RCC_CLOCK_HSE8_24MHZ]);
    TIMER_ENGINE_SETUP();
    TIMER_SERVO_SETUP();
    GPIO_SETUP();
    while (1){

    }
    return 0;
}

void GPIO_SETUP(void){
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_GPIOB);

    gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_10_MHZ, 
        GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO0 | GPIO1 | GPIO2 | GPIO3 | GPIO6 | GPIO7);

    gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_10_MHZ, 
        GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO0 | GPIO1);    
}

void TIMER_SERVO_SETUP(void){
    rcc_periph_clock_enable(RCC_TIM3);

    rcc_periph_reset_pulse(RST_TIM3);
    timer_set_mode(TIM3, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
    timer_set_prescaler(TIM3, (24-1)); //1Mhz (clock 24Mhz)
    timer_set_period(TIM3, 20000-1); // 50Hz (period 0 - 20 ms)

    timer_set_oc_mode(TIM3, TIM_OC1, TIM_OCM_PWM1); //PA6
    timer_set_oc_mode(TIM3, TIM_OC2, TIM_OCM_PWM1); //PA7
    timer_set_oc_mode(TIM3, TIM_OC3, TIM_OCM_PWM1); //PB0
    timer_set_oc_mode(TIM3, TIM_OC4, TIM_OCM_PWM1); //PB1
 
    timer_enable_oc_output(TIM3, TIM_OC1);
    timer_enable_oc_output(TIM3, TIM_OC2);
    timer_enable_oc_output(TIM3, TIM_OC3);
    timer_enable_oc_output(TIM3, TIM_OC4);

    timer_enable_counter(TIM3);
}

void TIMER_ENGINE_SETUP(void){
    rcc_periph_clock_enable(RCC_TIM2);

    rcc_periph_reset_pulse(RST_TIM2);
    timer_set_mode(TIM2, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
    timer_set_prescaler(TIM2, (2400-1)); //1Mhz (clock 24Mhz)
    //timer_set_period(TIM2, 20000-1); // 50Hz (period 0 - 20 ms)

    timer_set_oc_mode(TIM2, TIM_OC1, TIM_OCM_PWM1); //PA0
    timer_set_oc_mode(TIM2, TIM_OC2, TIM_OCM_PWM1); //PA1
    timer_set_oc_mode(TIM2, TIM_OC3, TIM_OCM_PWM1); //PA2
    timer_set_oc_mode(TIM2, TIM_OC4, TIM_OCM_PWM1); //PA3

    timer_enable_oc_output(TIM2, TIM_OC1);
    timer_enable_oc_output(TIM2, TIM_OC2);
    timer_enable_oc_output(TIM2, TIM_OC3);
    timer_enable_oc_output(TIM2, TIM_OC4);

    timer_enable_counter(TIM2);
}

void set_servo_angle(uint8_t angle, enum tim_oc_id type){
    if (angle > 180) angle = 180;
    timer_set_oc_value(TIM2, type, (uint32_t)(angle*11+500));
}

void set_engine_speed(uint8_t speed, enum tim_oc_id type){
    timer_set_oc_value(TIM2, type, (uint32_t)speed*39);
}

void set_rotation_direction(Direction direction, Wheel wheel){

}
