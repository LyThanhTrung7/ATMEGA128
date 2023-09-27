/* he thong canh bao nhiet do, do am 
 * - khi nhiet do, do am vuot nguong cho phep relay, dong co bat
 * - LCD hien thi trang thai ON/ OFF, gia tri nhiet do, do am 
 */
#include"TV_atmega_out.h"
#include<avr/io.h>
#include<stdio.h>
#include <avr/interrupt.h>
#include<util/delay.h>
#define F_CPU 8000000UL

int  nhietdo1,doam1, t;
unsigned char nhietdo2[7],doam2[7],doam3[7],nhietdo3[7];
////////////////////////////////////LCD/////////////////////////////////////////
void LCD_Khoi_tao(){ 
LCD_INS =0x38 ;LCDE_H ;_delay_us(1); LCDE_L; _delay_us(1);
_delay_us(200) ;
LCD_INS =0x0c ; LCDE_H ;_delay_us(1); LCDE_L; _delay_us(1);
_delay_us(200) ;
LCD_INS =0x06 ; LCDE_H ;_delay_us(1); LCDE_L; _delay_us(1);
_delay_us(200) ;
LCD_INS =0x01 ; LCDE_H ;_delay_us(1); LCDE_L; _delay_us(1);
_delay_ms(20) ;
}

void Print_LCD(const char *str,unsigned char line, unsigned char col){
    unsigned char add ;
    switch (line){
        case 0: add = 0x80; break;
        case 1: add = 0xC0; break;
        case 2: add = 0x94; break;
        case 3: add = 0xD4; break;
    }
    LCD_INS = add + col ;LCDE_H ;_delay_us(1); LCDE_L; _delay_us(50); 

    while(*(str)!='\0' ) 
      {
        LCD_DATA = *str++ ;LCDE_H ;_delay_us(1); LCDE_L; _delay_us(10);
      }   
}
///////////////////////////////////////////////////ADC/////////////////////////////////////////
int read_adc(unsigned int kenh_adc){
    ADMUX = kenh_adc| (1<<REFS0); // dua tg REFSO len 1 
    ADCSRA|=(1<<ADSC); 
    loop_until_bit_is_set(ADCSRA, ADIF);
    return ADCW;
}
///////////////////////////////////////////////LM35///////////////////////////////
int nhiet_do(){
    nhietdo1 =(int)(read_adc(0)/3.41); 
    sprintf(nhietdo2,"%d\337C", (int)nhietdo1);  
}
int do_am(){
    doam1 =(int)(read_adc(1)/3.41); 
    sprintf(doam2,"%d\337C", (int)doam1);
}
//////////////////////////DC,relay//////////////////////////
void trang_thai(){
    if(nhietdo1>=35){
        Motors.DC1=1;
        relays.relay.RL0=1;
        nhietdo3[3]="ON ";
    }
    if(nhietdo1<35){
         Motors.DC1=0;
        relays.relay.RL0=0;
        nhietdo3[3]="OFF";
     }
    if(doam1>=50){
        Motors.DC2=1;
        relays.relay.RL1=1;
        doam3[3]="ON ";
    }
    if(doam1<50){
         Motors.DC2=0;
        relays.relay.RL1=0;
        doam3[3]="OFF";
     }
    
    Motors_Activate;
    RELAY_ACTIVATION;
}
///////////////////////////LCD//////////////
void screen0(){
    Print_LCD("MENU_1:",0,6);
    Print_LCD("nhietdo: ",1,0);
    Print_LCD(nhietdo2,1,8); nhiet_do();
    Print_LCD("do am: ",2,0);
    Print_LCD(doam2,2,8); do_am();
    Print_LCD("DC1: ",3,0);
    Print_LCD("DC2: ",3,9);
    Print_LCD(nhietdo3[3],3,4);
    Print_LCD(doam3[3],3,13);
}
void main(void) {
    MCUCR |=0x80; 
    ADMUX|=(1<<REFS0);
    ADCSRA|=(1<<ADEN)|(1<<ADPS1)|(1<<ADPS0);
    DDRG =0xff;
    LCD_Khoi_tao();
    while(1){
        screen0();
        trang_thai();
    }
    return 0;
}   
 