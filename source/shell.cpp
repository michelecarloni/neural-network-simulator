#include "../header/shell.h"
#include "../header/neuralNet.h"
#include "../header/util.h"
#include "../header/functions.h"
#include <iostream>
#include <string>
#include <cstdlib>

// CONSTRUCTORS
Shell::Shell() : 
state()
{}

// GETTERS
std::string Shell::getCommand() { return this->command; }
vectorString& Shell::getCommandParsed() { return this->commandParsed; }
State& Shell::getState() { return this->state; }


// SETTERS
void Shell::setCommand(std::string command) { this->command = command;}
void Shell::setCommandParsed(vectorString& vec)
{
    vectorString& refCommandParsed = this->getCommandParsed();
    refCommandParsed.clear();
    for (int i = 0; i < vec.size(); i++)
    {
        refCommandParsed.push_back(vec[i]);
    }
}


// METHODS
void Shell::startContext()
{
    std::cout << "START SHELL" << std::endl;
    std::cout << std::endl;
}


void Shell::endContext()
{
    std::cout << std::endl;
    std::cout << "END SHELL" << std::endl;
}


void Shell::readCommand()
{
    std::string command;
    State& refState = this->getState();
    std::cout << refState.getCurrentAccess() << ">>" << "\t";
    std::getline(std::cin, command);
    this->setCommand(command);
    vectorString vec = this->parseCommand();
    this->setCommandParsed(vec);
    this->analyzeCommand();
}


vectorString Shell::parseCommand()
{
    std::string command = this->getCommand();
    vectorString stringVec;
    int size = command.length();
    std::string tempStr = "";

    for (int i = 0; i < size; i++)
    {
        if (command[i] == ' ')
        {
            if (tempStr.length() != 0)
            {
                stringVec.push_back(tempStr);
                tempStr = "";
            }
            continue;
        }
        tempStr += command[i];
    }
    if (tempStr != "")
        stringVec.push_back(tempStr);

    return stringVec;
}


