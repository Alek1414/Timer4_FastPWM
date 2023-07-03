/*

Description:

Class for generating PWM signals with timer 4.

For the working frequency of the microcontroller as a source, the following settings are available in the constructor:
    • prescaler: divider for Timer4. An enumeration Prescaler is defined for this setting with possible adjustable values.
    • top_limit: TOP value up to which the Timer4 counter counts. Should be less than 2047.

For the working frequency of the microcontroller as a source, the following settings are available in the constructor:
    • asynch_postscaler: divider for the frequency clock of the USB source. An enumeration AsynchPostscaler is defined for this setting with possible adjustable values.
    • prescaler: divider for Timer4. An enumeration Prescaler is defined for this setting with possible adjustable values.
    • top_limit: TOP value up to which the Timer4 counter counts. Should be less than 2048.

With this counter, pins 6, 10, and 13 (N) in the Arduino Leonardo can be used as PWM output. The following methods are available for each pin:
    • begin_PinN: initializes the counter and sets the output pin. If TRUE is given the PWM is invertet.
    • analogWrite_PinN: sets the duty cycle of the PWM signal. The value can be from 0 up to the set top_limit.
    • get_value_PinN: returns the current value for the duty cycle setting.

Formula to calculate the duty cycle:

D = k_REG / k_TOP · 100 %

Formula to calculate the resoluction of the duty cycle

R_%,PWM = 100% / k_TOP 

Formula to calculate the frecueny when using f_Mikrocontroller:

f_PWM = f_Mikrocontroller / (N_Prescaler · k_TOP)

Formula to calculate the frecueny when using f_USB:

f_PWM = f_USB / (N_Prescaler · N_Postscaler · k_TOP)

Symbol              Unit    Description
-----------------------------------------------------------------------------
D	                %	    Duty cycle
k_REG	            -	    Valuel for comparison with the counter value to set a PWM duty cycle
k_TOP	            -	    Value to set the PWM frequency
R_%,PWM	            %	    Resolution of the duty cycle
f_Mikrocontroller	Hz	    Operating frequency of the microcontroller
f_USB	            Hz	    Operating frequency of the USB unit in the microcontroller
N_Prescaler	        -	    Counter prescaler
N_Postscaler	    -	    Post-divider of the operating frequency of the USB unit

Author: Alejandro Miguel Kölbl
Date: 25.04.2023

*/

#ifndef TIMER4_FAST_PWM
#define TIMER4_FAST_PWM

#include <Arduino.h>

class Timer4_FastPWM
{
    public:
        enum Prescaler {PS_1 = 1,
                        PS_2 = 2,
                        PS_4 = 3,
                        PS_8 = 4,
                        PS_16 = 5,
                        PS_32 = 6,
                        PS_64 = 7,
                        PS_128 = 8,
                        PS_256 = 9,
                        PS_512 = 10,
                        PS_1024 = 11,
                        PS_2048 = 12,
                        PS_4096 = 13,
                        PS_8192 = 14,
                        PS_16384 = 15};

        enum AsynchPostscaler {APS_1=1,
                              APS_1_5=2,
                              APS_2=3};

        Timer4_FastPWM(Prescaler prescaler, uint16_t top_limit);
        Timer4_FastPWM(AsynchPostscaler asynch_postscaler, Prescaler prescaler, uint16_t top_limit);
        void begin_Pin13(bool invert);
        void begin_Pin10(bool invert);
        void begin_Pin6(bool invert);
        void analogWrite_Pin13(uint16_t value);
        void analogWrite_Pin10(uint16_t value);
        void analogWrite_Pin6(uint16_t value);
        uint16_t get_value_Pin13();
        uint16_t get_value_Pin10();
        uint16_t get_value_Pin6();

    private:
        bool configured;
        bool asynch_mode;
        Prescaler prescaler;
        AsynchPostscaler asynch_postscaler;
        uint16_t top_limit;
        uint16_t value_Pin13;
        uint16_t value_Pin10;
        uint16_t value_Pin6;
        void common_configuration();
        void write_register(volatile uint8_t &reg, uint16_t i);

};

#endif