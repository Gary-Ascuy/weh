
#include "ilog/Logger.h"

using namespace game::ilog;

Log::Log(Level level) {
    this -> level = level;
}

Log& Log::operator<<(std::initializer_list<std::string> codes) {
    for (auto& code : codes)
        *this << "[" << code << "]";
    *this << " ";
    return *this;
}

void Log::Write(std::ostream& out) {
    out << ss.str();
}

Level Log::GetLevel() {
    return level;
}

void Logger::Write(Log& log) {
    iIF_NOT(log.GetLevel()) return;

    switch (log.GetLevel()) {
        case Level::Error: Write(std::cerr, log, "ERROR"); break;
        case Level::Warning: Write(std::cerr, log, "WARNING"); break;
        case Level::Info: Write(std::cout, log, "INFO"); break;
        case Level::Fine: Write(std::cout, log, "FINE"); break;
        case Level::Finest: Write(std::cout, log, "FINEST"); break;
        default: Write(std::cerr, log, "UNKNOWN");
    }
}

void Logger::Write(std::ostream& out, Log& log, const std::string& level) {
    time_t now; time(&now);
    char buffer[80];
    struct tm * timeinfo;
    timeinfo = localtime(&now);
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
    out << "[" << buffer << "] " << level << " > ";
    log.Write(out);
    out << std::endl;
}
