// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/IChangeable.h
//! @brief     Defines virtual class IChangeable.
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ICHANGEABLE_H
#define ICHANGEABLE_H

//! @class IChangeable
//! @ingroup tools_internal
//! @brief The class to keep track whether object has been modified.

class BA_CORE_API_ IChangeable
{
public:
    IChangeable(bool is_changed=false) : m_is_changed(is_changed){}
    virtual ~IChangeable(){}

    bool isChanged()
    {
        bool result = m_is_changed;
        m_is_changed = false;
        return result;
    }

    void setIsChanged(bool is_changed) { m_is_changed = is_changed; }

private:
    bool m_is_changed;
};

#endif // ICHANGEABLE_H


