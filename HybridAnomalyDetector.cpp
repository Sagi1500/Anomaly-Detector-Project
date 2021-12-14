
#include "HybridAnomalyDetector.h"
#include "SimpleAnomalyDetector.h"
#include "anomaly_detection_util.h"

HybridAnomalyDetector::HybridAnomalyDetector() {
    // TODO Auto-generated constructor stub
}

void HybridAnomalyDetector::learnNormal(const TimeSeries &ts) {
    map<string, vector<float>> *pointer = new map<string, vector<float>>;
    *pointer = ts.get_map();
    //loop that runs on ts's map
    for (map<string, vector<float >>::iterator itr1 = pointer->begin(); itr1 != pointer->cend();
         itr1++) {
        // maxPearson for saving the max value of itr1 and itr2 pearson values, initialize by 0.
        float maxPearson = 0.9;
        float minPearson = 0.5;
        float currentPearson = 0;
        // c is for saving the title of the max pearson, initialize as empty string.
        string c;
        //loop that runs on ts's map from the next itr1 to the end.
        for (map<string, vector<float >>::iterator itr2 = itr1; ++itr2 != pointer->end();) {
            //calculate the pearson between itr1 float values and itr2 float values.
            float p = fabsf(
                    pearson(itr1->second.data(), itr2->second.data(), (int) itr1->second.size()));
            //if p is bigger than the maxPearson, set p to be the new maxPearson.
            if (p >= maxPearson) {
                maxPearson = p;
                currentPearson = p;
                c = itr2->first;
            } else if (p > currentPearson && p >= minPearson && p < maxPearson) {
                minPearson = p;
                currentPearson = p;
                c = itr2->first;
            }
        }
        // if was found pearson's value bigger than 0 than associate itr1 and itr2  as correlated features.
        if (!c.empty()) {
            //set correlatedFeatures's values.
            correlatedFeatures correlatedF;
            correlatedF.feature1 = itr1->first;
            correlatedF.feature2 = c;
            correlatedF.corrlation = currentPearson;
            //initialize array of points that will contain x's values from itr1 and y's values from itr2.
            Point *points[itr1->second.size()];
            //loop that creates all the points based on itr1 and itr2.
            Point *point;
            for (int i = 0; i < itr1->second.size(); ++i) {
                point = new Point(itr1->second.at(i), ts.get_map().find(c)->second.at(i));
                points[i] = point;
            }
            float space = 1.1;
            //if 0.5<= and >0.9 do:
            if (currentPearson >= 0.5 && currentPearson < 0.9) {
                //min_circle
                correlatedF.circle = findMinCircle(points, itr1->second.size());
                correlatedF.threshold = correlatedF.circle.radius * space;
            }
                //else if >= 0.9 do:
            else if (currentPearson >= 0.9) {
                //set correlatedFeatures's values based on the points.
                correlatedF.lin_reg = linear_reg(points, (int) itr1->second.size());
                correlatedF.threshold = biggestDev(points, itr1->second.size(), correlatedF.lin_reg) * space;
            }
            //add the current correlatedFeature to this correlatedFeature.
            this->cf.push_back(correlatedF);
            //delete alloc points
            for (int i = 0; i < itr1->second.size(); i++) {
                delete points[i];
            }
        }
    }
}

vector<AnomalyReport> HybridAnomalyDetector::detect(const TimeSeries &ts) {
    vector<correlatedFeatures> preVector = this->getNormalModel();
    vector<AnomalyReport> anomalyReportVector;
    //loop that runs on ts's raws values.
    for (long rawNumber = 0; rawNumber < ts.get_map().begin()->second.size(); ++rawNumber) {
        //loop that runs on the correlatedFeature of preVector's table.
        for (const correlatedFeatures &c: preVector) {
            //calculates x and y float values from ts in rawNumber and the 2 correlated feature from previous table.
            float floatValue1 = ts.get_map().find(c.feature1)->second.at(rawNumber);
            float floatValue2 = ts.get_map().find(c.feature2)->second.at(rawNumber);
            //create a point: x's value from feature1 and y's value from feature2.
            Point *p = new Point(floatValue1, floatValue2);
            //calculate the dev between the new given table's point to lin_reg from the pre table.
            bool isValid = true;
            //************* if we need to use lin_reg or minCircle
            if (c.corrlation >= 0.5 && c.corrlation < 0.9) {
                float distanceValue = distance(*p, c.circle.center);

                if (distanceValue > c.threshold) {
                    isValid = false;
                }
            } else if (c.corrlation >= 0.9) {
                float devValue = dev(*p, c.lin_reg);
                if (devValue > c.threshold) {
                    isValid = false;
                }
            }
            //delete alloc point.
            delete p;
            //if there is deviation (anomaly) its report.
            if (!isValid) {
                //raws' number start with 1 and not 0
                AnomalyReport anomalyReport(c.feature1 + "-" + c.feature2, rawNumber + 1);
                anomalyReportVector.push_back(anomalyReport);
            }
        }
    }
    return anomalyReportVector;
}

HybridAnomalyDetector::~HybridAnomalyDetector() = default;

