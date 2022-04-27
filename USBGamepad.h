#ifndef USBGAMEPAD_H
#define USBGAMEPAD_H

#include "USBHID.h"
#include "stdint.h"

#define REPORT_ID_GAMEPAD 8

enum BUTTONS {
    GREEN = 1,
    RED = 2,
    BLUE = 3,
    YELLOW = 4,
    JOY_1 = 5,
    JOY_2 = 6
};

enum JOYSTICKS {
    JOY_LEFT = 1,
    JOY_RIGHT = 2 
};

/* X and Y limits */
/* These values do not directly map to screen pixels */
/* Zero may be interpreted as meaning 'no movement' */
#define X_MIN_ABS    (1)        /*!< Minimum value on x-axis */
#define Y_MIN_ABS    (1)        /*!< Minimum value on y-axis */
#define X_MAX_ABS    (0x7fff)   /*!< Maximum value on x-axis */
#define Y_MAX_ABS    (0x7fff)   /*!< Maximum value on y-axis */

#define X_MIN_REL    (-127)     /*!< The maximum value that we can move to the left on the x-axis */
#define Y_MIN_REL    (-127)     /*!< The maximum value that we can move up on the y-axis */
#define X_MAX_REL    (127)      /*!< The maximum value that we can move to the right on the x-axis */
#define Y_MAX_REL    (127)      /*!< The maximum value that we can move down on the y-axis */

class USBGamepad: public USBHID {
public:


    /**
    * Constructor
    */
    USBGamepad(uint16_t vendor_id = 0x1234, uint16_t product_id = 0x0002, uint16_t product_release = 0x0001):
            USBHID(0, 0, vendor_id, product_id, product_release, false)
            {
                // button = 0;
                // this->mouse_type = mouse_type;
                init();
                connect();
            };
            
    // USBGamepad(uint16_t vendor_id = 0x1234, uint16_t = 0x0001, uint16_t product_release = 0x0001);

    virtual ~USBGamepad();

    void init();

    /**
     * Write a state of the Gamepad
     * 
     * @returns true if there is no error, false otherwise
     */
    bool update(int8_t x, int8_t y, uint8_t button, int8_t z, int8_t rx);
    
    /**
     * Press one of several buttons
     * @param button button state (ex: press(GREEN))
     * @returns true if there is no error, false otherwise
     */
    bool press(uint8_t button);

    /**
     * @param button button state (ex: press(GREEN))
     * @returns true if there is no error, false otherwise
     */
    bool release(uint8_t button);

    /**
     * @param button button state (ex: press(GREEN))
     * @returns true if there is no error, false otherwise
     */
    bool click(uint8_t button);

    /**
     * @returns true if there is no error, false otherwise
     * @param joystick selector ( ex: joystick(JOY_LEFT) )
     * @param x value of x-axis
     * @param y vale of y-axis
     */
    bool joystick(uint8_t joy, uint8_t x, uint8_t y);

    virtual uint8_t * reportDesc();
    
protected:

   //  virtual const uint8_t *configuration_desc(uint8_t index);

private:
    uint8_t _button;
    // uint8_t _configuration_descriptor[41];

    bool gamepad_send(int8_t x, int8_t y, uint8_t buttons, int8_t z, int8_t rx);

};

#endif
