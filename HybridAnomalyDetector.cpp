
#include "HybridAnomalyDetector.h"
#include "SimpleAnomalyDetector.h"
#include "anomaly_detection_util.h"

/**
 * constructor.
 */
HybridAnomalyDetector::HybridAnomalyDetector() = default;
//: SimpleAnomalyDetector() {
//    this->cf = SimpleAnomalyDetector::getNormalModel();
//}

/**
 * delete.
 */
HybridAnomalyDetector::~HybridAnomalyDetector() = default;

/**
 * add to correlatedF a threshold and lin_reg or circle.
 * @param correlatedF is a correlatedFeatures
 * @param points is array of points
 * @param size is the size of points' array.
 */
void HybridAnomalyDetector::addSpecificValToCF(correlatedFeatures &correlatedF, Point **points, size_t size) {
    float space = 1.1;
    //if 0.5<= and > threshold do:
    if (correlatedF.corrlation >= 0.5 && correlatedF.corrlation < threshold) {
        //min_circle
        correlatedF.circle = findMinCircle(points, size);
        correlatedF.threshold = correlatedF.circle.radius * space;
    }
        //else if >= threshold do:
    else {
        SimpleAnomalyDetector::addSpecificValToCF(correlatedF, points, size);
    }
}

/**
 * compare p to min or max pearson and set the current pearson value.
 * @param p is a abs pearson value.
 * @param maxPearson is the minimal max pearson value.
 * @param minPearson is maximal min pearson value.
 * @param currentPearson is the current pearson value.
 */
void HybridAnomalyDetector::setCurrentPearson(float &p, float &maxPearson, float &minPearson, float &currentPearson) {
    //if p is bigger than the maxPearson, set p to be the new maxPearson.
    if (p >= maxPearson) {
        maxPearson = p;
        currentPearson = p;
    } else if (p > currentPearson && p >= minPearson && p < maxPearson) {
        minPearson = p;
        currentPearson = p;
    }
}

/**
 *
 * @param c is a correlatedFeatures.
 * @param p is a pointer to point.
 * @return true if the point valid and doesn't creat anomaly and false otherwise.
 */
bool HybridAnomalyDetector::isPointIsValid(const correlatedFeatures &c, Point *p) {
    bool isValid = true;
    if (c.corrlation >= 0.5 && c.corrlation < threshold) {
        float distanceValue = distance(*p, c.circle.center);
        if (distanceValue > c.threshold) {
            isValid = false;
        }
    } else {
        isValid = SimpleAnomalyDetector::isPointIsValid(c, p);
    }
    return isValid;
}

