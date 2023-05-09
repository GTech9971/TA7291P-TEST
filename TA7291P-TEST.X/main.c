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
    TA7291P ta7291p = {0x00, 0x01, 0x08, 0};
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

    
    //0~500 forward
    //501~1000 back
    //1001~1023 stop 
    while (1)
    {
        if(count == 1023){
            count = 0;
        }
        
        if(count >= 0 && count <= 500){
            forward(&ta7291p, count);
        }else if(count >= 501 && count <= 1000){
            back(&ta7291p, count);
        }else{
            stop(&ta7291p);
        }
                
        __delay_ms(10);
        
        count++;
    }
}