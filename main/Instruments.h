#pragma once
#include "synths.h"

class GKick {
public:
    GKick(int type, double freq, double sampleRate);
    double getSample();
    void trigger();
    double getAddKickAttackEnvelope();
    void setFrequency(float freq);
    void setType(int type);
    
private:
    double freq;
    int mastertimer;
    double sampleRate;
    int length = 13000;
    bool active = false;
    SineSynth *base;
    SawtoothSynth *base2;
    SawtoothSynth *transient;
    int type;
    int addKickEnvelopeTimer;
};

GKick::GKick(int type, double freq, double sampleRate) {
    this->type = type;
    this->freq = freq;
    this->sampleRate = sampleRate;
    base = new SineSynth(freq, sampleRate);
    base2 = new SawtoothSynth(freq, sampleRate);
    transient = new SawtoothSynth(freq * 4, sampleRate);
}
double GKick::getSample() {
    if(active) {
        mastertimer++;
        auto transientAttackEnvelope = this->getAddKickAttackEnvelope();
        auto out = 0.0f;
        //out += transient->getSample() * transientAttackEnvelope * 0.5;
        
        if(this->type == 0) {
          out = base->getSample() * (1 - ((double)mastertimer/(double)length));
        }
        else if (this->type == 1) {
          out = base2->getSample() * (1 - ((double)mastertimer/(double)length));
        }
        base->setFrequency(freq * (1 - ((double)mastertimer/(double)length)));
        base2->setFrequency(freq * (1 - ((double)mastertimer/(double)length)));
        //transient->setFrequency(freq * 4 * transientAttackEnvelope);
        
        //Kicksynthesis
        
        if(mastertimer >= length) {
            active = false;
            mastertimer = 0;
            addKickEnvelopeTimer = 0;
            base->resetPhase();
            transient->resetPhase();
        }
        return out;
    }
    else {
        return 0;
    }
}
void GKick::trigger() {
    active = true;
}

double GKick::getAddKickAttackEnvelope() {
    addKickEnvelopeTimer++;
    if(addKickEnvelopeTimer <= 200) {
        return 1 - (addKickEnvelopeTimer/200);
    }
    else {
        return 0;
    }
}

void GKick::setFrequency(float freq) {
    this->freq = freq;
}
void GKick::setType(int type) {
    this->type = type;
}