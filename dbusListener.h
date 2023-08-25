#ifndef DBUSLISTENER_H
#define DBUSLISTENER_H

#include "direction-client-glue.h"

class dbusListener : public sdbus::ProxyInterfaces<org::gspine::Gesture_proxy> {
private:
    const int KEYBOARD_TOGGLE_SIGNAL = 34;
    int keyboard_pid_;
public:
    void onTouchEvent(const std::string& direction) override;
    dbusListener(std::string destination, std::string objectPath, int keyboard_pid): ProxyInterfaces(std::move(destination), std::move(objectPath)) {
        keyboard_pid_ = keyboard_pid;
        registerProxy();
    }
    ~dbusListener(){
        unregisterProxy();
    }
};

#endif // DBUSLISTENER_H
