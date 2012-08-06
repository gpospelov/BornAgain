#include "Exceptions.h"
#include <iostream>

namespace Exceptions {

void LogExceptionMessage(const std::string &message)
{
    std::cout << message << std::endl;
}

NotImplementedException::NotImplementedException(const std::string &message)
    : std::logic_error(message)
{
     LogExceptionMessage(message);
}

NullPointerException::NullPointerException(const std::string& message)
    : std::logic_error(message)
{
     LogExceptionMessage(message);
}

OutOfBoundsException::OutOfBoundsException(const std::string& message)
    : std::logic_error(message)
{
     LogExceptionMessage(message);
}

ClassInitializationException::ClassInitializationException(const std::string &message)
    : std::runtime_error(message)
{
     LogExceptionMessage(message);
}

SelfReferenceException::SelfReferenceException(const std::string& message)
    : std::logic_error(message)
{
     LogExceptionMessage(message);
}

DeadReferenceException::DeadReferenceException(const std::string &message)
    : std::runtime_error(message)
{
     LogExceptionMessage(message);
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

RuntimeErrorException::RuntimeErrorException(const std::string &message)
    : std::runtime_error(message)
{
    LogExceptionMessage(message);
}

DivisionByZeroException::DivisionByZeroException(const std::string &message)
    : std::runtime_error(message)
{
    LogExceptionMessage(message);
}

DomainErrorException::DomainErrorException(const std::string &message)
    : std::domain_error(message)
{
    LogExceptionMessage(message);
}

FileNotIsOpenException::FileNotIsOpenException(const std::string &message)
    : std::runtime_error(message)
{
    LogExceptionMessage(message);
}

}

