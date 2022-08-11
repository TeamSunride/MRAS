# MRAS - Multi Rocket Avionics System

During the academic year 2021-2022 the Sunride rocket team worked on 
two rocketry projects, Karman Alpha and SpaceDart. These rockets had 
different requirements and therefore two avionics systems were designed.

The team planned for both systems to share the same telemetry system. 
After a short while of development it was clear that it would beneficial 
for the systems to share software, so that it can be tested more regularly 
and the system can be more robust.

As an initial prototype was made for the SpaceDart avionics system, software 
development started. The software was designed to work regardless of the sensor 
hardware connected; for example any accelerometer could be used, GPS, etc.

However, there are limitations to this approach. For example, many of the specific 
features of the individual components (such as FIFO buffers and interrupt 
features in accelerometers) cannot be used when software is written in a more general 
sense. It is also difficult to maintain two different avionics designs, and more 
sensor driver code has to be written and tested if sensors used are not consistent.

In order to address this issue, the team has chosen to unify the hardware that is in 
use. 

This repository contains the software for MRAS. Despite the decision to unify hardware, 
the software should remain compatible with multiple different sensors. This is 
because supply can be unpredictable, so in future the design may change. Also, this 
allows flexibility for the design to evolve without drastic changes to the software.

## Sensor Interfaces

Every sensor connected to MRAS is a child of the `Sensor` interface. There are 
several things that all sensors can / must do:
- Start up
- Read data
- Self test

The `Sensor` interface defines two virtual functions: `begin()` and `readData()`.
These must be implemented by any children of `Sensor`. This is the case because every 
sensor can have a start-up routine and can read data, but not all sensors have a self test.

### Start-up sequence

When MRAS is powered on, a call will be made to the `begin()` function of every `Sensor`. This a
allows the sensor to run any setup that it needs to do. Some examples are:
- An I2C sensor might start by reading a constant known value from a register on the
device and comparing the result to the known value. If the value is incorrect, 
the function can be made to return a status code, to inform MRAS of the error.
- The sensor driver can use this time to set up any config registers within the device
- Any interrupts that the sensor offers can be registered here

The `begin()` function returns a signed 8-bit integer. A value of 0 means success, and any other 
value represents a status code.

### Data acquisition cycle

Each child of `Sensor` should contain a data store specific to its function. For example:
- Accelerometers store acceleration vectors (x,y,z)
- Barometers store temperature and pressure
- GPS units store position data

Like any other software written with the Arduino framework, after going through a setup sequence,
the program enters a loop. Every loop, for each sensor, the `readData()` function is called. 
This gives the `Sensor` an opportunity to update its current values with new ones.

> Whether the sensor updates its data store or not is its own choice. In general, the sensor 
> should attempt to minimise time spent reading data, as this slows down the loop.
> 
> Consider an example of a GPS device that updates at 5Hz, but the `readData()` function is called 
> at 200Hz. The sensor driver should know not to read from the GPS if there has not been an update, 
> as this would be unnecessary and slow the system down

### Self test

MRAS may want to check to see if a sensor is working normally. in order to do this, MRAS will 
call the `selfTest()` function.

A return value of `-1` means that this `Sensor` does not have a self test implemented, so the 
result is unknown.

A return value of `0` means that the `Sensor` passed the test, and is working normally.

A return value that does not equal `-1` or `0` means the test failed.

## How to init submodules:
    git pull --recurse-submodules