void Shell::analyzeCommand()
{
    vectorString& commandParsed = this->getCommandParsed();
    int returnType;

    if(this->validCommandBack(commandParsed))
    {
        returnType = this->callBack(commandParsed);
        if(returnType == 2)
            std::cout << "ERROR: " << "this comand shouldn't take any arguments" << std::endl;
    }
    else if(this->validCommandExit(commandParsed))
    {
        this->callExit();
    }
    else if(this->validCommandCreateNeuralNet(commandParsed))
    {
        returnType = this->callCreateNeuralNet(commandParsed);
        if (returnType == 1)
            std::cout << "new neural network succesfully created" << std::endl;
        else if (returnType == 2)
            std::cout << "ERROR: " << commandParsed[3] << " had already been created" << std::endl;
        else if (returnType == 3)
            std::cout << "ERROR: " << "spaces between the name" << std::endl;
        return;
    }
    else if (this->validCommandNets(commandParsed))
    {
        this->callOutputAllNeuralNets();
        return;
    }
    else if (this->validCommandLayers(commandParsed))
    {
        returnType = this->callOutputAllLayers();
        if (returnType == 2)
            std::cout << "ERROR: " << "neural net not selected" << std::endl;
        return;
    }
    else if (this->validCommandSelect(commandParsed))
    {
        returnType = this->callSelect(commandParsed);
        if (returnType == 2)
            std::cout << "ERROR: " << "no neural net found" << std::endl;
        return;
    }
    else if (this->validCommandAddInputLayer(commandParsed))
    {
        returnType = this->callAddInputLayer(commandParsed);
        if (returnType == 1)
            std::cout << "Input layer succesfully added" << std::endl; 
        else if(returnType == 2)
            std::cout << "ERROR: " << "Input layer already present" << std::endl;
        else if (returnType == 3)
            std::cout << "ERROR: " << "No argument" << std::endl;
        else if (returnType == 4)
            std::cout << "ERROR: " << "Invalid argument" << std::endl; 
        else if (returnType == 5)
            std::cout << "ERROR: " << "Neural net not selected" << std::endl;
        return;
    }
    else if (this->validCommandAddHiddenLayer(commandParsed))
    {
        returnType = this->callAddHiddenLayer(commandParsed);
        if (returnType == 1)
            std::cout << "Hidden layer succesfully added" << std::endl;
        else if(returnType == 2)
            std::cout << "ERROR: " << "Missing input layer" << std::endl;
        else if (returnType == 3)
            std::cout << "ERROR: " << "incorrect number of arguments" << std::endl;
        else if (returnType == 4)
            std::cout << "ERROR: " << "Invalid argument" << std::endl;
        else if (returnType == 5)
            std::cout << "ERROR: " << "Neural net not selected" << std::endl;
        else if (returnType == 6)
            std::cout << "ERROR: " << "activation function inexistent" << std::endl;
        return;
    }
    else if (this->validCommandAddOutputLayer(commandParsed))
    {
        returnType = this->callAddOutputLayer(commandParsed);
        if (returnType == 1)
            std::cout << "Output layer succesfully created" << std::endl;
        else if (returnType == 2)
            std::cout << "ERROR: " << "input layer and hidden layer missing" << std::endl; 
        else if (returnType == 3)
            std::cout << "ERROR: " << "hidden layer missing (hint: include at least 1 hidden layer)" << std::endl;
        else if (returnType == 4) 
            std::cout << "ERROR: " << "output layer already present" << std::endl;
        else if (returnType == 5)
            std::cout << "ERROR: " << "incorrect number of arguments" << std::endl;
        else if (returnType == 6)
            std::cout << "ERROR: " << "Invalid argument" << std::endl;
        else if (returnType == 7)
            std::cout << "ERROR: " << "Neural net not selected" << std::endl;
        else if (returnType == 8)
            std::cout << "ERROR: " << "activation function inexistent" << std::endl;
        return;

            
    }
    else if (this->validCommandComputeAllValues(commandParsed))
    {
        returnType = this->callComputeAllValues(commandParsed);
        if(returnType == 2)
            std::cout << "ERROR: " << "Input layer missing" << std::endl;
        else if(returnType == 3)
            std::cout << "ERROR: " << "Hidden layer missing" << std::endl;
        else if(returnType == 4)
            std::cout << "ERROR: " << "Output layer missing" << std::endl;
        else if(returnType == 5)
            std::cout << "ERROR: " << "Neural net not selected" << std::endl;
        return;
    }
    else if (this->validCommandPrintNet(commandParsed))
    {
        returnType = this->callPrintNet(commandParsed);
        if(returnType == 2)
            std::cout << "ERROR: " << "Too many arguments" << std::endl;
        else if(returnType == 3)
            std::cout << "ERROR: " << "No neural net with this name" << std::endl;
        return;
    }
    else
    {
        std::cout << "ERROR: non-existent command" << std::endl; 
    }

}


bool Shell::validCommandBack(vectorString& commandParsed)
{
    if (commandParsed.size() > 1)
        return false;

    std::string word_0 = commandParsed[0];
    if (Util::strLower(word_0) == "back")
        return true;
    return false;
}


bool Shell::validCommandExit(vectorString& commandParsed)
{
    if (commandParsed.size() != 1)
        return false;

    std::string word_0 = commandParsed[0];
    if (Util::strLower(word_0) == "exit")
        return true;
    return false;
}


bool Shell::validCommandCreateNeuralNet(vectorString& commandParsed)
{
    if (commandParsed.size() < 3)
        return false;

    std::string word_0 = commandParsed[0];
    std::string word_1 = commandParsed[1];
    std::string word_2 = commandParsed[2];
    if (Util::strLower(word_0) == "create" && Util::strLower(word_1) == "neural" && Util::strLower(word_2) == "net")
        return true;
    return false;
}


bool Shell::validCommandNets(vectorString& commandParsed)
{
    if (commandParsed.size() != 1)
        return false;
    
    std::string word_0 = commandParsed[0];
    if (Util::strLower(word_0) == "nets")
        return true;
    return false;
}


bool Shell::validCommandLayers(vectorString& commandParsed)
{
    if (commandParsed.size() != 1)
        return false;
    
    std::string word_0 = commandParsed[0]; 
    if (Util::strLower(word_0) == "layers")
        return true;
    return false;
}


