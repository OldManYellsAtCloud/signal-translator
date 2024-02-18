#ifndef COMMANDEXECUTOR_H
#define COMMANDEXECUTOR_H
#include <settingslib.h>
#include <sdbus-c++/sdbus-c++.h>

class CommandExecutor
{
private:
    SettingsLib* _settings;
    bool inhibitExecution = false;
public:
    explicit CommandExecutor(SettingsLib* settings);
    void runCommand(sdbus::Signal& signal);
    void disableExecution();
    void enableExecution();
};

#endif // COMMANDEXECUTOR_H
