#include "dbusListener.h"
#include "loglibrary.h"
#include <signal.h>

#define KEYBOARD_DIRECTION "RIGHT_TO_LEFT"

void dbusListener::onTouchEvent(const std::string &direction)
{
    DEBUG("Direction arrived: {}", direction);
    if (direction == KEYBOARD_DIRECTION) {
        int res = kill(keyboard_pid_, KEYBOARD_TOGGLE_SIGNAL);
        if (res) {
            ERROR("Could not send keyboard toggle signal: {}", errno);
        }
    }
}
