/* CORRCOEFF.C : 
    Peter Dobbs
    bien4290
    lab2`
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

float getMean(float *data, int size){
  float sum=0;
  for(int i=0; i<size; ++i) sum+=data[i];
  return (sum/size);
}

float getVariance(float *data, int size){
  int i=0;
  float mean = getMean(data,size), sum[size];
  for(i=0; i<size; ++i) sum[i]=pow(data[i]-mean,2);
  return getMean(sum, size);
}

float getCorrCoeff(float *x, float *y, int size){ // old code might not use the correct equation (check!)
  float varX = getVariance(x,size);
  float varY = getVariance(y,size);
  float meanX = getMean(x,size);
  float meanY = getMean(y,size);
  float numer = 0;
  for (int i=0; i<size; ++i){
    numer += ((x[i] - meanX)*(y[i] - meanY));
  }
  return (numer / sqrt(varX*varY));
}

int main(void){
  
  FILE *inputXFile, *inputYFile;
  unsigned int i=0, expectedSize=30000;
  float xdata[expectedSize], ydata[expectedSize];
  float r_xy=0;
  char infile[100];
  

  //printf("Enter desired number of data points to process: ");
  //scanf("%i", &expectedSize);

  scanf("%s",infile);
  inputXFile = fopen(infile,"r");
  scanf("%s",infile);
  inputYFile = fopen(infile,"r");
  if(inputXFile==NULL || inputYFile==NULL){
    printf("file does not exists.\n");
    exit(EXIT_FAILURE);
  }

  for(i=0; (i<expectedSize) & (fscanf(inputXFile,"%g",&xdata[i]) != EOF); ++i);
  expectedSize=i;
  for(i=0; (i<expectedSize) & (fscanf(inputYFile,"%g",&ydata[i]) != EOF); ++i);

  fclose(inputYFile);
  fclose(inputXFile);
    
  if(i<expectedSize){
    printf("data size mismatch\n");
    exit(EXIT_FAILURE);
  }

  // calculate correlation coefficient
  r_xy = getCorrCoeff(xdata, ydata, expectedSize);
  printf("%g\n", r_xy);
}
