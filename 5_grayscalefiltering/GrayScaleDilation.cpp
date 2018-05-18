#include <iostream>
#include "GrayScaleDilation.h"

float GrayScaleDilation::updatePixel(Image & hood){
  unsigned int i=0, j=0;
  float max=hood.getVal(i,j);
  for(i=0; i<hood.getNumRows(); ++i){
    for(j=0; j<hood.getNumCols(); ++j){
      if(hood.getVal(i,j)>max) max=hood.getVal(i,j);
    }
  }
  return max;
}
