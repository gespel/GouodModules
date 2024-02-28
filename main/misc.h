#include <GyverOLED.h>


class StatusLed {
public:
    StatusLed();
    void toggle();
private:
    int state = 0;
};

StatusLed::StatusLed() {

}
void StatusLed::toggle() {
    if(state == 0) {
        state = 1;
        digitalWrite(17, HIGH);
        //15
    }
    else {
        state = 0;
        digitalWrite(17, LOW);
    }
}

class DisplayHandler {
public:
    DisplayHandler();
    void printPotiValues(double v1, double v2, double v3);
    void printFooter();

private:
    GyverOLED<SSH1106_128x64> *oled;
};

DisplayHandler::DisplayHandler() {
    this->oled = new GyverOLED<SSH1106_128x64>();
    this->oled->init();
    this->oled->clear();   
    this->oled->update();  
    this->oled->setCursor(0,0);
    this->oled->print("Made by Gouod Records");
    this->oled->setCursor(0, 1);
    this->oled->print("GouodModule v0.1");
    this->oled->setCursor(0, 7);
    this->oled->print("Thats the spirit!");
    this->oled->update(); 
    delay(3000);
}

void DisplayHandler::printPotiValues(double v1, double v2, double v3) {
    this->oled->clear();
    this->oled->setCursor(0, 0);
    this->oled->print("Osc Freq 1: ");
    this->oled->print(v1);
    this->oled->setCursor(0, 1);
    this->oled->print("Osc Freq 2: ");
    this->oled->print(v2);
    this->oled->setCursor(0, 2);
    this->oled->print("Osc Freq 3: ");
    this->oled->print(v3);
    this->oled->setCursor(0, 7);
    this->oled->print("Thats the spirit!");
    this->oled->update(); 
}

void DisplayHandler::printFooter() {
    this->oled->setCursor(0, 7);
    this->oled->print("Thats the spirit!");
    this->oled->update(); 
}