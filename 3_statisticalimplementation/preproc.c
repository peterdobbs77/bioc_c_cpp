/* PREPROC.C
  Peter Dobbs
  BIEN 4290
  Created: 13 February 2018
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stats.h"
#include "vector_ops.h"

int main(void){
  int i=0,size=0;
  FILE *red, *redBackground, *green, *greenBackground, *outLR;
  char redFile[100], redBackFile[100], greenFile[100], greenBackFile[100], out[100];
  double redMean=0, greenMean=0;
  
  //printf("Enter the name of the file containing data from the sporulating cells (red): ");
  scanf("%s", redFile);
  //printf("Enter the name of the file containing the background red data: ");
  scanf("%s", redBackFile);
  //printf("Enter the name of the file containing data from the non-sporulating cells (green): ");
  scanf("%s", greenFile);
  //printf("Enter the name of the file containing the background green data: ");
  scanf("%s", greenBackFile);
  //printf("Enter the name of the file to which the calibrated data will be written: ");
  scanf("%s", out);
  //printf("Enter the number of genes to be analyzed: ");
  scanf("%i", &size);
  
  double* rData=(double*)malloc(size*sizeof(double));  
  double* rBackData=(double*)malloc(size*sizeof(double));  
  double* gData=(double*)malloc(size*sizeof(double));  
  double* gBackData=(double*)malloc(size*sizeof(double));  
  double* redDiff=(double*)malloc(size*sizeof(double));  
  double* greenDiff=(double*)malloc(size*sizeof(double));
  double* normRed=(double*)malloc(size*sizeof(double));  
  double* normGreen=(double*)malloc(size*sizeof(double));  
  double* lr=(double*)malloc(size*sizeof(double));
  
  red=fopen(redFile,"r");
  redBackground=fopen(redBackFile,"r");
  green=fopen(greenFile,"r");
  greenBackground=fopen(greenBackFile,"r");
  
  if(red==NULL||redBackground==NULL||green==NULL||greenBackground==NULL){
    printf("missing file\n");
    exit(EXIT_FAILURE);
  }
  
  for(i=0; (i<size) && (fscanf(red,"%lf",&rData[i]) != EOF); ++i);
  for(i=0; (i<size) && (fscanf(redBackground,"%lf",&rBackData[i]) != EOF); ++i);
  for(i=0; (i<size) && (fscanf(green,"%lf",&gData[i]) != EOF); ++i);
  for(i=0; (i<size) && (fscanf(greenBackground,"%lf",&gBackData[i]) != EOF); ++i);
  size=i;
  
  fclose(red);
  fclose(redBackground);
  fclose(green);
  fclose(greenBackground);
  
  //subtract the corresponding background intensities from red & green datasets
  vectorDifference(rData,rBackData,size,redDiff);
  vectorDifference(gData,gBackData,size,greenDiff);
  
  //calculate the means of the corrected red and green datasets
  redMean=getMean(redDiff,size);
  greenMean=getMean(greenDiff,size);
  
  //normalize the corrected data respective by their dataset mean
  vectorQuotient(redDiff,size,redMean,normRed);
  vectorQuotient(greenDiff,size,greenMean,normGreen);

  //calculate the log intensity ratio of the normalized data
  getLogRatio(normRed, normGreen, size, lr);
  
  outLR=fopen(out,"w");
  for(i=0;i<size;++i){
    fprintf(outLR,"%lf\n",lr[i]);
  }
  fclose(outLR);
  
  free(lr);
  free(normGreen);
  free(normRed);
  free(greenDiff);
  free(redDiff);
  free(gBackData);
  free(gData);
  free(rBackData);
  free(rData);
  
  return 0;
}