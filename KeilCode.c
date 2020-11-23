#include<reg51.h>
#define lcd_data P2
sbit rs = P0^0;
sbit rw=  P0^1;
sbit en = P0^2;


sbit rel_pin=P1^3;
sbit sensor_pin= P1^0;

void lcd_init();
void cmd(unsigned char a);
void dat(unsigned char b);
void show(unsigned char *s);
void lcd_delay();
 
void lcd_init()
{
    cmd(0x38);
    cmd(0x0e);
    cmd(0x01);
    cmd(0x06);
    cmd(0x0c);
    cmd(0x80);
}
 
void cmd(unsigned char a)
{
    lcd_data=a;
    rs=0;
    rw=0;
    en=1;
    lcd_delay();
    en=0;
}
 
void dat(unsigned char b)
{
    lcd_data=b;
    rs=1;
    rw=0;
    en=1;
    lcd_delay();
    en=0;
}
 
void show(unsigned char *s)
{
    while(*s) {
        dat(*s++);
    }
}
 
void lcd_delay (unsigned int ms)
{
  int i, j;
  for (i = 0; i < ms; i++)
    for (j = 0; j < 1275; j++);
}



void main(void)
{
  sensor_pin=1;
   rel_pin=1;
   lcd_init();
   cmd (0x80);
  show(" DRUNK DRIVE");
  cmd (0xc0);
  show(" BASED");
  lcd_delay (100);
  cmd (0x01);
  cmd (0x80);
  show(" ENGINE LOCK");
  cmd (0xc0);
  show(" SYSTEM ");
  lcd_delay (100);
  cmd (0x01);
   
 while(1)
 {
   if(sensor_pin==0)
   {
      
     rel_pin=0;//on
     cmd (0x80);
     show("ALOCHOL DETECTED");
     cmd (0xc0);
     show(" BUZZER ON ");
     lcd_delay (50);
     cmd (0x01);
   }
   
   else 
   {
     rel_pin = 1;//off
     cmd (0x80);
     show(" NO ALOCHOL");
     cmd (0xc0);
     show (" BUZZER OFF");
     lcd_delay(50);
     cmd(0x01);
   }
 }
}