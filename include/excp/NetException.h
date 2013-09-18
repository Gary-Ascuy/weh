
#ifndef EXCP_NETEXCEPTION_H_INCLUDED
#define EXCP_NETEXCEPTION_H_INCLUDED

#include<string>
#include<exception>

namespace game { namespace exception {

    class NetException : std::exception {
    public:
        NetException(const std::string& cause) : cause(cause) { }
        virtual const char* what() const throw() override { return cause.c_str(); }

    private:
        std::string cause;
    };

}}

#endif // EXCP_NETEXCEPTION_H_INCLUDED
