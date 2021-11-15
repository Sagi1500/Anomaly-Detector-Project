#include "SimpleAnomalyDetector.h"
#include "anomaly_detection_util.h"

/**
 * constructor.
 */
SimpleAnomalyDetector::SimpleAnomalyDetector() {

}

/**
 * delete.
 */
SimpleAnomalyDetector::~SimpleAnomalyDetector() {

}

/**
 *
 * @param points is array of points.
 * @param len is the length of points' array.
 * @param line is the linear_reg we want to compere the points.
 * @return the biggest dev value.
 */
float biggestDev(Point **points, int len, Line line) {
    float max = -1;
    //loop that runs on the points.
    for (int i = 0; i < len; i++) {
        float devValue = dev(*points[i], line);
        //find and set the max dev value.
        if (devValue > max) {
            max = devValue;
        }
    }
    return max;
}

/**
 * set SimpleAnomalyDetector by set all the correlated features in the TimeSeries.
 * @param ts is a TimeSeries.
 */
void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts) {
    map<string, vector<float>> *pointer = new map<string, vector<float>>;
    *pointer = ts.get_map();
    //loop that runs on ts's map
    for (map<string, vector<float>>::const_iterator itr1 = pointer->cbegin(); itr1 != pointer->cend(); itr1++) {
        // maxPearson for saving the max value of itr1 and itr2 pearson values, initialize by 0.
        float maxPearson = 0;
        // c is for saving the title of the max pearson, initialize as empty string.
        string c;
        //loop that runs on ts's map from the next itr1 to the end.
        for (map<string, vector<float>>::const_iterator itr2 = itr1; ++itr2 != pointer->end();) {
            //calculate the pearson between itr1 float values and itr2 float values.
            float p = pearson((float*)itr1->second.data(), (float*)itr2->second.data(), (int) itr1->second.size());
            //if p is bigger than the maxPearson, set p to be the new maxPearson.
            if (p > maxPearson) {
                maxPearson = p;
                c = itr2->first;
            }
        }
        // if was found pearson's value bigger than 0 than associate itr1 and itr2  as correlated features.
        if (!c.empty()) {
            //set correlatedFeatures's values.
            correlatedFeatures correlatedF;
            correlatedF.feature1 = itr1->first;
            correlatedF.feature2 = c;
            //initialize array of points that will contain x's values from itr1 and y's values from itr2.
            Point *points[itr1->second.size()];
            //loop that creates all the points based on itr1 and itr2.
            Point *point;
            for (int i = 0; i < itr1->second.size(); ++i) {
                point = new Point(itr1->second.at(i), ts.get_map().find(c)->second.at(i));
                points[i] = point;
            }
            //set correlatedFeatures's values based on the points.
            correlatedF.lin_reg = linear_reg(points, (int) itr1->second.size());
            correlatedF.corrlation = maxPearson;
            correlatedF.threshold = biggestDev(points, (int) itr1->second.size(), correlatedF.lin_reg);
            //add the current correlatedFeature to this correlatedFeature.
            this->cf.push_back(correlatedF);
           //printf("\n\n%d\n\n",this->getNormalModel().capacity());
            for (int i = 0; i < itr1->second.size(); i++) {
                delete points[i];
            }
        }
    }
    delete pointer;
//    for (correlatedFeatures c: this->getNormalModel()) {
//        printf("33: %s", c.feature1.data());
//        printf("   %s\n", c.feature2.data());
//    }
}


vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    vector<correlatedFeatures> preVector = this->getNormalModel();
    vector<AnomalyReport> anomalyReportVector;// = new vector<AnomalyReport>;
    //loop that runs on ts's raws values.
    for (int rawNumber = 0; rawNumber < ts.get_map().begin()->second.size(); ++rawNumber) {
        //loop that runs on the correlatedFeature of preVector's table.
        for (const correlatedFeatures &c: preVector) {
            //calculates x and y float values from ts in rawNumber and the 2 correlated feature from previous table.
            float floatValue1 = ts.get_map().find(c.feature1)->second.at(rawNumber);
            float floatValue2 = ts.get_map().find(c.feature2)->second.at(rawNumber);
            //create a point: x's value from feature1 and y's value from feature2.
            Point *p = new Point(floatValue1, floatValue2);
            //calculate the dev between the new given table's point to lin_reg from the pre table.
            float devValue = dev(*p, c.lin_reg);
            delete p;
            //if there is deviation (anomaly) its report.
            if (devValue > c.threshold) {
                AnomalyReport anomalyReport(c.feature1 + "-" + c.feature2, rawNumber + 1);
                anomalyReportVector.push_back(anomalyReport);
            }
        }
    }
    return anomalyReportVector;
}
