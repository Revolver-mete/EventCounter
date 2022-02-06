/*
 * File:   E_counter.c
 * Author: Revolver
 *
 * Created on January 29, 2022, 10:24 PM
 */

#include <xc.h>
#include "config.h"
#include <stdio.h>
#define _XTAL_FREQ 8000000

#define RS PORTCbits.RC0
#define RW PORTCbits.RC1
#define EN PORTCbits.RC2

void lcd_data(unsigned char data){
    
    PORTD = data;
    RS =1;
    RW =0;
    EN =1;
    __delay_ms(5);
    EN =0;
}
void lcd_cmd(unsigned char cmd){
    
    PORTD = cmd;
    RS =0;
    RW =0;
    EN =1;
    __delay_ms(5);
    EN =0;
}
void lcd_string(const unsigned char *str,unsigned char num){
    
    unsigned char i=0;
    for(int i=0;i<num;i++){
        lcd_data(str[i]);
    }
}
void lcd_initialiser(){
    
    lcd_cmd(0x38); // 16x2
    lcd_cmd(0x06);
    lcd_cmd(0x0C);   // display on cursor off
//    lcd_cmd(0x0F)
    lcd_cmd(0x01);   // LCD clear
    
}


void main(void) {
    OSCCON=0b01100100;
    TRISB = 0xFF;
    ANSELB = 0x00;
    TRISA = 0x00;
    ANSELA = 0x00;
//    this are for LCD left
    TRISC = 0x00;
    ANSELC = 0x00;
    TRISD = 0x00;
    ANSELD = 0x00;
   
    lcd_initialiser();
    char buf[10]; // used to store
    int count =0;
    lcd_cmd(0x83);      // first row third colum of LCD EMBEDDED
    lcd_string("No.Of Cars",11);
    
    for(;;){
            sprintf(buf,"%d",count);
            lcd_cmd(0xCA);
            lcd_string(buf,10);
            
            ///////////////////////////////////////////
            
        if(PORTBbits.RB0&&PORTBbits.RB1){//When the button is  pressed the LED is off
            PORTAbits.RA0 =1;
            PORTAbits.RA1 =1;
            count=count++; 
            while(PORTBbits.RB0&&PORTBbits.RB1);
        }
            else  {
                PORTAbits.RA0=0;
                PORTAbits.RA1=0;       
            }
            
            ///////////////////////////////////////////
            
            
            ////////////////////////////////////
        if (count > 2){//if count =20 aka 20 button presses the LED turns on
            lcd_cmd(0x01);   // LCD clear
            lcd_cmd(0x83);
            lcd_string("Full Capacity",13);
        }
        else{
            PORTAbits.RA0=0;
        }
            PORTBbits.RB0==0;
        }
    }

