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
public:
    SimpleAnomalyDetector();
	virtual ~SimpleAnomalyDetector();

	virtual void learnNormal(const TimeSeries& ts);
	virtual vector<AnomalyReport> detect(const TimeSeries& ts);
    virtual float biggestDev(Point **points, unsigned long len, Line line);

	vector<correlatedFeatures> getNormalModel(){
		return cf;
	}
};

#endif /* SIMPLEANOMALYDETECTOR_H_ */
