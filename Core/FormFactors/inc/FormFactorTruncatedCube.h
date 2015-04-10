#ifndef FORMFACTORTRUNCATEDCUBE_H
#define FORMFACTORTRUNCATEDCUBE_H

#include "IFormFactorBorn.h"

//! @class FormFactorTruncatedCube
//! @ingroup formfactors
//! @brief The formfactor of a truncated cube.

class BA_CORE_API_ FormFactorTruncatedCube : public IFormFactorBorn
{
public:
    //! @brief Truncated cube constructor
    //! @param side length of the full cube
    //! @param side length of the trirectangular tetrahedron removed from each vertex of the cube
    FormFactorTruncatedCube(double length, double removed_length);
    ~FormFactorTruncatedCube() {}
    virtual FormFactorTruncatedCube *clone() const;

    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    virtual int getNumberOfStochasticParameters() const { return 2; }

    virtual double getLength() const { return m_length; }
    virtual void setLength(double length) { m_length = length; }

    virtual double getRemovedLength() const { return m_removed_length; }
    virtual void setRemovedLength(double removed_length) { m_removed_length = removed_length; }

    virtual complex_t evaluate_for_q(const cvector_t& q) const;

protected:
    virtual void init_parameters();

private:
    complex_t FormFactorVertex(const cvector_t& q) const;

    double m_length;
    double m_removed_length;
};


#endif // FORMFACTORTRUNCATEDCUBE_H
