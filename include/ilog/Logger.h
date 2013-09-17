
#ifndef ILOG__LOGGER_H_INCLUDED
#define ILOG__LOGGER_H_INCLUDED

#include <ctime>
#include <iostream>
#include <initializer_list>
#include <sstream>

#define iLogger game::ilog::Logger::Write
#define iTAGS std::initializer_list<std::string>

#define iIF(level) if (level <= game::ilog::Logger::MinLevel)
#define iIF_NOT(level) if (level > game::ilog::Logger::MinLevel)

#define iLOGGER_MIN_LEVEL game::ilog::Level game::ilog::Logger::MinLevel

#define iLEVEL_ERROR game::ilog::Level::Error
#define iLEVEL_WARNING game::ilog::Level::Warning
#define iLEVEL_INFO game::ilog::Level::Info
#define iLEVEL_FINE game::ilog::Level::Fine
#define iLEVEL_FINEST game::ilog::Level::Finest

#define iERROR game::ilog::Log(iLEVEL_ERROR)
#define iWARNING game::ilog::Log(iLEVEL_WARNING)
#define iINFO game::ilog::Log(iLEVEL_INFO)
#define iFINE game::ilog::Log(iLEVEL_FINE)
#define iFINEST game::ilog::Log(iLEVEL_FINEST)

namespace game { namespace ilog {

    enum class Level : int8_t { Error = 0, Warning = 1, Info = 2, Fine = 3, Finest = 4 };

    class Log {
    public:
        Log(Level level);
        Log& operator<<(std::initializer_list<std::string> codes);

        template<class T>
        Log& operator<<(T value) {
            ss << value; return *this;
        }
        void Write(std::ostream& out);
        Level GetLevel();

    private:
        Level level;
        std::stringstream ss;

    };

    class Logger {
    public:
        static void Write(Log& log);
        static void Write(std::ostream& out, Log& log, const std::string& level);

        static Level MinLevel;
    };
}}

#endif // ILOG__LOGGER_H_INCLUDED
