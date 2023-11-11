

#include <xc.h>
#include "ADC.h"
#include "config.h"
#include "lcd.h"
#define _XTAL_FREQ 20000000
void main(void) {
    LCD_intialize();
    setcursor(1,5);
    while(1)
    {
       adc_conversion();
    }
}
