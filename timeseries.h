
#ifndef TIMESERIES_H_
#define TIMESERIES_H_

using namespace std;

class TimeSeries {

public:
    const char *CSVfileName;

    TimeSeries(const char *CSVfileName) {
        this->CSVfileName = CSVfileName;
    }
    virtual *vactor<string> readFile(const char *CSVfileName));
};


#endif /* TIMESERIES_H_ */
