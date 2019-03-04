//R. R. Otero, “SAM4S Xplained Pro ADC Demo,” Embedded Networks. [Online]. 
//Available: http://embedntks.com/project/sam4s-xpro-adc-demo/. [Accessed: 29-Nov-2018].
//Inspiration from the above source

#include <string.h>
#include <asf.h>

int main(void){
		
	bool light_left_on = false;
	bool light_right_on = false;
	bool light_game_over = false;
	bool game_over = false;
	bool game_start = false;
	
	volatile uint32_t points = 0;
	char pointsString[50]; 
	   
	//initialize the board
	hal_io_init();
	sysclk_init();
	
	//configure_adc();
	hal_adc_pinball_configure();

	//initializes lights
	hal_led_start_pinball();
	
	//Starts you "life" led
	hal_led_write_pinball(LedGameOver);
	
	//delay because atmel is awesome	
	delay_s(1);

	//main game loop
	while(!game_over){
		
		if(game_start)
		{
			//prints the score to the screen
			hal_display_cls();
			sprintf(pointsString, "%d", points);
			hal_display_putc_pinball(pointsString);
		}
	
		//turns on light one and adds 10 points
		if(hal_adc_pinball_read(2)<1000 && game_start)
		{
			light_left_on = true;
			points = points + 10;
			hal_led_write_pinball(Led0);
		}
		
		//turns on right light and adds 10 points
		if(hal_adc_pinball_read(3)<1000 && game_start)
		{
			light_right_on = true;
			points = points + 10;
			hal_led_write_pinball(Led1);		
		}
		
		
		if(hal_led_read_pinball(Led2)<1000 && game_start)
		{
			//initiate game over stuff
			hal_led_write_pinball(Led2);	
			hal_display_putc_pinball("<-Score - Game Over!");	
			while(true);
					
		}

			game_start = true;
				
		if(light_left_on)
		{
			delay_s(1);
			hal_led_write_pinball(Led0);
			light_left_on = false;
		}
				
		if(light_right_on)
		{
			delay_s(1);
			hal_led_write_pinball(Led1);		
			light_right_on = false;
		}
	}
}


/*HAL NOTES

Control of the led's is pretty much just copied and shifted over to the pins we are using from the led's on the board
Control of the adc channels is just Hallified
Method for writing to screen is similar
*/