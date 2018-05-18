/* STATS.H

Provides access to:
  MEAN
  VARIANCE
  MAXIMUM
  MINIMUM
*/

#ifndef STATS_H
# define STATS_H

  double distance(double, double);
  
  double getMean(double*, int);

  double getVariance(double*, int);

  double maximum(double*, int);

  double minimum(double*, int);

  double getCorrCoeff(double*, double*, unsigned int);

  void getLogRatio(double*, double*, int, double*);

#endif