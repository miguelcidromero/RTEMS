#ifndef USER_H
#define USER_H

#include <stdlib.h>
#include <math.h>

/* --- 1. Constantes de configuración --- */
#define ITERATIONS      1000
#define ARRAY_LENGTH    1000
#define MATRIX_SIZE     50
#define CLASS_PRECISION 0.0001
#define TRUE            1
#define FALSE           0

/* --- 2. Macros "Dummy" --- */
#define MEASURE_GLOBAL_VARIABLES()
#define MEASURE_START()
#define MEASURE_STOP()
#define CHECK_RESULT(cond)  (void)(cond)

/* --- 3. Funciones de Aleatoriedad --- */
static inline double random_get(void) {
    return (double)rand() / (double)RAND_MAX;
}

static inline void random_get_array(double *arr, int len) {
    for (int i=0; i<len; i++) arr[i] = random_get();
}

static inline void random_get_sarray(double *arr, int len) {
    random_get_array(arr, len);
}

/* --- 4. Prototipos de los Benchmarks --- */
void fibonacci(void);
void matrix_nn(void);
void binary_search(void);
void bsqrt(void);
void eq_root(void);
void exp_int(void);
void mc_integral(void);
void select_nmax(void);
void unstruct(void);
void multi_search(void);

#endif
