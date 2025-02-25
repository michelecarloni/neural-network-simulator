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
        bool checkHiddenLayerAldreadyPresentGivenindex(int index);
        int addInputLayer(std::vector<float>& values, int size);       // 'true' -> input layer added. 'false' -> input layer not added because is already present
        int addHiddenLayer(int totNeurons, std::string actFunction);                  
        int addOutputLayer(int totNeurons, std::string actFunction);
        int replaceInputLayer(std::vector<float>& values, int size);
        int replaceHiddenLayer(int totNeurons, std::string actFunction, int index);
        int replaceOutputLayer(int totNeurons, std::string actFunction);
        void computeWeights();
        void computeWeightsGivenThePreviousLayer(Layer& currentLayer, Layer& nextLayer);
        int computeAllValues();
        int computeAllValues(int index);
        void computeValuesGivenThePreviousLayer(Layer& prevLayer, Layer& currentLayer);  
        void deleteWeightsForGivenLayer(Layer& layer); 
};

#endif