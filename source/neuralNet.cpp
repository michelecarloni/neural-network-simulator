#include "../header/neuralNet.h"
#include "../header/layer.h"
#include "../header/neuron.h"
#include "../header/util.h"
#include "../header/functions.h"
#include <iostream>
#include <string>
#include <iomanip>


// CONSTRUCTORS
NeuralNet::NeuralNet(std::string name) : 
    name(name)
    {}

// GETTERS 
std::string NeuralNet::getName() { return this->name; }
vectorLayer& NeuralNet::getLayerVec() { return this->layerVec; }
bool NeuralNet::getCheckComplete() { return this->checkComplete; }
int NeuralNet::getTotLayers()
{
    vectorLayer& refLayerVec = this->getLayerVec();
    int totLayers = refLayerVec.size();
    return totLayers;
}

// SETTERS
void NeuralNet::setName(std::string name) { this->name = name; }
void NeuralNet::setCheckComplete()
{
    bool checkInput = this->checkInputLayerAlreadyPresent();
    bool checkHidden = this->checkAtLeastOneHiddenLayerAlreadyPresent();
    bool checkOutput = this->checkOutputLayerAlreadyPresent();
    this->checkComplete = checkInput && checkHidden && checkOutput;
}

// METHODS
void NeuralNet::printNeuralNet()
{
    std::string name = this->getName();
    vectorLayer& refLayerVec = this->getLayerVec();
    int totLayers = this->getTotLayers();

    std::cout << "NAME NERUAL NETWORK: " << name << '\n';
    std::cout << '\n';

    for (int i = 0; i < totLayers; i++)
    {
        Layer& layer = refLayerVec[i];
        layer.printLayer(i);
        std::cout << '\n';
    }
}


bool NeuralNet::checkInputLayerAlreadyPresent()
{
    try
    {
        vectorLayer& refLayerVec = this->getLayerVec();
        if (refLayerVec.empty())
            return false;

        Layer& refLayer = refLayerVec[0];
        std::string layerType = refLayer.getType();

        if (layerType == Layer::inputType)      // input layer already in the NeuralNet
            return true;
        else
            return false;
    }
    catch (...)
    {
        return false;
    }
}


bool NeuralNet::checkAtLeastOneHiddenLayerAlreadyPresent()
{
    try
    {
        vectorLayer& refLayerVec = this->getLayerVec();
        if (refLayerVec.empty())
            return false;

        Layer& refLayer = refLayerVec[1];
        std::string layerType = refLayer.getType();

        if (layerType == Layer::hiddenType)
            return true;
        else
            return false;
    }
    catch (...)
    {
        return false;
    }
}


bool NeuralNet::checkOutputLayerAlreadyPresent()
{
    try
    {
        vectorLayer& refLayerVec = this->getLayerVec();
        if (refLayerVec.empty())
            return false;
        
        int totLayers = this->getTotLayers();
        int index = totLayers - 1;
        Layer& refLayer = refLayerVec[index];
        std::string layerType = refLayer.getType();

        if (layerType == Layer::outputType)
            return true;
        else
            return false;
    }
    catch (...)
    {
        return false;
    }
}

bool NeuralNet::checkHiddenLayerAldreadyPresentGivenindex(int index)
{
    // checking if the index refering to the input layer
    if (index == 0)
        return false;

    // checking if the index is refering the output layer
    vectorLayer& refLayerVec = this->getLayerVec();
    int lastIndex = refLayerVec.size() - 1;
    Layer& refLastLayer = refLayerVec[lastIndex];
    if (index == lastIndex && refLastLayer.getType() == Layer::outputType)
        return false;
    return true;
}


int NeuralNet::addInputLayer(std::vector<float>& values, int size)
{
    if (this->checkInputLayerAlreadyPresent())
        return 2;
    
    vectorLayer& refLayerVec = this->getLayerVec();
    int newIndex = this->getTotLayers();
    std::string layerName = "input_layer_" + std::to_string(newIndex);
    Layer inputLayer(layerName, Layer::inputType, "");
    for (int i = 0; i < size; i++)
    {
        float value = values[i];
        Neuron neuron(value, 0.0f);
        inputLayer.addNeuron(neuron);
    }

    refLayerVec.push_back(inputLayer);
    this->setCheckComplete();
    return 1;
    
}

