#include "exception.h"

ChompException::ChompException(const std::string& _msg):exception() 
{
    msg = _msg;
    if (_msg.empty()) {
        msg = "An unknown error occured.";
    }
}

ChompException::~ChompException() throw()
{

}

const char* ChompException::what() const throw()
{
    return msg.c_str();
}