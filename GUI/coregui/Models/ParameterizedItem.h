// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      ParameterizedItem.h
//! @brief     Defines class ParameterizedItem.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARAMETERIZEDITEM_H_
#define PARAMETERIZEDITEM_H_

#include <QStandardItem>
#include <QList>
#include <QMap>

class ParameterizedItem : public QStandardItem
{
public:
    explicit ParameterizedItem(const QString &name);
    ~ParameterizedItem();

    //! retrieves the parameter's value
    double getParameterValue(const QString &name) const;

    //! sets the parameter's value, if it exists
    void setParameter(const QString &name, double value);

    //! retrieves the whole list of paramaters
    QMap<QString, double> &getParameters() {
        return m_parameters;
    }

    //! indicates if the passed item can be set as
    //! a child item
    bool acceptsAsChild(const QString &child_name) const;

    //! get list of acceptable child object names
    QList<QString> getAcceptableChildren() const {
        return m_valid_children;
    }
protected:
    QList<QString> m_valid_children;
    QMap<QString, double> m_parameters;
private:
};


#endif /* PARAMETERIZEDITEM_H_ */
