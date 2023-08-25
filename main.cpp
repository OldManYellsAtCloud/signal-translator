#include "dbusListener.h"
#include "logger.h"
#include <unistd.h>
#include <stdlib.h>

pid_t getKeyboardPid(){
    char line[10];
    FILE *cmd = popen("/bin/pidof wvkbd-mobintl", "r");
    fgets(line, 10, cmd);
    pid_t keyboard_pid = strtoul(line, NULL, 10);
    Logger::getLogger().log(LOG_INFO, "Keyboard pid: " + keyboard_pid);
    if (errno != 0) {
        Logger::getLogger().log(LOG_ERR, "Could not find the pid of keyboard! Error: " + errno);
    }
    pclose(cmd);
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
