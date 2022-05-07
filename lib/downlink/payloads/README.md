# Payload implementations

This directory contains data structures which define the layout of all payloads sent or received by the radio.

The radio is capable of transmitting byte arrays. In order to for the receiver to know how to convert these bytes into a
useful object, the first byte of the payload **always** represents the type

> My initial approach was to use abstract classes to enforce this, but this resulted in a change to the payload size 
> as [virtual functions took up space in memory](https://stackoverflow.com/questions/17281932/size-of-c-classes) 
> (I did not know this was the case until now)

Therefore any payload structs defined in this directory MUST follow the same structure and MUST implement the following 
features:

- The first field MUST be of type `downlink::PayloadType`
- There must be a method defined called `String toLineProtocol()` which converts the contents of the data structure to a Line Protocol string

For each payload type that is created, a corresponding entry to the enum `downlink::PayloadType` should be made

## Example

```cpp
struct Test_Payload {
    // this field MUST BE DEFINED FIRST
    downlink::PayloadType type = downlink::PayloadType::Test_Payload_Type;
    
    // other fields specific to this payload
    uint8_t x = 0;
    uint8_t y = 0;
    uint8_t z = 0;

    uint64_t timestamp = 0;

    String toLineProtocol() const;

    Test_Payload(int16_t _x, int16_t _y, int16_t _z) {
        x = _x;
        y = _y;
        z = _z;
    }
};
```