

#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {
public:

	HybridAnomalyDetector();
	virtual ~HybridAnomalyDetector();
    virtual void learnNormal(const TimeSeries &ts) override;
};

#endif /* HYBRIDANOMALYDETECTOR_H_ */
