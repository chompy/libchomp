#ifndef CHOMP_EXCEPTION
#define CHOMP_EXCEPTION

#include <SDL2/SDL.h>
#include <exception>
#include <string>

class ChompSdlInitException : public std::exception
{

public:
    ChompSdlInitException();
    ChompSdlInitException(const std::string&);
    virtual ~ChompSdlInitException() throw();
    virtual const char* what() const throw();
private:
    std::string msg;

};


#endif