int NeuralNet::addHiddenLayer(int totNeurons, std::string actFunction)
{
    if (!this->checkInputLayerAlreadyPresent())
        return 2;

    vectorLayer& refLayerVec = this->getLayerVec();
    int newIndex = this->getTotLayers();
    std::string layerName = "hidden_layer_" + std::to_string(newIndex);
    Layer hiddenLayer(layerName, Layer::hiddenType, actFunction);
    for (int i = 0; i < totNeurons; i++)
    {
        float bias = Util::generateRandomBias();
        Neuron neuron(0.0f, bias);
        hiddenLayer.addNeuron(neuron);
        this->computeWeights();
    }
    refLayerVec.push_back(hiddenLayer);
    this->getCheckComplete();
    return 1;
}


int NeuralNet::addOutputLayer(int totNeurons, std::string actFunction)
{
    if (!this->checkInputLayerAlreadyPresent())
        return 2;
    if (!this->checkAtLeastOneHiddenLayerAlreadyPresent())
        return 3;
    if (this->checkOutputLayerAlreadyPresent())
        return 4;

    vectorLayer& refLayerVec = this->getLayerVec();
    int newIndex = this->getTotLayers();
    std::string layerName = "output_layer_" + std::to_string(newIndex);
    Layer outputLayer(layerName, Layer::outputType, actFunction);
    for (int i = 0; i < totNeurons; i++)
    {
        float bias = Util::generateRandomBias();
        Neuron neuron(0.0f, bias);
        outputLayer.addNeuron(neuron);
        this->computeWeights();
    }
    refLayerVec.push_back(outputLayer);
    this->getCheckComplete();
    return 1;
}

// replace input layer only if it is already present
// bis there is a hidden layer the function computes also the values
int NeuralNet::replaceInputLayer(std::vector<float>& values, int size)
{
    if (!this->checkInputLayerAlreadyPresent())
        return 2;

    vectorLayer& refLayerVec = this->getLayerVec();
    Layer newInputLayer("input_layer_0", Layer::inputType, "");

    for (float value : values)
    {
        Neuron neuron(value, 0);
        newInputLayer.addNeuron(neuron);
    }
    refLayerVec[0] = newInputLayer;

    if (refLayerVec.size() >= 2)
    {
        this->computeWeightsGivenThePreviousLayer(refLayerVec[0], refLayerVec[1]);
    }

    return 1;
}

// replace hidden layer only if it is already present (based on the index)
int NeuralNet::replaceHiddenLayer(int totNeurons, std::string actFunction, int index)
{
    if (!this->checkHiddenLayerAldreadyPresentGivenindex(index))
        return 2;
    
    std::string name = "hidden_layer_" + std::to_string(index);
    Layer newHiddenLayer(name, Layer::hiddenType, actFunction);

    for(int i = 0; i < totNeurons; i++)
    {
        float bias = Util::generateRandomBias();
        Neuron neuron(0.0, bias);
        newHiddenLayer.addNeuron(neuron);
    }
    
    vectorLayer& refLayerVec = this->getLayerVec();
    refLayerVec[index] = newHiddenLayer;
    Layer& prevLayer = refLayerVec[index-1];
    prevLayer.deleteWeightsForAllNeurons();
    this->computeWeightsGivenThePreviousLayer(prevLayer, refLayerVec[index]);
    if (index < (refLayerVec.size() - 1))
    {
        Layer& nextLayer = refLayerVec[index + 1];
        this->computeWeightsGivenThePreviousLayer(refLayerVec[index], nextLayer);
    }
    this->computeAllValues(index);
    return 1;
}


int NeuralNet::replaceOutputLayer(int totNeurons, std::string actFunction)
{
    if (!this->checkOutputLayerAlreadyPresent())
        return 2;
    vectorLayer& refLayerVec = this->getLayerVec();
    int lastIndex = refLayerVec.size() - 1;
    std::string name = "output_layer_" + std::to_string(lastIndex);
    Layer newOutputLayer(name, Layer::outputType, actFunction);
    for (int i = 0; i < totNeurons; i++)
    {
        float bias = Util::generateRandomBias();
        Neuron neuron(0.0, bias);
        newOutputLayer.addNeuron(neuron);
    }
    refLayerVec[lastIndex] = newOutputLayer;
    Layer& prevLayer = refLayerVec[lastIndex - 1];
    prevLayer.deleteWeightsForAllNeurons();
    this->computeWeightsGivenThePreviousLayer(prevLayer, refLayerVec[lastIndex]);
    this->computeAllValues(lastIndex);
    return 1;
}


