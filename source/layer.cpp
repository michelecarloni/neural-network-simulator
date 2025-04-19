#include "../header/layer.h"
#include "../header/neuron.h"
#include "../header/functions.h"
#include <iostream>
#include <string>
#include <iomanip>

// CLASS STATIC MEMBERS
std::string Layer::inputType = "INPUT";
std::string Layer::hiddenType = "HIDDEN";
std::string Layer::outputType = "OUTPUT";

// CONSTRUCTORS
Layer::Layer(std::string name, std::string type, std::string actFunction) :
    name(name),
    type(type),
    actFunction(actFunction)
    {}


// GETTERS
std::string Layer::getName() { return this->name; }
std::string Layer::getType() { return this->type; }
std::string Layer::getActFunction() { return this->actFunction; }
vectorNeuron& Layer::getNeuronVec() {return this->neuronVec; }
int Layer::getTotNeurons()
{
    vectorNeuron& refNeuronVec = this->getNeuronVec();
    int size = refNeuronVec.size();
    return size;
}


// SETTERS
void Layer::setName(std::string name) { this->name = name; }
void Layer::setType(std::string type) { this->type = type; }
void Layer::setActFunction(std::string actFunction) { this->actFunction = actFunction; }


// METHODS
void Layer::printLayer(int index)
{
    std::string name = this->getName();
    std::string type = this->getType();
    std::string actFunction = this->getActFunction();
    vectorNeuron& refNeuronVec = this->getNeuronVec();
    int totNeurons = this->getTotNeurons();

    std::cout << index <<")\tNAME: " << name << "\t" << "TYPE: " << type << "\t" << "ACTIVATION FUNCTION: " << actFunction << '\n';
    std::cout << '\n';

    if (totNeurons <= 10)
    {
        for (int i = 0; i < totNeurons; i++)
        {
            Neuron& neuron = refNeuronVec[i];
            neuron.printNeuron(i);
        }
    }
    else
    {
        for (int i = 0; i < 5; i++)
        {
            Neuron& neuron = refNeuronVec[i];
            neuron.printNeuron(i);
        }
        std::cout << "." << std::endl;
        std::cout << "." << std::endl;
        std::cout << "." << std::endl;
        for (int i = totNeurons - 5; i < totNeurons; i++)
        {
            Neuron& neuron = refNeuronVec[i];
            neuron.printNeuron(i);
        }
    }
}


void Layer::addNeuron(Neuron neuron) 
{
    vectorNeuron& refNeuronVec =  getNeuronVec();
    refNeuronVec.push_back(neuron);
}

void Layer::removeNeuron(int index)
{
    // index of the neuron inside the Layer
    vectorNeuron& refNeuronVec = getNeuronVec();
    int size = refNeuronVec.size();
    if (index >= 0 && index < size)
    {
        if (index < size - 1)
        {
            for (int i = index + 1; i < size; i++)
            {
                refNeuronVec[i-1] = refNeuronVec[i]; 
            }
        }
        
        refNeuronVec.pop_back();
    }

}


void Layer::useActivationFunction(float& value, int index)
{
    std::string actFunction = this->getActFunction();
    if (actFunction == "relu")
        Functions::relu(value);
    else if (actFunction == "sigmoid")
        Functions::sigmoid(value);
    else if (actFunction == "tanh")
        Functions::tanh(value);
    else if (actFunction == "softmax")
    {
        vectorNeuron& refNeuronVec = this->getNeuronVec();
        std::vector<float>& refSoftmaxValuesVec = Functions::getSoftmaxValuesVec();
        // if refSoftmaxValuesVec is empty populate it, else just call Functions::softmax;
        // you also have to reset the vector to {} after all the neurons of the layer have been called for computing the function
        if (refSoftmaxValuesVec.empty()) 
        {
            for (int i = 0; i < refNeuronVec.size(); i++)
            {
                float value = refNeuronVec[i].getValue();
                refSoftmaxValuesVec.push_back(value);
            }
        }
        Functions::softmax(value, refSoftmaxValuesVec, index);
    }
}


void Layer::deleteWeightsForAllNeurons()
{
    vectorNeuron& refNeuronVec = this->getNeuronVec();
    for (Neuron& neuron : refNeuronVec)
    {
        neuron.deleteAllWeights();
    }
}