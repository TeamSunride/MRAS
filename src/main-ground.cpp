//
// Created by Tom Danvers on 24/04/2022.
// 2022 TeamSunride.
// This file runs if built with the "ground" environment
//

#include <Arduino.h>
#include "downlink.h"
#include "payloads/Test_Payload.h"
#include "payloads/DARTDebugPayload.h"
#include "buzzer.h"
#include "Adafruit_NeoPixel.h"

#define NEOPIXEL_PIN    11
#define NUM_PIXELS       2

Adafruit_NeoPixel pixels(NUM_PIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

#if defined(RADIOLIB_SPI_SLOWDOWN)

#warning "RADIOLIB SPI SLOWDOWN ENABLED"
#endif

uint8_t radioBuffer[255];

int packets_received = 0;
uint32_t last_packet_update = 0;



#if defined(ARDUINO_SAMD_ZERO) && defined(SERIAL_PORT_USBVIRTUAL)
// Required for Serial on Zero based boards
#define Serial SERIAL_PORT_USBVIRTUAL

#endif

void setup() {
    pinMode(BUZZER_PIN, OUTPUT);
    Serial.begin(2000000);
    buzzer_startup();

    pixels.begin();
    pixels.setBrightness(50);

    // while (!Serial) {}
    downlink::setupRadio();
    Serial.println("Finished setting up radio. State: " + String(downlink::radioState));

    if (downlink::radioState == 0) {
        // radio startup was successful
        buzzer_tone(1800, 100, true);
        delay(20);
        buzzer_tone(1800, 100, true);

        // set pixel 0 to green to indicate successful radio startup
        pixels.setPixelColor(0, pixels.Color(0, 255, 0));
    } else {
        buzzer_error();

        pixels.setPixelColor(0, pixels.Color(255, 0, 0));
        // set pixel 0 to red to indicate radio startup failure
    }
    pixels.show();

    // start receiving data
    downlink::receive();
    Serial.println("Started receiving");
}
void loop() {
    if (downlink::radioAvailable) {

        // clear the radio buffer
        memset(radioBuffer, 0, sizeof radioBuffer);

        uint32_t start = micros();
        // output all data into the buffer. Setting `len` to zero retrieves the packet length automatically
        int state = downlink::radio.readData(radioBuffer, 0);
        uint32_t read_time = micros() - start;

        // put the radio back into receive mode
        downlink::receive();

        // CRC error checking
        if (state == 0) {   // no error
            pixels.setPixelColor(1, pixels.Color(0, 195, 255));     // light blue
        } else if (state == -7) {
            pixels.setPixelColor(1, pixels.Color(255, 132, 0));     // orange
        } else {
            pixels.setPixelColor(1, pixels.Color(255, 0, 0));     // red
            buzzer_tone(500, 500);
        }
        pixels.show();

        if (state == 0) {
            // determine which payload type was received by reading the first byte
            auto receivedPayloadType = static_cast<downlink::PayloadType>(radioBuffer[0]);

            switch (receivedPayloadType) {
                case downlink::UNDEFINED:
                    // Serial.println("Received undefined payload type, cannot print result");
                    break;
                case downlink::Test_Payload_Type: {
                    Test_Payload testPayload = fromByteArray<Test_Payload>(radioBuffer);
                    Serial.println(testPayload.toLineProtocol());
                    break;
                }
                case downlink::DARTDebugPayload: {
                    DARTDebugPayload dartDebugPayload = fromByteArray<DARTDebugPayload>(radioBuffer);
                    char output_string[512];
                    dartDebugPayload.toLineProtocol(output_string);
                    // Serial.println(output_string);
                    break;
                }
            }

            packets_received++;
        }

    }
    if (millis() - last_packet_update > 1000) {
        Serial.printf("Packets received: %d\n", packets_received);

        if (MRAS_ENABLE_BEEPING) {
            if (packets_received > 0) {
                buzzer_tone(1000 + packets_received * 20, 50);
            } else {
                buzzer_tone(500, 100);
            }
        }

        packets_received = 0;
        last_packet_update = millis();
    }
}