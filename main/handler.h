class PotiHandler {
public:
    PotiHandler();
    void handle();
    float getPoti(int potinr);
    void printDebug();
    int getPotiThird(int potinr);
    bool getPotiButton(int potinr);
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

int PotiHandler::getPotiThird(int potinr) {
    float val = this->getPoti(potinr);
    if(val >= 0 && val <= 0.33) {
        return 0;
    }
    else if(val > 0.33 && val <= 0.66) {
        return 1;
    }
    else {
        return 2;
    }
}

bool PotiHandler::getPotiButton(int potinr) {
    float val = this->getPoti(potinr);
    if(val >= 0 && val <= 0.5) {
        return false;
    }
    else {
        return true;
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

class ButtonHandler {
    public:
        ButtonHandler();
        bool getButtonPressed(int buttonnr);
    private:
};

ButtonHandler::ButtonHandler() {

}

bool ButtonHandler::getButtonPressed(int buttonnr) {
    
}

