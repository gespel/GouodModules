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
    }
    else {
        state = 0;
        digitalWrite(17, LOW);
    }
}