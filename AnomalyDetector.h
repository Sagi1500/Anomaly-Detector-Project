
#ifndef ANOMALYDETECTOR_H_
#define ANOMALYDETECTOR_H_

#include <string>
#include <vector>
#include "timeseries.h"
#include "math.h"

using namespace std;


class AnomalyReport{
public:
	const string description;
	const long timeStep;
    // report of description and timeStep
	AnomalyReport(string description, long timeStep):description(description),timeStep(timeStep){}
};

class TimeSeriesAnomalyDetector {
public:
    //first need to learn about the TimeSeries table
	virtual void learnNormal(const TimeSeries& ts)=0;
    //get TimeSeries table and return vector of description and timeStep
	virtual vector<AnomalyReport> detect(const TimeSeries& ts)=0;
    //delete func
	virtual ~TimeSeriesAnomalyDetector(){}
};

#endif /* ANOMALYDETECTOR_H_ */
