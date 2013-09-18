
#ifndef EXCP__GUIEXCEPTION_H_INCLUDED
#define EXCP__GUIEXCEPTION_H_INCLUDED

#include<string>
#include<exception>

namespace game { namespace excp {

    class GuiException : std::exception {
    public:
        GuiException(const std::string& cause) : cause(cause) { }
        virtual const char* what() const throw() override { return cause.c_str(); }

    private:
        std::string cause;
    };

}}

#endif // EXCP__GUIEXCEPTION_H_INCLUDED
