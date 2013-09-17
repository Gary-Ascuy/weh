
#ifndef GUI__TIMECONTROLLER_H_INCLUDED
#define GUI__TIMECONTROLLER_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#include <sstream>
#include <iomanip>

#include "global.h"

#include "ilog/Logger.h"

namespace game { namespace gui {

    class TimeController {
    public:
        TimeController(double FPS);
        TimeController(Uint16 deltaTime);
        TimeController& Wait();

    private:
        void CPU(Uint32 consumedTime);
        void LogCPUStatus(Uint32 consumedTime);

        Uint16 deltaTime;
        Uint64 ticks;

        Uint32 now;
        Uint32 lastTime;

        double cpu;
        double fps;
    };
}}

#endif // GUI__TIMECONTROLLER_H_INCLUDED
