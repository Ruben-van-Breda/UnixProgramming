
#include <stdlib.h>

typedef struct Point {
    int x;
    int y;
}Point ; 

double rectangle_area(Point a, Point b){
  // a and b are (x,y) cordinates of 
  // opposite corners of a rectangle.
  int height = abs(a.y - b.y);
  int width = abs(a.x - b.x);
  // Return the area of the rectangle.
  double area = width * height;
  return area;
}