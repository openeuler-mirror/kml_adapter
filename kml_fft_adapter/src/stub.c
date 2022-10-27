#include <stdint.h>
#include <stdlib.h>

#include "fft_type.h"

#define KML_FFT_CACHELINE_SIZE 64
#define UNUSED(x) (void)(x)

#define ALGN 16

const char FFTW(version)[] = "kfft-x.x.x";
const char FFTW(constructor)[] = "gcc";
const char FFTW(codelet_optim)[] = "";

void FFTW(cleanup)(void)
{
}

FP *FFTW(alloc_real)(size_t n)
{
    return (FP *)KML(malloc)(sizeof(FP) * n);
}

int FFTW(import_wisdom_from_filename)(const char *filename)
{
    UNUSED(filename);
    return 0;
}

int FFTW(import_wisdom_from_file)(FILE *input_file)
{
    UNUSED(input_file);
    return 0;
}

void FFTW(export_wisdom_to_file)(FILE *output_file)
{
    UNUSED(output_file);
    return;
}

void FFTW(set_timelimit)(double t)
{
    UNUSED(t);
    return;
}

void FFTW(flops)(const FFTW(plan) p, double *add, double *mul, double *fmas)
{
    UNUSED(p);
    *add = 0;
    *mul = 0;
    *fmas = 0;
    return;
}

double FFTW(estimate_cost)(const FFTW(plan) p)
{
    UNUSED(p);
    return 0.0f;
}

double FFTW(cost)(const FFTW(plan) p)
{
    UNUSED(p);
    return 0.0f;
}

int FFTW(alignment_of)(FP *p)
{
    return (int)(((uintptr_t) p) % ALGN);
}

void FFTW(fprint_plan)(const FFTW(plan) p, FILE *output_file)
{
    UNUSED(p);
    UNUSED(output_file);
    return;
}

void FFTW(print_plan)(const FFTW(plan) p)
{
    UNUSED(p);
    return;
}

void FFTW(forget_wisdom)(void)
{
    return;
}

void install_hook(void) {
    return;
}

void uninstall_hook(void) {
    return;
}

void * FFTW(the_planner)(void) {
    return (void *)malloc(KML_FFT_CACHELINE_SIZE);
}

void FFTW(make_planner_thread_safe)(void) {
    return;
}