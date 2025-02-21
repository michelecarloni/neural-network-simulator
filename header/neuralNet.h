#ifndef NEURALNET_H
#define NEURALNET_H

#include "../header/layer.h"
#include "../header/neuron.h"
#include <string>
#include <vector>

using vectorLayer = std::vector<Layer>;

class NeuralNet
{
    private:
        std::string name;
        vectorLayer layerVec;
        bool checkComplete = false;
    
    public:
        // CONSTRUCTORS
        NeuralNet(std::string name);
        
        // GETTERS 
        std::string getName();
        vectorLayer& getLayerVec();
        bool getCheckComplete();
        int getTotLayers();

        // SETTERS
        void setName(std::string name);
        void setCheckComplete();

        // METHODS
        void printNeuralNet();
        bool checkInputLayerAlreadyPresent();
        bool checkAtLeastOneHiddenLayerAlreadyPresent();
        bool checkOutputLayerAlreadyPresent();
        int addInputLayer(std::vector<float>& values, int size);       // 'true' -> input layer added. 'false' -> input layer not added because is already present
        int addHiddenLayer(int totNeurons, std::string actFunction);                  
        int addOutputLayer(int totNeurons, std::string actFunction);
        void computeWeights();
        int computeAllValues();
        void computeValuesGivenThePreviousLayer(Layer& prevLayer, Layer& currentLayer);   
};

#endif