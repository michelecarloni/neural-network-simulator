#ifndef STATE_H
#define STATE_H

#include "../header/neuralNet.h"
#include "../header/layer.h"
#include "../header/neuron.h"
#include <vector>
#include <string>

using vectorNeuralNet = std::vector<NeuralNet>;

class State
{
    private:
        vectorNeuralNet neuralNetVec;
        NeuralNet* selectedNeuralNet = nullptr;
        Layer* selectedLayer = nullptr;
        Neuron* selectedNeuron = nullptr;
        
    public:
        // CONSTRUCTORS
        State();

        // GETTERS
        vectorNeuralNet& getNeuralNetVec();
        NeuralNet* getSelectedNeuralNet();
        Layer* getSelelctedLayer();
        Neuron* getSelectedNeuron();
        std::string getCurrentAccess();

        // SETTERS
        void setSelectedNeuralNet(NeuralNet& neuralNet);
        void setAllSelectedToNullptr();

        // METHODS
        void addNeuralNet(std::string name);
};

#endif