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

const int BUFSIZE = 1024;

const int sampleRate = 16000; // Beispielrate (Hz)
const int bitDepth = 16; // Audio-Bit-Tiefe
const int i2sChannel = 0; // I2S-Kanal (0 oder 1, je nach ESP32-Modell)
float phase = 0;
uint16_t audioBuffer[BUFSIZE];
StatusLed sled;
SawtoothSynth base(55, sampleRate);
SawtoothSynth ss(55, sampleRate);
//SawtoothSynth *ss2;
//SawtoothSynth *ss3;
float arr[2];
Vector<float> x(arr);
StepSequencer *step;
GKick gk(1, 110.f, sampleRate);
GKick kick(0, 82.5f, sampleRate);


int i = 0;
float steps = 1;
PotiHandler ph;


void setup() {
  x.push_back(1.0);
  x.push_back(2.0);
  step = new StepSequencer(sampleRate, x);
  step->setSpeed(0.5);
  //ss2 = new SawtoothSynth(110.f, sampleRate);
  //ss3 = new SawtoothSynth(110.f, sampleRate);
  Serial.begin(19200);
  pinMode(17, OUTPUT);
  pinMode(18, INPUT);
  // Konfigurieren Sie den I2S-Ausgang
  setup_i2n();
  kick.setType(0);
  gk.setType(0);    
}

void loop() {
    
  if(i % 2 == 0) {

  }
  i++;
  if(i % 4 == 0) {
    sled.toggle();
    int rt = random(3);
    int rf = random(10);
    if(rt == 1) {
      gk.setFrequency(rf*110);
      gk.trigger();
    }
  }
  if(i % 8 == 0) {
    step->doStep();
    ss.setFrequency(step->getSample()*55.f);
    kick.trigger();   
  }
  if(i % 16 == 0) {
    i = 0;
    //ph.printDebug();
  }
  
  int16_t sample;
  size_t bytes_written;
  int x = 0;

  for (int i = 0; i < BUFSIZE; i++) {
    float sample = gk.getSample() + kick.getSample() + ss.getSample()*0.1;
    audioBuffer[i] = sample;

    //step.randomTick();
    
  }
  
  i2s_write((i2s_port_t)i2sChannel, audioBuffer, sizeof(audioBuffer), &bytes_written, portMAX_DELAY);
}
