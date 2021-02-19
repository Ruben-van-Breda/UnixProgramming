#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Point
{
    double x;
    double y;
} Point;

double rectangle_area(struct Point a, struct Point b);
double compute_cost(double area, double cost);


#endif