#include "minCircle.h"
#include <math.h>
#include <vector>
#include "anomaly_detection_util.h"

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