//#include <iostream>
//#include <vector>
//#include <stdlib.h>
//#include <time.h>
//#include <math.h>
//#include "minCircle.h"
//#include <chrono>
//
//using namespace std;
//using namespace std::chrono;
//
//
//Point** generate(Point center,int R, size_t size){
//	Point** p =new Point*[size];
//	for(size_t i=0;i<size;i++){
//		float r=1+rand()%R;
//		float a=3.14159*(rand()%360)/180;
//		float x=center.x+r*cos(a);
//		float y=center.y+r*sin(a);
//		p[i]=new Point(x,y);
//	}
//	return p;
//}
//
//
//int main(){
//	srand (time(NULL));
//	const size_t N=250;
//	float R=10+rand()%1000;
//	float cx=-500+rand()%1001;
//	float cy=-500+rand()%1001;
//	Point** ps=generate(Point(cx,cy),R,N);
//
//	// your working copy
//	Point** ps_copy=new Point*[N];
//	for(size_t i=0;i<N;i++)
//		ps_copy[i]=new Point(ps[i]->x,ps[i]->y);
//
//	auto start = high_resolution_clock::now();
//	Circle c=findMinCircle(ps_copy,N);
//	auto stop = high_resolution_clock::now();
//
//	if((int)c.radius>(int)R)
//		cout<<"you need to find a minimal radius (-40)"<<endl;
//
//	bool covered=true;
//	for(size_t i=0;i<N && covered;i++){
//		float x2=(c.center.x-ps[i]->x)*(c.center.x-ps[i]->x);
//		float y2=(c.center.y-ps[i]->y)*(c.center.y-ps[i]->y);
//		float d=sqrt(x2+y2);
//		if(d>c.radius+1)
//			covered=false;
//	}
//	if(!covered)
//		cout<<"all points should be covered (-45)"<<endl;
//
//	auto duration = duration_cast<microseconds>(stop - start);
//	int stime=duration.count();
//	cout<<"your time: "<<stime<<" microseconds"<<endl;
//	if(stime>3000){
//		cout<<"over time limit ";
//		if(stime<=3500)
//			cout<<"(-5)"<<endl;
//		else if(stime<=4000)
//			cout<<"(-8)"<<endl;
//		else if(stime<=6000)
//			cout<<"(-10)"<<endl;
//		else cout<<"(-15)"<<endl;
//	}
//
//	for(size_t i=0;i<N;i++){
//		delete ps[i];
//		delete ps_copy[i];
//	}
//	delete[] ps;
//	delete[] ps_copy;
//
//	cout<<"done"<<endl;
//	return 0;
//}
//
#include "minCircle.h"
#include <math.h>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <iostream>
#include <math.h>
#include <vector>

/**
 *
 * @param p1 is the first point
 * @param p2 is a second point
 * @return the distance between the 2 points
 */
