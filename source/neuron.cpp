#include "../header/neuron.h"
#include "../header/util.h"

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>


// CONSTRUCTORS

// input neurons: (value, 0)
// hidden neurons: (0.0f, bias)
// output neurons: (0.0f, bias)

Neuron::Neuron(float value, float bias) :        
    value(value),
    bias(bias)
    {}


// GETTERS 
float Neuron::getValue() { return this->value; }
float Neuron::getBias() { return this->bias; }
vectorWeight& Neuron::getWeightVec() { return this->weightVec;}


// SETTERS
void Neuron::setValue(float value) { this->value = value; } 
void Neuron::setBias(float bias) { this->bias = bias; }


// METHODS
void Neuron::printNeuron(int index)
{
    float value = this->getValue();
    float bias = this->getBias();
    vectorWeight& refWeightVec = this->getWeightVec();

    std::cout << '\t' << index << ") value: " << std::fixed << std::setprecision(4) << value << "\t" << "bias: " << std::fixed << std::setprecision(4) << bias << "\t" << "[ ";

    if (refWeightVec.size() <= 10)
    {
        for (float weight : refWeightVec)
        {
            std::cout << std::fixed << std::setprecision(4) << weight << ", ";
        }
    }
    else
    {
        for (int i = 0; i < 5; i++)
        {
            std::cout << std::fixed << std::setprecision(4) << refWeightVec[i] << ", ";
        }  
        std::cout << std::fixed << std::setprecision(4) << "..." << ", ";
        for (int i = refWeightVec.size() - 5; i < refWeightVec.size(); i++)
        {
            std::cout << std::fixed << std::setprecision(4) << refWeightVec[i] << ", ";
        }  
    }
    std::cout << "]" << '\n';
}


void Neuron::addSingleWeight(float weight) { this->weightVec.push_back(weight); }


void Neuron::deleteSingleWeight(int index)
{
    vectorWeight& tempWeightVec = getWeightVec();
    int size = tempWeightVec.size();
    if (index >= 0 && index < size)
    {
        if (index < size - 1)
        { 
            for (int i = index + 1; i < size; i++)
            {
                tempWeightVec[i-1] = tempWeightVec[i];
            }
        }
        
        tempWeightVec.pop_back();
    }  
    
}


void Neuron::deleteAllWeights()
{
    vectorWeight& refWeightVec = this->getWeightVec();
    refWeightVec.clear();
    refWeightVec.shrink_to_fit();
}