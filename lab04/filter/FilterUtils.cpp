#include "FilterUtils.h"
#include <algorithm>
#include "math.h"
#include <cstring>

namespace FilterUtils {

inline unsigned char REAL2byte(float f) {
    int i = static_cast<int>((f * 255.0 + 0.5));
    return (i < 0) ? 0 : (i > 255) ? 255 : i;
}

void Convolve2D(RGBA* data, int width, int height, const std::vector<float> &kernel) {
    // TODO: Task 9 Create buffer to store new image data
    RGBA result[width * height];

    // TODO: Task 10 Obtain kernel dimension
    int kernelSize = sqrtf(kernel.size());
    const int dx = kernelSize/2;
    const int dy = kernelSize/2;

    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            size_t centerIndex = r * width + c;

            // TODO: Task 11 Initialize color to accumulate convolution data
           float red_acc =0 , green_acc=0, blue_acc = 0;


            // TODO: Task 12
            // Iterate over the kernel using the value from task 10
            // Obtain the value at current index of kernel
            // Find correct index in original image data
            // Accumulate the kernel applied to pixel value in color_acc



           for(int i = 0;i < kernelSize; i++){


               for(int j = 0;j < kernelSize; j++)
               {


                   int x = c - dx + j;
                   int y = r - dy + i;

                  // TODO: Task 13 Ignore outside bounds
                  if( x >= 0 && x < width  && y >= 0 && y < height )
                  {
                     red_acc += (float)data[y*width+x].r * (float)kernel[i*kernelSize+j];
                     green_acc += (float)data[y*width+x].g * (float)kernel[i*kernelSize+j];
                     blue_acc += (float)data[y*width+x].b * (float)kernel[i*kernelSize+j];
                  }

               }

           }




            // TODO: Task 14 Update buffer with accumulated color
           unsigned char new_r =  REAL2byte((float)red_acc);
           unsigned char new_g =  REAL2byte((float)green_acc);
           unsigned char new_b =  REAL2byte((float)blue_acc);
             RGBA resultColor(red_acc,green_acc,blue_acc,255);
           //RGBA resultColor(new_r,new_g,new_b,255);
             result[centerIndex] = resultColor;
        }
    }

    // TODO: Task 15 Copy over buffer to canvas data
    memcpy(data,result,width * height * sizeof(RGBA));
}

}
