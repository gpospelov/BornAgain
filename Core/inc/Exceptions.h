#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   Exceptions.h
//! @brief  Definition of Exceptions
//! @author Scientific Computing Group at FRM II
//! @date   01.05.2012

#include <stdexcept>
#include <string>


class NotImplementedException : public std::logic_error
{
public:
    NotImplementedException(const std::string &message);
};

class NullPointerException : public std::logic_error
{
public:
    NullPointerException(const std::string& message);
};

class OutOfBoundsException : public std::logic_error
{
public:
    OutOfBoundsException(const std::string& message);
};

class ClassInitializationException : public std::runtime_error
{
public:
    ClassInitializationException(const std::string& message);
};

class SelfReferenceException : public std::logic_error
{
public:
    SelfReferenceException(const std::string &message);
};

class DeadReferenceException : public std::runtime_error
{
public:
    DeadReferenceException(const std::string& message);
};

#endif // EXCEPTIONS_H
