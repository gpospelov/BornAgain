// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SampleModel.h
//! @brief     Declares class SampleModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef SAMPLEMODEL_H
#define SAMPLEMODEL_H

#include "SessionModel.h"
#include "MaterialProperty.h"
#include <QStringList>

class MultiLayerItem;
class BA_CORE_API_ SampleModel : public SessionModel
{
    Q_OBJECT

public:
    explicit SampleModel(QObject *parent = 0);
    virtual ~SampleModel(){}

    virtual SampleModel *createCopy(SessionItem *parent = 0);

    MultiLayerItem *multiLayerItem(const QString &item_name=QString());

public slots:
    void onMaterialModelChanged(const QModelIndex &first, const QModelIndex &second);

private:
    void exploreForMaterials(const QModelIndex &parentIndex = QModelIndex());
    QString m_material_identifier;
};

#endif
