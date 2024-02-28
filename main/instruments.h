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

class FatPad {
    public:
        FatPad(double freq, double sampleRate);
        void setFreq(double freq);
        void setVoiceFreq(int voiceNr, double freq);
        double getSample();

    private:
        SawtoothSynth *v1;
        SawtoothSynth *v2;
        SawtoothSynth *v3;
        double sampleRate;
        double freq[3] = {55.0, 55.0, 55.0};
        void updateVoices();
};

FatPad::FatPad(double freq, double sampleRate) {
    this->v1 = new SawtoothSynth(freq, sampleRate);
    this->v2 = new SawtoothSynth(freq, sampleRate);
    this->v3 = new SawtoothSynth(freq, sampleRate);
    this->freq[0] = freq;
    this->freq[1] = freq;
    this->freq[2] = freq;
    this->sampleRate = sampleRate;
}

double FatPad::getSample() {
    return (this->v1->getSample() + this->v2->getSample() + this->v3->getSample()) / 3;
}

void FatPad::updateVoices() {
    this->v1->setFrequency(this->freq[0]);
    this->v2->setFrequency(this->freq[1]);
    this->v3->setFrequency(this->freq[2]);
}

void FatPad::setFreq(double freq) {
    this->freq[0] = freq;
    this->freq[1] = freq;
    this->freq[2] = freq;
    this->updateVoices();
}

void FatPad::setVoiceFreq(int voiceNr, double freq) {
    this->freq[voiceNr] = freq;
    this->updateVoices();
}

class StrangeFM {
    public:
        StrangeFM(double freq, double sampleRate);
        double getSample();
        void setBaseFreq(double freq);
        void setModulatorFreq(double freq);
    private:
        SineSynth *base;
        SineSynth *modulator;
        double baseFreq;
        double modulatorFreq;
        double sampleRate;
        int counter = 0;
};

StrangeFM::StrangeFM(double freq, double sampleRate) {
    this->baseFreq = freq;
    this->modulatorFreq = freq;
    this->sampleRate = sampleRate;
    this->base = new SineSynth(this->baseFreq, this->sampleRate);
    this->modulator = new SineSynth(this->modulatorFreq, this->sampleRate);
}

double StrangeFM::getSample() {
    counter++;
    double out = base->getSample();
    if(counter >= 256) {
        base->setFrequency(this->baseFreq * modulator->getSample() / 5000);
        counter = 0;
    }
    

    return out;
}

void StrangeFM::setBaseFreq(double freq) {
    this->baseFreq = freq;
    this->base->setFrequency(this->baseFreq);
}

void StrangeFM::setModulatorFreq(double freq) {
    this->modulatorFreq = freq;
    this->modulator->setFrequency(this->modulatorFreq);
}



