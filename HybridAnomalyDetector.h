

#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {
public:

	HybridAnomalyDetector();
	virtual ~HybridAnomalyDetector();
    virtual void addSpecificValToCF(correlatedFeatures &correlatedF, Point **points, size_t size) override;
    virtual void setCurrentPearson(float &p, float &maxPearson, float &minPearson, float &currentPearson) override;
    virtual bool isPointIsValid(const correlatedFeatures &c, Point *p) override;
};

#endif /* HYBRIDANOMALYDETECTOR_H_ */
