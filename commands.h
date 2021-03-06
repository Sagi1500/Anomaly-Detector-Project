
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
     * The function will receive a file name and read it.
     * @param file_name is the new file name.
     */
    void read_file(string file_name) {
        // creating a new string and new out stream to a file.
        string data = "";
        ofstream out(file_name);

        // read from the file until row that contain done. done is the last word in the file.
        while ((data = read()) != "done") {
            out << data << endl;
        }

        // close the out stream.
        out.close();
    }
};

/**
 * This struct will contain the information of each group of rows in the output.
 * first is the starting time step time.
 * last is the last time step time.
 * description is the common discretion for all the rows form start to end.
 */
struct AnomalyGroup {
    int first;
    int last;
    string description;
    bool is_true_positive;

    /**
     * Constructor.
     */
    AnomalyGroup() {
        first = 0;
        last = 0;
        description = "";
        is_true_positive = false;
    }
};

/**
 * This struct will contain information that might be needed for executing the commands.
 */
struct CurrentState {
    float threshold;
    vector<AnomalyReport> reports;
    vector<AnomalyGroup> anomaly_group;
    int rows_in_test;

    /**
     * Constructor.
     */
    CurrentState() {
        threshold = 0.9;
        rows_in_test = 0;
    }
};

/**
 * Command class.
 */
class Command {
protected:
    DefaultIO *dio;
public:
    const string description;

    Command(DefaultIO *dio, const string description) : dio(dio), description(description) {}

    virtual void execute(CurrentState *current_state) = 0;

    virtual ~Command() {}
};

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
            float input;
            dio->write("Please enter new threshold value\n");
            dio->read(&input);
            // checking if the input is legal.
            if (input <= 1 && input > 0) {
                current_state->threshold = input;
                is_legal_input = true;
            } else {
                dio->write("please choose a value between 0 and 1.\n");
            }
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
     * The function will analyze the anomaly report vector and create the groups.
     * Rows will be at the same group if the description is the same and the time steps are following.
     * At the end each group will be an element in the vector.
     * @param current_state is the current state.
     */
    void analyze_results(CurrentState *current_state) {
        // create a new group and initialize his members.
        AnomalyGroup group;

        // The loop will go over all the report and create the groups.
        for (std::vector<AnomalyReport>::iterator report = current_state->reports.begin();
             report != current_state->reports.end(); report++) {
            /*
             * checking if the description is equal and the timeStep is 1 less than the group last which means
             * there are in the same group.
             */
            if (report->description == group.description && report->timeStep == group.last + 1) {
                group.last++;
            } else {
                current_state->anomaly_group.push_back(group);
                group.first = report->timeStep;
                group.last = group.first;
                group.description = report->description;
            }
        }
        // push the group to the vector.
        current_state->anomaly_group.push_back(group);
        current_state->anomaly_group.erase(current_state->anomaly_group.begin());
    }

    /**
     * The function will execute the AnomalyDetectionCommand command
     * @param current_state is the current state for the current input.
     */
    void execute(CurrentState *current_state) override {
        // creating time series for the csv files.
        TimeSeries train("anomaly train.csv");
        TimeSeries test("anomaly test.csv");


        // create the Hybrid anomaly and save the number of rows in the test file.
        HybridAnomalyDetector had;
        vector<correlatedFeatures> cf_vector = had.getNormalModel();
        current_state->rows_in_test = test.get_row_number();

        // setting the threshold to the current value.
        had.setThreshold(current_state->threshold);

        // learn the train csv file.
        had.learnNormal(train);

        // detect the anomaly in the test file.
        current_state->reports = had.detect(test);

        // analyze the results.
        analyze_results(current_state);

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
            dio->write("\t" + anomalyReport.description + "\n");
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
     * The function will decide if the group from the starting index to the end index is ture positive.
     * @param currentState is the current state.
     * @param start is the starting index.
     * @param end is the end index.
     * @return true if find true positive (TP), 0 otherwise.
     */
    bool find_true_positive(CurrentState *currentState, int start, int end) {
        for (int i = 0; i < currentState->anomaly_group.size(); i++) {
            AnomalyGroup group = currentState->anomaly_group[i];
            if (is_true_positive(start, end, group.first, group.last)) {
                currentState->anomaly_group[i].is_true_positive = true;
                return true;
            }
        }
        return false;
    }

    /**
     * @param num1_start is the start for the first.
     * @param num1_end is the end for the first.
     * @param num2_start is the start for the second.
     * @param num2_end is the end for the second.
     * @return 1 if true positive, 0 otherwise.
     */
    bool is_true_positive(int num1_start, int num1_end, int num2_start, int num2_end) {
        return (num1_end >= num2_start && num2_end >= num1_start);
    }

    /**
     * initialize all the anomaly to false positive
     * @param current_state is the current state.
     */
    void initialize_to_false_positive(CurrentState *current_state) {
        for (size_t i = 0; i < current_state->anomaly_group.size(); i++) {
            current_state->anomaly_group[i].is_true_positive = false;
        }
    }

    /**
    * The function will execute the UploadAndAnalyzeCommand command
    * @param current_state is the current state for the current input.
    */
    void execute(CurrentState *current_state) override {
        string start, end, line;
        int sum = 0, positive = 0;
        int first, last;
        float true_positive = 0, false_positive = 0;

        initialize_to_false_positive(current_state);

        dio->write("Please upload your local anomalies file.\n");
        while ((line = dio->read()) != "done") {
            size_t i = 0;
            for (; line[i] != ','; i++);
            start = line.substr(0, i);
            end = line.substr(i + 1, line.length());

            // converting from string to int.
            first = stoi(start);
            last = stoi(end);

            // calculate the negative.
            sum += last - first + 1;
            positive++;

            // checking for true positive.
            if (find_true_positive(current_state, first, last))
                true_positive++;
        }
        dio->write("Upload complete.\n");

        // checking for false positive.
        for (AnomalyGroup v: current_state->anomaly_group) {
            if (!v.is_true_positive) {
                false_positive++;
            }
        }

        // calculate and print output.
        float N = (current_state->rows_in_test -1 )/2 - sum ;
        false_positive = ((int) (1000.0 * false_positive / N)) / 1000.0;
        true_positive = ((int) (1000.0 * true_positive / positive)) / 1000.0;
        dio->write("True Positive Rate: ");
        dio->write(true_positive);
        dio->write("\n");
        dio->write("False Positive Rate: ");
        dio->write(false_positive);
        dio->write("\n");
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
