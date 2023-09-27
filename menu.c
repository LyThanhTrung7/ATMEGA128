/*MENU hien thi tren LCD 
 * dieu khien dong,trang thai man hinh LCD co thong qua button 
 * left: quay lai
 * right: tieng toi 
 * up,down: len, xuong
 * go: thuc hien chuc nang bat, tat relay va dong co.
 */
#include <xc.h>
#include<stddef.h> // for NULL popinter
#include "menu.h"
#define F_CPU 1000000
#include<util/delay.h>
unsigned char select;
////////////////////////////////LCD/////////////////////////////
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

    while(*(str)!='\0' ) // contro den space
      {
        LCD_DATA = *str++ ;LCDE_H ;_delay_us(1); LCDE_L; _delay_us(10);
      }  
}
void LCD_CLEAR(){
    LCD_INS =0x01 ; LCDE_H ;_delay_us(1); LCDE_L; _delay_us(1);
}

//////////////////////////////////////////////////////
void menu_display(Menu *menu, unsigned char select){
    Print_LCD(menu->Title,0,0);
    Print_LCD(menu->List1,1,0);
    Print_LCD(menu->List2,2,0);  
    Print_LCD(menu->List3,3,0);  
    Print_LCD(">",select,0);  
}

void main(void) {
    
    Menu *menu;
    select = 1;
    MCUCR |= 0x80; // external memory wait states ON, 1 wait state
    XMCRA = 0;
    DDRG =0x0f;
    menu = &MainMenu;
    LCD_Khoi_tao(); 
    menu_display(menu,select);
    while(1){
           READKEY ;
        if (!Buttons.DOWN){
            while(!Buttons.DOWN) READKEY ;
            select = (select==3)?1:select+1 ;
            menu_display(menu,select);
        }
        if (!Buttons.UP){
            while(!Buttons.UP) READKEY ;
            select = (select==1)?3:select-1 ;
            menu_display(menu,select); 
        }
        if (!Buttons.RIGHT){
            while(!Buttons.RIGHT) READKEY ;
            LCD_CLEAR();
            switch (select){
                case 1:menu=(menu->MenuList1==NULL)?menu:menu->MenuList1;break; 
                case 2:menu=(menu->MenuList2==NULL)?menu:menu->MenuList2;break;
                case 3:menu=(menu->MenuList3==NULL)?menu:menu->MenuList3;break;
            }
                   menu_display(menu,select);
            } 
        
        if (!Buttons.LEFT){
            while(!Buttons.LEFT) READKEY ;
             menu=(menu->pre==NULL)?menu:menu->pre;
              LCD_CLEAR();
             menu_display(menu,select);
        } 
        if (!Buttons.GO){ 
              while(!Buttons.GO) READKEY ;
              switch(select){
              case 1:
                  if(menu->activation_on!=NULL)menu->activation_off(menu->MenuID,ON);
                  break;
              case 2:
                  if(menu->activation_on!=NULL)menu->activation_off(menu->MenuID,OFF);
                  break;
              }
        }
    }
    return;
}
