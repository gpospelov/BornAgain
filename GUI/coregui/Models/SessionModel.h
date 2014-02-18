// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Models/SessionModel.h
//! @brief     Defines class SessionModel.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SESSIONMODEL_H
#define SESSIONMODEL_H

#include <QStandardItemModel>
#include "ParameterizedItem.h"

class SessionModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit SessionModel(QObject *parent=0);
    ~SessionModel();

    QString filename() const { return m_filename; }
    void setFilename(const QString &filename) {
        m_filename = filename;
    }
    QStandardItem *insertNewItem(QString model_type,
                                 const QModelIndex &index);

//    void load(const QString &filename=QString());
//    void save(const QString &filename=QString());

private:
    void initialize();
    QStandardItem *createNewItem(QStandardItem *parent,
                                 QString model_type);
    QString m_filename;
};

#endif // SESSIONMODEL_H
