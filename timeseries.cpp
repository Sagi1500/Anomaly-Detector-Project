/*
 * timeseries.cpp
 * Author: Shoval Argov 206626681 and Sagi Wiletnzik 208827527
 */

#include "timeseries.h"


/**
 * The function will print a map in the from of  map<string,vector<float>>
 */
void TimeSeries::print_map() {
    for (map<string, vector<float>>::iterator itr = this->m_map.begin(); itr != this->m_map.end(); itr++) {
        cout << itr->first << endl;
        print_vector(itr->second);
    }
}


/**
 * The function will print the vector.
 * @param input is the vector to print.
 */
void TimeSeries::print_vector(const vector<float> &input) {
    for (int i = 0; i < input.size(); i++) {
        cout << input.at(i) << ' ';
    }
    cout << "" << endl;
}
