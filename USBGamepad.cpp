#include "USBGamepad.h"
// #include "stdint.h"
// #include "usb_phy_api.h"

//USBGamepad::USBGamepad(bool connect_blocking, uint16_t vendor_id, uint16_t product_id, uint16_t product_release) : 
//    USBHID(get_usb_phy(), 0, 0, vendor_id, product_id, product_release)
//{   
//    _button = 0;
//    if (connect_blocking) {
//        USBDevice::connect();
//        wait_ready();
//    } else {
//        init();
//    }
//}
//
//USBGamepad::USBGamepad(USBPhy *phy, uint16_t vendor_id, uint16_t product_id, uint16_t product_release):
//    USBHID(get_usb_phy(), 0, 0, vendor_id, product_id, product_release)
//{
//}

void USBGamepad::init() {
    
   _button = 0x00;            
}

USBGamepad::~USBGamepad()
{
    // deinit();
}

bool USBGamepad::update(int8_t x, int8_t y, uint8_t buttons, int8_t z, int8_t rx) 
{
    bool ret;

    while (x > 127) {
        if (!gamepad_send(127, 0, buttons, 0, 0)) {
            return false;
        }
        x = x - 127;
    }
    while (x < -128) {
        if (!gamepad_send(-128, 0, buttons, 0, 0)) {
            return false;
        }
        x = x + 128;
    }
    while (y > 127) {
        if (!gamepad_send(0, 127, buttons, 0, 0)) {
            return false;
        }
        y = y - 127;
    }
    while (y < -128) {
        if (!gamepad_send(0, -128, buttons, 0, 0)) {
            return false;
        }
        y = y + 128;
    }
    while (z > 127) {
        if (!gamepad_send(0, 0, buttons, 127, 0)) {
            return false;
        }
        z = z - 127;
    }
    while (z < -128) {
        if (!gamepad_send(0, 0, buttons, -128, 0)) {
            return false;
        }
        z = z + 128;
    }
    while (rx > 127) {
        if (!gamepad_send(0, 0, buttons, 0, 127)) {
            return false;
        }
        rx = rx - 127;
    }
    while (rx < -128) {
        if (!gamepad_send(0, 0, buttons, 0, -128)) {
            return false;
        }
        rx = rx + 128;
    }
    ret = gamepad_send(x, y, buttons, z, rx);

    return ret;

}

bool USBGamepad::press(uint8_t button)
{
    _button = button & 0x0F; // Bit mask with 1111

    bool ret = update(0, 0, _button, 0, 0);

    return ret;

}

bool USBGamepad::release(uint8_t button)
{

    _button = (_button & (~button)) & 0x0F;
    bool ret = update(0, 0, _button, 0, 0);
    
    return ret;
}

bool USBGamepad::click(uint8_t button) {

    if (!update(0, 0, button, 0, 0)) {
        return false;
    }
    wait(1);
    // TODO 
    // rtos::ThisThread::sleep_for(10ms);
    bool ret = update(0, 0, 0, 0, 0);

    return ret; 
}

bool USBGamepad::joystick(uint8_t joy, uint8_t x, uint8_t y) 
{
    bool ret;

    if (joy == JOY_LEFT) {
        ret = update(x, y, _button, 0, 0);
    } else {
        ret = update(0, 0, _button, x, y);
    }
    return ret;
}


bool USBGamepad::gamepad_send(int8_t x, int8_t y, uint8_t buttons, int8_t z, int8_t rx) 
{
    HID_REPORT report;

    report.data[0] = buttons;
    report.data[1] = x;
    report.data[2] = y;
    report.data[3] = z;
    report.data[4] = rx;

    report.length = 5;

    bool ret = send(&report);

    return ret;
}


uint8_t *USBGamepad::reportDesc() 
{
    // TODO check if need a report_id
    static uint8_t report_descriptor[] = {
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
    reportLength = sizeof(report_descriptor);
    return report_descriptor;
}
