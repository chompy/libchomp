#ifndef CHOMP_EXCEPTION_H
#define CHOMP_EXCEPTION_H

#include <string>

class ChompException
{
public:
    
    ChompException(std::string _message);
    ~ChompException();

    std::string getMessage();

protected:

    std::string message;

};

#endif