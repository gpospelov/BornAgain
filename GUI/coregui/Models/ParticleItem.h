// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Models/ParticleItem.h
//! @brief     Defines class ParticleItem.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARTICLEITEM_H
#define PARTICLEITEM_H

#include "ParameterizedGraphicsItem.h"

class ParticleItem : public ParameterizedGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(ParameterizedItem::FormFactorEnum formfactor READ formFactor
               WRITE setFormFactor)
public:
    explicit ParticleItem(ParameterizedItem *parent=0);
    ~ParticleItem();

    ParameterizedItem::FormFactorEnum formFactor() const {
        return m_form_factor;
    }
    void setFormFactor(const ParameterizedItem::FormFactorEnum& form_factor)
    {
        m_form_factor = form_factor;
    }

private:
    ParameterizedItem::FormFactorEnum m_form_factor;
};

#endif // PARTICLEITEM_H

