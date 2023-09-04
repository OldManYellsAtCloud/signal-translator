#include "dbusListener.h"
#include "logger.h"
#include <signal.h>

void dbusListener::onTouchEvent(const std::string &direction)
{
    LOG(LOG_DEBUG, "Direction arrived: " + direction);
    if (direction == "LEFT_TO_RIGHT") {
        int res = kill(keyboard_pid_, KEYBOARD_TOGGLE_SIGNAL);
        if (res) {
            Logger::getLogger().log(LOG_ERR, "Could not send keyboard toggle signal: " + errno);
        }
    }
}
