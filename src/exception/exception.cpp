#include "exception.h"

Chomp::Exception::Exception(const std::string& _msg):exception() 
{
    msg = _msg;
    if (_msg.empty()) {
        msg = "An unknown error occured.";
    }
}

Chomp::Exception::~Exception() throw()
{

}

const char* Chomp::Exception::what() const throw()
{
    return msg.c_str();
}