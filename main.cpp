
#include <stdio.h>
#include <stdlib.h>

#include "main.h"

/**
 * Log level
 **/
iLOGGER_MIN_LEVEL = iLEVEL_INFO;

/**
 * SDL Entry Point
 **/
int main(int carg, char ** varg) {
    UPDATE_STD_OUTPUTS; QUEUE_UP;

    game::gui::GUIGame game(WEH_NAME, WEH_WIDTH, WEH_HEIGHT);
    return game.Load().Loop().Success();
}
