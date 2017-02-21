/**
    This file is part of Libchomp.

    Libchomp is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Libchomp is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Libchomp.  If not, see <http://www.gnu.org/licenses/>.
**/

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