#include "exception.h"

ChompSdlInitException::ChompSdlInitException():exception() 
{
    msg = SDL_GetError();
}

ChompSdlInitException::ChompSdlInitException(const std::string& _msg):exception() 
{
    msg = _msg;
}

ChompSdlInitException::~ChompSdlInitException() throw()
{

}

const char* ChompSdlInitException::what() const throw()
{
    return msg.c_str();
}