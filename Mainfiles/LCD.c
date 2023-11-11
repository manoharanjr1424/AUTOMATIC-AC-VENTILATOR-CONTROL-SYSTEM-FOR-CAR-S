#include "lcd.h"
#include "config.h"
#include <xc.h>
#define _XTAL_FREQ 20000000
#define RS RC0
#define EN RC1
unsigned int ten,one,thousand,hundred;
void LCD_intialize()//Definition for the LCD_initialize function
{
    TRISC=0xC0;
    TRISD=0x00;
       cmd(0x30);//Setting the LCD in 8 Mode
      __delay_ms(100);
      cmd(0x30);//Setting the LCD in 8 Mode
      __delay_ms(100);
      cmd(0x30);//Setting the LCD in 8 Mode
      __delay_ms(100);
      cmd(0x38);//Clearing the RAM of the LCD
      __delay_ms(100);
      cmd(0x0C);//Turn On the LCD and cursor Off
      __delay_ms(100);
      cmd(0x06);//Display the From right to left 
      __delay_ms(100);
      cmd(0x01);//clear display
      __delay_ms(100);
}
void data(unsigned char a)//definition for LCD_data function
{
    RS=1;//Enable the Register select pin
    PORTD=a;//Assign the data to the PORTD
    EN=1;//Enable the Enable pin
    __delay_ms(10);
    EN=0;//Disable the Enable pin
}

void cmd(unsigned char b)
{
    RS=0;//Disable the Register Select pin
    PORTD=b;//Assign the data to the PORTD
    EN=1;//Enable the Enable pin
    __delay_ms(10);
    EN=0;//Disable the Enable pin
}

void setcursor(unsigned int x,unsigned int y)
{
    if(x==1)
        cmd(0x80+(y-1));
    else if(x>1)
        cmd(0xC0+(y-1));
}

void conversion(unsigned int cov)
{
    setcursor(1,10);
    if(cov<10)
    {
        data((0x30+cov));
        data("");
    }
    else 
    {
        ten=(cov/10);
        cov%=10;
        one=cov;  
        data((0x30+ten));
        data((0x30+one));
    }
}
