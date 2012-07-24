#ifndef ISQUAREDFUNCTION_H_
#define ISQUAREDFUNCTION_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   ISquaredFunction.h
//! @brief  Definition of
//! @author Scientific Computing Group at FRM II
//! @date   Jul 20, 2012

class ISquaredFunction
{
public:
    virtual ~ISquaredFunction() {}
    virtual ISquaredFunction *clone() const=0;

    virtual double calculateSquaredDifference(double real_value, double simulated_value) const=0;
};

class DefaultSquaredFunction : public ISquaredFunction
{
public:
    DefaultSquaredFunction() {}
    virtual ~DefaultSquaredFunction() {}
    virtual DefaultSquaredFunction *clone() const { return new DefaultSquaredFunction(); }

    virtual double calculateSquaredDifference(double real_value, double simulated_value) const {
        return (simulated_value-real_value)*(simulated_value-real_value);
    }
};


#endif /* ISQUAREDFUNCTION_H_ */
