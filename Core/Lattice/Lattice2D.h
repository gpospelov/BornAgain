// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Lattice/Lattice2D.h
//! @brief     Defines classes of Lattice2D family.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef LATTICE2D_H
#define LATTICE2D_H

#include "ICloneable.h"
#include "INode.h"

class BA_CORE_API_ Lattice2D : public ICloneable, public INode
{
public:
    explicit Lattice2D(double rotation_angle = 0.0);
    Lattice2D* clone() const = 0;

    struct ReciprocalBases {
        double m_asx, m_asy; //!< x,y coordinates of a*
        double m_bsx, m_bsy; //!< x,y coordinates of b*
    };

    virtual double length1() const=0;
    virtual double length2() const=0;
    virtual double latticeAngle() const=0;
    virtual double unitCellArea() const=0;

    double rotationAngle() const { return m_xi; }

    ReciprocalBases reciprocalBases() const;

    void setRotationEnabled(bool enabled);

protected:
    virtual void onChange();
    Lattice2D(const Lattice2D& other);
    double m_xi;
};

class BA_CORE_API_ BasicLattice : public Lattice2D
{
public:
    BasicLattice(double length1, double length2, double angle, double rotation_angle = 0.0);
    BasicLattice* clone() const;
    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    virtual double length1() const { return m_length1; }
    virtual double length2() const { return m_length2; }
    virtual double latticeAngle() const { return m_angle; }
    virtual double unitCellArea() const;

private:
    BasicLattice(const BasicLattice& other);
    void init_parameters();

    double m_length1, m_length2;
    double m_angle;
};

class BA_CORE_API_ SquareLattice : public Lattice2D
{
public:
    explicit SquareLattice(double length, double rotation_angle = 0.0);
    SquareLattice* clone() const;
    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    virtual double length1() const { return m_length; }
    virtual double length2() const { return m_length; }
    virtual double latticeAngle() const;
    virtual double unitCellArea() const;

private:
    SquareLattice(const SquareLattice& other);
    void init_parameters();

    double m_length;
};

class BA_CORE_API_ HexagonalLattice : public Lattice2D
{
public:
    explicit HexagonalLattice(double length, double rotation_angle = 0.0);
    HexagonalLattice* clone() const;
    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    virtual double length1() const { return m_length; }
    virtual double length2() const { return m_length; }
    virtual double latticeAngle() const;
    virtual double unitCellArea() const;

private:
    HexagonalLattice(const HexagonalLattice& other);
    void init_parameters();

    double m_length;
};

#endif // LATTICE2D_H
