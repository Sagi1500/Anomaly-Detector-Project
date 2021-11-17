#ifndef TIMESERIES_H_
#define TIMESERIES_H_

#include <map>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>


using namespace std;
/*
 * timeseries.h
 * Author: Shoval Argov 206626681 and Sagi Wiletnzik 208827527
 */


class TimeSeries {
private:
    // member for TimeSeries
    map<string, vector<float>> m_map;
public:

    /**
     * Constructor
     * @param CSVfileName is the file name.
     */
     TimeSeries(const char *CSVfileName) {
        m_map = {};

        // Create an input filestream
        ifstream my_file(CSVfileName);

        // Make sure the file is open
        if (!my_file.is_open()) {
            throw runtime_error("File does not open");
        }

        // read the titles and create keys in the map.
        string key, line, value;
        int counter = 0;
        if (my_file.good()) {
            getline(my_file, line);
            stringstream s(line);
            stringstream temp(line);
            while (getline(s, key, ',')) {
                counter++;
            }

            //creating an array for saving the titles and insert to the array.
            string arr[counter];
            counter = 0;
            while (getline(temp, key, ',')) {
                arr[counter] = key;
                counter++;
            }

            //add titles to the map.
            int array_size = arr->length();
            for (int i = 0; i < array_size; i++) {
                vector<float> v;
                m_map.insert(pair<string, vector<float>>(arr[i], v));
            }

            /*
             *  adding the values to the map by taking each row and split on every ",".
             *  On each round i = 0 for starting with the first column of the file.
             */
            while (getline(my_file, line)) {
                stringstream s(line);
                int i = 0;
                // insert to the map
                while (getline(s, key, ',')) {
                    m_map[arr[i]].push_back(stof(key));
                    i++;
                }
            }
            //clear the string streams.
            temp.clear();
            s.clear();

        }
        // close the stream.
        my_file.close();
    }

    /**
     * Getter for the map.
     * @return the map.
     */
    map<string, vector<float>> get_map() const {
        return this->m_map;
    }

    /**
     * The function will print a map in the from of  map<string,vector<float>>
     */
    void print_map();

    /**
     * The function will print the vector.
     * @param input is the vector to print.
     */
    static void print_vector(vector<float> const &input);


};

#endif /* TIMESERIES_H_ */