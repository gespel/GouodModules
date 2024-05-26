#pragma once
#include <Vector.h>

#include <Arduino.h>
#include <driver/i2s.h>
#include <math.h>
#include "GouodModulesLib/synths.h"
#include "GouodModulesLib/stepsequencer.h"
#include "GouodModulesLib/misc.h"
#include "GouodModulesLib/instruments.h"
#include "GouodModulesLib/handler.h"
#include "GouodModulesLib/gios.h"


SemaphoreHandle_t semaphore;


const int BUFSIZE = 2048;

float phase = 0;
uint16_t audioBuffer[BUFSIZE];

TaskHandle_t giostask;
TaskHandle_t audiotask;

int i = 0;

int sharedInteger = 0;

void osTask(void * pvParameters) {
    StatusLed sled;

    while(1) {
        sled.toggle();
        delay(200);
    }
}

void audioTask(void * pvParameters) {
    int sampleRate = 48000;

    setup_i2n(sampleRate, 16, 0);
    SawtoothSynth ss(110.0, sampleRate);
    SawtoothSynth ss2(55.0, sampleRate);

    while(1) {
        int16_t sample;
        size_t bytes_written;
        int x = 0;

        for (int i = 0; i < BUFSIZE; i++) {
            //double sample = sf.getSample();
            double sample = (ss2.getSample() + ss.getSample()) * 5;
            //fp.setFreq(step->getSample()*55*ph.getPoti(0));
            //sample *= 0.5;
            audioBuffer[i] = sample;

            
            
        }
        
        i2s_write((i2s_port_t)0, audioBuffer, sizeof(audioBuffer), &bytes_written, portMAX_DELAY);


        /*if (xSemaphoreTake(semaphore, ( TickType_t ) 100) == pdTRUE) {
            // Verringern des Integer-Werts
            sharedInteger--;
            Serial.println("Subtracted!");
            // Freigeben der Semaphore, damit andere Tasks darauf zugreifen können
            xSemaphoreGive(semaphore);
        }*/
    }
    
}

void setup() {
    Serial.begin(19200);
    pinMode(17, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(14, OUTPUT);
    pinMode(16, OUTPUT);
    pinMode(18, OUTPUT);
    pinMode(34, OUTPUT);
    pinMode(32, OUTPUT);
    pinMode(33, OUTPUT);

    semaphore = xSemaphoreCreateMutex();
    xTaskCreatePinnedToCore(
        osTask,
        "gios",
        10000,
        NULL,
        1,
        &giostask,
        1
    );
    delay(500);     

    xTaskCreatePinnedToCore(
        audioTask,
        "audio",
        10000,
        NULL,
        1,
        &audiotask,
        0
    );
    delay(500);      
}


void loop() {

}
