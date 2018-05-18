#include <cstring>
#include <iostream>
#include "Image.h"
#include "Filter.h"
#include "EdgeDetection.h"

#define HOOD_N 3
#define HOOD_M 3

int main(void){
  char iFile[50]="lab5_spatial_image.bin";
  //char iFile[50]="lab5_noise_image.bin";
  char oFileX[50]="edgeDetection_output_X.bin";
  char oFileY[50]="edgeDetection_output_Y.bin";
  //char oFile[50] = "edgeDetection_noise_output_3_3.bin";
  Image im(256,256);

  float imageThreshold=0;



  //read in image
  im.readImage(iFile);
    
  //process image
  Image kernel(HOOD_M,HOOD_N);
  //k_x
  kernel.setVal(0,0,-1);
  kernel.setVal(0,1,0);
  kernel.setVal(0,2,1);
  kernel.setVal(1,0,-2);
  kernel.setVal(1,1,0);
  kernel.setVal(1,2,2);
  kernel.setVal(2,0,-1);
  kernel.setVal(2,1,0);
  kernel.setVal(2,2,1);

  EdgeDetection gX(kernel);
  Image imX=gX.process(im,HOOD_M,HOOD_N);

  imX.writeImage(oFileX);

  //k_y
  kernel.setVal(0,0,1);
  kernel.setVal(0,1,2);
  kernel.setVal(0,2,1);
  kernel.setVal(1,0,0);
  kernel.setVal(1,1,0);
  kernel.setVal(1,2,0);
  kernel.setVal(2,0,-1);
  kernel.setVal(2,1,-2);
  kernel.setVal(2,2,-1);

  EdgeDetection gY(kernel);
  Image imY=gY.process(imX,HOOD_M,HOOD_N);
  
  //write image to file
  imY.writeImage(oFileY);

  imageThreshold=im.getAverageValue();


  return 0;
}
