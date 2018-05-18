//
#include <stdio.h>
#include <stdlib.h>

int main(void){
  FILE *inFile, *outFile;
  int sum=0, i=0, temp=0;

  //inFile = fopen("~/lab1/twentyRandomNumbers.txt","r");
  inFile = fopen("twentyRandomNumbers.txt","r");
  if(inFile==NULL){
    printf("no such file exists\n");
    exit(EXIT_FAILURE);
  }
  for(i=0; fscanf(inFile,"%i",&temp) != EOF; ++i){
    sum+=temp;
  }
  fclose(inFile);

  outFile = fopen("sumOutput.txt","w");
  fprintf(outFile,"%i\n",sum);
  fclose(outFile);

  printf("%i\n",sum);

  return 0;
}
