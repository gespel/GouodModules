#include <GyverOLED.h>

class GIOS {
    public:
        GIOS(String version);
        void printMainMenu();
    private:
        GyverOLED<SSH1106_128x64> *oled;
};

GIOS::GIOS(String version) {
    this->oled = new GyverOLED<SSH1106_128x64>();
    this->oled->init();
    this->oled->clear();   
    this->oled->update();  
    this->oled->setCursor(0,0);
    this->oled->print("GIOS v" + version);
    this->oled->setCursor(0, 1);
    this->oled->print("Made by Gouod Records");
    this->oled->setCursor(0, 7);
    this->oled->print("Thats the spirit!");
    this->oled->update(); 
    delay(3000);
}

void GIOS::printMainMenu() {
    this->oled->clear();
    this->oled->update();
    this->oled->setCursor(0, 0);
    this->oled->print("Synthesizer");
    this->oled->update();
}
