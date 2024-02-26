#pragma once
#include <Vector.h>

#include <Arduino.h>
#include <driver/i2s.h>
#include <math.h>
#include "synths.h"
#include "StepSequencer.h"
#include "Misc.h"
#include "Instruments.h"
#include "Potis.h"
#include "gios.h"


PotiHandler ph;
SemaphoreHandle_t semaphore;


const int BUFSIZE = 2048;
const int sampleRate = 16000; // Beispielrate (Hz)
const int bitDepth = 16; // Audio-Bit-Tiefe
const int i2sChannel = 0; // I2S-Kanal (0 oder 1, je nach ESP32-Modell)
float phase = 0;
uint16_t audioBuffer[BUFSIZE];

TaskHandle_t giostask;
TaskHandle_t audiotask;

int i = 0;

int sharedInteger = 0;

void osTask(void * pvParameters) {
    GIOS g("1.0");
    StatusLed sled;
    while(1) {
        //g.printMainMenu();
        sled.toggle();

        if (xSemaphoreTake(semaphore, ( TickType_t ) 100) == pdTRUE) {
            // Erhöhen des Integer-Werts
            sharedInteger++;
            Serial.println("Added!");
            // Freigeben der Semaphore, damit andere Tasks darauf zugreifen können
            xSemaphoreGive(semaphore);
        }

        delay(200);
    }
    
    
}

void audioTask(void * pvParameters) {
    setup_i2n(sampleRate, bitDepth, i2sChannel);
    SawtoothSynth ss(110.0, sampleRate);

    while(1) {

        
        
        int16_t sample;
        size_t bytes_written;
        int x = 0;

        for (int i = 0; i < BUFSIZE; i++) {
            //double sample = sf.getSample();
            double sample = ss.getSample() * 5;
            //fp.setFreq(step->getSample()*55*ph.getPoti(0));
            //sample *= 0.5;
            audioBuffer[i] = sample;

            
            
        }
        
        i2s_write((i2s_port_t)i2sChannel, audioBuffer, sizeof(audioBuffer), &bytes_written, portMAX_DELAY);


        if (xSemaphoreTake(semaphore, ( TickType_t ) 100) == pdTRUE) {
            // Verringern des Integer-Werts
            sharedInteger--;
            Serial.println("Subtracted!");
            // Freigeben der Semaphore, damit andere Tasks darauf zugreifen können
            xSemaphoreGive(semaphore);
        }
    }
    
}

void setup() {
    Serial.begin(19200);
    pinMode(17, OUTPUT);
    pinMode(16, OUTPUT);
    pinMode(18, INPUT);
    

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
    //vTaskStartScheduler();
}


void loop() {
    /*ph.handle();

    if(i % 2 == 0) {
        
    }
    i += 1;
    if(i % 4 == 0) {
        //fp.setVoiceFreq(0, ph.getPoti(0) * 440);
        //fp.setVoiceFreq(1, ph.getPoti(1) * 440);
        //fp.setVoiceFreq(2, ph.getPoti(2) * 440);

    }
    if(i % 8 == 0) {
    
    }
    if(i % 16 == 0) {
        sled.toggle();
        //dp->printPotiValues(ph.getPoti(0) * 440, ph.getPoti(1) * 440, 0);
        
        

    }
    
    if(i % 128 == 0) {
        i = 0;
        
        
    }
    
    int16_t sample;
    size_t bytes_written;
    int x = 0;

    for (int i = 0; i < BUFSIZE; i++) {
        //double sample = sf.getSample();
        double sample = fp.getSample() * 5;
        //fp.setFreq(step->getSample()*55*ph.getPoti(0));
        //sample *= 0.5;
        audioBuffer[i] = sample;
        step->tick();

        float steps = step->getSample();
        
        
    }
    
    i2s_write((i2s_port_t)i2sChannel, audioBuffer, sizeof(audioBuffer), &bytes_written, portMAX_DELAY);*/
}