// it takes the last layer in the layerVec of the current neural network and
// it computes one weight for each neuron in it
void NeuralNet::computeWeights()            
{
    vectorLayer& refLayerVec = this->getLayerVec();
    Layer& layer = refLayerVec[refLayerVec.size() - 1];
    vectorNeuron& refNeuronVec = layer.getNeuronVec();
    int totNeurons = refNeuronVec.size();
    for (int i = 0; i < totNeurons; i++)
    {
        float weight = Util::generateRandomWeight();
        Neuron& neuron = refNeuronVec[i];
        neuron.addSingleWeight(weight);
    }
}


void NeuralNet::computeWeightsGivenThePreviousLayer(Layer& currentLayer, Layer& nextLayer)
{
    vectorNeuron& refNeuronVecNextLayer = nextLayer.getNeuronVec();
    int totNeuronsNextLayer = refNeuronVecNextLayer.size();

    vectorNeuron& refNeuronVecCurrentLayer = currentLayer.getNeuronVec();
    for (Neuron& n : refNeuronVecCurrentLayer)
    {
        for (int i = 0; i < totNeuronsNextLayer; i++)
        {
            float weight = Util::generateRandomWeight();
            n.addSingleWeight(weight);
        }
    }
}


// THE USER CAN CALL THIS FUNCTION
// it checks if the structure of the neural network is complete.
// In that case it computes the values for all the neurons.
int NeuralNet::computeAllValues()
{
    if (!this->checkInputLayerAlreadyPresent())
        return 2;
    if (!this->checkAtLeastOneHiddenLayerAlreadyPresent())
        return 3;
    if (!this->checkOutputLayerAlreadyPresent())
        return 4;

    vectorLayer& refLayerVec = this->getLayerVec();
    int totLayers = this->getTotLayers();
    for (int i = 1; i < totLayers; i++)
    {
        Layer& prevLayer = refLayerVec[i-1];
        Layer& currentLayer = refLayerVec[i];
        computeValuesGivenThePreviousLayer(prevLayer, currentLayer);
    }
    return 1;
}


int NeuralNet::computeAllValues(int index)
{
    if (!this->checkInputLayerAlreadyPresent())
        return 2;
    if (!this->checkAtLeastOneHiddenLayerAlreadyPresent())
        return 3;
    if (!this->checkOutputLayerAlreadyPresent())
        return 4;

    vectorLayer& refLayerVec = this->getLayerVec();
    int totLayers = this->getTotLayers();
    for (int i = index; i < totLayers; i++)
    {
        Layer& prevLayer = refLayerVec[i-1];
        Layer& currentLayer = refLayerVec[i];
        computeValuesGivenThePreviousLayer(prevLayer, currentLayer);
    }
    return 1;
}


void NeuralNet::computeValuesGivenThePreviousLayer(Layer& prevLayer, Layer& currentLayer)
{
    int prevLayerTotNeurons = prevLayer.getTotNeurons();
    int currentLayerTotNeurons = currentLayer.getTotNeurons();

    vectorNeuron& refNeuronVecPrevLayer = prevLayer.getNeuronVec();
    vectorNeuron& refNeuronVecCurrentLayer = currentLayer.getNeuronVec();

    for (int i = 0; i < currentLayerTotNeurons; i++)
    {
        float currentValue = 0;
        for (int j = 0; j < prevLayerTotNeurons; j++)
        {
            Neuron& prevNeuron = refNeuronVecPrevLayer[j];
            vectorWeight& refWeightVec = prevNeuron.getWeightVec();
            float value = prevNeuron.getValue();
            float weight = refWeightVec[i];
            currentValue += (value * weight);
        }
        // 'currentValue' must be going through an activation function.
        Neuron& currentNeuron = refNeuronVecCurrentLayer[i];
        currentValue += currentNeuron.getBias();
        // currentLayer.useActivationFunction(currentValue, i);     // modify the value based on the activation function
        currentNeuron.setValue(currentValue);
    }

    for (int i = 0; i < currentLayerTotNeurons; i++)
    {
        Neuron& currentNeuron = refNeuronVecCurrentLayer[i];
        float currentValue = currentNeuron.getValue();
        currentLayer.useActivationFunction(currentValue, i);
        currentNeuron.setValue(currentValue);
    }

    // clean softmaxValuesVec
    std::vector<float>& refSoftmaxValuesVec = Functions::getSoftmaxValuesVec();
    refSoftmaxValuesVec.clear();
    
}