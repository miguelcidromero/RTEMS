#include <rtems.h>
#include <stdio.h>

/* Prototipos de los benchmarks renombrados */
extern int main_init_fibonacci();
extern int main_init_bsqrt();

rtems_task Init(rtems_task_argument argument) {
    printf("\n*** INICIANDO PORT DE ABSURD BENCHMARKS ***\n");
    main_fibonacci();
    main_bsqrt();
    printf("\n*** PRUEBAS COMPLETADAS ***\n");
    rtems_shutdown_executive(0);
}

/* Configuración obligatoria para la placa STM32F4 */
#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER [cite: 471]
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER [cite: 470]
#define CONFIGURE_MAXIMUM_TASKS 1
#define CONFIGURE_RTEMS_INIT_TASKS_TABLE
#define CONFIGURE_INIT
#include <rtems/confdefs.h>
