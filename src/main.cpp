#include <sdbus-c++/sdbus-c++.h>
#include <loglibrary.h>
#include <settingslib.h>

#include <thread>
#include <chrono>
#include <vector>

#include "commandexecutor.h"

size_t findProxyInVector(const std::vector<std::unique_ptr<sdbus::IProxy>>& input, const std::string& objectPath){
    for (size_t i = 0; i < input.size(); ++i){
        if (input.at(i)->getObjectPath() == objectPath)
            return i;
    }
    return SIZE_MAX;
}

int main(int argc, char *argv[])
{
    std::vector<std::unique_ptr<sdbus::IProxy>> dbusProxies;

    SettingsLib settings{"/etc"};

    CommandExecutor ce(&settings);
    auto onSignalArrived = [&](sdbus::Signal s){ce.runCommand(s);};


    for (std::string section: settings.getSections()){
        std::string objectPath = settings.getValue(section, "objectPath");
        size_t proxyIndex = findProxyInVector(dbusProxies, objectPath);

        if (proxyIndex == SIZE_MAX){
            std::string destination = settings.getValue(section, "destination");
            auto dbusProxy = sdbus::createProxy(sdbus::ServiceName{destination}, sdbus::ObjectPath{objectPath});
            dbusProxies.push_back(std::move(dbusProxy));
            proxyIndex = dbusProxies.size() - 1;
        }

        std::string interface = settings.getValue(section, "interface");
        std::string signalName = settings.getValue(section, "signalName");

        dbusProxies.at(proxyIndex)->registerSignalHandler(sdbus::InterfaceName{interface}, sdbus::SignalName{signalName}, onSignalArrived);

        LOG("Registered interface {}, signalName {}", interface, signalName);
    }

    for (;;){
        std::this_thread::sleep_for(std::chrono::milliseconds(100000));
    }
    return 0;
}
