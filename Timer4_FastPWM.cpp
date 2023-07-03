#include "Timer4_FastPWM.h"

Timer4_FastPWM::Timer4_FastPWM(Prescaler prescaler, uint16_t top_limit)
{
    this->asynch_mode = false;

    this->configured = false;
    this->prescaler = prescaler;
    this->top_limit = top_limit;
}

Timer4_FastPWM::Timer4_FastPWM(AsynchPostscaler asynch_postscaler, Prescaler prescaler, uint16_t top_limit)
{
    this->asynch_mode = true;
    this->asynch_postscaler = asynch_postscaler;

    this->configured = false;
    this->prescaler = prescaler;
    this->top_limit = (uint16_t)(top_limit / 2);
}

void Timer4_FastPWM::common_configuration()
{
    // Enable PLL if used
    if (this->asynch_mode)
    {
        PLLCSR |= _BV(PLLE); 
        while (PLLCSR & _BV(PLOCK) != 1); // Wait for PLL to be locked
        PLLFRQ |= (0b11001111 & PLLFRQ) | (this->asynch_postscaler << 4); // Configure PLL Postcaler
    }
    TCCR4B = (0b11110000 & TCCR4B) | this->prescaler; // Set the timer4 prescaler
    TCCR4E |= _BV(ENHC4); // Enable the 11-Bit resolution
    TCCR4D &= ~_BV(WGM41) & ~_BV(WGM40); // Set the Fast PWM Mode of operation
    this->write_register(OCR4C, this->top_limit); // Set the TOP limit of the timer (Overflow)
    this->configured = true;
}

void Timer4_FastPWM::begin_Pin13(bool invert)
{
    if (!this->configured)
        this->common_configuration();
    this->write_register(OCR4A, 0); // Set a PWM of 0% for the pin 13
    // Activate the Fast PWM on pin 13
    TCCR4A |= _BV(COM4A1) | _BV(PWM4A);
    // Invert the signal if necessary
    if (invert)
        TCCR4A  |= _BV(COM4A0);
    else
        TCCR4A &= ~_BV(COM4A0);
    pinMode(13, OUTPUT); // Configure the pin as output
}

void Timer4_FastPWM::begin_Pin10(bool invert)
{
    if (!this->configured)
        this->common_configuration();
    this->write_register(OCR4B, 0); // Set a PWM of 0% for the pin 10
    // Activate the Fast PWM on pin 10
    TCCR4A |= _BV(COM4B1) | _BV(PWM4B);
    // Invert the signal if necessary
    if (invert)
        TCCR4A  |= _BV(COM4B0);
    else
        TCCR4A &= ~_BV(COM4B0);
    pinMode(10, OUTPUT); // Configure the pin as output
}

void Timer4_FastPWM::begin_Pin6(bool invert)
{
    if (!this->configured)
        this->common_configuration();
    this->write_register(OCR4D, 0); // Set a PWM of 0% for the pin 6
    // Activate the Fast PWM on pin 6
    TCCR4C |= _BV(COM4D1) | _BV(PWM4D);
    // Invert the signal if necessary
    if (invert)
        TCCR4C  |= _BV(COM4D0);
    else
        TCCR4C &= ~_BV(COM4D0);
    pinMode(6, OUTPUT); // Configure the pin as output
}

void Timer4_FastPWM::analogWrite_Pin13(uint16_t value)
{
    this->value_Pin13 = value;
    this->write_register(OCR4A, value);
}

void Timer4_FastPWM::analogWrite_Pin10(uint16_t value)
{
    this->value_Pin10 = value;
    this->write_register(OCR4B, value);
}

void Timer4_FastPWM::analogWrite_Pin6(uint16_t value)
{
    this->value_Pin6 = value;
    this->write_register(OCR4D, value);
}

uint16_t Timer4_FastPWM::get_value_Pin13()
{
    return this->value_Pin13;
}

uint16_t Timer4_FastPWM::get_value_Pin10()
{
    return this->value_Pin10;
}

uint16_t Timer4_FastPWM::get_value_Pin6()
{
    return this->value_Pin6;
}

void Timer4_FastPWM::write_register(volatile uint8_t &reg, uint16_t i)
{
    unsigned char sreg = SREG; // Save global interrupt flag
    cli(); // Disable interrupts
    TC4H = (i >> 8); // Set TC4H with the MSB of value
    reg = (unsigned char)i; // Set the LSB of the register with the LSB of the value
    SREG = sreg; // Restore global interrupt flag
}