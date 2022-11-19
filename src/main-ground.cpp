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
#include "Payload.h"
#include "SD.h"

#define NEOPIXEL_PIN    11
#define NUM_PIXELS       2

Adafruit_NeoPixel pixels(NUM_PIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

#if defined(RADIOLIB_SPI_SLOWDOWN)

#warning "RADIOLIB SPI SLOWDOWN ENABLED"
#endif

uint8_t radioBuffer[255];

int packets_received = 0;
uint32_t last_packet_update = 0;

// file for SD card logging
File log_file;


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
    } else {
        buzzer_error();
        // set pixel 0 to red to indicate radio startup failure
    }

    // setup SD card
    if (!SD.begin(4)) {
        Serial.println("SD card init failed");
        buzzer_error();
    }

    char filename[8] = "";
    // pick an appropriate file name
    for (int i = 0; i < 1000; i++) {
        sprintf(filename, "%d.csv", i);
        if (!SD.exists(filename)) {
            break;
        }
    }

    Serial.print("SD filename: ");
    Serial.println(filename);

    log_file = SD.open(filename, FILE_WRITE);

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
            auto* payload = (Payload*)radioBuffer;

            switch (payload->get_type()) {
                case UNDEFINED:
                    // Serial.println("Received undefined payload type, cannot print result");
                    break;
                case Test_Payload_t: {
                    Test_Payload testPayload = fromByteArray<Test_Payload>(radioBuffer);
                    Serial.println(testPayload.toLineProtocol());
                    break;
                }
                case DARTDebugPayload_t: {
                    DARTDebugPayload dartDebugPayload = fromByteArray<DARTDebugPayload>(radioBuffer);
                    char output_line_protocol[512];
                    char output_csv[512];
                    dartDebugPayload.toLineProtocol(output_line_protocol);
                    dartDebugPayload.toCSVformat(output_csv);
                    log_file.println(output_csv);
                    Serial.println(output_line_protocol);

                    switch(dartDebugPayload.fixType) {
                        case 0: {
                            // No fix, red
                            pixels.setPixelColor(0, pixels.Color(255, 0, 0));
                            break;
                        }
                        case 1: {
                            // Dead reckoning, orange
                            pixels.setPixelColor(0, pixels.Color(255, 120, 10));
                        }
                        case 2: {
                            // 2D fix, yellow
                            pixels.setPixelColor(0, pixels.Color(250, 222, 42));
                        }
                        case 3: {
                            // 3D fix, green
                            pixels.setPixelColor(0, pixels.Color(0, 255, 0));
                        }
                        case 4: {
                            // GNSS + Dead Reckoning, purple
                            pixels.setPixelColor(0, pixels.Color(184, 119, 217));
                        }
                        case 5: {
                            // Time fix, pink
                            pixels.setPixelColor(0, pixels.Color(255, 115, 131));
                        }
                    }
                    break;
                }
            }

            packets_received++;
        }

    }
    if (millis() - last_packet_update > 1000) {
        // Serial.printf("Packets received: %d\n", packets_received);

        // make sure bytes are written to SD card
        log_file.flush();
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