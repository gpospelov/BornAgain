// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Models/GUIObjectBuilder.h
//! @brief     Defines class GUIObjectBuilder.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef GUIOBJECTBUILDER_H
#define GUIOBJECTBUILDER_H

#include "ISampleVisitor.h"
#include "Samples.h"
#include <QMap>

class SessionModel;
class ParameterizedItem;

class GUIObjectBuilder : public ISampleVisitor
{
public:
    GUIObjectBuilder();
    ~GUIObjectBuilder(){}

    void populateModel(SessionModel *model, ISample *sample);

    using ISampleVisitor::visit;

    virtual void visit(const ParticleLayout *);

    virtual void visit(const Layer *);

    virtual void visit(const MultiLayer *);

private:
    SessionModel *m_sessionModel;

    //ParameterizedItem *m_parentItem;
    QMap<int, ParameterizedItem *> m_levelToParent;
};

#endif // GUIOBJECTBUILDER_H
