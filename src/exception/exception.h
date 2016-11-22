#ifndef CHOMP_EXCEPTION
#define CHOMP_EXCEPTION

#include <exception>
#include <string>

/**
 * Base exception class.
 */
class ChompException : public std::exception
{

public:

    /**
     * Constructor.
     * @param _msg Exception message.
     */
    ChompException(const std::string& _msg);

    /**
     * Destructor.
     */
    virtual ~ChompException() throw();

    /**
     * Return exception message.
     * @return Char array with message
     */
    virtual const char* what() const throw();
    
private:

    /**
     * String containing exception message.
     */
    std::string msg;

};

#endif