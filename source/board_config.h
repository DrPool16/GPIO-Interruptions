/*! @file : board_config.h
 * @author  Cristian Eduardo Silva Abril
 * @version 1.0.0
 * @date    31 mar. 2026
 * @brief   Driver para 
 * @details
 *
 */
/**
 * @file    board_config.h
 * @brief   Definiciones de hardware para FRDM-K32L2B3.
 *
 * @details Centraliza todos los pines y periféricos usados en el
 *          proyecto. Modificar solo este archivo al cambiar de placa.
 *
 * @author  Tu nombre
 * @date    2025-XX-XX
 */

#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#include "fsl_common.h"

/* ----------------------------------------------------------------
 * LED VERDE
 * Fuente: Esquemático FRDM-K32L2B3, sheet X
 * ---------------------------------------------------------------- */

/** @brief Instancia GPIO del LED verde */
#define LED_GREEN_GPIO          GPIOD

/** @brief Puerto (PORT) del LED verde */
#define LED_GREEN_PORT          PORTD

/** @brief Número de pin del LED verde */
#define LED_GREEN_PIN           (5U)

/** @brief Máscara SIM_SCGC5 para habilitar clock del PORT del LED */
#define LED_GREEN_PORT_CLOCK    SIM_SCGC5_PORTD_MASK


/* ----------------------------------------------------------------
 * BOTÓN SW3
 * Fuente: Esquemático FRDM-K32L2B3, sheet X
 * ---------------------------------------------------------------- */

/** @brief Instancia GPIO del botón SW3 */
#define BTN_SW3_GPIO            GPIOC

/** @brief Puerto (PORT) del botón SW3 */
#define BTN_SW3_PORT            PORTC

/** @brief Número de pin del botón SW3 */
#define BTN_SW3_PIN             3U

/** @brief Máscara SIM_SCGC5 para habilitar clock del PORT del botón */
#define BTN_SW3_PORT_CLOCK      SIM_SCGC5_PORTC_MASK

/** @brief IRQ number del PORT del botón (para NVIC) */
#define BTN_SW3_IRQn            PORTC_PORTD_IRQn

/** @brief Prioridad de la interrupción del botón (0=más alta, 3=más baja) */
#define BTN_SW3_IRQ_PRIORITY    (2U)

/** @brief Tiempo mínimo entre pulsaciones válidas en ms (debounce) */
#define BTN_DEBOUNCE_MS         (50U)

#endif /* BOARD_CONFIG_H */
