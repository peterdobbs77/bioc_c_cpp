#ifndef FILTER_H
#define FILTER_H
  #include "Image.h"
  class Filter{
    protected:
      virtual float updatePixel(Image & hood) = 0;
    public:
      Image process(Image & im, int m, int n);
    private:
      void checkThatDimensionsAreOdd(int m, int n);
  };
#endif
