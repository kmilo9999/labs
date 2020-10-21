#include "FilterInvert.h"

FilterInvert::~FilterInvert()
{
}

void FilterInvert::apply(Canvas2D *canvas) {
    int width = canvas->width();

    RGBA* current_pixel = nullptr;
    RGBA* data = canvas->data();

    // TODO: Task 8 [Optional] Use bitwise complement to set inversion
    int* intData = reinterpret_cast<int*>(canvas->data());
    for (int r = 0; r < canvas->height(); r++) {
      //  current_pixel = current_row;

        for (int c = 0; c < canvas->width(); c++) {
            // TODO: Task 7 Update the color with its inversion
//             data[ r*width+c].r =255 - data[ r*width+c].r;
//             data[ r*width+c].g =255 - data[ r*width+c].g;
//             data[ r*width+c].b =255 - data[ r*width+c].b;
            intData[ r*width+c] = ~intData[ r*width+c];


            // CONTINUED: Task 8 [Optional]

         //   current_pixel++;
        }
       // current_row += width;
    }
}
