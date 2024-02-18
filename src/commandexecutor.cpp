#include <loglibrary.h>
#include "commandexecutor.h"


CommandExecutor::CommandExecutor(SettingsLib *settings)
{
    _settings = settings;
}

void CommandExecutor::runCommand(sdbus::Signal &signal)
{
    if (inhibitExecution)
        return;

    std::string interface = signal.getInterfaceName();
    std::string memberName = signal.getMemberName();
    for (const auto& section: _settings->getSections()){
        if (_settings->getValue(section, "interface") != interface)
            continue;
        if (_settings->getValue(section, "signalName") != memberName)
            continue;

        std::string cmd = _settings->getValue(section, "cmd");

        LOG("Running command: {}", cmd);

        FILE *cmd_output = popen(cmd.c_str(), "r");
        if (!cmd_output){
            ERROR("Could not execute command: {}, errno: {}", cmd, errno);
            continue;
        }

        pclose(cmd_output);
    }
}

void CommandExecutor::disableExecution()
{
    inhibitExecution = true;
}

void CommandExecutor::enableExecution()
{
    inhibitExecution = false;
}
