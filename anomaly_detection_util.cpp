/*
 * anomaly_detection_util.cpp
 *
 * Author: Shoval Argov 206626681 and Sagi Wiletnzik 208827527
 */


#include <iostream>
#include <math.h>
#include <cstdio>
#include "anomaly_detection_util.h"


/**
 * @param x is a pointer to the number.
 * @param size is the size of x;
 * @return the variance of x.
 */
float var(float* x, int size){

    // checking the case when the size is 0.
    if (size == 0) {
        throw "Division by zero condition";
    }

    // checking the case when size is not  0;
    float sum = 0;
    float powerSum = 0;

    // The loop calculates the regular sum and another sum when each number is in the power of 2.
    for (int i=0 ; i < size ; i++) {
        sum += x[i];
        powerSum += pow(x[i],2);
    }

    return ((1 / (float)size) * powerSum) - (pow((1 / (float) size) * sum,2));
}


/**
 * @param x  is a pointer to the first number.
 * @param y is a pointer to the second number.
 * @param size is the valid size for x and y.
 * @return the variance between the 2 numbers.
 */
float cov(float* x, float* y, int size) {

    // checking the case when the size is 0.
    if (size == 0) {
        throw "Division by zero condition";
    }

    // checking the case when the size is not 0.
    float avgX = avg(x,size);
    float avgY =avg(y,size);

    float cov = 0;

    // This loop calculates the cov.
    for (int i=0 ; i < size ; i++) {
        cov += (x[i]-avgX) * (y[i] - avgY);
    }
    return cov / (float) size;
}

/**
 * @param x  is a pointer to the first number.
 * @param y is a pointer to the second number.
 * @param size is the valid size for x and y.
 * @return the Pearson correlation coefficient of X and Y.
 */
float pearson(float* x, float* y, int size) {

    // checking the case when the size is 0.
    if (size == 0) {
        throw "Division by zero condition";
    }
    float v = sqrt((double) var(x,size)) * sqrt((double) var(y,size));
    if (v == 0) {
        throw "Division by zero condition";
    }
    return (cov(x,y,size)) / (v);
}

/**
 *
 * @param points is a pointer to array of points.
 * @param size is the array's size.
 * @return  The function performs a linear regression and returns the line equation
 */
Line linear_reg(Point** points, int size){

    float x [size];
    float y [size];
    for (int i=0 ; i < size ; i++){
        x[i] = points[i]->x;
        y[i] = points[i]->y;
    }
    float varA = var(x,size);
    if (varA == 0) {
        return Line ();
    }
    float a = cov(x,y,size) / varA;
    float b = avg(y,size) - a * avg(x,size);
    return Line(a,b);
}

/**
 *
 * @param p is a point.
 * @param points is a pointer to array of points.
 * @param size is the array's size.
 * @return  the deviation between point p and the line equation of the points
 */
float dev(Point p,Point** points, int size){
    Line line = linear_reg(points,size);
    return dev(p,line);
}


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
 * @param p is the point.
 * @param l is the line.
 * @return the deviation between point p and the line
 */
float dev(Point p,Line l){
    return fabs(getYValueFromLine(p.x,l) - p.y);
}

/**
 *
 * @param value is a pointer to array.
 * @param size is the array's size.
 * @return the average.
 */
float avg(float *value,int size){

    // checking the case when the size is 0.
    if (size == 0) {
        throw "Division by zero condition";
    }

    float sumX=0;
    for (int i=0 ; i < size ; i++) {
        sumX += value[i];
    }
    return sumX / size;
}



