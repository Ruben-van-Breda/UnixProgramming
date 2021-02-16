#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rectangle.h"

// // // == Modify Below here for step 1 == //
// double rectangle_area(struct Point a, struct Point b){
//   // a and b are (x,y) cordinates of 
//   // opposite corners of a rectangle.
//   int height = fabs(a.y - b.y);
//   int width = fabs(a.x - b.x);
//   // Return the area of the rectangle.
//   double area = width * height;
//   return area;
// }



// == Modify above here for step 1 == //

int main(int argc, char* argv[]) {

  if (argc != 6){
    fprintf(stderr, "Error, incorrect arguments\n"
        "Usage: %s a.x a.y b.x b.y cost\n", argv[0]);
    return 1;
  }

  Point P1;
  Point P2;
  P1.x = atof(argv[1]);
  P1.y = atof(argv[2]);
  P2.x = atof(argv[3]);
  P2.y = atof(argv[4]);

  double cost = atof(argv[5]);
  double area = rectangle_area(P1, P2);

  printf ("Area: %2.2lf Cost: %2.2lf\n", area, compute_cost(area, cost));
  return 0;
}