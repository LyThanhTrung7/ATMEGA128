/*
 * dieu khien dong co thong qua nut nhan
 * _ hien thi len led7doan trang thai: 
 * 1: DC xoay cung chieu
 * 0 : DC tat
 * 2: DC xoay nguoc
 * button left: dk dong co 1
 * button right: dk dong co 2
 */
#include <xc.h>
#include "DC_ngoai.h"
#define F_CPU 1000000
#include<util/delay.h>
unsigned char SegCode[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E};
unsigned int i=0;
unsigned int j=0;

void phimnhan(){
    READKEY;
    if( Buttons.GO==0){
            while(!Buttons.GO) READKEY;
            i++;
            if(i>3)
                i=0;
           
        }
        if( Buttons.LEFT==0){
            while(!Buttons.LEFT) READKEY;
            j++;
            if(j>3)
                j=0;
        }
}

void dongco1(){
        if(i==0){
            Motors.DC1=0;
            LED7D1=SegCode[0];}
        if(i==1){ 
            Motors.DC1=1;
            LED7D1=SegCode[1];}
        if(i==2){
            Motors.DC1=0;
            LED7D1=SegCode[0];}
        if(i==3){
            Motors.DC1=2;
            LED7D1=SegCode[2];}
        Motors_Activate;
       
}
void dongco2(){
        if(j==0){
            Motors.DC2=0;
            LED7D4=SegCode[0];}
        if(j==1){ 
            Motors.DC2=1;
            LED7D4=SegCode[1];}
        if(j==2){
            Motors.DC2=0;
            LED7D4=SegCode[0];}
        if(j==3){
            Motors.DC2=2;
            LED7D4=SegCode[2];}
        Motors_Activate;
}
void main(void) {
    MCUCR = 0x80; // external memory wait states ON, 1wait state
    XMCRA = 0;
    while(1){
        phimnhan();
        dongco1();
        dongco2();
        Motors_Activate;
    }
    return;
}