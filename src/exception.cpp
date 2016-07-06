#include "exception.h"

ChompException::ChompException(std::string _message)
{
    message = _message;
}

ChompException::~ChompException()
{

}

std::string ChompException::getMessage()
{
    if (message.empty()) {
        return std::string("An unknown error has occured.");
    }
    return message;
}