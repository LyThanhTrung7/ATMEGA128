#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H
#include<stddef.h> // for NULL popinter
#include <xc.h>

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

#define EXMEM_ADD 0x1100
#define porta *(unsigned char *)0x3B
#define EXMEM *(unsigned short *) (EXMEM_ADD+0)
// CS offset
#define CS0 0
#define CS1 1
#define CS2 2
#define CS3 3
#define CS4 4
#define CS5 5
#define CS6 6
#define CS7 7
#define CS8 8
#define CS9 9
#define CS10 10
#define CS11 11
#define CS12 12
#define CS13 13
#define CS14 14
#define CS15 15
#define CS16 16
#define CS17 17
#define CS18 18
#define CS19 19
//define external device
#define LCDE_H (PORTG |= (1<<3))
#define LCDE_L (PORTG &= ~(1<<3))


#define LED0 *(unsigned char *)(EXMEM_ADD + CS0) // GOI LED 0 TRO VAO GIA TRI BEN NGOAI (1100+0)
#define LED1 *(unsigned char *)(EXMEM_ADD + CS1) // GOI LED 1 TRO VAO GIA TRI BEN NGOAI (1100+1)
#define LED2 *(unsigned char *)(EXMEM_ADD + CS2) // GOI LED 2 TRO VAO GIA TRI BEN NGOAI (1100+2)
#define LED3 *(unsigned char *)(EXMEM_ADD + CS3) // GOI LED 3 TRO VAO GIA TRI BEN NGOAI (1100+3)

#define LED7D1 *(unsigned char *) (EXMEM_ADD+CS4)
#define LED7D2 *(unsigned char *) (EXMEM_ADD+CS5)
#define LED7D3 *(unsigned char *) (EXMEM_ADD+CS6)
#define LED7D4 *(unsigned char *) (EXMEM_ADD+CS7)

#define LED7IDCTR *(unsigned char *) (EX_MEN_ADD+CS8)  // dk 
#define LED7IDDATA *(unsigned char *) (EX_MEN_ADD+CS9)  // data

#define RELAY_ACTIVATION (*(unsigned char *)(EXMEM_ADD+CS10) = *( unsigned char *)(&relays))
#define LCD_DATA *(unsigned char *)(EXMEM_ADD+ CS11) 
#define LCD_INS *(unsigned char *)(EXMEM_ADD+ CS12)

#define Motors_Activate (*(volatile unsigned char *)(EXMEM_ADD+CS13) = *(unsigned char *)(&Motors))
#define READKEY (*(unsigned char *)(&Buttons) =*(volatile unsigned char *)(EXMEM_ADD+CS14))

#define STOP 0
#define FORWARD 1
#define REWARD 2

struct Motor {
unsigned char DC1 : 2 ;
unsigned char DC2: 2;
unsigned char DCFree: 4;
};
struct Motor Motors ;

struct bits{
unsigned char RL0 : 1 ;
unsigned char RL1 : 1 ;
unsigned char RL2 : 1 ;
unsigned char RL3 : 1 ;
unsigned char RL4 : 1 ;
unsigned char RL5 : 1 ;
unsigned char RL6 : 1 ;
unsigned char RL7 : 1 ;
};

union RL{
    unsigned char relayall;
    struct bits relay;
};
union RL relays;

struct Button{
unsigned char LEFT  : 1 ;
unsigned char RIGHT : 1 ;
unsigned char UP    : 1 ;
unsigned char DOWN  : 1 ;
unsigned char GO    : 1 ;
unsigned char BTN1  : 1 ;
unsigned char BTN2  : 1 ;
unsigned char BTN3  : 1 ;
};
struct Button Buttons;

////////////////////////////
#define ON  1
#define OFF 0
#define Device_Relay  0
#define Device_Motor1 1
#define Device_Motor2 2
#define Device_Led    3

void actuators_activation(char devices, char tt)
{
    switch(devices){
        case Device_Relay: 
            if(tt) relays.relayall = 0xff;
            else relays.relayall = 0x00;
            RELAY_ACTIVATION; 
            break;
        case Device_Motor1: Motors.DC1 = tt; Motors_Activate;
             break;
        case Device_Motor2: Motors.DC2 = tt; Motors_Activate;
             break; 
        case Device_Led: 
            if(tt==ON) LED0 = 0xff;
            else LED0 = 0x00;
            break;     
    }
}

typedef struct linker {
    char MenuID;
    struct linker *pre ;
    char Title[20];
    char List1[20];
    struct linker *MenuList1; void (*activation_on)(char, char);
    char List2[20];
    struct linker *MenuList2; void(*activation_off)(char, char);
    char List3[20];
    struct linker *MenuList3;
} Menu ;
Menu MainMenu,xem_mode,DK_relay,DK_dongco,bat_tat_relay,bat_tat_DC;

//////////// TOTAL MENU (SCREEN 1) ////////////
Menu MainMenu = {
NULL,
NULL,
        " --Main Menu-- " ,
        " Xem mode hoat dong" , &xem_mode,NULL,
        " DK relay" , &DK_relay, NULL,
        " DK dong co " , &DK_dongco,
}; 
//////////list 1 //////////////////
Menu xem_mode = {
    NULL,
&MainMenu,
        " xem mode HD" ,
        " Dang: Manual" ,NULL,NULL,
        " Quay lai " ,&MainMenu,NULL,
};
///////LIST 2////////////
Menu DK_relay = {
    NULL,
    &MainMenu,
            " --DK relay-- " ,
            " HT: Manual " , NULL,NULL,
            " Bat/tat relay  " ,&bat_tat_relay,NULL,
            " Quay lai" , &MainMenu,
};

Menu bat_tat_relay = {
    Device_Relay,  
    &DK_relay,
            " --Bat/tat relay--" ,
            " ON " , NULL, &actuators_activation,
            " OFF " , NULL, &actuators_activation,
            " Quay lai " ,&DK_relay,
};
///////LIST 3////////////
Menu DK_dongco = {
    NULL,
&MainMenu,
        "  --DK dong co--" ,
        " HT: Manual",NULL,NULL,
        " Bat/Tat DC" ,&bat_tat_DC,NULL,
        " Quay lai" ,&MainMenu,
};
Menu bat_tat_DC= {
Device_Motor1,     
&DK_dongco,
        " --Bat/tat DC--" ,
        " ON " , NULL, &actuators_activation,
        " OFF " , NULL, &actuators_activation,
        " Quay lai " ,&DK_dongco,
};


