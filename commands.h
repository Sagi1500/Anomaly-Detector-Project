
#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>

#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

class DefaultIO {
public:
    virtual string read() = 0;

    virtual void write(string text) = 0;

    virtual void write(float f) = 0;

    virtual void read(float *f) = 0;

    virtual ~DefaultIO() {}

    /**
     * The function will receive a file name and read it to a file.
     * @param file_name is the new file name.
     */
    void read_file(string file_name) {
        // creating a new string and new out stream to a file.
        string s = "";
        ofstream out(file_name);

        // read from the file until row that contain done. done is the last word in the file.
        while ((s = read()) != "done") {
            out << s << endl;
        }

        // close the out stream.
        out.close();
    }
};


// you may add here helper classes

/**
 * This struct will contain information that might be needed for executing the commands.
 */
struct CurrentState {
    float threshold;
    vector<AnomalyReport> reports;

    /**
     * Constructor.
     */
    CurrentState() {
        threshold = 0.9;
    }

};


// you may edit this class
class Command {
protected:
    DefaultIO *dio;
public:
    const string description;

    Command(DefaultIO *dio, const string description) : dio(dio), description(description) {}

    virtual void execute(CurrentState *current_state) = 0;

    virtual ~Command() {}
};

// implement here your command classes

/**
 * UploadCommand Class
 * This class will upload a csv file form the client to the server.
 */
class UploadCommand : public Command {
public:
    /**
     * Constructor for UploadCommand.
     * @param dio is the IO type.
     */
    UploadCommand(DefaultIO *dio) : Command(dio, "upload a time series csv file") {}

   /**
    * The function will execute the UploadCommand command
    * @param current_state is the current state for the current input.
    */
    void execute(CurrentState *current_state) override {
        dio->write("Please upload your local train CSV file.\n");
        dio->read_file("anomaly train.csv");
        dio->write("Upload complete.\n");
        dio->write("Please upload your local test CSV file.\n");
        dio->read_file("anomaly test.csv");
        dio->write("Upload complete.\n");
    }
};

/**
 * SetAlgorithmCommand class
 * The command will show the client the current threshold and give him the opportunity to change it.
 */
class SetAlgorithmCommand : public Command {
public:
    /**
     * Constructor for SetAlgorithmCommand
     * @param dio is the IO type.
     */
    SetAlgorithmCommand(DefaultIO *dio) : Command(dio, "algorithm settings") {}

     /**
      * The function will execute the SetAlgorithmCommand command
      * @param current_state is the current state for the current input.
      */
    void execute(CurrentState *current_state) override {
        bool is_legal_input = false;
        dio->write("The current correlation threshold is");
        dio->write(current_state->threshold);
        dio->write("\n");

        // This loop will ask the client to choose new threshold and run until he chooses one that is between 0 and 1.
        while (!is_legal_input) {
            float *f;
            dio->write("Please enter new threshold value\n");
            dio->read(f);
            // checking if the input is legal.
            if (*f <= 1 && *f > 0) {
                is_legal_input = true;
            }
            dio->write("please choose a value between 0 and 1.\n");
        }
    }
};

/**
 * AnomalyDetectionCommand class
 */
class AnomalyDetectionCommand : public Command {
public:
    /**
     * Constructor for AnomalyDetectionCommand
     * @param dio is the IO type.
     */
    AnomalyDetectionCommand(DefaultIO *dio) : Command(dio, "detect anomalies") {}

    /**
     * The function will execute the AnomalyDetectionCommand command
     * @param current_state is the current state for the current input.
     */
    void execute(CurrentState *current_state) override {
        // creating time series for the csv files.
        TimeSeries train("anomaly train.csv");
        TimeSeries test("anomaly test.csv");
        HybridAnomalyDetector had;
        vector<correlatedFeatures> cf_vector = had.getNormalModel();

        // setting the threshold to the current value.
        had.setThreshold(current_state->threshold);

        // learn the train csv file.
        had.learnNormal(train);

        // detect the anomaly in the test file.
        current_state->reports = had.detect(test);

        dio->write("anomaly detection complete.\n");
    }
};

/**
 * DisplayResultsCommand class
 */
class DisplayResultsCommand : public Command {
public:
    /**
     * Constructor for DisplayResultsCommand
     * @param dio is the IO type.
     */
    DisplayResultsCommand(DefaultIO *dio) : Command(dio, "display results") {}

    /**
     * The function will execute the DisplayResultsCommand command
     * @param current_state is the current state for the current input.
     */
    void execute(CurrentState *current_state) override {
        for (AnomalyReport anomalyReport: current_state->reports) {
            dio->write(anomalyReport.timeStep);
            dio->write("\t"+anomalyReport.description+"\n");
        }
        dio->write("Done.\n");
    }
};

/**
 * UploadAndAnalyzeCommand class
 */
class UploadAndAnalyzeCommand : public Command {
public:
    /**
     * Constructor for UploadAndAnalyzeCommand
     * @param dio is the IO type.
     */
    UploadAndAnalyzeCommand(DefaultIO *dio) : Command(dio, "upload anomalies and analyze results") {}

    /**
    * The function will execute the UploadAndAnalyzeCommand command
    * @param current_state is the current state for the current input.
    */
    void execute(CurrentState *current_state) override {

    }
};

/**
 * ExitCommand class
 * This command will exit the menu and stop the communication with the client.
 */
class ExitCommand : public Command {
public:
    /**
   * Constructor for ExitCommand
   * @param dio is the IO type.
   */
    ExitCommand(DefaultIO *dio) : Command(dio, "exit") {}

    /**
     * The function will execute the ExitCommand
     * @param current_state is the current state for the current input.
     */
    void execute(CurrentState *current_state) override {
        // must implement the execute function.
    }

};






#endif /* COMMANDS_H_ */
