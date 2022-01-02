#include "CLI.h"

/**
 * Constructor for CLI.
 *  creating the commands for the menu and insert them to the vector.
 * @param dio
 */
CLI::CLI(DefaultIO* dio) {
    this->dio = dio;
    commands.push_back(new UploadCommand(dio));
    commands.push_back(new SetAlgorithmCommand(dio));
    commands.push_back(new AnomalyDetectionCommand(dio));
    commands.push_back(new DisplayResultsCommand(dio));
    commands.push_back(new UploadAndAnalyzeCommand(dio));
    commands.push_back(new ExitCommand(dio));
}

/**
 * The function will use the Default IO and create the menu for the client.
 * The function will read the input from the client the execute the command.
 */
void CLI::start(){
    CurrentState current_state;
    int size = commands.size();
    int num = -1;
    while (num != size) {
        this->dio->write("Welcome to the Anomaly Detection Server.\n");
        this->dio->write("Please choose an option:\n");
        for (int i = 1; i <= size ; i++ ) {
            this->dio->write(to_string(i));
            this->dio->write(commands[i-1]->description + "\n");
        }
        string input = dio->read();
        num = stoi(input);
        if (num > 0 && num <= size) {
            commands[num-1]->execute(&current_state);
        }
    }

}

/**
 * Distract the CLI.
 */
CLI::~CLI() {
    for (Command* command : commands) {
        delete command;
    }
}

