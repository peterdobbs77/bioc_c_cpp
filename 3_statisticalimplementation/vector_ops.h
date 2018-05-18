/* VECTOR_OPS.H
    Peter Dobbs
    BIEN 4290
    Created: 13 February 2018
*/
#ifndef VECTOR_OPS_H
# define VECTOR_OPS_H

  double* vectorSum(double *x, double *y, int size, double *sum);

  double* vectorDifference(double *x, double *y, int size, double *difference);

  double* vectorProduct(double *x, double *y, int size, double *product);

  double* vectorQuotient(double *data, int size, int divisor, double *quotient);

#endif