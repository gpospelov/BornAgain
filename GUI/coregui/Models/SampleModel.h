// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/SampleModel.h
//! @brief     Defines class SampleModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
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

    virtual SampleModel *createCopy(ParameterizedItem *parent = 0);

    QMap<QString, ParameterizedItem *> getSampleMap() const;

    MultiLayerItem *getMultiLayerItem(const QString &item_name=QString());

public slots:
    void onMaterialModelChanged(const QModelIndex &first, const QModelIndex &second);

private:
    void exploreForMaterials(const QModelIndex &parentIndex = QModelIndex());
    QString m_material_identifier;
};

#endif
