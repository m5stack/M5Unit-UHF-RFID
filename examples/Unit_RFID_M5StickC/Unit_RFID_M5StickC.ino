/*
 * SPDX-FileCopyrightText: 2024 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */

#include <M5StickC.h>
#include <M5GFX.h>

#include "UNIT_UHF_RFID.h"

M5GFX display;
M5Canvas canvas(&display);
Unit_UHF_RFID uhf;

String info = "";

void setup() {
    M5.begin();
    // Serial2.begin(unsigned long baud, uint32_t config, int8_t rxPin, int8_t
    // txPin, bool invert) uhf.begin(HardwareSerial *serial = &Serial2, int
    // baud=115200, uint8_t RX = 16, uint8_t TX = 17, bool debug = false);
    uhf.begin(&Serial2, 115200, 33, 32, false);
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

    display.begin();
    canvas.setRotation(3);
    canvas.setColorDepth(1);  // mono color
    canvas.setFont(&fonts::efontCN_14);
    canvas.createSprite(display.width(), display.height());
    canvas.setTextSize(1);
    canvas.setPaletteColor(1, GREEN);
    canvas.setTextScroll(true);
    canvas.println(info);
    canvas.println("1.BtnA Write or Read Card Info");
    canvas.println("2.BtnB Select Card EPC");
    canvas.pushSprite(0, 0);
}

uint8_t write_buffer[]  = {0xab, 0xcd, 0xef, 0xdd};
uint8_t reade_buffer[4] = {0};

void log(String info) {
    Serial.println("Write Data...");
    canvas.println(info);
    canvas.pushSprite(0, 0);
}

void loop() {
    if (M5.BtnA.wasPressed()) {
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
                canvas.printf("%x", reade_buffer[i]);
            }
            canvas.pushSprite(0, 0);
        } else {
            log("Read ERROR");
        }
    }
    if (M5.BtnB.wasPressed()) {
        if (uhf.select(uhf.cards[0].epc)) {
            log("Select OK");
        } else {
            log("Select ERROR");
        }
        log("Current Select EPC:");
        log(uhf.selectInfo());
    }
    M5.update();
}