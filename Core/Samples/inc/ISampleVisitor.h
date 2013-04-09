// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/ISampleVisitor.h
//! @brief     Defines interface class ISampleVisitor.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISAMPLEVISITOR_H
#define ISAMPLEVISITOR_H

class ISample;

//! Interface to visit a sample tree and perform operations on its nodes

class ISampleVisitor
{
public:
    //! Destructor
    virtual ~ISampleVisitor() {}

    //! Performs specific action on the given sample
    //! Needs to be overloaded for different ISample types
    virtual void visit(ISample *sample);
};


#endif // ISAMPLEVISITOR_H
