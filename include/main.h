
#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include "global.h"
#include "gui/GUIGame.h"

#include "ilog/Logger.h"

#define WEH_UPDATE_STD_OUTPUTS
#define WEH_FILE_MODE "a"
#define WEH_FILE_MODE_CLEAN "wt"

#define WEH_STDOUT "output\\stdout.txt"
#define WEH_STDERR "output\\stderr.txt"

#ifdef WEH_UPDATE_STD_OUTPUTS
#define UPDATE_STD_OUTPUTS freopen(WEH_STDOUT, WEH_FILE_MODE_CLEAN, stdout); freopen(WEH_STDERR, WEH_FILE_MODE_CLEAN, stderr);
#else
#define UPDATE_STD_OUTPUTS
#endif

#define QUEUE_UP atexit([] { iLogger(iINFO << "Ending Application"); });

#endif // MAIN_H_INCLUDED
