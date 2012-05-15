#include "Exceptions.h"
#include <iostream>

void LogExceptionMessage(const std::string &message)
{
    std::cout << message << std::endl;
}

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

UnknownClassRegistrationException::UnknownClassRegistrationException(const std::string &message)
    : std::runtime_error(message)
{
    LogExceptionMessage(message);
}

ExistingClassRegistrationException::ExistingClassRegistrationException(const std::string &message)
    : std::runtime_error(message)
{
    LogExceptionMessage(message);
}


LogicErrorException::LogicErrorException(const std::string &message)
    : std::logic_error(message)
{
    LogExceptionMessage(message);
}

DivisionByZeroException::DivisionByZeroException(const std::string &message)
    : std::runtime_error(message)
{
    LogExceptionMessage(message);
}
