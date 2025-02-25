#ifndef NEURON_H
#define NEURON_H

#include <vector>

using vectorWeight = std::vector<float>;

class Neuron
{

    private:
        float value = 0.0f;
        float bias = 0.0f;
        vectorWeight weightVec;

    public:
        Neuron(float value, float bias);

        // GETTERS
        float getValue();
        float getBias();
        vectorWeight& getWeightVec();

        // SETTERS
        void setValue(float value);
        void setBias(float bias);

        // METHODS
        void printNeuron(int index = 0);
        void addSingleWeight(float weight);
        void deleteSingleWeight(int index);
        void deleteAllWeights();
};

#endif