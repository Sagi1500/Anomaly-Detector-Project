/*
 * SimpleAnomalyDetector.h
 * Author: Shoval Argov 206626681 and Sagi Wiletnzik 208827527
 */

#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>
#include "minCircle.h"

struct correlatedFeatures{
    string feature1,feature2;  // names of the correlated features
	float corrlation;
	Line lin_reg;
    Circle circle = {{0,0},-1};
	float threshold;
};


class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{
protected:
    vector<correlatedFeatures> cf;
    float threshold;
public:
    SimpleAnomalyDetector();
	virtual ~SimpleAnomalyDetector();

	virtual void learnNormal(const TimeSeries& ts);
	virtual vector<AnomalyReport> detect(const TimeSeries& ts);
    virtual float biggestDev(Point **points, unsigned long len, Line line);
    virtual void addSpecificValToCF(correlatedFeatures &correlatedF, Point **points, size_t size);
    virtual void setCurrentPearson(float &p, float &maxPearson, float &minPearson, float &currentPearson);
    virtual bool isPointIsValid(const correlatedFeatures &c, Point *p);
	vector<correlatedFeatures> getNormalModel(){
		return cf;
	}
    void setThreshold(float threshold) {
        this->threshold = threshold;
    }
};

#endif /* SIMPLEANOMALYDETECTOR_H_ */
