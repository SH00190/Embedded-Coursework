#include <avr/io.h> // Importing necessary libraries for the required functions
#include <util/delay.h> 
#include "adc.h" 

void init(); 

int main(void){        //main code 
  init();     //calls the void init function at the bottom
  Serial.begin(9600);  
  
  while (1)  //infinite loop 
  {
      int button = PIND & (1 << 7) ;   //checking port 7 if the switch has been flipped
      Serial.println(button);

     if(button)       //if statement for the switch
     {
       PORTB = PORTB & ~(1 << 2);
     }
     else
     {
       PORTB = PORTB | (1 << 2);
     }


    unsigned short a = Adc_ReadChannel(0);   //potentiometer values saved in variable a

    if( a == 0)     //if statement for potentiometer 
    {
      
      PORTB = PORTB & ~(1 << 0);    //leds are off
      PORTB = PORTB & ~(1 << 1);    //leds are off
      //_delay_ms(1000);
    }
    else if (a < 200)  //
    {
      PORTB = PORTB | (1 << 1);    //led is on
      PORTB = PORTB & ~(1 << 0);  //led is off
      //_delay_ms(1000);
    }
    
    else
    {
       PORTB = PORTB | (1 << 0);    //led is off
      PORTB = PORTB & ~(1 << 1);   //led is on
      //_delay_ms(1000);
    }

  }
return 0;
}

void init(){
  DDRC = 0x00; //makes all C ports inputs

  DDRB = DDRB | (1 << 0);  //switches' led is set as an output
  DDRB = DDRB | (1 << 1); //led 1 set as output


  DDRB = DDRB | (1 << 2); // led with switch


  DDRD = DDRD & !(1 << 7); //sets pin 7 as an input for switch
  PORTD = PORTD |(1 << 7);
  
  adc_Init(); //initialize ADC module with default settings
}

