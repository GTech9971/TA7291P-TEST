#pragma once

#include <xc.h>

/**
 * モータードライバーを制御する構造体
 */
typedef struct {
    /**
     * ロジック入力端子1のピン
     */
    uint8_t input1_pin;
    /**
     * ロジック入力端子2のピン     
     */
    uint8_t input2_pin;            
    /**
     * 制御電源端子用のピン
     */
    uint8_t vref_pin;
    /**
     * モーターのスピード 0~1023
     */
    uint16_t speed;
} TA7291P;



static void set_input1_pin_low(TA7291P *p);
static void set_input1_pin_high(TA7291P *p);

static void set_input2_pin_low(TA7291P *p);
static void set_input2_pin_high(TA7291P *p);

/**
 * ピンのANSEL,TRISの設定
 * pwmの設定を行う
 * @param p
 */
void initialize(TA7291P *p);

/**
 * モーターのスピードを設定する
 * @param p
 * @param speed
 */
void set_speed(TA7291P *p, uint16_t speed);

/**
 * pwmのデューティー比を変更する
 * @param duty_value 0~1023
 */
static void pwm_load_duty_value(uint16_t duty_value);

/**
 * モーター停止
 * @param p
 */
void stop(TA7291P *p);

/**
 * モーター直進
 * @param p
 * @param value
 */
void forward(TA7291P *p, uint16_t value);

/**
 * モーター後退
 * @param p
 * @param value
 */
void back(TA7291P *p, uint16_t value);