class StepSequencer {
public:
    StepSequencer(float sampleRate, Vector<float> seq);
    void setSequence(Vector<float> seq);
    void setSpeed(float speed);
    float getSample();
    float getRandomSample();
    void randomTick();

private:
    float sampleRate;
    Vector<float> seq;
    float speed;
    float numPerStep;
    int i;
    int counter;
    int randomCounter;
};

StepSequencer::StepSequencer(float sampleRate, Vector<float> seq) {
    this->sampleRate = sampleRate;
    this->seq = seq;
    this->speed = 1;
    this->numPerStep = 0;
    this->setSpeed(this->speed);
    this->i = 0;
    this->counter = 0;
    this->randomCounter = 0;
}

void StepSequencer::setSequence(Vector<float> seq) {
    this->seq = seq;
}

void StepSequencer::setSpeed(float speed) {
    this->speed = speed;
    this->numPerStep = (this->sampleRate * (1 / this->speed)) / this->seq.size();
}

float StepSequencer::getSample() {
    if (this->i > this->numPerStep) {
        this->counter++;
        if (this->counter > this->seq.size() - 1) {
            this->counter = 0;
        }
        this->i = 0;
    }
    this->i++;
    return this->seq.at(counter);
}

void StepSequencer::randomTick() {
  if (this->i > this->numPerStep) {
        this->randomCounter = random(this->seq.size());
        this->i = 0;
    }
    this->i++;
}

float StepSequencer::getRandomSample() {
    return this->seq[this->randomCounter];
}
