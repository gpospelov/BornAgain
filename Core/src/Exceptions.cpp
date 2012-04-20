#include "Exceptions.h"

NotImplementedException::NotImplementedException(const std::string &message)
    : std::logic_error(message)
{
}

NullPointerException::NullPointerException(const std::string& message)
    : std::logic_error(message)
{
}

OutOfBoundsException::OutOfBoundsException(const std::string& message)
    : std::logic_error(message)
{
}

ClassInitializationException::ClassInitializationException(const std::string &message)
    : std::runtime_error(message)
{
}

SelfReferenceException::SelfReferenceException(const std::string& message)
    : std::logic_error(message)
{
}

DeadReferenceException::DeadReferenceException(const std::string &message)
    : std::runtime_error(message)
{
}
