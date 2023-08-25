#include "dbusListener.h"
#include "logger.h"
#include <unistd.h>
#include <stdlib.h>

pid_t getKeyboardPid(){
    char line[10];
    int timeout = 10;
    char *cmd = "/bin/pidof wvkbd-mobintl";
    pid_t keyboard_pid = 0;

    int i;
    for (i = 0; i < timeout; ++i){
        FILE *cmd_output = popen(cmd, "r");
        if (!cmd_output){
            Logger::getLogger().log(LOG_ERR, "Could not start pidof command: " + errno);
        }
        fgets(line, 10, cmd_output);
        keyboard_pid = strtoul(line, NULL, 10);
        pclose(cmd_output);

        if (keyboard_pid)
            break;

        sleep(1);
    }

    if (!keyboard_pid){
        Logger::getLogger().log(LOG_ERR, "Could not find the pid of keyboard after 10 seconds! Error: " + errno);
        exit(1);
    }

    return keyboard_pid;
}

int main(int argc, char *argv[])
{
    dbusListener dt("org.gspine.gesture", "/org/gspine/gesture", getKeyboardPid());
    for(;;){
        sleep(10);
    }
    return 0;
}
