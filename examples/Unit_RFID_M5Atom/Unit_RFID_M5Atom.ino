/*
 * SPDX-FileCopyrightText: 2024 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */

#include <M5Atom.h>
#include "UNIT_UHF_RFID.h"

Unit_UHF_RFID uhf;

String info = "";

void setup() {
    M5.begin(true, true, true);
    // Serial2.begin(unsigned long baud, uint32_t config, int8_t rxPin, int8_t
    // txPin, bool invert) uhf.begin(HardwareSerial *serial = &Serial2, int
    // baud=115200, uint8_t RX = 16, uint8_t TX = 17, bool debug = false);
    uhf.begin(&Serial2, 115200, 32, 26, false);
    //   uhf.begin();
    while (1) {
        info = uhf.getVersion();
        if (info != "ERROR") {
            Serial.println(info);
            break;
        }
    }

    // max: 26dB
    uhf.setTxPower(2600);
}

uint8_t write_buffer[]  = {0xab, 0xcd, 0xef, 0xdd};
uint8_t reade_buffer[4] = {0};

void log(String info) {
    Serial.println("Write Data...");
}

void loop() {
    if (M5.Btn.wasPressed()) {
        log("Write Data...");
        // uhf.writeCard(uint8_t *data, size_t size, uint8_t membank, uint16_t
        // sa, uint32_t access_password = 0);
        if (uhf.writeCard(write_buffer, sizeof(write_buffer), 0x04, 0, 0x00000000)) {
            log("Write OK");
        } else {
            log("Write ERROR");
        }
        delay(1000);
        log("Read Data...");
        // uhf.readCard(uint8_t *data, size_t size, uint8_t membank, uint16_t
        // sa, uint32_t access_password = 0);
        if (uhf.readCard(reade_buffer, sizeof(reade_buffer), 0x04, 0, 0x00000000)) {
            log("Read OK");
            log("Data Content");
            for (uint8_t i = 0; i < sizeof(reade_buffer); i++) {
                Serial.printf("%x", reade_buffer[i]);
            }
        } else {
            log("Read ERROR");
        }
    }
    M5.update();
}