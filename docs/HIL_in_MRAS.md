# Hardware-In-the-Loop testing in MRAS
#### -- Nikilesh Ramesh

### Introduction 
Hardware-In-the-Loop (hereinafter HIL) is a way of testing embedded systems software. Stream simulated data over from either a deicated test rig or a computer to then measure the output to test if the system performs as expected. More information can be found [here](https://uk.mathworks.com/discovery/hardware-in-the-loop-hil.html).


### Simulink Model Explanation
Simulink is used to test MRAS. Data is streamed over serial to MRAS from the launch data collected during previous flights. Launch data is saved as csv file. `From spreadsheet` block in Simulink can be used to read the csv file. *Note: csv file needs to be formatted as per SIMULINK requirements see [here](https://uk.mathworks.com/help/simulink/slref/fromspreadsheet.html)*

The `pressure` and `y_accel` (acceleration y direction, up) is then concatenated using the `vector concatenate` block. They are then casted to floating points with `cast to single` block. Then `Byte pack` is used to convert them into bytes. 

Simulink's Instument Control blockset provides a neat way of communicating with the board without much restrictions on the software, only a module that can read and write to serial is needed to communicate using this blockeset therfore this was chosen instead of Simulink's Arduino support package. 

To send this data, first a `Serial Configuration` block must be added to the model. Set the baud rate, COM port and other essential details here. Then use `Serial Send` to stream data over to the board (again set the parameters as required and you are recommened by the author to skip the headers/break section for this block as it does not provide much added value if you are only testing a small system). How this data is proccessed on MRAS will be discussed in the next section.

Now `Serial Recieve` block provides the interface to read the data that MRAS outputs again in bytes. Configure the parameters as necessary, important parameters include `Serial Port`, `Input` and `Headers` (Headers are recommended here as Simulink deals with it so why not). Then cast to double before using the `Mux` block to divide the input vector into two values (the order of values depends on how you handle it in MRAS)

![Simulink model](docs/images/SimulinkSS.png)

### MRAS rocketHIL env Explanation

On MRAS a new `env` has been added dedicated for HIL testing named `rocketHIL`, checkout the `platformio.ini` and `main-rocketHIL.cpp` files. A new `Subsystem` has been added (if you are not familiar with MRAS subsystems you are encouranged to checkout either [Architecture overview](https://mras.sunride.space/md_docs_software_architecture_overview.html) or [a beginner guide to MRAS](https://mras.sunride.space/md_docs_BeginnerExplanation.html)) to interface with Simulink called `SimulinkDataLogger`. It logs recieves data from Simulink, casts it to the appropriate internal `SystemMessage`, then "publishes" it. The `StateEstimator` (more about this [here](https://mras.sunride.space/md_docs_state_estimation.html))is the sole subscriber to the said message. It proccess this message and then itself publishes a new `StateEstimatorMsg`. `SimulinkDataLogger` (it is subscribed to `StateEstimator`, thus making a two-way connection) then formats this message into the required format and then writes to Serial. 

Well to convert data to bytes and vice-versa is an excellent use-case of `Union` data type that `c++` provides. An union is basically a struct but all its members define the same value (recommended watch [Cherno](https://www.youtube.com/watch?v=6uqU9Y578n4)). 

```cpp
typedef union{
    float number;
    uint8_t bytes[4];
} FLOATUNION_t;
```

Here the `float number` and `uint8_t bytes[4]` define the same value. A `float` is made up of 4 bytes, `uint8_t` or `char` type is made of 1 byte, now an array of four `char` is then 4 bytes. So we can now represent a `float` as an array of four `uint8_t`. Then use Arduino framework's `Serial.write()` to write the **bytes** but to read it use the `Serial.read()` into `number` (c++ automatically changes the `bytes` array everytime `number` is re-assigned). 

### References

Best source of reference for the Simulink side of things is the [Mathworks Documentation](https://uk.mathworks.com/products/simulink.html). For the interface there is an excellent [github repository](https://github.com/leomariga/Simulink-Arduino-Serial) with examples you can try out. Additionally [Cherno's C++ series](https://www.youtube.com/playlist?list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb) was helpful. 
