
#ifndef MODEL__LOG_H_INCLUDED
#define MODEL__LOG_H_INCLUDED

#include <iostream>
#include <sstream>
#include <ctime>

using namespace std;

namespace game { namespace model {

    enum LogLevel { WEH_LOG_ERROR = 0, WEH_LOG_WARNING = 1, WEH_LOG_INFO = 2, WEH_LOG_FINE = 3, WEH_LOG_FINEST = 4 };

    class Log {
    public:
        static void Write(ostream& out, const string& message, LogLevel level = WEH_LOG_INFO);
        static void Write(const string& message, LogLevel level = WEH_LOG_INFO);
        static void WriteErr(const string& message, const string& cause, LogLevel level = WEH_LOG_ERROR);

        static LogLevel MinLevel;
    };

}}

#endif // MODEL__LOG_H_INCLUDED
