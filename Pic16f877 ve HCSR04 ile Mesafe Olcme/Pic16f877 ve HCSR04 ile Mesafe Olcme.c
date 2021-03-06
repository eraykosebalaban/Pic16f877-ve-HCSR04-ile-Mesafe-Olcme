#include<16f877.h>

#fuses HS,NOWDT,NOPUT,NOLVP,NOCPD,NOPROTECT,NODEBUG,NOBROWNOUT,NOWRT 

#use delay(clock = 4000000)

#define use_portb_lcd TRUE
#include<lcd.c>

#use fast_io(a)

#use rs232(baud=9600, xmit=pin_c6, rcv=pin_c7, parity=N, stop=1)

#define trigger pin_a0
#define echo input(pin_a1)

unsigned int mesafe;

void main(){
setup_psp(PSP_DISABLED);
setup_timer_1(T1_DISABLED);
setup_timer_2(T2_DISABLED,0,1);
setup_ccp1(CCP_OFF);
setup_ccp2(CCP_OFF);

set_tris_a(0x02);

lcd_init();

while(true){

output_high(trigger); //Mesafe sensörünü tetikliyoruz.
delay_us(20);
output_low(trigger);

while(echo==0);

while(echo==1){ // echo pini aktif olduğunda yapılacakları belirtiyoruz.

mesafe=mesafe+1; // mesafeyi her seferinde 1 artıyırouz.
delay_us(50);

}
delay_ms(200);

if(mesafe>70){

printf(lcd_putc,"\fMenzil disinda");
delay_ms(500);

}

else{
printf(lcd_putc,"\fMesafe:%1d cm",mesafe);
delay_ms(200);
mesafe=0;
}

}

}
