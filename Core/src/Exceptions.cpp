#include "Exceptions.h"
#include <iostream>

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
    std::cout << message << std::endl;
}

DeadReferenceException::DeadReferenceException(const std::string &message)
    : std::runtime_error(message)
{
    std::cout << message << std::endl;
}

UnknownClassRegistrationException::UnknownClassRegistrationException(const std::string &message)
    : std::runtime_error(message)
{
    std::cout << message << std::endl;
}

ExistingClassRegistrationException::ExistingClassRegistrationException(const std::string &message)
    : std::runtime_error(message)
{
    std::cout << message << std::endl;
}


LogicErrorException::LogicErrorException(const std::string &message)
    : std::logic_error(message)
{
    std::cout << message << std::endl;
}