bool Shell::validCommandSelect(vectorString& commandParsed)
{
    if (commandParsed.size() < 1)
        return false;
    std::string word_0 = commandParsed[0];
    if (Util::strLower(word_0) == "selnet")
        return true;
    return false;
}


bool Shell::validCommandAddInputLayer(vectorString& commandParsed)
{
    if (commandParsed.size() < 3)
        return false;
    
    std::string word_0 = commandParsed[0];
    std::string word_1 = commandParsed[1];
    std::string word_2 = commandParsed[2];

    if (Util::strLower(word_0) == "add" && Util::strLower(word_1) == "input" && Util::strLower(word_2) == "layer")
        return true;
    return false;
}


bool Shell::validCommandAddHiddenLayer(vectorString& commandParsed)
{
    if (commandParsed.size() < 3)
        return false;
    
    std::string word_0 = commandParsed[0];
    std::string word_1 = commandParsed[1];
    std::string word_2 = commandParsed[2];

    if (Util::strLower(word_0) == "add" && Util::strLower(word_1) == "hidden" && Util::strLower(word_2) == "layer")
        return true;
    return false;
}


bool Shell::validCommandAddOutputLayer(vectorString& commandParsed)
{
    if (commandParsed.size() < 3)
        return false;
    
    std::string word_0 = commandParsed[0];
    std::string word_1 = commandParsed[1];
    std::string word_2 = commandParsed[2];

    if (Util::strLower(word_0) == "add" && Util::strLower(word_1) == "output" && Util::strLower(word_2) == "layer")
        return true;
    return false;
}


bool Shell::validCommandComputeAllValues(vectorString& commandParsed)
{
    if (commandParsed.size() != 3)
        return false;
    std::string word_0 = commandParsed[0];
    std::string word_1 = commandParsed[1];
    std::string word_2 = commandParsed[2];

    if (Util::strLower(word_0) == "compute" && Util::strLower(word_1) == "all" && Util::strLower(word_2) == "values")
        return true;
    return false;
}


bool Shell::validCommandPrintNet(vectorString& commandParsed)
{
    if (commandParsed.size() < 2)
        return false;
    std::string word_0 = commandParsed[0];
    std::string word_1 = commandParsed[1];

    if (Util::strLower(word_0) == "print" && Util::strLower(word_1) == "net")
        return true;
    return false;
}


int Shell::callBack(vectorString& commandParsed)
{
    if (commandParsed.size() > 1)
        return 2;
    State& refState = this->getState();
    refState.setAllSelectedToNullptr();
    return 1;
}


int Shell::callExit()
{
    this->endContext();
    exit(0);
}


int Shell::callCreateNeuralNet(vectorString& commandParsed)
{
    if (commandParsed.size() > 4)
        return 3;
    std::string neuralNetName = commandParsed[3];
    if(checkNameNeuralNetAlreadyUsed(neuralNetName))
    {
        return 2;
    }
    State& refState = this->getState();
    refState.addNeuralNet(neuralNetName);
    vectorNeuralNet& refNeuralNetVec = refState.getNeuralNetVec();
    NeuralNet& newNeuralNet = refNeuralNetVec[refNeuralNetVec.size() - 1];
    refState.setSelectedNeuralNet(newNeuralNet);
    return 1;

}


void Shell::callOutputAllNeuralNets()
{
    State& refState = this->getState();
    vectorNeuralNet& refNeuralNetVec = refState.getNeuralNetVec();
    for (int i = 0; i < refNeuralNetVec.size(); i++)
    {
        std::string name = refNeuralNetVec[i].getName();
        std::cout << i << ") " << name << std::endl;

    }
}


int Shell::callOutputAllLayers()
{
    State& refState = this->getState();
    NeuralNet* refSelectedNeuralNet = refState.getSelectedNeuralNet();
    if (refSelectedNeuralNet == nullptr)
        return 2;

    vectorLayer& refLayerVec = refSelectedNeuralNet->getLayerVec();
    for (int i = 0; i < refLayerVec.size(); i++)
    {
        Layer& layer = refLayerVec[i];
        std::string name = layer.getName();
        std::cout << i << ") " << name << std::endl;
    }
    return 1;

}


