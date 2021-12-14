
#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_

#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "anomaly_detection_util.h"

using namespace std;


// ------------ DO NOT CHANGE -----------

class Circle{
public:
	Point center;
	float radius;
	Circle(Point c,float r):center(c),radius(r){}
};
// --------------------------------------

Circle findMinCircle(Point **points, size_t size);
float distance (const Point &p1, const Point &p2);
bool is_in_circle(const Point &p, const Circle &c);


// you can add here additional methods

#endif /* MINCIRCLE_H_ */
