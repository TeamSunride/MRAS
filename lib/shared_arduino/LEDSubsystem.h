//
// Created by Tom Danvers on 01/06/2023.
//

#ifndef MRAS_LEDSUBSYSTEM_H
#define MRAS_LEDSUBSYSTEM_H


#include "Subsystem.h"
#include "Adafruit_NeoPixel.h"

class LEDSubsystem : public Subsystem {
private:
    Adafruit_NeoPixel pixels;
protected:

    // create subsystem boilerplate
    SUBSYSTEM_NAME("LEDSubsystem")

    // create setup and loop functions
    int8_t setup() override;

    int8_t loop() override;

    void on_message(SystemMessage *msg) override;

public:
// constructor
LEDSubsystem(uint8_t id, uint8_t pin, uint8_t num_pixels) : Subsystem(id),
                                                            pixels(num_pixels, pin, NEO_GRB + NEO_KHZ800) {}
};


#endif //MRAS_LEDSUBSYSTEM_H
