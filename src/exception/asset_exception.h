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

#ifndef CHOMP_EXCEPTION_ASSET
#define CHOMP_EXCEPTION_ASSET

#include "../sdl_includes.h"
#include "exception.h"

namespace Chomp
{

    /**
     * Exception that is thrown when asset
     * loading fails.
     */
    class AssetException : public Chomp::Exception
    {
    public:

        /**
         * Constructor.
         * _msg Exception message.
         */
        AssetException(const std::string& _msg) : Chomp::Exception(_msg) { }
        
    };
    
};

#endif