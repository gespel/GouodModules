class PotiHandler {
public:
  PotiHandler();
  void handle();
  float getPoti(int potinr);
private:
  float poti0 = 0;
  float poti1 = 0;
  float poti2 = 0;
};

PotiHandler::PotiHandler() {

}

void PotiHandler::handle() {
  this->poti0 = analogRead(13);
}

float PotiHandler::getPoti(int potinr) {
  if(potinr == 0) {
    return (this->poti0)/4095;
  }
}
