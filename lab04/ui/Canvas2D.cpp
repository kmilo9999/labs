/**
 * @file Canvas2D.cpp
 *
 * CS123 2-dimensional canvas.
 *
 */

#include <assert.h>
#include <memory>
#include "Canvas2D.h"
#include "Settings.h"
#include <QCoreApplication>
#include "filter/Filter.h"
#include "filter/FilterGray.h"
#include "filter/FilterInvert.h"
#include "filter/FilterIdentity.h"
#include "filter/FilterShift.h"

#include <QPainter>

Canvas2D::Canvas2D() {
    notifySizeChanged(width(), height());
}

Canvas2D::~Canvas2D()
{
}

void Canvas2D::filterImage() {


    // TODO: Task 1
   std::unique_ptr<Filter> myFiter ;
    // TODO: Task 2
   switch(settings.filterType)
   {
     case FilterType::FILTER_GRAYSCALE:
          myFiter= std::make_unique<FilterGray>();
      break;
     case  FILTER_INVERT:
            myFiter= std::make_unique<FilterInvert>();
       break;
     case FILTER_IDENTITY:
               myFiter= std::make_unique<FilterIdentity>();
       break;
     case FILTER_SHIFT_LEFT:
            myFiter= std::make_unique<FilterShift>(ShiftDirection::SHIFT_LEFT);
       break;
     case FILTER_SHIFT_RIGHT:
            myFiter= std::make_unique<FilterShift>(ShiftDirection::SHIFT_RIGHT);
       break;
     default:
       break;
   }

    // TODO: Task 3
    myFiter->apply(this);


    this->update();
}

void Canvas2D::paintEvent(QPaintEvent *e) {
    // You probably won't need to fill this in, but you can if you want to override any painting
    // events for the 2D canvas. For now, we simply call the superclass.
    SupportCanvas2D::paintEvent(e);
}
