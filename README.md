# Welcome to the mbed-gamepad-drivers wiki!  
(ECE - 4180 Final Project) 

**Team Members:**  
* Vineeth Voruganti    
* Srikar Tallapragada    
* Joshua Chang

## Components

Mbed:

![image](https://user-images.githubusercontent.com/55115625/165156167-0309541c-6c7b-47cb-8d9c-993f8ffe2a6e.png)

Sparkfun Pushbuttons:

![image](https://user-images.githubusercontent.com/55115625/165156036-b5e7fef8-fbd1-4be6-a94c-d572dda7a0df.png)

Sparkfun Thumb Joystick:

![pic](https://user-images.githubusercontent.com/55115625/165156073-c6d87b62-2bb1-4d99-9bc5-23f313190107.JPG)

Sparkfun USB Mini-B Breakout: 

![image](https://user-images.githubusercontent.com/55115625/165846035-e74226aa-aa22-462a-ab3b-7c7246a1dc14.png)

## Wiring

Sparkfun Thumb Joystick:

![wiring](https://user-images.githubusercontent.com/55115625/165156106-d178d4de-5bc2-4867-8c88-ae914498e4c1.JPG)

Sparkfun USB Mini-B Breakout:

![test](https://user-images.githubusercontent.com/55115625/165858588-faf845af-0f92-48aa-beb7-02a719414c2a.png)

Pushbuttons:

![image](https://user-images.githubusercontent.com/55115625/163015386-f72815b7-37fd-4497-9429-6f359b494cf6.png)

## Software

The software for this project is split between two parts: The driver code (`USBGamepad.h` and `USBGamepad.cpp`) 
and an example usage in `main.cpp`

### Driver Code

HID drivers work by constantly sending a *report* to the host device with the state of the inputs in the device.
The structure of this report has to be very explicitly defined with a descriptor. Below is the exact descriptor
used in these drivers

```cpp
{
    USAGE_PAGE(1),      0x01,       // Generic Desktop
    USAGE(1),           0x05,       // Gamepad
    COLLECTION(1),      0x01,       // Application
    COLLECTION(1),      0x00,       // Physical

    REPORT_COUNT(1),    0x06,       // 6 Buttons
    REPORT_SIZE(1),     0x01,       // 1 bit each
    USAGE_PAGE(1),      0x09,       // Buttons
    USAGE_MINIMUM(1),       0x01,   // Button #1 
    USAGE_MAXIMUM(1),       0x06,   // Button #6
    LOGICAL_MINIMUM(1),     0x00,   // Minimum = 0 
    LOGICAL_MAXIMUM(1),     0x01,   // Maximum = 1
    INPUT(1),           0x02,       // INPUT type TODO check this INPUT(data,var,abs)
    REPORT_COUNT(1),    0x01,       // Unused Bits for buttons
    REPORT_SIZE(1),     0x02,
    INPUT(1),           0x03,       // INPUT(Cnst,var,abs)

    REPORT_COUNT(1),    0x04,       // 4 Axies
    REPORT_SIZE(1),     0x08,       // 1 Byte Each 
    USAGE_PAGE(1),      0x01,       // Generic Desktop
    USAGE(1),           0x30,       // X
    USAGE(1),           0x31,       // Y
    USAGE(1),           0x32,       // Z
    USAGE(1),           0x33,       // Rx
    LOGICAL_MINIMUM(1),     0x81,   // Logical Minimum (-127)
    LOGICAL_MAXIMUM(1),     0x7f,   // Logical Maximum (127)
    INPUT(1),           0x02,       // Relative data INPUT(data,var,abs)

    END_COLLECTION(0),
    END_COLLECTION(0),
};
```
This descriptor was made using the [USB reference tables](https://usb.org/sites/default/files/hut1_3_0.pdf)
on the USB specification website.

It describes a device meant for a general desktop, that acts as a gamepad with 6 buttons and 4 axies of control.

This driver code is defined in `USBGamepad.h` and `USBGamepad.cpp`. The constructor defines a generic USB HID device and connects to
the host device. The `gamepad_send()` method is used to send the *reports* to the host device.

### Example

The example code itself is a sample implementation that utilizes the driver code with our hardware peripherals.
Our hardware had 6 buttons including the ones in the sparkfun joysticks and 4 axies of control. The `main.cpp`
file initalizes a gamepad instance and all other relevant hardware peripherals. 

The `main` block contains a while loop that continuously polls the state of the hardware and sends it to the
host device via the `update()` method of the gamepad

## Summary of results

The final result of this project was a perfectly working HID controller that works on a windows 10 laptop. This
was tested using both the `joy.cpl` and the video game Zero ranger. 

## Future Works

Currently, the drivers are hardcoded for the hardware we designed, but in the future, it could be made more
generalized by passing in a custom report descriptor to the constructor.

