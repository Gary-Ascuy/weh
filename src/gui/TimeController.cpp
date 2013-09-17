
#include "gui/TimeController.h"

using  namespace game::gui;

TimeController::TimeController(double FPS) : TimeController ((Uint16)(1000.0 / FPS)) {
}

TimeController::TimeController(Uint16 deltaTime) {
    this -> deltaTime = deltaTime;
    now = lastTime = SDL_GetTicks();
    ticks = 0; cpu = -1;
    fps = 1000.0 / deltaTime;
}

TimeController& TimeController::Wait() {
    ticks++;

    lastTime = now;
    now = SDL_GetTicks();
    Uint32 consumedTime = now - lastTime;
    CPU(consumedTime);
    if (deltaTime > consumedTime)
        SDL_Delay(deltaTime - consumedTime);
    now = SDL_GetTicks();
    return *this;
}

void TimeController::CPU(Uint32 consumedTime) {
    if (cpu >= 0) {
        cpu = cpu * 0.5 + ((consumedTime + 0.0) / deltaTime) * 0.5;
    } else cpu = (consumedTime + 0.0) / deltaTime;
    LogCPUStatus(consumedTime);
}

void TimeController::LogCPUStatus(Uint32 consumedTime) {
    iIF(iLEVEL_FINEST) iLogger(iFINEST << iTAGS({"frame"}) << " -CPU:" << (cpu * 100) << "% -TIME:" << consumedTime << "/" << deltaTime << " -FPS:" << fps);
}