int Shell::callSelect(vectorString& commandParsed)
{
    std::string name = commandParsed[1];
    State& refState = this->getState();
    vectorNeuralNet& refNeuralNetVec = refState.getNeuralNetVec();
    for (int i = 0; i < refNeuralNetVec.size(); i++)
    {
        NeuralNet& neuralNet = refNeuralNetVec[i];
        if (name == neuralNet.getName())
        {
            refState.setSelectedNeuralNet(neuralNet);
            return 1;
        }
    }
    return 2;
}


int Shell::callAddInputLayer(vectorString& commandParsed)
{
    if (commandParsed.size() == 3)
        return 3;

    State& refState = this->getState();
    NeuralNet* refSelectedNeuralNet = refState.getSelectedNeuralNet();
    int returnType;
    std::vector<float> valueVec;

    if (refSelectedNeuralNet == nullptr)
        return 5;

    for (int i = 3; i < commandParsed.size(); i++)
    {
        float value;
        try
        {
            value = std::stof(commandParsed[i]);
        }
        catch(...)
        {
            return 4;
        }
        valueVec.push_back(value);
    }
    returnType = refSelectedNeuralNet->addInputLayer(valueVec, valueVec.size());
    return returnType;
}


int Shell::callAddHiddenLayer(vectorString& commandParsed)
{
    if (commandParsed.size() != 5)
        return 3;
    State& refState = this->getState();
    NeuralNet* refSelectedNeuralNet = refState.getSelectedNeuralNet();       
    int totNeurons;
    std::string actFunction;
    int returnType;

    if (refSelectedNeuralNet == nullptr)
        return 5;

    try
    {
        totNeurons = std::stoi(commandParsed[3]);
        actFunction = Util::strLower(commandParsed[4]);
    }
    catch(...)
    {
        return 4;
    }
    if(!Functions::checkFunctionExist(actFunction))
        return 6;
    returnType = refSelectedNeuralNet->addHiddenLayer(totNeurons, actFunction);
    return returnType;
}


int Shell::callAddOutputLayer(vectorString& commandParsed)
{
    if(commandParsed.size() != 5)
        return 5;
    State& refState = this->getState();
    NeuralNet* refSelectedNeuralNet = refState.getSelectedNeuralNet();       
    int totNeurons;
    std::string actFunction;
    int returnType;

    if (refSelectedNeuralNet == nullptr)
        return 7;

    try
    {
        totNeurons = std::stoi(commandParsed[3]);
        actFunction = Util::strLower(commandParsed[4]);
    }
    catch(...)
    {
        return 6;
    }
    if(!Functions::checkFunctionExist(actFunction))
        return 8;
    returnType = refSelectedNeuralNet->addOutputLayer(totNeurons, actFunction);
    return returnType;
}


int Shell::callComputeAllValues(vectorString& commandParsed)
{
    State& refState = this->getState();
    NeuralNet* refSelectedNeuralNet = refState.getSelectedNeuralNet();

    if (refSelectedNeuralNet == nullptr)
        return 5;
    
    int returnType = refSelectedNeuralNet->computeAllValues();
    return returnType;
}


int Shell::callPrintNet(vectorString& commandParsed)
{
    if (commandParsed.size() > 3)
        return 2;
    State& refState = this->getState();
    vectorNeuralNet refNeuralNetVec = refState.getNeuralNetVec();
    std::string inputNetName = commandParsed[2];
    for (NeuralNet& nn : refNeuralNetVec)
    {
        if (nn.getName() == inputNetName)
        {
            nn.printNeuralNet();
            return 1;
        }
    }
    return 3;
}


bool Shell::checkNameNeuralNetAlreadyUsed(std::string neuralNetName)
{
    State& refState = this->getState();
    vectorNeuralNet& refNeuralNetVec = refState.getNeuralNetVec();

    for (NeuralNet nn : refNeuralNetVec)
    {
        std::string nameNN = nn.getName(); 
        if (nameNN == neuralNetName)
            return true;
    }
    return false;
}
