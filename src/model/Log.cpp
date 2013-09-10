
#include "model/Log.h"

using namespace game::model;

void Log::Write(ostream& out, const string& message, LogLevel level) {
    if (level > Log::MinLevel) return;

    time_t now; time(&now);
    char buffer[80];
    struct tm * timeinfo;
    timeinfo = localtime(&now);
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);

    out << "[" << buffer << "] ";
    switch (level) {
        case WEH_LOG_ERROR: out << "ERROR"; break;
        case WEH_LOG_WARNING: out << "WARNING"; break;
        case WEH_LOG_INFO: out << "INFO"; break;
        case WEH_LOG_FINE: out << "FINE"; break;
        case WEH_LOG_FINEST: out << "FINEST"; break;
        default: out << "UNKNOWN";
    }
    out << " > " << message << endl;
}

void Log::Write(const string& message, LogLevel level) {
    switch (level) {
        case WEH_LOG_ERROR:
        case WEH_LOG_WARNING:
            Write(cerr, message, level);
            break;
        default:
            Write(cout, message, level);
    }
}

void Log::WriteErr(const string& message, const string& cause, LogLevel level) {
    Write(message + " - By: " + cause, level);
}
