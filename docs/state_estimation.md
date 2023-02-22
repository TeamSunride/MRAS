# StateEstimator in MRAS
#### -- Nikilesh Ramesh

### Introduction
*State Estimation as of feb 2023 uses a linear kalman filter, fusing accelerometer and barometer data.*

A linear kalman filter (also called Linear Quadratic Estimator) is a predictive filter that can be used on a linear model. Since the barometer and accelerometer data have a lot of noise, we could fuse them together to reduce the noise in the system. It can also reveal the hidden state (if designed to), in this case the velocity, as the acceleration to position relation involves a conversion to velocity. The state esitmator uses the linear equations that define acceleration with position:
$$
    s = u + \frac{1}{2} a {t}^2 \\\
    v = a t 
$$
where \f$ s, v, a and t \f$ position, velocity, acceleration and time step respectively. These parameters define the state of the system. Accelerometers measure the acceleration and position (altitude) is resolved from the barometer (see [Atmosphere](https://mras.sunride.space/md_docs_atmosphere_class_guide.html)). Velocity is a "hidden" state as the system doesn't include a sensor that outputs velocity.

But these are for continous funcitons, \f$ t \f$ would be replaced with \f$ \Delta t \f$ to discretize it. For ease of computation, these functions need to be in matrix form. But the the function must be decoupled from the measurement so we could update the `state`. 

$$
    state = \begin{bmatrix} position \\\ velocity \end{bmatrix} + \begin{bmatrix} \frac{1}{2} {\Delta t}^2 \\\ \Delta t \end{bmatrix}  (acceleration + g)
$$

where \f$ g = -9.81 \f$ which accounts for gravity, as accelerometers don't account for it.

The next important concept for the filter is `covariance`. As the filter is probablistic it also needs the standard deviation and error data at compile time. This is then used to update the covariance matrix to then keep track of how the error propagates in time.

For more information on the background theory see [Kalman Filter](https://www.kalmanfilter.net/default.aspx)

### Implementation
There's 4 files that implements the State Estimation: `StateEstimator.h`, `StateEstimator.cpp`, `LinearKalmanFilter.h` and `LinearKalmanFilter.cpp`. The `StateEstimator` class interfaces with the MRAS, it inherits from `Subsystem` class (see [Software Architecture](https://mras.sunride.space/md_docs_software_architecture_overview.html))

`LinearKalmanFilter.h` is the class that filters the data. It's method include: `update(float pressure)`, `predict(float accel)`, `get_altitude()`, `get_velocity()` and `get_timeStep()`. 

![Linear Kalman Filter Loop](docs/images/kalmanloop.png)

The `predict()` and `update()` functions correspond to the Predict and Correct block in the diagram above. Initialize block is excuted in the constructor of `LinearKalmanFilter` class. The constructor takes in three floats: time step, acceleration standard deviation and altimeter standard deviation. 

**NOTE: THE TIME STEP IS THE MOST IMPORTANT PARAMETER HERE, IT HAS TO MATCH THE SAMPLING TIME EXACTLY ELSE THE RESULTS ARE UNUSABLE**

```cpp
    LinearKalmanFilter Filter(float dt, float accelSTD, float altimeterSTD);
``` 

The `predict()` and `update()` methods implement the filter algorithm by using [Eigen](https://eigen.tuxfamily.org/index.php?title=Main_Page). Specifically the [borderflight/eigen](https://github.com/bolderflight/eigen)

The `StateEstimator` class has four methods; three of the inherited methods from `Subsystem` class: `setup()`, `loop()` and `on_message()` and one extra method `altitudeEstimate()` which outputs the altitude just from the barometer. 

1. `LinearKalmanfilter` is initialized in the `setup()` 
2. The `on_message(SystemMessage *msg)` sorts the incoming messages for the `BarometerDataMsg` and `AccelerometerDataMsg` then copies it to a member variable
3. `loop()` handles the filtering and publishing the data

