#include <Vector.h>

#include <Arduino.h>
#include <driver/i2s.h>
#include <math.h>
#include "synths.h"
#include "StepSequencer.h"
#include "Misc.h"

const int BUFSIZE = 1024;

const int sampleRate = 16000; // Beispielrate (Hz)
const int bitDepth = 16; // Audio-Bit-Tiefe
const int i2sChannel = 0; // I2S-Kanal (0 oder 1, je nach ESP32-Modell)
float phase = 0;
uint16_t audioBuffer[BUFSIZE];
StatusLed *sled;
SawtoothSynth *base;
SawtoothSynth *ss;
SawtoothSynth *ss2;
SawtoothSynth *ss3;
StepSequencer *step;
float arr[8];
Vector<float> x(arr);
int i = 0;


void setup() {
    sled = new StatusLed();
    x.push_back(1.0);
    x.push_back(2.0);
    x.push_back(3.0);
    x.push_back(4.0);
    x.push_back(5.0);
    x.push_back(6.0);
    x.push_back(7.0);
    x.push_back(8.0);
    
    step = new StepSequencer(sampleRate, x);
    step->setSpeed(0.5);
    base = new SawtoothSynth(54.0f, sampleRate);
    ss = new SawtoothSynth(110.0f, sampleRate);
    ss2 = new SawtoothSynth(110.f, sampleRate);
    ss3 = new SawtoothSynth(110.f, sampleRate);
    Serial.begin(19200);
    pinMode(17, OUTPUT);
    pinMode(18, INPUT);
    // Konfigurieren Sie den I2S-Ausgang
    setup_i2n();
}

void loop() {
    i++;
    if(i % 16 == 0) {
        sled->toggle();
        i = 0;
    }
    // Erzeugen Sie einen Sinus-Ton und geben Sie ihn über I2S aus
    
    int16_t sample;
    size_t bytes_written;
    int input = analogRead(33);
    int x = 0;

    for (int i = 0; i < BUFSIZE; i++) {
      float sample = (base->getSample() + ss->getSample() + ss2->getSample() + ss3->getSample()) / 4;
      audioBuffer[i] = sample;

      float steps = step->getRandomSample();
      ss->setFrequency(steps*55.f);
      ss2->setFrequency(steps*110.f);
      ss3->setFrequency(steps*112.f);
    }
    
    i2s_write((i2s_port_t)i2sChannel, audioBuffer, sizeof(audioBuffer), &bytes_written, portMAX_DELAY);
    //sleep(1);

    
    //sleep(1);   
}
