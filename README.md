# Timer4_FastPWM

This C++ class provides functionality for generating high-resolution PWM signals with Timer4 on an Arduino Leonardo board. While it was designed for the Arduino Leonardo, it may also be compatible with other Arduino boards, although it has not been extensively tested on them.

## Description

The `Timer4_FastPWM` class allows you to generate PWM signals on pin 6, 10, and 13 of the Arduino Leonardo. It utilizes Timer4 and provides methods for initializing the counter, setting the duty cycle, and retrieving the current duty cycle value.

The class has two constructors that allow you to initialize the PWM settings based on the timer's working frequency. One constructor is used to initialize the Timer4_FastPWM object with a specific prescaler and top limit value. It allows you to set the parameters for generating the PWM signal using the microcontroller's working frequency as the source. The other constructor is used to initialize the Timer4_FastPWM object with additional parameters for generating the PWM signal using the USB unit's working frequency as the source.

The constructor `Timer4_FastPWM(Prescaler prescaler, uint16_t top_limit)` offers the following settings:
- `prescaler` ($`N_{Prescaler}`$): The prescaler value determines the divider for Timer4. It is specified using the Prescaler enumeration, which provides adjustable values ranging from PS_1 to PS_16384, representing different division ratios.
- `top_limit` ($`k_{TOP}`$): The top limit value specifies the maximum value up to which the Timer4 counter counts. It should be a value less than 2047.

In addition, the constructor `Timer4_FastPWM(AsynchPostscaler asynch_postscaler, Prescaler prescaler, uint16_t top_limit)` offers the following setting:
- `asynch_postscaler`: Determines the divider for the frequency clock of the USB source. It is specified using the `AsynchPostscaler` enumeration, which provides adjustable values of `APS_1`, `APS_1_5`, and `APS_2`, representing different division ratios.
  
## Usage

To use the `Timer4_FastPWM` class, follow these steps:

1. Include the `Timer4_FastPWM.h` header file in your Arduino sketch.
2. Create an instance of the `Timer4_FastPWM` class. Choose between one constructor or the other and configure acordingly.
4. Call the `begin_PinX()` method to initialize the counter and configure pin X as the PWM output. Optionally, you can set the `invert` parameter to `true` to invert the PWM signal.
5. Use the `analogWrite_PinX()` method to set the duty cycle of the PWM signal. Pass a value between 0 and the configured `top_limit`.
6. Retrieve the current duty cycle value using the `get_value_PinX()` method if needed.

## Formulas

The following formulas can be used to calculate various aspects of the PWM signal:

- Duty Cycle:
  $`D = (k_{REG} / k_{TOP}) * 100 \% `$

- Resolution of the Duty Cycle:
  $`R_{\%PWM} = 100\% / k_{TOP}`$
  
- PWM Frequency when using the microcontroller's working frequency:
   $`f_{PWM} = f_{Mikrocontroller} / (N_{Prescaler} * k_{TOP})`$
  
- PWM Frequency when using the USB unit's working frequency:
   $`f_{PWM} = f_{USB} / (N_{Prescaler} * N_{Postscaler} * k_{TOP})`$

Where:
- $`D`$ in % : Duty cycle in percentage
- $`k_{REG}`$ : Value for comparison with the counter value to set a PWM duty cycle
- $`k_{TOP}`$ : Value to set the PWM frequency (top limit)
- $`R_{\%PWM}`$ in % : Resolution of the duty cycle in percentage
- $`f_{PWM}`$ in Hz : Frequency of the PWM signal
- $`f_{Mikrocontroller}`$ in Hz : Operating frequency of the microcontroller (16NHz)
- $`f_{USB}`$ in Hz : Operating frequency of the USB unit in the microcontroller (96MHz)
- $`N_{Prescaler}`$ : Counter prescaler
- $`N_{Postscaler}`$ : Post-divider of the operating frequency of the USB unit

## Example

Here's an example usage of the `Timer4_FastPWM` class to generate a PWM signal of 2KHz on Pin 13 with a duty cycle of 75%:

```cpp
#include <Timer4_FastPWM.h>

// Initialize with prescaler and top_limit values for a frequency of 2KHz
Timer4_FastPWM pwm(Timer4_FastPWM::Prescaler::PS_8, 1000);

void setup() {
  // Other setup code
  pwm.begin_Pin13(false);  // Initialize Pin 13 as PWM output, not inverted
}

void loop() {
  // Other loop code
  pwm.analogWrite_Pin13(750);  // Set duty cycle of Pin 13 PWM signal to 75%
}
```

Here's an example usage of the `Timer4_FastPWM` class to generate a PWM signal of 20KHz on Pin 13 with a duty cycle of 25%:

```cpp
#include <Timer4_FastPWM.h>

// Initialize with asynch_postscaler, prescaler, and top_limit values for a frequency of 20KHz
Timer4_FastPWM pwm(Timer4_FastPWM::AsynchPostscaler::APS_1_5, Timer4_FastPWM::Prescaler::PS_2, 1600);

void setup() {
  // Other setup code
  pwm.begin_Pin13(false);  // Initialize Pin 13 as PWM output, not inverted
}

void loop() {
  // Other loop code
  pwm.analogWrite_Pin13(400);  // Set duty cycle of Pin 13 PWM signal to 25%
}
```

## Author
This class was created by Alejandro Miguel Kölbl.

## License
This project is licensed under the MIT License. Feel free to modify and adapt the class as needed for your project.
