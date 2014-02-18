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
    double getParameterValue(QString name);

    //! sets the parameter's value, if it exists
    void setParameter(QString name, double value);

    //! retrieves the whole list of paramaters
    QMap<QString, double> &getParameters() {
        return m_parameters;
    }

    //! indicates if the passed item can be set as
    //! a child item
    bool acceptsAsChild(ParameterizedItem *child);
protected:
    QList<QString> m_valid_parents;
    QMap<QString, double> m_parameters;
private:
    //! indicates if the item name, passed as argument
    //! can be the current item's parent
    bool isValidParent(QString parentName);
};


#endif /* PARAMETERIZEDITEM_H_ */
