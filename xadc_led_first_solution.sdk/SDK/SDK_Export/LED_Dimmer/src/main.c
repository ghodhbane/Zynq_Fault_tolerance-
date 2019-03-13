/*****************************************************************************/
/*                               H E A D E R                                 */
/*****************************************************************************/

// Program Name          : main.c
// Program Type          : C application program for Zynq
// Platform              : Zynq All Programmable SoC
// Board                 : ZedBoard
// Date                  : 2014-03-05

/*****************************************************************************/
/*                         I N C L U D E   F I L E S                         */
/*****************************************************************************/

#include "xparameters.h"
#include "xgpio.h"

/*****************************************************************************/
/*                           C O N S T A N T S                               */
/*****************************************************************************/

//The following constant maps to the name of the hardware instances that
// were created in the Vivado system.

#define GPIO_EXAMPLE_DEVICE_ID  XPAR_AXI_GPIO_0_DEVICE_ID

// The following constant is used to determine which channel of the GPIO is
// used for the LED if there are 2 channels supported.

#define LED_CHANNEL 1


/*****************************************************************************/
/*                            V A R I A B L E S                              */
/*****************************************************************************/


XGpio Gpio;        // The Instance of the GPIO Driver


/*****************************************************************************/
/*                                M A I N                                    */
/*****************************************************************************/


int main(void)
{
    int Status;
    u32 value           = 0;
    u32 period          = 0;
    u32 brightness      = 0;

    // Initialize the GPIO driver

    Status = XGpio_Initialize(&Gpio, GPIO_EXAMPLE_DEVICE_ID);
    if (Status != XST_SUCCESS) {
        return XST_FAILURE;
    }

    // Clear the LEDs
    XGpio_DiscreteWrite(&Gpio, LED_CHANNEL, 0);

    while (1) {
       print(" Select a Brightness between 0 and 9 : ");
       value = inbyte();
       period = value - 0x30;
       xil_printf("Brightness Level %d selected ", period);

       // Since the LED width is 1e6 clk cycles, we need to normalize
       // the period to that clk.  Since we accept values 0-9, that will
       // scale period from 0-999,000.  0 turns off LEDs, 999,000 is full
       // brightness

       brightness = period * 110000;
       // Write the duty_cycle width (Period) out to the PL GPIO peripheral

       XGpio_DiscreteWrite(&Gpio, LED_CHANNEL, brightness);

    }

    return XST_SUCCESS;
}
