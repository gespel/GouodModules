#include <GyverOLED.h>

typedef enum displayMenu {
    MAIN,
    SYNTH,
    SSEQ,
    SETTINGS,
} DisplayMenu;

class GIOS {
    public:
        GIOS(String version);
        void printMainMenu(int selected);
        void printSettings();
        void println(int line, String text);
        void menuChanged();
        void clear();
        DisplayMenu currentDisplay;
    private:
        GyverOLED<SSH1106_128x64> *oled;
        int currentMenuSelect = 0;
        bool changedMenu = true;
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
}

void GIOS::clear() {
    this->oled->clear();
}

void GIOS::printMainMenu(int selected) {
    if(this->changedMenu) {
        this->currentDisplay = MAIN;
        this->currentMenuSelect = selected;
        this->oled->clear();
        this->oled->update();

        this->oled->setCursor(0, 0);
        this->oled->print("Menu:");


        this->oled->setCursor(0, 1);
        if(currentMenuSelect == 0) {
            this->oled->invertText(true);
            this->oled->print("Synthesizer");
            this->oled->invertText(false);
        }
        else {
            this->oled->print("Synthesizer");
        }
        

        this->oled->setCursor(0, 2);
        if(currentMenuSelect == 1) {
            this->oled->invertText(true);
            this->oled->print("Step Sequencer");
            this->oled->invertText(false);
        }
        else {
            this->oled->print("Step Sequencer");
        }


        this->oled->setCursor(0, 3);
        if(currentMenuSelect == 2) {
            this->oled->invertText(true);
            this->oled->print("Settings");
            this->oled->invertText(false);
        }
        else {
            this->oled->print("Settings");
        }


        this->oled->update();
        this->changedMenu = false;
    }
    
}

void GIOS::printSettings() {
    this->currentDisplay = SETTINGS;
    this->oled->clear();
    this->oled->setCursor(0, 0);
    this->oled->print("GIOS was written by");
    this->oled->setCursor(0, 1);
    this->oled->print("Sten Heimbrodt");
    this->oled->setCursor(0, 2);
    this->oled->print("Gouod Labs");
    this->oled->update();
    this->changedMenu = true;
}

void GIOS::println(int line, String text) {
    this->oled->setCursor(0, line);
    this->oled->print(text);
    this->oled->update();
}

void GIOS::menuChanged() {
    this->changedMenu = true;
}
