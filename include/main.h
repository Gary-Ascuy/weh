
#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <cstdio>
#include <cstdlib>
#include <cstring>

/**
 * Local includes
 */
#include "gui/GUIGame.h"
#include "gui/Environment.h"
#include "ilog/Logger.h"
#include "excp/GuiException.h"
#include "net/TCPServer.h"
#include "net/Socket.h"

#include "optionparser.h"

/**
 * Output definitions
 */
#define WEH_FILE_MODE "a"
#define WEH_FILE_MODE_CLEAN "wt"
#define WEH_STDOUT "output/stdout.txt"
#define WEH_STDERR "output/stderr.txt"
#define UPDATE_STD_OUTPUTS freopen(WEH_STDOUT, WEH_FILE_MODE_CLEAN, stdout); freopen(WEH_STDERR, WEH_FILE_MODE_CLEAN, stderr);

#define APPLICATION_LOG iLogger(iINFO << "Starting Application"); atexit([] { iLogger(iINFO << "Ending Application"); });

/**
 * Command line interface
 */
namespace game { namespace cmd {
    enum Command {
        iCMD_Unknown,
        iCMD_Help,

        iCMD_Logger,
        iCMD_LogLevel,

        iCMD_Width,
        iCMD_Height,
        iCMD_FullScreen,

        iCMD_ServerMode,
        iCMD_ClientMode,

        iCMD_Host,
        iCMD_Port
    };

    struct Arg: public option::Arg {

        static void printError(const char* msg1, const option::Option& opt, const char* msg2) {
            fprintf(stderr, "%s", msg1);
            fwrite(opt.name, opt.namelen, 1, stderr);
            fprintf(stderr, "%s", msg2);
        }

        static option::ArgStatus Numeric(const option::Option& option, bool msg) {
            char* endptr = 0;
            if (option.arg != 0 && strtol(option.arg, &endptr, 10)){};
            if (endptr != option.arg && *endptr == 0) return option::ARG_OK;
            if (msg) printError("Option '", option, "' requires a numeric argument.\n\n");
            return option::ARG_ILLEGAL;
        }

    };

    const option::Descriptor usage[] = {
        {iCMD_Unknown,     0,   "",           "",    option::Arg::None, "USAGE: weh [options]\n\nOptions:" },
        {iCMD_Help,        0,  "?",       "help",    option::Arg::None, "  --help       \t\tPrint usage and exit.\n" },

        {iCMD_Logger,      0,  "o",     "logger",    option::Arg::None, "  --logger     \t\tLogger write the logs in console." },
        {iCMD_LogLevel,    0,  "l",     "level",          Arg::Numeric, "  --level      \t\tDefine min level logs e.g. Error=0 to Finest=4\n" },

        {iCMD_Width,       0, "sw",      "width",         Arg::Numeric, "  --width      \t\tWidth size of screen in pixels." },
        {iCMD_Height,      0, "sh",     "height",         Arg::Numeric, "  --height     \t\tHeight size of screen in pixels." },
        {iCMD_FullScreen,  0,  "f", "fullscreen",    option::Arg::None, "  --fullscreen \t\tEnable fullscreen." },

        {iCMD_ServerMode,  0,  "s",     "server",    option::Arg::None, "  --server     \t\tStart the game in server mode." },
        {iCMD_ClientMode,  0,  "c",     "client",    option::Arg::None, "  --client     \t\tStart the game in client mode." },
        {iCMD_Host,        0,  "h",     "host",      option::Arg::None, "  --host       \t\tDefine host or IP address to multiplayer." },
        {iCMD_Port,        0,  "p",     "port",           Arg::Numeric, "  --port       \t\tDefine the port to multiplayer" },

        {iCMD_Unknown,     0,   "",           "",    option::Arg::None, "\nExamples:\n  weh -w1024 -h768 --fullscreen" },

        {0,0,0,0,0,0}
    };

    uint16_t screen_size(long value, uint16_t min, uint16_t max) {
        if (value > max) return max;
        if (value <= min) return min;
        return value;
    }

    uint16_t ipv4_port(long value, uint16_t default_value) {
        if (value >= 1024 && value < 65535) return value;
        return default_value;
    }

    void command_line_interface(int length, char ** values, game::gui::Settings& settings) {
        //UPDATE_STD_OUTPUTS;
        length-=(length>0); values+=(length>0);

        option::Stats stats(game::cmd::usage, length, values);
        option::Option options[stats.options_max], buffer[stats.buffer_max];
        option::Parser parse(game::cmd::usage, length, values, options, buffer);

        if (parse.error()) {
            option::printUsage(std::cout, game::cmd::usage);
            exit(EXIT_FAILURE);
        }

        /// help
        if (options[iCMD_Help] || length == 0) {
            option::printUsage(std::cout, game::cmd::usage);
            if (options[iCMD_Help]) exit(0);
        }

        /// logger and level
        if (!options[iCMD_Logger]) {
            UPDATE_STD_OUTPUTS;
        }

        if (options[iCMD_LogLevel]) {
            game::ilog::Logger::MinLevel = (game::ilog::Level) atol(options[iCMD_LogLevel].arg);
        }

        /// Settings
        if (options[iCMD_FullScreen]) settings.fullscreen = true;
        if (options[iCMD_Width]) settings.width = screen_size(atol(options[iCMD_Width].arg), 320, 1920);
        if (options[iCMD_Height]) settings.height = screen_size(atol(options[iCMD_Height].arg), 240, 1080);

        if (options[iCMD_ServerMode]) settings.server = true;
        if (options[iCMD_ClientMode]) settings.client = true;

        if (options[iCMD_Host]) {
            //settings.host = options[iCMD_Host].arg;

            const char * ip = parse.nonOption(0);
            int len = strlen(ip);
            settings.host = (char*) malloc(sizeof(char) * (len + 1));
            strcpy(settings.host, ip);
        }
        if (options[iCMD_Port]) settings.port = ipv4_port(atol(options[iCMD_Port].arg), settings.port);
    }
}}

/**
 * Using namespaces
 */
using namespace game::gui;
using namespace game::excp;

#endif // MAIN_H_INCLUDED
