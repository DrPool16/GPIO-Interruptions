/*! @file : gpio_driver.c
 * @author  Cristian Eduardo Silva Abril
 * @version 1.0.0
 * @date    31 mar. 2026
 * @brief   Driver para 
 * @details
 *
*/
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <gpio_driver.h>
#include <board_config.h>
#include <K32L2B31A.h>

/* SDK NXP — estas son las que necesitas */
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Private Prototypes
 ******************************************************************************/
static volatile bool s_buttonFlag = false;

static volatile uint32_t s_lastPressTime = 0U;

volatile uint32_t s_msTicks = 0U;

uint32_t tiempo_actual;


/*******************************************************************************
 * External vars
 ******************************************************************************/


/*******************************************************************************
 * Local vars
 ******************************************************************************/


/*******************************************************************************
 * Private Source Code
 ******************************************************************************/


/*******************************************************************************
 * Public Source Code
 ******************************************************************************/
void GPIO_Driver_SysTickCallback(void)
{
    s_msTicks++;
}

static uint32_t GetCurrentMs(void)
{
    return s_msTicks;
}


 void GPIO_Driver_Init(void){
	 /* PASO 1 — Habilitar clocks de los PORTs via SIM_SCGC5 */
	 SIM->SCGC5 |= LED_GREEN_PORT_CLOCK | BTN_SW3_PORT_CLOCK;

	 /* PASO 2 — Configurar PCR del LED */
	 LED_GREEN_PORT->PCR[LED_GREEN_PIN] = PORT_PCR_MUX(1);		//PIN LED_GREEN

	 /* PASO 3 — Configurar PCR del botón SW3 */
	 BTN_SW3_PORT->PCR[BTN_SW3_PIN] = PORT_PCR_MUX(1) |			// PIN BUTTON SW3 |
			 	 	 	 	 	 	  PORT_PCR_PE(1)  |			// PULL-UP ENABLE |
									  PORT_PCR_PS(1)  |			// PULL SELECT	  |
									  PORT_PCR_IRQC(11);		// ISF flag and Interrupt on falling-edge.

	 /* PASO 4 — Configurar GPIO del LED y el botón*/
	 LED_GREEN_GPIO->PDDR |= (1 << 5);
	 LED_GREEN_GPIO->PSOR = (1 << 5);

	 BTN_SW3_GPIO->PDDR &= (0 << 3);

	 /* PASO 5 — Habilitar IRQ en el NVIC*/
	 NVIC_SetPriority(BTN_SW3_IRQn, BTN_SW3_IRQ_PRIORITY);
	 EnableIRQ(BTN_SW3_IRQn);

	 SysTick_Config(SystemCoreClock / 1000U);

 }

 void GPIO_Driver_SetLED(led_state_t state){
	if(LED_ON){
		LED_GREEN_GPIO->PCOR = (1 << 5);
	}else{
		LED_GREEN_GPIO->PSOR = (1 << 5);
	}
 }

 void GPIO_Driver_toggleLED(void){
		LED_GREEN_GPIO->PCOR = (1 << 5);
		for(int i = 0; i <300000; i++);
		LED_GREEN_GPIO->PSOR = (1 << 5);
		for(int j = 0; j <300000; j++);

 }

bool GPIO_Driver_ButtonPressed(void){
	 if(s_buttonFlag == false) return false;

	 tiempo_actual = GetCurrentMs();
	 if(s_buttonFlag == true){
		 if((tiempo_actual - s_lastPressTime) < BTN_DEBOUNCE_MS){
			 s_buttonFlag = false;
			 return false;
		 }
	 }else{
		 s_lastPressTime = tiempo_actual;
		 s_buttonFlag    = false;
		 return true;
	 }
}









