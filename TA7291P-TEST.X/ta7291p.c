#include "./ta7291p.h";

static void set_input1_pin_low(TA7291P *p){
    LATA &= ~p->input1_pin;
}
static void set_input1_pin_high(TA7291P *p){
    LATA |= p->input1_pin;
}

static void set_input2_pin_low(TA7291P *p){
    LATA &= ~p->input1_pin;
}
static void set_input2_pin_high(TA7291P *p){
    LATA |= p->input2_pin;
}

/**
 * ピンのANSEL,TRISの設定
 * @param p
 */
void initialize(TA7291P *p){    
    //input1_pin
    //input2_pin
    //vref_pin
    //出力設定(input:1, output:0)
    TRISA &= ~p->input1_pin;
    TRISA &= ~p->input2_pin;
    TRISA &= ~p->vref_pin;
    
    //vrefピンのアナログ設定(analog:1, digital:0)
    ANSELA |= p->vref_pin;
}

/**
 * モーターのスピードを設定する
 * @param p
 * @param speed
 */
void set_speed(TA7291P *p, uint16_t speed){
    if(speed >= 0 && speed <= 1023){
        p->speed = speed;
        pwm_load_duty_value(p->speed);
    }
}

/**
 * pwmのデューティー比を変更する
 * @param duty_value 0~1023
 */
static void pwm_load_duty_value(uint16_t duty_value){
    // Writing to 8 MSBs of pwm duty cycle in CCPRL register
    CCPR3L = ((duty_value & 0x03FC)>>2);
    
   // Writing to 2 LSBs of pwm duty cycle in CCPCON register
    CCP3CON = ((uint8_t)(CCP3CON & 0xCF) | ((duty_value & 0x0003)<<4));
}

/**
 * モーター停止
 * @param p
 */
void stop(TA7291P *p){
    set_input1_pin_low(p);
    set_input2_pin_low(p);
    
    set_speed(p, 0);
}

/**
 * モーター直進
 * @param p
 * @param value
 */
void forward(TA7291P *p, uint16_t value){
    set_input1_pin_high(p);
    set_input2_pin_low(p);
    
    set_speed(p, value);
}

/**
 * モーター後退
 * @param p
 * @param value
 */
void back(TA7291P *p, uint16_t value){    
    set_input1_pin_low(p);
    set_input2_pin_high(p);
    
    set_speed(p, value);
}
