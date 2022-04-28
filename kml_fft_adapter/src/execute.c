#include "fft_type.h"

void FFTW(execute)(const FFTW(plan) plan)
{
    KML(execute)((KML(plan))plan);
}

void FFTW(execute_dft)(const FFTW(plan) plan, FFTW(complex) *in, FFTW(complex) *out)
{
    KML(execute_dft)((KML(plan))plan, (KML(complex) *)in, (KML(complex) *)out);
}

void FFTW(execute_dft_r2c)(const FFTW(plan) plan, FP *in, FFTW(complex) *out)
{
    KML(execute_dft_r2c)((KML(plan))plan, in, (KML(complex) *)out);
}

void FFTW(execute_dft_c2r)(const FFTW(plan) plan, FFTW(complex) *in, FP *out)
{
    KML(execute_dft_c2r)((KML(plan))plan, (KML(complex) *)in, out);
}

void FFTW(execute_r2r)(const FFTW(plan) plan, FP *in, FP *out)
{
    KML(execute_r2r)((KML(plan))plan, in, out);
}

void FFTW(execute_split_dft)(const FFTW(plan) plan, FP *ri, FP *ii, FP *ro, FP *io)
{
    KML(execute_split_dft)((KML(plan))plan, ri, ii, ro, io);
}

void FFTW(execute_split_dft_r2c)(const FFTW(plan) plan, FP *in, FP *ro, FP *io)
{
    KML(execute_split_dft_r2c)((KML(plan))plan, in, ro, io);
}

void FFTW(execute_split_dft_c2r)(const FFTW(plan) plan, FP *ri, FP *ii, FP *out)
{
    KML(execute_split_dft_c2r)((KML(plan))plan, ri, ii, out);
}