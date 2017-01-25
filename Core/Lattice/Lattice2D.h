// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Lattice/Lattice2DParameters.h
//! @brief     Defines class Lattice2DParameters.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef LATTICE2DPARAMETERS_H
#define LATTICE2DPARAMETERS_H

#include "ICloneable.h"
#include "INode.h"

class Lattice2D : public ICloneable, public INode
{
public:
    Lattice2D(double length1, double length2, double angle, double rotation_angle = 0.0);
    Lattice2D* clone() const = 0;

    struct ReciprocalBases {
        double m_asx, m_asy; //!< x,y coordinates of a*
        double m_bsx, m_bsy; //!< x,y coordinates of b*
    };

    double length1() const { return m_length1; }
    virtual double length2() const { return m_length2; }
    double latticeAngle() const { return m_angle; }
    double rotationAngle() const { return m_xi; }

    double unitCellArea() const;

    ReciprocalBases reciprocalBases() const;

protected:
    virtual void onChange();
    Lattice2D(const Lattice2D& other);
    double m_length1, m_length2;
    double m_angle;
    double m_xi;
};

class BasicLattice : public Lattice2D
{
public:
    BasicLattice(double length1, double length2, double angle, double rotation_angle = 0.0);
    BasicLattice* clone() const;
    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

private:
    BasicLattice(const BasicLattice& other);
    void init_parameters();
};

class SquareLattice : public Lattice2D
{
public:
    SquareLattice(double length, double rotation_angle = 0.0);
    SquareLattice* clone() const;
    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }
    double length2() const { return m_length1; } // m_length2 is not used

private:
    SquareLattice(const SquareLattice& other);
    void init_parameters();
};

class HexagonalLattice : public Lattice2D
{
public:
    HexagonalLattice(double length, double rotation_angle = 0.0);
    HexagonalLattice* clone() const;
    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }
    double length2() const { return m_length1; } // m_length2 is not used

private:
    HexagonalLattice(const HexagonalLattice& other);
    void init_parameters();
};

#endif // LATTICE2DPARAMETERS_H
