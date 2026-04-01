#include <stdio.h>
#include <stdbool.h>
#include <K32L2B31A.h>
#include <gpio_driver.h>
#include <board_config.h>




int main(void) {

	GPIO_Driver_Init();

	while(1){
		if(GPIO_Driver_ButtonPressed() == true){
			GPIO_Driver_toggleLED();
		}
	}
    return 0 ;
}
