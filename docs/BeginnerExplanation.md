# MRAS code to a Beginner 

These explain a few concepts that I found difficult to grasp as new member looking into MRAS codebase. Intentionally used informal tone to format it like a conversation rather than a reference material. 

## System Message Explanation
MRAS system is split into sub-systems with each subsytem talking to each other with messages, specifically system messages (`SystemMessage`). The second most popular word among Sunride software team-members is sub-system, the first being message. So before we explore the sub-systems it's important to understand the messaging infrastructure. 

The `SystemMessage.h` includes a enum `SystemMessageType` which contains all the **types** that the `SystemMessage` can be like barometer data, accelerometer data etc. These data are named using this format `{Name of Source}DataMsg_t`. So for example baromoter message is named as `BarometerDataMsg_t`. This is strictly for other classes to diffrentiate message types and is **NOT** an actual *data type* in c++ context, an example use case is lets say you only want the environmental data, you would only care about the barometer output so you can use a `switch` statement to only print out the message **if** its of the type `BarometerDataMsg_t`. Since they are contained within an enum each "message type" expands to an int. The acutal *data type* (in c++ context) is formatted as `{Name of Source}DataMsg`, an example would be `BarometerDataMsg` (the undersore t is dropped). 

Now lets understand `BarometerDataMsg`. This is its definition:
```cpp
struct BarometerDataMsg : public SystemMessage {
explicit BarometerDataMsg() : SystemMessage(BarometerDataMsg_t) {}

float pressure = 0;
float temperature = 0;
};
```
As you can see it's a `struct`, in C++, structs are their own "data type" so each subsystem **class** has a struct that is the message it would "send" and the data type is the name of the struct. Let's break this down line-by-line. In the first line the `:` operator suggests that it inherits from another **class** *(structs == class in c++, with different default behaviour [more here](https://stackoverflow.com/questions/3574040/c-can-a-struct-inherit-from-a-class))* `SystemMessage`. In the second line you can find `:` operator combined with constructors, here it simply means we are calling (explicitly) the constructor of `SystemMessage`. `BarometerDataMsg_t` that is parsed into the constructor simply acts as an ID for the message. Then you have the acutal content of the message/struct. 

Detour to `SystemMessage`, the reason why it exists (in my opinion) is to enforce the use of the messaging infrastructure and mainly as a placeholder for when the messages are **published**. Emphasis on publish, as the `SystemMessage` is "published" to all of its "subscribers", subscribers are other sub-systems that require this message. Like a newspaper/magazine, `SystemMessage` is the newspaper/magazine, the sub-systems are the publishing house and you are the sub-systems that recieves the message. Now that you have recieved it, you have a lot of data that you may or may not want, if you are like me you might only want to look at pictures so `SystemMessage` class provides a neat way of sorting it. Here's an example:

```cpp
void StateEstimator::on_message(SystemMessage *msg)
{
if (msg->get_type() == BarometerDataMsg_t)
{
    auto Nmsg = (BarometerDataMsg *) msg;
    log("Estimated altitude: %f", altitudeEstimate(Nmsg));
}

}
```

The `StateEstimator` class recieves a catalogue of information everytime a sub-system publishes, the `SystemMessage` but it only needs the barometer reading so it can simply use the function `get_type()` in an if statement to filter out the barometer data.  
	
## Subsystem Explanation
Now we talk about the sub-systems themselves. There are two types of them in MRAS, Message Handlers and Non-Message Handlers. As I understand it any sub-system that recieves and proccesses the messages is deemed message handlers and the sub-systems that only publish are non-message handlers. So the sensors fall under non-handlers and data logging systems fall under handlers. 

The `MRAS_system` is the highest level of control in MRAS. It keeps track of all the sub-systems and the paradigm is to operate all the others through the `MRAS_system`. For example: 
```cpp
int main() {
TextLogger* logger = new NativeTextLogger(0);
MRAS_System* mras = MRAS_System::get_instance();

auto *accelerometer = new FakeAccelerometer(1);
auto *data_logger = new NativeDataLogger(2);
auto *barometer = new FakeBarometer(3);
auto *altitudeEstimator = new StateEstimator(4);

mras->set_logger(logger);
mras->add_subsystem(accelerometer);
mras->add_subsystem(barometer);
mras->add_subsystem(altitudeEstimator);

accelerometer->add_subscriber(data_logger);
barometer->add_subscriber(data_logger);
barometer->add_subscriber(altitudeEstimator);
altitudeEstimator->add_subscriber(data_logger);


mras->setup();

mras->loop();

return 0;
}
```
In this `main()` we first define all the subsytems with unique IDs. And then call `add_subsytem` on `mras` to setup `mras` to track all the subsytems. Now when `setup()` and `loop()` is called on `mras` it's also called on every other subsystem that was added.
	
## Steps to make your own Sub-system:

1. Determine if your subsystem is a message handler or not
2. Accordingly implement the class. For non-message handlers a `SUBSYSTEM_NO_MESSAGE_HANDLER` is added towards at the end of the class (check out *[How to implement a Subsytem](https://mras.sunride.space/md_docs_subsystem_implementation_guide.html)*)
3. Add your system message type to the `SystemMessageType`
4. Now add the struct that defines your sub-system's message in the `system_messages` folder.
5. Now add your sub-system as subscriber to any other sub-system if needed
6. Finally add your sub-system to `mras` like found above. 
7. Take a shot everytime you type out "Msg".