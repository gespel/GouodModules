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

const int sampleRate = 48000; // Beispielrate (Hz)
const int bitDepth = 16; // Audio-Bit-Tiefe
const int i2sChannel = 0; // I2S-Kanal (0 oder 1, je nach ESP32-Modell)
float phase = 0;
uint16_t audioBuffer[BUFSIZE];
StatusLed sled;
PotiHandler ph;

float arr[4];
Vector<float> x(arr);
StepSequencer *step;

FatPad fp(55.0, sampleRate);

int i = 0;
float steps = 1;

void setup() {
  x.push_back(1.0);
  x.push_back(2.0);
  x.push_back(4);
  x.push_back(6);

  step = new StepSequencer(sampleRate, x);
  step->setSpeed(1);
  Serial.begin(19200);
  pinMode(17, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(18, INPUT);
  setup_i2n();
}

void loop() {
  ph.handle();

  if(i % 2 == 0) {
    
  }
  i += 1;
  if(i % 4 == 0) {

  }
  if(i % 8 == 0) {
  
  }
  if(i % 16 == 0) {
    sled.toggle();
    ph.handle();
    fp.setVoiceFreq(0, (1 - ph.getPoti(0)) * 440);
    fp.setVoiceFreq(1, ph.getPoti(1) * 440);
    fp.setVoiceFreq(2, ph.getPoti(2) * 440);

  }

  if(i % 128 == 0) {
    i = 0;
    
    
  }
  
  int16_t sample;
  size_t bytes_written;
  int x = 0;

  for (int i = 0; i < BUFSIZE; i++) {
    float sample = fp.getSample();
    //sample *= 0.5;
    audioBuffer[i] = sample;
    step->tick();

    float steps = step->getSample();
    
    
  }
  
  i2s_write((i2s_port_t)i2sChannel, audioBuffer, sizeof(audioBuffer), &bytes_written, portMAX_DELAY);
}
