#include <sdbus-c++/sdbus-c++.h>
#include <loglibrary.h>
#include <settingslib.h>

#include <thread>
#include <chrono>

#include "commandexecutor.h"

#define BUTTON_DESTINATION "org.gspine.button"
#define BUTTON_OBJECTPATH  "/org/gspine/button"

#define GESTURE_DESTINATION "org.gspine.gesture"
#define GESTURE_OBJECTPATH  "/org/gspine/gesture"

#define INHIBIT_DESTINATION "org.gspine.lowpower"
#define INHIBIT_OBJECTPATH  "/org/gspine/lowpower"


int main(int argc, char *argv[])
{
    auto gestureProxy = sdbus::createProxy(GESTURE_DESTINATION, GESTURE_OBJECTPATH);
    auto buttonProxy  = sdbus::createProxy(BUTTON_DESTINATION, BUTTON_OBJECTPATH);

    SettingsLib settings{"/etc"};

    CommandExecutor ce(&settings);
    auto onSignalArrived = [&](sdbus::Signal& s){ce.runCommand(s);};


    for (std::string section: settings.getSections()){
        std::string interface = settings.getValue(section, "interface");
        std::string signalName = settings.getValue(section, "signalName");
        std::string cmd = settings.getValue(section, "cmd");

        if (interface.find("button") != std::string::npos)
            buttonProxy->registerSignalHandler(interface, signalName, onSignalArrived);
        else
            gestureProxy->registerSignalHandler(interface, signalName, onSignalArrived);

        LOG("Registered interface {}, signalName {}", interface, signalName);
    }

    gestureProxy->finishRegistration();
    buttonProxy->finishRegistration();

    for (;;){
        std::this_thread::sleep_for(std::chrono::milliseconds(100000));
    }
    return 0;
}
