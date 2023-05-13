#include "mcc_generated_files/mcc.h"
#include "./ta7291p.h"

#define _XTAL_FREQ 8000000


void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    
    //input1_pin RA0
    //input2_pin RA1
    //vref_pin RA3
    //speed 0
    TA7291P ta7291p = {0x01, 0x02, 0x08, 0};
    initialize(&ta7291p);

    
    //pwm initialize
    // CCP3M PWM; DC3B 3; 
	CCP3CON = 0x3C;    
	// CCPR3L 127; 
	CCPR3L = 0x7F;    
	// CCPR3H 0; 
	CCPR3H = 0x00;    
	// Selecting Timer 2
	CCPTMRS0bits.C3TSEL = 0x0;
    
    //timer2 initialize
     // PR2 255; 
    PR2 = 0xFF;
    // TMR2 0; 
    TMR2 = 0x00;
    // Clearing IF flag.
    PIR1bits.TMR2IF = 0;
    // T2CKPS 1:1; T2OUTPS 1:1; TMR2ON on; 
    T2CON = 0x04;
    
    uint16_t count = 0;

    //pwmの値が低いとモーターが動かないある程度の値は必要
    bool is_forward = true;    
    while (1)
    {
        if(count == 1023){
            count = 0;
            stop(&ta7291p);
            __delay_ms(1000);
            is_forward = !is_forward;
        }
        
        if(is_forward){
            forward(&ta7291p, count);
        }else{
            back(&ta7291p, count);
        }        
        
                
        __delay_ms(10);
        
        count++;
    }
}