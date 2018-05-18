/* STATS.C: 
  Peter Dobbs
  BIEN 4290
  Created: 13 February 2018
*/
#include <math.h>
#include "stats.h"
#include "vector_ops.h"

double distance(double a, double b){
  return (fabs(a-b));
}

double getMean(double *data, int size){
  unsigned int i=0;
  double sum=0;
  for(i=0; i<size; ++i)
    sum+=data[i];
  return (sum/size);
}

double getVariance(double *data, int size){
  unsigned int i=0;
  double mean=getMean(data,size), sum[size];
  for(i=0; i<size; ++i) sum[i]=pow(data[i]-mean,2);
  return getMean(sum, size);
}

double maximum(double *data, int size){
  unsigned int i=0;
  double max=0;
  for(i=0; i<size; ++i){
    if(data[i]>max) max=data[i];
  }
  return max;
}

double minimum(double *data, int size){
  unsigned int i=0;
  double min=maximum(data,size);
  for(i=0; i<size; ++i){
    if(data[i]<min) min=data[i];
  }
  return min;
}

double getCorrCoeff(double *x, double *y, unsigned int size){
  unsigned int i=0;
  double meanX=0, meanY=0, sumXY=0, sumXX=0, sumYY=0, numer=0, denom=0;
  meanX=getMean(x,size);
  meanY=getMean(y,size);
  for (i=0; i<size; ++i){
    sumXY+=(x[i]*y[i]);
    sumXX+=(x[i]*x[i]);
    sumYY+=(y[i]*y[i]);
  }
  return ((sumXY-(size*meanX*meanY))/(sqrt((sumXX-(size*meanX*meanX))*(sumYY-(size*meanY*meanY)))));
}

void getLogRatio(double *i_numer, double *i_denom, int size, double *logRatio){
  unsigned int i=0;
  for(i=0; i<size; ++i){
    logRatio[i]=log10(i_numer[i]/i_denom[i]);
  }
}