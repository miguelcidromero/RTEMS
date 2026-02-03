#include <rtems.h>
#include <stdio.h>
#include <stdlib.h>

/* Prototipos de los benchmarks renombrados con el comando sed */
extern int main_fibonacci();
extern int main_bsqrt();
extern int main_matrix_nn();

rtems_task Init(rtems_task_argument argument) {
    printf("\n*** RTEMS ABSURD BENCHMARKS PORT - STM32F4 ***\n"); [cite: 120, 125]

    printf("\nEjecutando Fibonacci...\n");
    main_fibonacci();

    printf("\nEjecutando Bsqrt...\n");
    main_bsqrt();

    printf("\nEjecutando Matrix NN...\n");
    main_matrix_nn();

    printf("\n*** PRUEBAS COMPLETADAS ***\n");
    exit(0);
}

/* Configuración de RTEMS para la placa stm32f4 */
#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER [cite: 471]
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER [cite: 470]
#define CONFIGURE_MAXIMUM_TASKS 1
#define CONFIGURE_RTEMS_INIT_TASKS_TABLE
#define CONFIGURE_INIT

#include <rtems/confdefs.h> [cite: 220]
