
#include "main.h"

/**
 * Default min log level
 **/
iLOGGER_MIN_LEVEL = iLEVEL_INFO;

/**
 * SDL Entry Point
 **/
int main(int argc, char ** argv) {
    game::cmd::command_line_interface(argc, argv);

    APPLICATION_LOG;
    try {
        Environment environment(WEH_FULL_ENV);
        return environment.Run().Success();
    } catch (const GuiException& ge) {
        iLogger(iERROR << iTAGS({"GuiException"}) << ge.what());
    } catch (...) {
        iLogger(iERROR << "There has been a unexpected error");
    }
    return EXIT_FAILURE;
}
