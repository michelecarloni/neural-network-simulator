#ifndef LAYER_H
#define LAYER_H

#include "../header/neuron.h"
#include <vector>
#include <string>

using vectorNeuron = std::vector<Neuron>;

class Layer
{
    // types of layers 
    public:
        static std::string inputType;
        static std::string hiddenType;
        static std::string outputType;

    private:
        std::string name;
        std::string type;
        std::string actFunction = "None";
        vectorNeuron neuronVec;

    public:
        // CONSTRUCTORS
        Layer(std::string name, std::string type, std::string actFunction);

        // GETTERS
        std::string getName();
        std::string getType();
        std::string getActFunction();
        vectorNeuron& getNeuronVec();
        int getTotNeurons();

        // SETTERS
        void setName(std::string name);
        void setType(std::string type);
        void setActFunction(std::string actFunction);

        // METHODS
        void printLayer(int index = 0);
        void addNeuron(Neuron neuron);
        void removeNeuron(int index);
        void useActivationFunction(float& value);
};

#endif