# GPIO + Interrupciones — FRDM-K32L2B3

Proyecto de aprendizaje de sistemas embebidos: manejo de GPIO y interrupciones externas sobre la placa **NXP FRDM-K32L2B3** (familia Kinetis KL).

---

## Objetivo

Implementar un driver de GPIO que detecte la pulsación del botón **SW3** mediante una interrupción por flanco de bajada, y controle el **LED verde** interno con debounce por software y polling no bloqueante.

---

## Hardware

| Elemento | Puerto | Pin | Notas |
|----------|--------|-----|-------|
| LED verde | PORTD / GPIOD | PD5 | Activo bajo — PCOR enciende, PSOR apaga |
| Botón SW3 | PORTC / GPIOC | PC3 | Activo bajo, pull-up interno habilitado |

La placa es la [FRDM-K32L2B3 de NXP](https://www.nxp.com/design/design-center/development-boards-and-designs/freedom-development-boards/mcus/frdm-k32l2b3:FRDM-K32L2B3), basada en el microcontrolador **K32L2B31AVLH4** (ARM Cortex-M0+).

---

## Estructura del proyecto

```
├── board_config.h              # Definiciones de hardware (pines, clocks, IRQ)
├── gpio_driver.h               # Interfaz pública del driver
├── gpio_driver.c               # Implementación del driver
└── GPIO_+_Interruptions.c      # Lógica de aplicación
```

### Separación de responsabilidades

| Archivo | Responsabilidad |
|---------|----------------|
| `board_config.h`                | Centraliza los pines y máscaras — si cambia la placa, solo se edita este archivo |
| `gpio_driver.c/h`               | Encapsula todo el acceso al hardware — clocks, PCR, NVIC, ISR, SysTick |
| `GPIO_+_Interruptions.c (main)` | Lógica de aplicación — no accede a registros directamente |

---

## Conceptos implementados

### 1. Habilitación de clocks (SIM_SCGC5)
En la familia KL, los periféricos están apagados por defecto para ahorrar energía. Antes de usar cualquier PORT o GPIO hay que habilitar su clock via `SIM->SCGC5`.

```c
SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTC_MASK;
```

### 2. Configuración del PCR (Port Control Register)
Cada pin tiene un registro PCR que define su función (MUX), pull-up/down, y condición de interrupción.

```c
// LED — GPIO sin pull
LED_GREEN_PORT->PCR[LED_GREEN_PIN] = PORT_PCR_MUX(1);

// Botón — GPIO con pull-up e interrupción por flanco de bajada
BTN_SW3_PORT->PCR[BTN_SW3_PIN] = PORT_PCR_MUX(1)   |
                                   PORT_PCR_PE(1)    |  // Pull enable
                                   PORT_PCR_PS(1)    |  // Pull-up select
                                   PORT_PCR_IRQC(11);   // Falling edge
```

`IRQC(11)` = interrupción en flanco de bajada (botón presionado, pin cae de 3.3V a 0V).

### 3. Dirección del pin (PDDR)

```c
LED_GREEN_GPIO->PDDR |=  (1U << LED_GREEN_PIN);   // salida
BTN_SW3_GPIO->PDDR  &= ~(1U << BTN_SW3_PIN);      // entrada
```

> **Error frecuente:** usar `(0 << pin)` en vez de `~(1U << pin)` — el primero pone a cero **todo** el registro.

### 4. ISR y regla de oro de las interrupciones

La ISR hace lo mínimo posible: limpiar el flag de hardware y activar una bandera de software.

```c
void PORTC_PORTD_IRQHandler(void)
{
    PORT_ClearPinsInterruptFlags(BTN_SW3_PORT, 1U << BTN_SW3_PIN);
    s_buttonFlag = true;
}
```

> **Nunca** poner delays, printf ni lógica compleja dentro de una ISR. El procesador debe salir lo antes posible.

### 5. Debounce por software

Los botones mecánicos rebotan al presionar y soltar, generando múltiples flancos en microsegundos. El debounce filtra pulsaciones que ocurran dentro de una ventana de tiempo mínima (50 ms).

```c
bool GPIO_Driver_ButtonPressed(void)
{
    if(!s_buttonFlag) return false;

    uint32_t tiempo_actual = GetCurrentMs();
    if((tiempo_actual - s_lastPressTime) < BTN_DEBOUNCE_MS) {
        s_buttonFlag = false;
        return false;   // rebote — ignorar
    }
    s_lastPressTime = ahora;
    s_buttonFlag    = false;
    return true;        // pulsación válida
}
```

### 6. SysTick como base de tiempo

`SysTick_Config(SystemCoreClock / 1000U)` configura una interrupción cada 1 ms. El handler incrementa un contador global que se usa para medir el tiempo transcurrido sin bloquear el procesador.

```c
void SysTick_Handler(void) { s_msTicks++; }
```

### 7. Toggle del LED con PTOR

El registro `PTOR` (Port Toggle Output Register) invierte el estado actual del pin en un solo ciclo, sin necesidad de leer el estado previo ni usar delays.

```c
void GPIO_Driver_toggleLED(void){
    LED_GREEN_GPIO->PTOR = (1U << LED_GREEN_PIN);
}
```

---

## Errores cometidos y lecciones aprendidas

| Error | Causa | Corrección |
|-------|-------|-----------|
| Lógica invertida en `ButtonPressed()` | El `return true` estaba en el `else` inalcanzable | Reestructurar el flujo |
| Faltaba `PORTC_PORTD_IRQHandler` | Sin ISR, la interrupción no hace nada útil | Definir el handler y limpiar ISF |
| Faltaba `SysTick_Handler` | `s_msTicks` nunca incrementaba, debounce roto | Definir el handler del SysTick |
| `static` en prototipo del `.h` | Genera una copia por unidad de compilación | Mantener `static` solo en el `.c` |

---

## Comportamiento final

```c
while(1){
    if(GPIO_Driver_ButtonPressed()){
        GPIO_Driver_toggleLED();
    }
}
```

Cada pulsación válida de SW3 invierte el estado del LED verde. El debounce filtra rebotes mecánicos de hasta 50 ms, garantizando una sola acción por pulsación.

---

## Herramientas

- **IDE:** MCUXpresso IDE
- **SDK:** NXP MCUXpresso SDK para K32L2B3
- **Toolchain:** ARM GCC
- **Placa:** FRDM-K32L2B3

---

## Próximos temas

- UART — comunicación serial para debug y comunicación entre dispositivos
- Timers (TPM) — interrupciones periódicas sin usar SysTick
- ADC — lectura de sensores analógicos
