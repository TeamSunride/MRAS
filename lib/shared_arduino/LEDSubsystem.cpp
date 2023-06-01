//
// Created by Tom Danvers on 01/06/2023.
//

#include "LEDSubsystem.h"
#include "system_messages/LEDMsg.h"
#include "system_messages/GNSSDataMsg.h"
#include "MRAS_Config.h"

int8_t LEDSubsystem::setup() {
    log("Setting up LEDSubsystem");
    pixels.begin();
    pixels.clear();

    pixels.setBrightness(50);

    pixels.show();

    log("LEDSubsystem setup complete");
    return 0;
}

int8_t LEDSubsystem::loop() {
    return 0;
}

void LEDSubsystem::on_message(SystemMessage *msg) {
    if (msg->get_type() == LEDMsg_t) {
        auto *ledMsg = (LEDMsg *) msg;
        pixels.setPixelColor(ledMsg->pixel, Adafruit_NeoPixel::Color(ledMsg->r, ledMsg->g, ledMsg->b));
        log("Setting pixel %d to %d %d %d", ledMsg->pixel, ledMsg->r, ledMsg->g, ledMsg->b);
        pixels.show();
    }

    if (msg->get_type() == GNSSDataMsg_t) {
        auto *gnssMsg = (GNSSDataMsg *) msg;
        int pin = 0;
        switch (gnssMsg->id) {
            case MAXM10s_ID:
                pin = 0;
                break;
            case SAMM10Q_ID:
                pin = 1;
                break;
        }

        // calculate rgb colour for each fix type case
        uint8_t r = 0;
        uint8_t g = 0;
        uint8_t b = 0;
        switch (gnssMsg->fix_type) {
            case 2: // 2D fix
                // BLUE
                pixels.setPixelColor(pin, Adafruit_NeoPixel::Color(0, 251, 255));
                break;
            case 3: // 3D fix
            case 4: // GNSS + dead reckoning
                // GREEN
                pixels.setPixelColor(pin, Adafruit_NeoPixel::Color(0, 255, 0));
                break;
            case 5: // time only fix
                // ORANGE
                pixels.setPixelColor(pin, Adafruit_NeoPixel::Color(255, 145, 0));
                break;
            default: // no fix
                // RED
                pixels.setPixelColor(pin, Adafruit_NeoPixel::Color(255, 0, 0));
                break;
        }
        pixels.show();
    }
}
