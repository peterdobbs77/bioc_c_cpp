/* PREPROC.C
  Peter Dobbs
  BIEN 4290
  Created: 13 February 2018
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stats.h"
#include "vector_ops.h"

int main(void){
  FILE *in, *outExpressed, *outSuppressed, *outStationary;
  unsigned int size=0, i=0, numPoints1=0, numPoints2=0, numPoints3=0;
  double suppMean=-0.5, statMean=0, exprMean=0.5, dist=0, tempDist=0, temp=0, criteria=0;
  double suppMeanOld=0, statMeanOld=0, exprMeanOld=0, dist1=0, dist2=0, dist3=0;

  in=fopen("log_ratio_input.dat","r");
  if(in==NULL){
    printf("missing file\n");
    exit(EXIT_FAILURE);
  }
  
  //printf("Enter desired number of data points to process: ");
  scanf("%i", &size);
  
  double* logRatio=(double*)malloc(size*sizeof(double));
  int* clusterEntry=(int*)malloc(size*sizeof(int));
  char* geneName=(char*)malloc(100);
  
  for(i=0; (i<size) & (fscanf(in,"%lf",&logRatio[i]) != EOF); ++i);
  size=i;
  
  fclose(in);
  
  criteria=0;
  do{
    suppMeanOld=suppMean;
    statMeanOld=statMean;
    exprMeanOld=exprMean;
    
    numPoints1=0;
    numPoints2=0;
    numPoints3=0;

    for(i=0; i<size; i++){
      dist1=distance(logRatio[i],suppMeanOld);
      dist2=distance(logRatio[i],statMeanOld);
      dist3=distance(logRatio[i],exprMeanOld);
      
      if(dist1<dist2 && dist1<dist3){
        clusterEntry[i]=1;
        suppMean+=logRatio[i];
        numPoints1++;
      }else if(dist2<dist1 && dist2<dist3){
        clusterEntry[i]=2;
        statMean+=logRatio[i];
        numPoints2++;
      } else {
        clusterEntry[i]=3;
        exprMean+=logRatio[i];
        numPoints3++;
      }
    }
    suppMean/=numPoints1;
    statMean/=numPoints2;
    exprMean/=numPoints3;
    
    criteria = fabs(suppMean-suppMeanOld)+fabs(statMean-statMeanOld)+fabs(exprMean-exprMeanOld);
  }while(criteria>0.0001);
  
  printf("final cluster means: %f %f %f\n", suppMean, statMean, exprMean);
  
  in=fopen("gene_list.txt","r");
  outExpressed=fopen("expressed_genes.txt","w");
  outSuppressed=fopen("suppressed_genes.txt","w");
  outStationary=fopen("stationary_genes.txt","w");
  
  if(in==NULL){
    printf("gene list is missing\n");
    exit(EXIT_FAILURE);
  }
  if(outExpressed==NULL || outSuppressed==NULL || outStationary==NULL){
    printf("output file is null \n");
    exit(EXIT_FAILURE);
  }
  
  for(i=0; i<size; i++){
    fgets(geneName, 20, in);
    if(clusterEntry[i]==1)
      fprintf(outSuppressed, "%s", geneName);
    if(clusterEntry[i]==2)
      fprintf(outStationary, "%s", geneName);
    if(clusterEntry[i]==3)
      fprintf(outExpressed, "%s", geneName);
  }
  
  fclose(outStationary);
  fclose(outSuppressed);
  fclose(outExpressed);
  fclose(in);
  free(logRatio);
  free(clusterEntry);
  
  return 0;
}
