/* VECTOR_OPS.C
    Peter Dobbs
    BIEN 4290
    Created: 13 February 2018
*/

#include "vector_ops.h"

double* vectorSum(double *x, double *y, int size, double *sum){
  unsigned int i=0;
  for(i=0; i<size; ++i){
    sum[i]=x[i]+y[i];
  }
  return sum;
}

double* vectorDifference(double *x, double *y, int size, double *difference){
  unsigned int i=0;
  for(i=0; i<size; ++i){
    difference[i]=x[i]-y[i];
  }
  return difference;
}

double* vectorProduct(double *x, double *y, int size, double *product){
  unsigned int i=0;
  for(i=0; i<size; ++i){
    product[i]=x[i]*y[i];
  }
  return product;
}

double* vectorQuotient(double *data, int size, int divisor, double *quotient){
  unsigned int i=0;
  for(i=0; i<size; ++i){
    quotient[i]=(data[i]/divisor);
  }
  return quotient;
}