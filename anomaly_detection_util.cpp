/*
 * anomaly_detection_util.cpp
 *
 * Author: Shoval Argov 206626681 and Sagi Wiletnzik 208827527
 */

#include <cmath>
#include "anomaly_detection_util.h"

/**
 * @param x is the x value.
 * @param line is the line.
 * @return the y value.
 */
float getYValueFromLine(float x, Line line) {
    return line.a * x + line.b;
}


/**
 *
 * @param value is a pointer to array.
 * @param size is the array's size.
 * @return the average.
 */
float avg(float *value, int size) {

    // checking the case when the size is 0 or negative.
    if (size < 1) {
        throw "invalid division";
    }
    float sumX = 0;
    for (int i = 0; i < size; i++) {
        sumX += value[i];
    }
    return sumX / (float) size;
}

/**
 * @param x is a pointer to the number.
 * @param size is the size of x;
 * @return the variance of x.
 */
float var(float *x, int size) {

    // checking the case when the size is 0 or negative.
    if (size < 1) {
        throw "invalid division";
    }
    float powerSum = 0;

    // The loop calculates the sum when each number is in the power of 2.
    for (int i = 0; i < size; i++) {
        powerSum += x[i] * x[i];
    }
    float avgX = avg(x, size);
    return (powerSum / (float) size) - (avgX * avgX);
}


/**
 * @param x  is a pointer to the first number.
 * @param y is a pointer to the second number.
 * @param size is the valid size for x and y.
 * @return the variance between the 2 numbers.
 */
float cov(float *x, float *y, int size) {

    // checking the case when the size is 0 or negative.
    if (size < 1) {
        throw "invalid division";
    }

    // checking the case when the size is not 0.
    float avgX = avg(x, size);
    float avgY = avg(y, size);

    float sum = 0;

    // This loop calculates the cov.
    for (int i = 0; i < size; i++) {
        sum += x[i] * y[i];
    }
    return (sum / (float) size) - (avgX * avgY);
}

/**
 * @param x  is a pointer to the first number.
 * @param y is a pointer to the second number.
 * @param size is the valid size for x and y.
 * @return the Pearson correlation coefficient of X and Y.
 */
float pearson(float *x, float *y, int size) {

    float v = sqrtf(var(x, size)) * sqrtf(var(y, size));
    // checking the case when the variance is 0.
    if (v == 0) {
        throw "Division by zero condition";
    }
    return (cov(x, y, size)) / (v);
}

/**
 *
 * @param points is a pointer to array of points.
 * @param size is the array's size.
 * @return  The function performs a linear regression and returns the line equation
 */
Line linear_reg(Point **points, int size) {

    float x[size];
    float y[size];
    for (int i = 0; i < size; i++) {
        x[i] = points[i]->x;
        y[i] = points[i]->y;
    }
    float varA = var(x, size);
    // checking the case when the variance is 0.
    if (varA == 0) {
        throw "Division by zero condition";
    }
    float a = cov(x, y, size) / varA;
    float b = avg(y, size) - a * avg(x, size);
    return Line(a, b);
}

/**
 *
 * @param p is the point.
 * @param l is the line.
 * @return the deviation between point p and the line
 */
float dev(Point p, Line l) {
    return fabsf(getYValueFromLine(p.x, l) - p.y);
}

/**
 *
 * @param p is a point.
 * @param points is a pointer to array of points.
 * @param size is the array's size.
 * @return  the deviation between point p and the line equation of the points
 */
float dev(Point p, Point **points, int size) {
    Line line = linear_reg(points, size);
    return dev(p, line);
}