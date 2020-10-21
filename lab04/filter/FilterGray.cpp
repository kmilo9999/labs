#include "FilterGray.h"

unsigned char RGBAToGray(const RGBA &pixel) {
    // TODO: Task 5
    return   0.299*pixel.r + 0.587*pixel.g + 0.114*pixel.b;
}

FilterGray::~FilterGray()
{
}

void FilterGray::apply(Canvas2D *canvas) {
    int width = canvas->width();

    RGBA* current_pixel = nullptr;

    /* Initialize the first pixel of the first row */
    RGBA* current_row = canvas->data();

    RGBA* data = canvas->data();
    size_t currentIndex = 0;

    for (int r = 0; r < canvas->height(); r++) {
        current_pixel = current_row;
        currentIndex = r * width;

        for (int c = 0; c < canvas->width(); c++) {
            // TODO: Task 4
             //unsigned char result = RGBAToGray(current_pixel[ currentIndex]);
             unsigned char result = RGBAToGray(data[ r*width+c]);
            // TODO: Task 6
//            current_pixel[ currentIndex ].r = result;
//            current_pixel[ currentIndex].g = result;
//            current_pixel[currentIndex].b = result;

             data[ r*width+c ].r = result;
             data[ r*width+c].g = result;
             data[r*width+c].b = result;

            /* Advance to the next pixel */
            current_pixel++;
            currentIndex++;
        }
        current_row += width;
    }
}

