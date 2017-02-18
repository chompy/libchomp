#ifndef CHOMP_EXCEPTION
#define CHOMP_EXCEPTION

#include <exception>
#include <string>

namespace Chomp
{

    /**
     * Base exception class.
     */
    class Exception : public std::exception
    {

    public:

        /**
         * Constructor.
         * @param _msg Exception message.
         */
        Exception(const std::string& _msg);

        /**
         * Destructor.
         */
        virtual ~Exception() throw();

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
};

#endif