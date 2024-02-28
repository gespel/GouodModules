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


SemaphoreHandle_t semaphore;


const int BUFSIZE = 2048;

float phase = 0;
uint16_t audioBuffer[BUFSIZE];

TaskHandle_t giostask;
TaskHandle_t audiotask;

int i = 0;

int sharedInteger = 0;

void osTask(void * pvParameters) {
    GIOS g("1.0");
    delay(1000);
    StatusLed sled;
    g.println(2, "Loaded StatusLED...");
    delay(700);
    PotiHandler ph;
    ph.handle();
    g.println(3, "Loaded PotiHandler...");
    
    int prev_poti1 = ph.getPotiThird(0);
    bool select_pot = ph.getPotiButton(1);

    delay(700);
    g.currentDisplay = MAIN;
    g.printMainMenu(0);

    while(1) {
        if(g.currentDisplay == MAIN) {
            if(prev_poti1 != ph.getPotiThird(0)) {
                g.menuChanged();
                g.printMainMenu(ph.getPotiThird(0));
                prev_poti1 = ph.getPotiThird(0);
            }
            if(ph.getPotiButton(1)) {
                if(ph.getPotiThird(0) == 2) {
                    g.printSettings();
                }
            }
        }

        if(g.currentDisplay == SETTINGS) {
            if(!ph.getPotiButton(1)) {
                g.menuChanged();
                g.printMainMenu(ph.getPotiThird(0));
                prev_poti1 = ph.getPotiThird(0);
            }
        }
        
        Serial.println(g.currentDisplay);
        sled.toggle();

        /*if (xSemaphoreTake(semaphore, ( TickType_t ) 100) == pdTRUE) {
            sharedInteger++;
            Serial.println("Added!");
            xSemaphoreGive(semaphore);
        }*/
        ph.handle();
        delay(50);
    }
    
    
}

void audioTask(void * pvParameters) {
    int sampleRate = 16000;

    setup_i2n(sampleRate, 16, 0);
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
}


void loop() {

}
