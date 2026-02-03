/* init.c - LA VERSIÓN DEFINITIVA (Benchmarks + Luces + Configuración Segura) */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems.h>
#include <stdint.h>
#include <stdlib.h>
#include "user.h" /* Tus 10 benchmarks */

/* --- DIRECCIONES DE HARDWARE STM32F4 (Discovery) --- */
#define RCC_AHB1ENR  (*((volatile uint32_t *)0x40023830))
#define GPIOD_MODER  (*((volatile uint32_t *)0x40020C00))
#define GPIOD_ODR    (*((volatile uint32_t *)0x40020C14))

/* Prototipo obligatorio */
rtems_task Init(rtems_task_argument arg);

/* Configura PD12-PD15 como salidas */
static void led_setup(void) {
    RCC_AHB1ENR |= (1 << 3); /* Reloj GPIOD */
    GPIOD_MODER &= ~(0xFF000000); 
    GPIOD_MODER |=  (0x55000000); /* Salida */
}

/* Pausa "tonta" (Busy Wait) - NO depende de drivers de RTEMS */
static void busy_wait(int count) {
    for(volatile int k=0; k < count; k++);
}

/* Controla el patrón de luces (Serpiente 8 pasos) */
static void set_led_progress(int step) {
    uint32_t current_state = GPIOD_ODR;
    current_state &= ~(0xF000); /* Limpiar */

    switch (step % 8) {
        /* Llenado */
        case 1: current_state |= (1 << 12); break; // G
        case 2: current_state |= (1 << 12) | (1 << 13); break; // G+O
        case 3: current_state |= (1 << 12) | (1 << 13) | (1 << 14); break; // G+O+R
        case 4: current_state |= (0xF000); break; // ALL
        /* Vaciado */
        case 5: current_state |= (1 << 13) | (1 << 14) | (1 << 15); break; // -G
        case 6: current_state |= (1 << 14) | (1 << 15); break; // -O
        case 7: current_state |= (1 << 15); break; // B
        case 0: break; // OFF
    }
    GPIOD_ODR = current_state;
}

typedef void (*bench_fn_t)(void);
typedef struct { const char *name; bench_fn_t fn; } bench_t;

/* TUS 10 BENCHMARKS */
static bench_t benches[] = {
  { "Fibonacci",       fibonacci },
  { "Matrix NN",       matrix_nn },
  { "Binary Search",   binary_search },
  { "Bsqrt",           bsqrt },
  { "Eq Root",         eq_root },
  { "Exp Int",         exp_int },
  { "MC Integral",     mc_integral },
  { "Select Nmax",     select_nmax },
  { "Unstruct",        unstruct },
  { "Multi Search",    multi_search },
};

static void run_all(void) {
  size_t n = sizeof(benches) / sizeof(benches[0]);

  for (size_t i = 0; i < n; i++) {
    /* 1. Ponemos la luz correspondiente al paso */
    set_led_progress(i + 1);

    /* 2. Ejecutamos el benchmark (¡Cálculos reales!) */
    benches[i].fn();

    /* 3. Esperamos un poco para ver la luz (aprox 0.5 segs) */
    busy_wait(3000000); 
  }
}

rtems_task Init(rtems_task_argument arg) {
    (void) arg;

    /* 1. Configurar Hardware */
    led_setup();

    /* 2. Destello inicial ROJO para confirmar arranque */
    GPIOD_ODR |= (1 << 14);
    busy_wait(1000000);
    GPIOD_ODR &= ~(1 << 14);

    /* 3. Correr Benchmarks */
    run_all();

    /* 4. FINAL: Encender todo */
    GPIOD_ODR |= (0xF000);

    /* 5. Morir aquí (Bucle infinito) */
    while(1);
    
    rtems_shutdown_executive(0);
}

/* --- CONFIGURACIÓN "A PRUEBA DE BALAS" (Igual que Opción A) --- */
/* Desactivamos Clock y Consola para evitar cuelgues */
#define CONFIGURE_APPLICATION_DOES_NOT_NEED_CLOCK_DRIVER
#define CONFIGURE_MAXIMUM_TASKS 1
#define CONFIGURE_RTEMS_INIT_TASKS_TABLE
/* Aumentamos stack por si Matrix o Fibonacci gastan mucho */
#define CONFIGURE_INIT_TASK_STACK_SIZE (32 * 1024) 
#define CONFIGURE_INIT
#include <rtems/confdefs.h>
