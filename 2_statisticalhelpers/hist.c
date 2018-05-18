/* HIST.C : 
    Peter Dobbs
    bien4290
    lab2 
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
//#include "stats.h"

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

float maximum(float *data, int size){
  float max=0;
  for(int i=0; i<size; ++i){
    if(data[i]>max) max=data[i];
  }
  return max;
}

float minimum(float *data, int size){
  float min=maximum(data,size);
  for(int i=0; i<size; ++i){
    if(data[i]<min) min=data[i];
  }
  return min;
}
    
int main(void){
  
  FILE *inputFile;
  unsigned int i=0, j=0, expectedDataSize=30000, freqSize=0;
  float data[expectedDataSize];
  float mean=0, stdev=0, binWidth=0, binStart=0, binStop=0, binLoc=0, max=0, min=0; 
  char infile[100];

  //printf("Enter desired number of data points to process: ");
  //scanf("%i", &expectedDataSize);

  printf("Enter input filename: ");
  scanf("%s",infile);

  inputFile = fopen(infile,"r");
  if(inputFile==NULL){
    printf("file does not exists.\n");
    exit(EXIT_FAILURE);
  }

  for(i=0; (i<expectedDataSize) & (fscanf(inputFile,"%g",&data[i]) != EOF); ++i);
  expectedDataSize=i;  

  fclose(inputFile);
  
  mean = getMean(data,expectedDataSize);
  stdev = sqrt(getVariance(data,expectedDataSize));
  
  //estimate a histogram
  binWidth = 0.4*stdev;
  binStart = mean-2.4*stdev;
  binStop  = mean+2.4*stdev;
  freqSize = (binStop-binStart)/binWidth;
  
  float binLocn[freqSize+1];
  int frequency[freqSize+1];
  int freqIndex=0;
  
  //build histogram bins
  binLoc   = binStart;
  for(i=0; binLoc<=binStop; ++i){
    binLocn[i]=binLoc;
    binLoc+=binWidth;
  }
  
  for(i=0; i<freqSize; ++i){
    frequency[i]=0; //somehow this wasn't already empty
  }
  
  //build histogram values
  for(i=0; i<expectedDataSize; i++){
    freqIndex=0;
    if((data[i]>binStart) & (data[i]<binStop)){
      freqIndex = (data[i]-binStart)/binWidth;
    } else if(data[i]>binStop){
      freqIndex = freqSize;
    }
    ++frequency[freqIndex];
  }
   
  // time to print stuff
  printf("Number of data points analyzed: %i\n", expectedDataSize);
  printf("Mean value of data: %g\n",mean);
  printf("Stdev of data: %g\n", stdev);
  printf("Minimum of data: %g\n",minimum(data,expectedDataSize));
  printf("Maximum of data: %g\n",maximum(data,expectedDataSize));
  
  //histogram  
  printf("Histogram:\n");
  for(i=0; i<freqSize; ++i){
    printf("%g2\t|",binLocn[i]);
    for(j=0; j<frequency[i] && j<expectedDataSize; ++j){
      printf("*");
    }
    printf("\n");
  }
  printf("Done.\n");
  return 0;
}
