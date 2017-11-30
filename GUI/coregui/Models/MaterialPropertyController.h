// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/MaterialPropertyController.h
//! @brief     Defines MaterialPropertyController class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef MATERIALPROPERTYCONTROLLER_H
#define MATERIALPROPERTYCONTROLLER_H

#include "WinDllMacros.h"
#include <QObject>

class MaterialModel;
class SampleModel;
class SessionItem;

//! Listens MaterialModel for changes in MaterialItems and then
//! updates MaterialProperties in all related items in SampleModel.

class BA_CORE_API_ MaterialPropertyController : public QObject
{
    Q_OBJECT
public:
    MaterialPropertyController(QObject* parent = nullptr);

    void setModels(MaterialModel* materialModel, SampleModel* sampleModel);

private slots:
    void onMaterialDataChanged(const QModelIndex &topLeft, const QModelIndex &, const QVector<int> &);
    void onMaterialRowsAboutToBeRemoved(const QModelIndex &parent, int first, int last);
    void onMaterialModelLoad();

private:
    QVector<SessionItem*> relatedSampleItems();

    MaterialModel* m_materialModel;
    SampleModel* m_sampleModel;
};

#endif
