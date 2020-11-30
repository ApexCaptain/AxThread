#include <Arduino.h>
#include <AxThread.hpp>

void setup() {
    Serial.begin(115200);
    Axt::setTimeout(2000, []() -> Axt::AxSignal {
        Serial.println("Hello AxT!");
        return Axt::CONTINUE;
    });
}

void loop() {
    Axt::executeThreads();
}