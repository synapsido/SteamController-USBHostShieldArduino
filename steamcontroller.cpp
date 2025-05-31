//
//  steamcontroller.cpp
//  Arduino library for HID with the Valve Steam Controller through the USB Host Shield
//
//  Created by Mauricio Emilio Iturri Calvo @synapsido on 6/9/17.
//
//

#include <Usb.h>
#include <hiduniversal.h>
#include <usbhub.h>
#include "steamcontroller.h"

USBHost Usb;
USBHub Hub(&Usb);
HIDUniversal Hid(&Usb);

// Parser personalizado para el Steam Controller
class SteamControllerParser : public HIDReportParser {
public:
    virtual void Parse(HID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf) {
        // Procesar los datos del controlador aquí
        Serial.print("Datos recibidos: ");
        for (int i = 0; i < len; i++) {
            Serial.print(buf[i], HEX);
            Serial.print(" ");
        }
        Serial.println();
    }
};

SteamControllerParser SteamParser;

void setup() {
    Serial.begin(115200);
    Serial.println("Iniciando USB Host...");

    if (Usb.Init() == -1) {
        Serial.println("Error al inicializar USB Host");
        while (1); // Detener si hay error
    }

    // Filtrar por VID/PID del Steam Controller
    Hid.SetReportParser(0, &SteamParser);
    Hid.AddDevice(STEAM_CONTROLLER_VID, STEAM_CONTROLLER_PID);
}

void loop() {
    Usb.Task();
    delay(10);
}