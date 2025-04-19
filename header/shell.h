#ifndef SHELL_H
#define SHELL_H

#include "../header/state.h"
#include <string>
#include <vector>

using vectorString = std::vector<std::string>;

class Shell
{
    private:
        std::string command;
        vectorString commandParsed;
        State state;

    public:
        // CONSTRUCTORS
        Shell();

        // GETTERS
        std::string getCommand();
        vectorString& getCommandParsed();
        State& getState();

        // SETTERS
        void setCommand(std::string command);
        void setCommandParsed(vectorString& vec);

        // METHODS
        void startContext();
        void endContext();
        void readCommand();
        vectorString parseCommand();
        void analyzeCommand();
        bool validCommandBack(vectorString& commandParsed);
        bool validCommandExit(vectorString& commandParsed);
        bool validCommandCreateNet(vectorString& commandParsed);
        bool validCommandNets(vectorString& commandParsed);
        bool validCommandLayers(vectorString& commandParsed);
        bool validCommandSelect(vectorString& commandParsed);
        bool validCommandAddInputLayer(vectorString& commandParsed);
        bool validCommandAddHiddenLayer(vectorString& commandParsed);
        bool validCommandAddOutputLayer(vectorString& commandParsed);
        bool validCommandComputeAllValues(vectorString& commandParsed);
        bool validCommandPrintNet(vectorString& commandParsed);
        bool validCommandReplaceInputLayer(vectorString& commandParsed);
        bool validCommandReplaceHiddenLayer(vectorString& commandParsed);
        bool validCommandReplaceOutputLayer(vectorString& commandParsed);
        bool validCommandRenameNet(vectorString& commandParsed);

        int callBack(vectorString& commandParsed);
        int callExit();
        int callCreateNet(vectorString& commandParsed);
        void callOutputAllNeuralNets();
        int callOutputAllLayers();
        int callSelect(vectorString& commandParsed);
        int callAddInputLayer(vectorString& commandParsed);
        int callAddHiddenLayer(vectorString& commandParsed);
        int callAddOutputLayer(vectorString& commandParsed);
        int callComputeAllValues(vectorString& commandParsed);
        int callPrintNet(vectorString& commandParsed);
        int callReplaceInputLayer(vectorString& commandParsed);
        int callReplaceHiddenLayer(vectorString& commandParsed);
        int callReplaceOutputLayer(vectorString& commandParsed);
        int callRenameNet(vectorString& commandParsed);
        
        bool checkEmptyCommand(vectorString& commandParsed);
        bool checkNameNeuralNetAlreadyUsed(std::string name);
};

#endif