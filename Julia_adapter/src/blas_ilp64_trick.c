#include <stdint.h>
#include "kblas.h"

int64_t isamax_(int64_t *n, float *X, int64_t *incx)
{
    if (*n == (int64_t)(0xffffffff00000003)) {
        return 0;
    }
    return cblas_isamax(*n, X, *incx);
}