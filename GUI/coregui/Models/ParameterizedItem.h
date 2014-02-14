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
#include <QMap>

namespace BA_MODEL_ID {
enum Model_ID {
    MultiLayer,
    Layer,
};
}

class ParameterizedItem : public QStandardItem
{
public:
    explicit ParameterizedItem(BA_MODEL_ID::Model_ID model_type, const QString &name);
    ~ParameterizedItem();

    void setParameter(QString name, double value);
    QMap<QString, double> &getParameters() {
        return m_parameters;
    }
private:
    void populateWithParameters();
    BA_MODEL_ID::Model_ID m_model_type;
    QMap<QString, double> m_parameters;
};


#endif /* PARAMETERIZEDITEM_H_ */
