#include "FilterShift.h"
#include "FilterUtils.h"

FilterShift::FilterShift(ShiftDirection direction):
    m_shiftDir(direction)
{
     // TODO: Task 19 Initialize kernel for shift
    if(m_shiftDir == SHIFT_LEFT)
    {
        m_kernel = {
                    0.0,0.0,0.0,
                    0.0,0.0,1.0,
                    0.0,0.0,0.0
                   };
    }
    else
    {
            m_kernel = {
                        0.0,0.0,0.0,
                        1.0,0.0,0.0,
                        0.0,0.0,0.0
                       };
    }

//    m_kernel = {
//                0.0,0.0,0.0,0.0,0.0,0.0,0.0,
//                0.0,0.0,0.0,0.0,0.0,0.0,0.0,
//                0.0,0.0,0.0,0.0,0.0,0.0,0.0,
//                0.0,0.0,0.0,0.0,0.0,0.0,0.0,
//                0.0,0.0,0.0,0.0,0.0,0.0,0.0,
//                0.0,0.0,0.0,0.0,0.0,0.0,0.0,
//                0.0,0.0,0.0,1.0,0.0,0.0,0.0
//               };
}

FilterShift::~FilterShift()
{
}

void FilterShift::apply(Canvas2D *canvas) {
    // TODO: Task 18 Call convolve function from superclass
    FilterUtils ::Convolve2D(canvas->data(), canvas->width(), canvas->height(), m_kernel);
}
