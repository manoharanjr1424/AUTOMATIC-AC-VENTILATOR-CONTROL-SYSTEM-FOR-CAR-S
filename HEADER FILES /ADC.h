#include "config.h"
#include "ADC.h"
#include "lcd.h"
#include <xc.h>
#define _XTAL_FREQ 20000000
unsigned char init[]={"CAR_TEMP:"};
unsigned int readdata,msb,lsb,finalresult,temp,i;
void adc_initialize()
{
    TRISA=0x01;
    ADCON0=0x81;
    ADCON1=0x8E; 
    CCP1CON|=0x0C;
    setcursor(1,1);
    while(init[i]!='\0')
    {
        data(init[i]);
        i++;
    }
    setcursor(1,12);
        data('*');
        data('C');
}
int adc_read()
{
    ADCON0|=0x04;
    while(ADCON0&0x04);
    msb=ADRESH;
    lsb=ADRESL;
    readdata=(((unsigned int)lsb)+((unsigned int)msb<<8));
    __delay_ms(10);
    return readdata;
}
int adc_conversion()
{
    adc_initialize();
    temp=adc_read();
    finalresult=temp*51/1024;
    conversion(finalresult);
    temp_level();
   
}

void temp_level()
{
    unsigned char high[]={"TEMP IS HIGH"},
            medium[]={"TEMP IS MEDIUM"},
            low[]={"TEMP IS LOW"};
    setcursor(2,1);
    if(finalresult>=0&&finalresult<16)
    {
        while(int i<12)
        {
            data(low[i]);
            i++;
        }
    }
    else if(finalresult>=16&&finalresult<35)
        {
        while(int i<15)
        {
            data(medium[i]);
            i++;
        }
    }
     else if(finalresult>=35&&finalresult<50)
        {
        while(int i<13)
        {
            data(high[i]);
            i++;
        }
    }
}

