#include "inc/Exceptions.h"

NotImplementedException::NotImplementedException(const std::string& message)
    : std::logic_error(message)
{
}

NullPointerException::NullPointerException(const std::string& message)
    : std::logic_error(message)
{
}
