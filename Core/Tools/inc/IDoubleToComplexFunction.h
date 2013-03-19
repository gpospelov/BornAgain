// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @copyright Forschungszentrum Jülich GmbH 2013
//             
//  Homepage:  apps.jcns.fz-juelich.de/BornAgain
//  License:   GNU General Public License v3 or higher (see COPYING)
//
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
//! @file      Tools/IDoubleToComplexFunction.h 
//! @brief     Defines class IDoubleToComplexFunction.
//
// ************************************************************************** //

#ifndef IDOUBLETOCOMPLEXFUNCTION_H_
#define IDOUBLETOCOMPLEXFUNCTION_H_

#include "Types.h"
#include "ICloneable.h"

//! Virtual base class for double to complex interpolators.

class IDoubleToComplexFunction : public ICloneable
{
public:
	virtual ~IDoubleToComplexFunction() {}
	virtual IDoubleToComplexFunction *clone() const=0;

	virtual complex_t evaluate(double value)=0;
};

//! Virtual base class for double to complex map.

class IDoubleToComplexMap : public ICloneable
{
public:
    virtual ~IDoubleToComplexMap() {}
    virtual IDoubleToComplexMap *clone() const = 0;

    virtual const complex_t &evaluate(double value) const = 0;
};

//! Virtual base class for double to complexpair_t map.

class IDoubleToPairOfComplexMap : public ICloneable
{
public:
    virtual ~IDoubleToPairOfComplexMap() {}
    virtual IDoubleToPairOfComplexMap *clone() const = 0;

    virtual const complexpair_t &evaluate(double value) const = 0;
};

//! ?

class DoubleToComplexFunctionWrapper : public IDoubleToComplexFunction
{
public:
	typedef complex_t (*double_to_complex_t)(double);
	DoubleToComplexFunctionWrapper(double_to_complex_t function) : m_function(function) {}
	virtual DoubleToComplexFunctionWrapper *clone() const {
	    return new DoubleToComplexFunctionWrapper(m_function);
	}

	virtual complex_t evaluate(double value) { return m_function(value); }

private:
	double_to_complex_t m_function;
};

#endif /* IDOUBLETOCOMPLEXFUNCTION_H_ */
