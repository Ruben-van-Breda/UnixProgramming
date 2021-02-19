#include "rectangle.h"




double rectangle_area(Point a, Point b){
  // a and b are (x,y) cordinates of 
  // opposite corners of a rectangle.
  int height = fabs(a.y - b.y);
  int width = fabs(a.x - b.x);
  // Return the area of the rectangle.
  double area = width * height;
  return area;
}