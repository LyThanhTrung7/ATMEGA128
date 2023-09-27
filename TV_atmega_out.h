

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

//define

#define EX_MEN_ADD 0x1100

// cs offset
//chan

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

// define enternal device ( input) 
#define LED0 *(unsigned char *)(EX_MEN_ADD + CS0) // GOI LED 0 TRO VAO GIA TRI BEN NGOAI (1100+0)
#define LED1 *(unsigned char *)(EX_MEN_ADD + CS1) // GOI LED 1 TRO VAO GIA TRI BEN NGOAI (1100+1)
#define LED2 *(unsigned char *)(EX_MEN_ADD + CS2) // GOI LED 2 TRO VAO GIA TRI BEN NGOAI (1100+2)
#define LED3 *(unsigned char *)(EX_MEN_ADD + CS3) // GOI LED 3 TRO VAO GIA TRI BEN NGOAI (1100+3)

#define LED7D1 *(unsigned char *) (EX_MEN_ADD+CS4)
#define LED7D2 *(unsigned char *) (EX_MEN_ADD+CS5)
#define LED7D3 *(unsigned char *) (EX_MEN_ADD+CS6)
#define LED7D4 *(unsigned char *) (EX_MEN_ADD+CS7)

#define RELAY_ACTIVATION (*(unsigned char *)(EX_MEN_ADD+CS10) = *( unsigned char *)(&relays)) // output
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

#define LCDE_H (PORTG |= (1<<3))
#define LCDE_L (PORTG &= ~(1<<3))
#define LCD_DATA *(unsigned char *)(EX_MEN_ADD+CS11) 
#define LCD_INS *(unsigned char *)(EX_MEN_ADD+CS12)

#define Motors_Activate (*(volatile unsigned char *)(EX_MEN_ADD+CS13) = *(unsigned char *)(&Motors)) // output
#define STOP 0
#define FORWARD 1
#define REWARD 2
struct Motor {
unsigned char DC2 : 2 ;
unsigned char DC1: 2;
unsigned char DCFree: 4;
};
struct Motor Motors ;


//volatile: giup cho du lieu dua vao duoc coi nhu 1 du lieu moi trach viec lap lai tt ban dau 
#define READKEY (*(unsigned char *)(&Buttons) =*(volatile unsigned char *)(EX_MEN_ADD+CS14)) // input
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

