
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
    stringstream ss;
    ss << "[" << setfill('0') << setw(15) << ticks << "]" << " Frame";
    ss << " -CPU:" <<  setiosflags(ios::fixed) << setprecision(5) << (cpu * 100) << "%";
    ss << " -TIME:" << consumedTime << "/" << deltaTime;
    ss << " -FPS:" << fps;
    Log::Write(ss.str(), WEH_LOG_FINEST);
}
