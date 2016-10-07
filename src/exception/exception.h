#ifndef CHOMP_EXCEPTION
#define CHOMP_EXCEPTION

#include <exception>
#include <string>

class ChompException : public std::exception
{

public:
    ChompException(const std::string& _msg);
    virtual ~ChompException() throw();
    virtual const char* what() const throw();
private:
    std::string msg;

};

#endif