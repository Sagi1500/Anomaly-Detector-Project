/*
 * animaly_detection_util.cpp
 *
 * Author: write your ID and name here
 */
#include <iostream>
#include <math.h>
#include <cstdio>
#include "anomaly_detection_util.h"

float getYValueFromLine(float x, Line line);

// returns the variance of X
float var(float* x, int size){

    // checking the case when the size is 0.
    if (size == 0) {
        throw "Division by zero condition";
    }

    // checking the case when size is not  0;
    float sum = 0;
    float powerSum = 0;
    for (int i=0 ; i < size ; i++) {
        sum += x[i];
        powerSum += pow(x[i],2);
    }

    return ((1 / (float)size) * powerSum) - (pow((1 / (float) size) * sum,2));
}

// returns the covariance of X and Y
float cov(float* x, float* y, int size) {

    // checking the case when the size is 0.
    if (size == 0) {
        throw "Division by zero condition";
    }

    // checking the case when the size is not 0.
    float avgX = avg(x,size);
    float avgY =avg(y,size);

    float cov = 0;
    for (int i=0 ; i < size ; i++) {
        cov += (x[i]-avgX) * (y[i] - avgY);
    }
    return cov / (float) size;
}


// returns the Pearson correlation coefficient of X and Y
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

// performs a linear regression and returns the line equation
Line linear_reg(Point** points, int size){

    float x [size];
    float y [size];
    for (int i=0 ; i < size ; i++){
        x[i] = points[i]->x;
        y[i] = points[i]->y;
    }
    float varA = var(x,size);
    if (varA == 0) {
        return Line ()
    }
    float a = cov(x,y,size) / varA;
    float b = avg(y,size) - a * avg(x,size);
    return Line(a,b);
}

// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size){
    return 0;
}

// returns the deviation between point p and the line
float dev(Point p,Line l){
    return abs(p.y - getYValueFromLine(p.x,l) );
}

float getYValueFromLine(float x, Line line) {
    return line.a * x + line.b;
}

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



