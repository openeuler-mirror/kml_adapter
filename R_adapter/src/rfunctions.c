#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "vsl_types.h"
#include "kvsl.h"
VslPolicy *policy;
#define CONSTRUCTOR __attribute__((constructor))
#define DESTRUCTOR __attribute__((destructor))
CONSTRUCTOR void PreInitPolicy(void)
{
    KmlVslResult res = kml_vsl_init(&policy, SUPER_DUPER, time(NULL));
    if (res != VSL_OK) {
        exit(-1);
    }
}
void kml_runif(int *len, double *result, double *min, double *max, int *normalKind)
{
    KmlVslResult status = kml_vsl_runif(policy, *normalKind, *len, result, *min, *max);
    if (status != VSL_OK) {
        fprintf(stderr, "error occured!\n");
    }
}

void kml_rbeta(int *len, double *result, double *aa, double *bb, int *normalKind)
{
    KmlVslResult status = kml_vsl_rbeta(policy, *normalKind, *len, result, *aa, *bb);
    if (status != VSL_OK) {
        fprintf(stderr, "error occured!\n");
    }
}

void kml_rbinom(int *len, int *result, int *size, double *prob, int *normalKind)
{
    KmlVslResult status = kml_vsl_rbinom(policy, *normalKind, *len, result, *size, *prob);
    if (status != VSL_OK) {
        fprintf(stderr, "error occured!\n");
    }
}

void kml_rnbinom(int *len, int *result, int *size, double *prob, int *normalKind)
{
    KmlVslResult status = kml_vsl_rnbinom(policy, *normalKind, *len, result, *size, *prob);
    if (status != VSL_OK) {
        fprintf(stderr, "error occured!\n");
    }
}

void kml_rhyper(int *len, int *result, int *m, int *n, int *k, int *normalKind)
{
    KmlVslResult status = kml_vsl_rhyper(policy, *normalKind, *len, result, *m, *n, *k);
    if (status != VSL_OK) {
        fprintf(stderr, "error occured! %d %d %d\n", *m, *n, *k);
    }
}

void kml_rgamma(int *len, double *result, double *shape, double *scale, int *normalKind)
{
    KmlVslResult status = kml_vsl_rgamma(policy, *normalKind, *len, result, *shape, *scale);
    if (status != VSL_OK) {
        fprintf(stderr, "error occured!\n");
    }
}
void kml_rcauchy(int *len, double *result, double *location, double *scale, int *normalKind)
{
    KmlVslResult status = kml_vsl_rcauchy(policy, *normalKind, *len, result, *location, *scale);
    if (status != VSL_OK) {
        fprintf(stderr, "error occured!\n");
    }
}

void kml_rexp(int *len, double *result, double *rate, int *normalKind)
{
    KmlVslResult status = kml_vsl_rexp(policy, *normalKind, *len, result, *rate);
    if (status != VSL_OK) {
        fprintf(stderr, "error occured!\n");
    }
}

void kml_rgeom(int *len, int *result, double *p, int *normalKind)
{
    KmlVslResult status = kml_vsl_rgeom(policy, *normalKind, *len, result, *p);
    if (status != VSL_OK) {
        fprintf(stderr, "error occured!\n");
    }
}

void kml_rlnorm(int *len, double *result, double *meanlog, double *sdlog, int *normalKind)
{
    KmlVslResult status = kml_vsl_rlnorm(policy, *normalKind, *len, result, *meanlog, *sdlog);
    if (status != VSL_OK) {
        fprintf(stderr, "error occured!\n");
    }
}

void kml_rnorm(int *len, double *result, double *mu, double *sigma, int *normalKind)
{
    KmlVslResult status = kml_vsl_rnorm(policy, *normalKind, *len, result, *mu, *sigma);
    if (status != VSL_OK) {
        fprintf(stderr, "error occured!\n");
    }
}

void kml_rpois(int *len, int *result, double *mu, int *normalKind)
{
    KmlVslResult status = kml_vsl_rpois(policy, *normalKind, *len, result, *mu);
    if (status != VSL_OK) {
        fprintf(stderr, "error occured!\n");
    }
}

void kml_rweibull(int *len, double *result, double *shape, double *scale, int *normalKind)
{
    KmlVslResult status = kml_vsl_rweibull(policy, *normalKind, *len, result, *shape, *scale);
    if (status != VSL_OK) {
        fprintf(stderr, "error occured!\n");
    }
}
void kml_rng_kind(int *kind)
{
    KmlVslResult status = kml_vsl_setRNGKind(policy, *kind);
    if (status != VSL_OK) {
        fprintf(stderr, "error occured!\n");
    }
}
void kml_set_seed(int *seed)
{
    KmlVslResult status = kml_vsl_setSeed(policy, *seed);
    if (status != VSL_OK) {
        fprintf(stderr, "error occured!\n");
    }
}