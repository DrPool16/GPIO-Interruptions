/*! @file : gpio_driver.h
 * @author  Cristian Eduardo Silva Abril
 * @version 1.0.0
 * @date    31 mar. 2026
 *
 * @brief   Driver de GPIO e interrupciones para FRDM-K32L2B3.
 * @details Expone una interfaz para inicializar el LED verde y el
 *          botón SW3 con interrupción por flanco de bajada y
 *          debounce por software. No contiene lógica de aplicación.
 *
 */
#ifndef GPIO_DRIVER_H_
#define GPIO_DRIVER_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdbool.h>
#include <stdint.h>
/*******************************************************************************
 * Public Definitions
 ******************************************************************************/
typedef enum {
    LED_OFF = 0U,   /**< LED apagado */
    LED_ON  = 1U    /**< LED encendido */
} led_state_t;

// Inicializa el GPIO del LED verde y del botón SW3.
void GPIO_Driver_Init(void);

// state   LED_ON para encender, LED_OFF para apagar.
void GPIO_Driver_SetLED(led_state_t state);

// Invierte el estado actual del LED verde.
void GPIO_Driver_toggleLED(void);

// Retorna true si el botón fue presionado desde la última consulta.
bool GPIO_Driver_ButtonPressed(void);

void GPIO_Driver_SysTickCallback(void);

static uint32_t GetCurrentMs(void);

/*******************************************************************************
 * External vars
 ******************************************************************************/

/*******************************************************************************
 * Public vars
 ******************************************************************************/

/*******************************************************************************
 * Public Prototypes
 ******************************************************************************/

/** @} */ // end of X group
/** @} */ // end of X group

#endif /* GPIO_DRIVER_H_ */
