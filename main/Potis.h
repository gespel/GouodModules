class PotiHandler {
public:
  PotiHandler();
  void handle();
  float getPoti(int potinr);
  void printDebug();
private:
  float poti0 = 0;
  float poti1 = 0;
  float poti2 = 0;
};

PotiHandler::PotiHandler() {

}

void PotiHandler::handle() {
  this->poti0 = analogRead(13);
  this->poti1 = analogRead(12);
  this->poti2 = analogRead(14);
}

float PotiHandler::getPoti(int potinr) {
  if(potinr == 0) {
    return (this->poti0)/4095;
  }
  if(potinr == 1) {
    return (this->poti1)/4095;
  }
  if(potinr == 2) {
    return (this->poti2)/4095;
  }
}

void PotiHandler::printDebug() {
  Serial.print("Poti 0:");
  Serial.println(this->getPoti(0));
  Serial.print("Poti 1:");
  Serial.println(this->getPoti(1));
  Serial.print("Poti 2:");
  Serial.println(this->getPoti(2)); 
}
