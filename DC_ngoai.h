#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h>
#define EXMEM_ADD 0x1100
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

#define LED7D1 *(unsigned char *) (EXMEM_ADD+CS4)
#define LED7D2 *(unsigned char *) (EXMEM_ADD+CS5)
#define LED7D3 *(unsigned char *) (EXMEM_ADD+CS6)
#define LED7D4 *(unsigned char *) (EXMEM_ADD+CS7)


#define READKEY (*(unsigned char *)(&Buttons) =*(volatile unsigned char *)(EXMEM_ADD+CS14))
struct Button{
unsigned char LEFT : 1 ;
unsigned char RIGHT : 1 ;
unsigned char UP : 1 ;
unsigned char DOWN : 1 ;
unsigned char GO : 1 ;
unsigned char BTN1 : 1 ;
unsigned char BTN2 : 1 ;
unsigned char BTN3 : 1 ;
};
struct Button Buttons;

#define Motors_Activate (*(volatile unsigned char *)(EXMEM_ADD+CS13) = *(unsigned char *)(&Motors))
#define STOP 0
#define FORWARD 1
#define REWARD 2

struct Motor {
unsigned char DC1 : 2 ;
unsigned char DC2: 2;
unsigned char DCFree: 4;
};
struct Motor Motors ;


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */