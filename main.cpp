
#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "global.h"
#include "model/Log.h"
#include "gui/GUIGame.h"

using namespace std;
using namespace game::gui;
using namespace game::model;

/**
 * SDL Entry Point
 **/
int main(int carg, char ** varg) {
    UPDATE_STD_OUTPUTS; QUEUE_UP;

    GUIGame game(WEH_NAME, WEH_WIDTH, WEH_HEIGHT);
    return game.Load().Loop().Success();
}

/**
 * Update standar outputs
 **/
void change_std_outputs() {
    freopen(WEH_STDOUT, WEH_FILE_MODE_CLEAN, stdout);
    freopen(WEH_STDERR, WEH_FILE_MODE_CLEAN, stderr);
}

/**
 * Exit from application
 **/
void weh_exit() {
    Log::Write("Ending Application");
}
