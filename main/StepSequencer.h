class StepSequencer {
public:
    StepSequencer(float sampleRate, Vector<float> seq);
    void setSequence(Vector<float> seq);
    void setSpeed(float speed);
    float getSample();
    float getRandomSample();
    void randomTick();
    void tick();
    void doStep();

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

void StepSequencer::doStep() {
  this->counter++;
  if (this->counter > this->seq.size() - 1) {
    this->counter = 0;
  }
}

void StepSequencer::tick() {
  if (this->i > this->numPerStep) {
        this->doStep();
        this->i = 0;
    }
    this->i++;
}
float StepSequencer::getSample() {
    
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
