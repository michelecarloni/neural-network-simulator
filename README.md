# Neural Net backpropagation Simulator

This is a simulator developed specifically to understand how the backpropagation algorithm works over a simple feedforward neural network.
The user can interact with the program by writing simple commands using the shell developed inside.

PS. so far it's only possible to create neural networks and compute all the values. The backprop algorithm will be developed soon.

## List of commands

all the following commands currently work to interact with the system

- **create net** *neural_net_name*
    create a new neural network. The name can be chosen arbitrarily.
    <div align="left">
        <img src = "img/img1.png" style = "width: 50%">
    </div

- **nets**  
    print all the neural networks created so far.
    <div align="left">
        <img src = "img/img2.png" style = "width: 23%">
    </div

- **layers** 
    print all the layers created so far inside a neural network (This requires to select a neural network already created with the command 'selnet').
    <div align="left">
        <img src = "img/img3.png" style = "width: 50%">
    </div 

- **selnet** *neural_net_name*
    select a neural network already created.
    <div align="left">
        <img src = "img/img4.png" style = "width: 50%">
    </div   

- **back** 
    move to an external component (i.e. if you are inside a neural network you will move out of it).
    <div align="left">
        <img src = "img/img5.png" style = "width: 50%">
    </div 

- **exit**  
    exit the program.
    <div align="left">
        <img src = "img/img6.png" style = "width: 23%">
    </div     

- **add input layer** *float_value_1* *float_value_2* *float_value_n* 
    add a new input layer by defining the input values (use 'replace input layer' if the input layer already exists).
    <div align="left">
        <img src = "img/img7.png" style = "width: 75%">
    </div 

- **add hidden layer** *totNeurons* *actFunction*  
    add a new hidden layer by defining how many neurons it has (totNeurons) and the respective activation function (actFunction) (use 'replace hidden layer' by define the index if the hidden layer with that index already exists).
    <div align="left">
        <img src = "img/img8.png" style = "width: 75%">
    </div   

- **add output layer** *totNeurons* *actFunction* 
    add a new output layer by defining how many neurons it has (totNeurons) and the respective activation function (actFunction) (use 'replace output layer' if the output layer already exists).
    <div align="left">
        <img src = "img/img9.png" style = "width: 75%">
    </div

- **compute all values**
    compute all the values of each hidden and the output layer of the neural network (select first a neural network with 'selnet'. The neural network should have input, hidden and output layer).
    <div align="left">
        <img src = "img/img10.png" style = "width: 68%">
    </div 

- **print net** *name*
    print the neural network in details (layers, neurons for each layer, values, weights, biases).
    <div align="left">
        <img src = "img/img11.png" style = "width: 75%">
    </div 

- **replace input layer** *float_value_1* *float_value_2* *float_value_n*
    replace the input layer already present in the selected ('selnet') neural network (if there is no input layer use 'add input layer' to add one). 
    <div align="left">
        <img src = "img/img12.png" style = "width: 75%">
    </div 

- **replace hidden layer** *totNeurons* *actFunction* *index*
    replace the hidden layer already present in the selected ('selnet') neural network by defining its index (if there is no hidden layer with that index use 'add hidden layer' to add one). 
    <div align="left">
        <img src = "img/img13.png" style = "width: 80%">
    </div 

- **replace output layer** *totNeurons* *actFunction*
    replace the output layer already present in the selected ('selnet') neural network (if there is no output layer use 'add output layer' to add one). 
    <div align="left">
        <img src = "img/img14.png" style = "width: 75%">
    </div 

- **rename net** *previous_name* *new_name*
    change the name of a neural network. 
    <div align="left">
        <img src = "img/img15.png" style = "width: 86%">
    </div 


## activation functions
so far the system support the following activation functions:

- **relu**
$\text{ReLU}(x) = \max(0, x)$
    <div align="left">
        <img src = "img/reluGraph.png" style = "width: 50%">
    </div> 
<br></br>

- **sigmoid**\
$\text{sigmoid}(x) = \frac{1}{1 + e^{-x}}$

    <div align="left">
        <img src = "img/sigmoidGraph.png" style = "width: 50%">
    </div>
<br></br>

- **tanh**
$\text{tanh}(x) = \frac{e^{x} - e^{-x}}{e^{x} + e^{-x}}$
    <div align="left">
        <img src = "img/tanhGraph.png" style = "width: 50%">
    </div> 
<br></br>

- **softmax**
$\text{softmax}(\mathbf{z})_i = \frac{e^{z_i}}{\sum_{j=1}^{K} e^{z_j}}$
    <div align="left">
        <img src = "img/softmaxGraph.png" style = "width: 50%">
    </div> 
<br></br>