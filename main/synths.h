class SineSynth {
public:
  SineSynth(double freq, double sampleRate);
  double getSample();
  void setFrequency(double freq);
  void resetPhase();
private:
  float freq = 0;
  float phase = 0;
  float sampleRate = 0;
};

SineSynth::SineSynth(double freq, double sampleRate) {
    this->freq = freq;
    this->sampleRate = sampleRate;
}
double SineSynth::getSample() {
    this->phase += (this->freq / this->sampleRate) * 2.0 * 3.14159265;
    return sin(this->phase) * 5000;
}
void SineSynth::setFrequency(double freq) {
    this->freq = freq;
}
void SineSynth::resetPhase() {
    this->phase = 0;
}

class SawtoothSynth {
public:
    SawtoothSynth(double freq, double sampleRate);
    double getSample();
    void setFrequency(double freq);
    void resetPhase();
private:
    double sample = 0;
    float freq = 0;
    float phase = 0;
    float sampleRate = 0;
};

SawtoothSynth::SawtoothSynth(double freq, double sampleRate) {
    this->freq = freq;
    this->sampleRate = sampleRate;
}
double SawtoothSynth::getSample() {
    sample += this->freq/this->sampleRate;
    if(sample > 1) {
        sample = -1;
    }
    return sample * 5000;
}
void SawtoothSynth::setFrequency(double freq) {
    this->freq = freq;
}
void SawtoothSynth::resetPhase() {
    this->sample = -1;
}