float distance(const Point &p1, const Point &p2) {
    return sqrtf((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

/**
 *
 * @param p is a point
 * @param c is a circle
 * @return true if the point is inside or on the circle and false otherwise.
 */
bool is_in_circle(const Point &p, const Circle &c) {
    return distance(p, c.center) <= c.radius;
}

/**
 * helper for founding the center of a unique circle created by 3 points.
 * @param p1 is a point
 * @param p2  is a point
 * @return the center of a circle.
 */
Point find_center(const Point &p1, const Point &p2) {
    float b = (p1.x * p1.x) + (p1.y * p1.y);
    float c = (p2.x * p2.x) + (p2.y * p2.y);
    float d = (p1.x * p2.y) - (p1.y * p2.x);
    return Point((p2.y * b - p1.y * c) / (2 * d), (p1.x * c - p2.x * b) / (2 * d));
}

/**
 *
 * @param p1 is a point
 * @param p2 is a point
 * @param p3 is a point
 * @return a unique circle created by the 3 points.
 */
Circle create_circle(const Point &p1, const Point &p2, const Point &p3) {
    Point center = find_center(Point(p2.x - p1.x, p2.y - p1.y), Point(p3.x - p1.x, p3.y - p1.y));
    center.x += p1.x;
    center.y += p1.y;
    return Circle(center, distance(center, p1));
}

/**
 *
 * @param p1 is a point
 * @param p2 is a point
 * @return a circle that the 2 points are its diameter.
 */
Circle create_circle(const Point &p1, const Point &p2) {
    Point center = Point((p1.x + p2.x) / 2.0, (p1.y + p2.y) / 2.0);
    // the radius is half of the distance between p1 and p2
    return Circle(center, distance(p1, p2) / 2);
}

/**
 *
 * @param c is a circle.
 * @param points is an array of points.
 * @param size is the size of points' array.
 * @return true if all the points are inside or on the circle and false otherwise.
 */
bool is_valid(const Circle &c, const Point **points, const size_t size) {
    for (int i = 0; i < size; i++) {
        if (!is_in_circle(*points[i], c)) {
            return false;
        }
    }
    return true;
}

/**
 *
 * @param points is an array of points
 * @param size is the size of points' array.
 * @return the minimum circle for 3 points or 2 points or 1 point.
 */
Circle min_circle(const Point **points, const size_t size) {
    if (0 == size) {
        return Circle(Point(0, 0), 0);
    } else if (1 == size) {
        return Circle(*points[0], 0);
    } else if (2 == size) {
        return create_circle(*points[0], *points[1]);
    }
    for (int i = 0; i < size; i++) {
        for (int j = 1 + 1; j < 3; j++) {
            Circle c = create_circle(*points[i], *points[j]);
            if (is_valid(c, points, size)) {
                return c;
            }
        }
    }
    return create_circle(*points[0], *points[1], *points[2]);
}

/**
 *
 * @param another_array helper array.
 * @param points ia an array (main) of points.
 * @param sizeP is the size op points' array (main).
 * @return the minimum circle that including all the points.
 */
Circle
find_min_circle_with_anther_array(const Point **another_array, size_t sizeA, const Point **points, size_t sizeP) {
    if (sizeP == 0 || sizeA == 3) {
        return min_circle(another_array, sizeA);
    }
    Circle temp = find_min_circle_with_anther_array(another_array, sizeA, points, sizeP - 1);
    if (is_in_circle(*points[sizeP - 1], temp)) {
        return temp;
    }
    another_array[sizeA] = points[sizeP - 1];
    sizeA++;
    return find_min_circle_with_anther_array(another_array, sizeA, points, sizeP - 1);

}

/**
 *
 * @param points is an array of points
 * @param size is the size of the points' array
 * @return the minimum circle including all the points.
 */
Circle findMinCircle(const Point **points, size_t size) {
    const Point *temp[3];
    size_t size_temp = 0;
    return find_min_circle_with_anther_array(temp, size_temp, points, size);
}






//*****************************************************************************************




using namespace std;

// Defining infinity
const float INF = 1e18;


// Function to return the euclidean distance
// between two points
float dist(const Point &a, const Point &b) {
    return sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// Function to check whether a point lies inside
// or on the boundaries of the circle
bool is_inside(const Circle &c, const Point &p) {
    return dist(c.center, p) <= c.radius;
}

// The following two functions are used
// To find the equation of the circle when
// three points are given.

// Helper method to get a circle defined by 3 points
Point get_circle_center(float bx, float by,
                        float cx, float cy) {
    float B = bx * bx + by * by;
    float C = cx * cx + cy * cy;
    float D = bx * cy - by * cx;
    return {(cy * B - by * C) / (2 * D),
            (bx * C - cx * B) / (2 * D)};
}

// Function to return a unique circle that
// intersects three points
Circle circle_from(const Point &A, const Point &B,
                   const Point &C) {
    Point I = get_circle_center(B.x - A.x, B.y - A.y,
                                C.x - A.x, C.y - A.y);

    I.x += A.x;
    I.y += A.y;
    return {I, dist(I, A)};
}

// Function to return the smallest circle
// that intersects 2 points
Circle circle_from(const Point &A, const Point &B) {
    // Set the center to be the midpoint of A and B
    Point C = {((A.x + B.x) / 2.0), (A.y + B.y) / 2.0};

    // Set the radius to be half the distance AB
    return {C, dist(A, B) / 2.0};
}

// Function to check whether a circle
// encloses the given points
bool is_valid_circle(const Circle &c,
                     const vector<Point> &P) {

    // Iterating through all the points
    // to check  whether the points
    // lie inside the circle or not
    for (const Point &p: P)
        if (!is_inside(c, p))
            return false;
    return true;
}


Circle min_circle_trivial(vector<Point> &P) {
    assert(P.size() <= 3);
    if (P.empty()) {
        return {{0, 0}, 0};
    } else if (P.size() == 1) {
        return {P[0], 0};
    } else if (P.size() == 2) {
        return circle_from(P[0], P[1]);
    }

    // To check if MEC can be determined
    // by 2 points only
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {

            Circle c = circle_from(P[i], P[j]);
            if (is_valid_circle(c, P))
                return c;
        }
    }
    return circle_from(P[0], P[1], P[2]);
}

Circle welzl_helper(vector<Point> &P,
                    vector<Point> R, int n) {
    if (n == 0 || R.size() == 3) {
        return min_circle_trivial(R);
    }

    int idx = rand() % n;
    Point p = P[idx];

    swap(P[idx], P[n - 1]);

    Circle d = welzl_helper(P, R, n - 1);

    if (is_inside(d, p)) {
        return d;
    }

    R.push_back(p);

    return welzl_helper(P, R, n - 1);
}

Circle welzl(const vector<Point> &P) {
    vector<Point> P_copy = P;
    random_shuffle(P_copy.begin(), P_copy.end());
    return welzl_helper(P_copy, {}, P_copy.size());
}


int main() {
    Circle mec = welzl({{0, 0},
                        {0, 1},
                        {1, 0}});
    cout << "Center = { " << mec.center.x << ", " << mec.center.y
         << " } Radius = " << mec.radius << endl;

    Circle mec2 = welzl({{5,  -2},
                         {-3, -2},
                         {-2, 5},
                         {1,  6},
                         {0,  2}});
    cout << "Center = { " << mec2.center.x << ", " << mec2.center.y
         << " } Radius = " << mec2.radius << endl;

    return 0;
}