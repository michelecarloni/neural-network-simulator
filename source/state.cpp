#include "../header/state.h"
#include <string>
#include <vector>

// CONSTRUCTORS
State::State() {}

// GETTERS
vectorNeuralNet& State::getNeuralNetVec() { return this->neuralNetVec; }
NeuralNet* State::getSelectedNeuralNet() { return this->selectedNeuralNet; }
Layer* State::getSelelctedLayer() { return this->selectedLayer; }
Neuron* State::getSelectedNeuron() { return this->selectedNeuron; }
std::string State::getCurrentAccess()
{
    std::string currentAccess;

    NeuralNet* refSelectedNeuralNet = this->getSelectedNeuralNet();
    Layer* refSelectedLayer = this->getSelelctedLayer();
    Neuron* refSelectedNeuron = this->getSelectedNeuron();

    if (refSelectedNeuralNet == nullptr)
        return "";
    if (refSelectedLayer == nullptr)
        return refSelectedNeuralNet->getName() + " ";
    if (refSelectedNeuron == nullptr)
        return refSelectedNeuralNet->getName() + "/" + refSelectedLayer->getName() + " ";
}

// SETTERS
void State::setSelectedNeuralNet(NeuralNet& neuralNet) { this->selectedNeuralNet = &neuralNet; }
void State::setAllSelectedToNullptr() {
    this->selectedNeuralNet = nullptr;
    this->selectedLayer = nullptr;
    this->selectedNeuron = nullptr;
}

// METHODS
void State::addNeuralNet(std::string name)
{
    vectorNeuralNet& refNeuralNetVec = this->getNeuralNetVec();
    NeuralNet neuralNet(name);
    refNeuralNetVec.push_back(neuralNet);
}
