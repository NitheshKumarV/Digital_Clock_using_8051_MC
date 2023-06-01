#include <REGX51.H>// 8051 family
#include <stdio.h>
#define LCD_dat P2
sbit rs = P1^0;
/*sbit rw = P3^1;*/
sbit en = P1^2;
sbit set = P1^3;
sbit inc = P1^4;		
sbit next = P1^5;
sbit fin = P1^6;
sbit fin1 = P1^7;
void delay(unsigned int dly);
void lcd_cmd(unsigned char ch);
void lcd_data(unsigned char ch);
void lcd_str(unsigned char *str);

void main(void)
	{
	unsigned int digit = 0;
  unsigned int j,k;
	unsigned int mode = 0;
	char date1[2], mon1[2], year1[2],hrs1[2],min1[2],sec1[2];
  unsigned int date = 0;
	unsigned int mon = 0;
	unsigned int year = 22;
	unsigned int hrs = 0;
	unsigned int min = 0;
	unsigned int sec = 0;
	unsigned char am1[2]="am";
	unsigned char pm1[2]="pm";
	unsigned int am = 1;
		start:
	lcd_cmd (0x38);
	lcd_cmd (0x0e);
	lcd_cmd(0x80);
	lcd_str("Digital Clock");
	lcd_cmd(0xC0);
	lcd_str("By Group 13");
	delay(2000);
	lcd_cmd (0x01);
	lcd_cmd (0x80);
	lcd_str("Please Set Date");
	lcd_cmd(0xC0);
	lcd_str("And Time");
	delay(2000);
	lcd_cmd (0x01);
	lcd_cmd(0x0E);
	lcd_cmd (0x80);
	lcd_str("Date ");
	for(j=0;fin!=0;j++)
	{if (set == 0){mode=0;
									delay(500);}
	if (next == 0){++mode;
									delay(500);}
	if (inc==0 && mode==0){
													if(date<=30){++date;}
													else if(date>30) {date=1;}
													delay(500);
													}
	if(inc==0 && mode==1){if(mon<=11){++mon;}
													else if(mon>11) {mon=1;}
												delay(500); 
												}
	if(inc==0 && mode==2){if(year<=98){++year;}
													else if(year>98) {year=0;}
												delay(500); 
												}
												sprintf(date1,"%u",date);
												if(date>=10){
													lcd_cmd(0x85);
											    lcd_str(date1);}
												else{lcd_cmd(0x85);
														 lcd_data('0');
												     lcd_cmd(0x86);
												     lcd_str(date1);}
													lcd_cmd(0x87);
													lcd_data('/');
												  sprintf(mon1,"%u",mon);
												if(mon>=10){
													lcd_cmd(0x88);
											    lcd_str(mon1);}
												else{lcd_cmd(0x88);
														 lcd_data('0');
												     lcd_cmd(0x89);
												     lcd_str(mon1);}
													lcd_data('/');
													lcd_data('2');
													lcd_data('0');
												  sprintf(year1,"%u",year);
												if(year>=10){
													lcd_cmd(0x8d);
											    lcd_str(year1);}
												else{lcd_cmd(0x8d);
														 lcd_data('0');
												     lcd_cmd(0x8e);
												     lcd_str(year1);}
	}
	lcd_cmd(0xC0);
	lcd_cmd(0x0E);
	lcd_str("Time ");
	mode = 0;
	fin = 1;
	for(k=0;fin1!=0;k++)
	{if (set == 0){mode=0;
									delay(500);}
	if (next == 0){++mode;
									delay(500);}
	if (inc==0 && mode==0){
													if(hrs<=11){++hrs;}
													else if(hrs>11) {hrs=1;}
													delay(500);
													}
	if(inc==0 && mode==1){if(min<=58){++min;}
												else if(min>58) {min=0;}
												delay(500); 
												}
	if(inc==0 && mode==2){if(am==0){am=1;}
												else if (am==1) {am=0;}
												delay(500); 
												}
												sprintf(hrs1,"%u",hrs);
												if(hrs>=10){
													lcd_cmd(0xc5);
											    lcd_str(hrs1);}
												else{lcd_cmd(0xc5);
														 lcd_data('0');
												     lcd_cmd(0xc6);
												     lcd_str(hrs1);}
													lcd_cmd(0xc7);
													lcd_data(':');
												  sprintf(min1,"%u",min);
												if(min>=10){
													lcd_cmd(0xc8);
											    lcd_str(min1);}
												else{lcd_cmd(0xc8);
														 lcd_data('0');
												     lcd_cmd(0xc9);
												     lcd_str(min1);}
												  lcd_cmd(0xca);
													lcd_data(':');
													lcd_data('0');
													lcd_data('0');
													lcd_data(' ');
													if (am==1){lcd_str(am1);}
													if (am==0){lcd_str(pm1);}
												  
	}
	lcd_cmd(0x01);
	while(1)/*infinity loop*/
		{++ sec;
			if(sec>59){sec=0;
									++min;}
			if(min>59){min=0;
									++hrs;}
			if(hrs>12){hrs=1;
									if(am==1){am=0;}
								  if(am==0){++date;
														am=1;}
								}
			if(date>30){date=0;
									++mon;}
			if(mon>12){mon=0;
									++year;}
			if(set==0){break;}
			
	//lcd_cmd(0x01);
	lcd_cmd(0x0E);
	lcd_cmd (0x80);
	lcd_str("Date ");
			sprintf(date1,"%u",date);
			sprintf(mon1,"%u",mon);
			sprintf(year1,"%u",year);
			sprintf(hrs1,"%u",hrs);
			sprintf(min1,"%u",min);
			sprintf(sec1,"%u",sec);
			if(date>=10){lcd_cmd(0x85);
									 lcd_str(date1);}
			else{lcd_cmd(0x85);
					 lcd_data('0');
					 lcd_cmd(0x86);
					 lcd_str(date1);}
			lcd_cmd(0x87);
			lcd_data('/');
			if(mon>=10){lcd_cmd(0x88);
									lcd_str(mon1);}
			else{lcd_cmd(0x88);
					 lcd_data('0');
				   lcd_cmd(0x89);
					 lcd_str(mon1);}
			lcd_cmd(0x8a);
			lcd_data('/');
			lcd_cmd(0x8b);
			lcd_data('2');
			lcd_cmd(0x8c);
			lcd_data('0');
			if(year>=10){lcd_cmd(0x8d);
									 lcd_str(year1);}
			else{lcd_cmd(0x8d);
					 lcd_data('0');
			     lcd_cmd(0x8e);
			     lcd_str(year1);}
			lcd_cmd(0x8f);
			lcd_data(' ');
			lcd_cmd(0xc0);
			lcd_cmd(0x0E);
			lcd_str("time ");
			if(hrs>=10){lcd_cmd(0xc5);
									lcd_str(hrs1);}
			else{lcd_cmd(0xc5);
					 lcd_data('0');
					 lcd_cmd(0xc6);
					 lcd_str(hrs1);}
			lcd_cmd(0xc7);
			lcd_data(':');
			if(min>=10){lcd_cmd(0xc8);
									lcd_str(min1);}
			else{lcd_cmd(0xc8);
					 lcd_data('0');
					 lcd_cmd(0xc9);
					 lcd_str(min1);}
			lcd_cmd(0xca);
			lcd_data(':');
			if(sec>=10){lcd_cmd(0xcb);
									lcd_str(sec1);}
			else{lcd_cmd(0xcb);
					 lcd_data('0');
					 lcd_cmd(0xcc);
					 lcd_str(sec1);}
			lcd_data(' ');
			if(am==1){lcd_str(am1);}
			if(am==0){lcd_str(pm1);}
			delay(486);
			
			  
		}
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_str("Resetting");
		delay(2000);
		goto start;

  }
void lcd_str(unsigned char *str)
{
   unsigned int loop = 0;
	for(loop =0;str[loop]!='\0';loop++)
	{ 
		lcd_data(str[loop]);
	}
}

void lcd_data(unsigned char ch)
{
LCD_dat = ch;
	rs =1; // for data rs = 1
	//rw = 0; //for writing display rw =0
	en = 1;
	delay(5);
	en = 0;
}

void lcd_cmd(unsigned char ch)
{
LCD_dat = ch;
	rs = 0; //for command rs = 0
	//rw = 0; //for writing display rw =0
	en = 1;
	delay(5);
	en = 0;
}
void delay(unsigned int dly)
{
unsigned int loop = 0;
unsigned int delay_gen = 0;
	for (loop=0; loop<dly; loop++){
		for (delay_gen=0; delay_gen<115; delay_gen++);
	}
}
