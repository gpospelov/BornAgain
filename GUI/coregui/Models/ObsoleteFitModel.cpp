// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ObsoleteFitModel.cpp
//! @brief     Implements class ObsoleteFitModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ObsoleteFitModel.h"
#include "SampleModel.h"
#include "InstrumentModel.h"
#include "ObsoleteFitParameterItems.h"
#include "SessionItem.h"
#include "SessionModel.h"
#include "ComboProperty.h"
#include <QStringList>


ObsoleteFitModel::ObsoleteFitModel(SampleModel *samples, InstrumentModel *instruments, QObject *parent)
    : SessionModel(SessionXML::FitModelTag, parent)
    , m_sampleModel(samples)
    , m_instrumentModel(instruments)
{

}

ObsoleteFitParameterContainer *ObsoleteFitModel::getFitParameterContainer() {
    return dynamic_cast<ObsoleteFitParameterContainer *>
            (itemForIndex(QModelIndex())->getChildOfType(Constants::ObsoleteFitParameterContainerType));
}

ObsoleteFitSelectionItem *ObsoleteFitModel::getFitSelection() {
    return dynamic_cast<ObsoleteFitSelectionItem *>
            (itemForIndex(QModelIndex())->getChildOfType(Constants::ObsoleteFitSelectionType));
}

ObsoleteInputDataItem *ObsoleteFitModel::getInputData() {
    return dynamic_cast<ObsoleteInputDataItem *>
            (itemForIndex(QModelIndex())->getChildOfType(Constants::ObsoleteInputDataType));
}

QString ObsoleteFitModel::getSelectedSampleName () {
    return getFitSelection()->getItemValue(ObsoleteFitSelectionItem::P_SAMPLE).toString();
}

QString ObsoleteFitModel::getSelectedInstrumentName(){
    return getFitSelection()->getItemValue(ObsoleteFitSelectionItem::P_INSTRUMENT).toString();
}

QStringList ObsoleteFitModel::getSampleNames() {
    return retrieveDisplayNames(m_sampleModel, Constants::MultiLayerType);
}

QStringList ObsoleteFitModel::getInstrumentNames() {
    return retrieveDisplayNames(m_instrumentModel, Constants::InstrumentType);
}

QStringList ObsoleteFitModel::retrieveDisplayNames(SessionModel *model, const QString &type) {
    QStringList list;
    for (int i_row = 0; i_row < model->rowCount(QModelIndex()); ++i_row) {
        QModelIndex itemIndex = model->index(i_row, 0, QModelIndex());
        if (SessionItem *item = model->itemForIndex(itemIndex)) {
            if (item->modelType()  == type) {
                list << item->displayName();
            }
        }
    }
    return list;
}

QString ObsoleteFitModel::getSampleItemNameForDisplayName(const QString &displayName) {
    if (auto *item = m_sampleModel->itemForIndex(QModelIndex())->getChildByName(displayName)) {
        return item->itemName();
    }
    return "";
}

QString ObsoleteFitModel::getInstrumentItemNameForDisplayName(const QString &displayName) {
    if (auto *item = m_instrumentModel->itemForIndex(QModelIndex())->getChildByName(displayName)) {
        return item->itemName();
    }
    return "";
}

SessionItem *ObsoleteFitModel::getSelectedMultiLayerItem() {
    SessionItem *samplesRoot = m_sampleModel->itemForIndex(QModelIndex());
    return samplesRoot->getChildByName(getSelectedSampleName());
}

SessionItem *ObsoleteFitModel::getSelectedInstrumentItem() {
    SessionItem *instrumentRoot = m_instrumentModel->itemForIndex(QModelIndex());
    return instrumentRoot->getChildByName(getSelectedInstrumentName());
}

void ObsoleteFitModel::setSelectedSample(const QString &displayName) {
    SessionItem *selection = getFitSelection();
    selection->setItemValue(ObsoleteFitSelectionItem::P_SAMPLE, displayName);
}

void ObsoleteFitModel::setSelectedInstrument(const QString &displayName) {
    SessionItem *selection = getFitSelection();
    selection->setItemValue(ObsoleteFitSelectionItem::P_INSTRUMENT, displayName);
}

ObsoleteMinimizerSettingsItem *ObsoleteFitModel::getMinimizerSettings() {
    return dynamic_cast<ObsoleteMinimizerSettingsItem *>
            (itemForIndex(QModelIndex())->getChildOfType(Constants::ObsoleteMinimizerSettingsType));
}

QString ObsoleteFitModel::getMinimizerAlgorithm() {
    if (auto *item = getMinimizerSettings()) {
        return item->getItemValue(ObsoleteMinimizerSettingsItem::P_ALGO).value<ComboProperty>()
                .getValue();
    }
    return QString();
}

QString ObsoleteFitModel::getInputDataPath() {
    if (auto *item = getInputData()) {
        return item->getItemValue(ObsoleteInputDataItem::P_PATH).toString();
    }
    return "";
}

void ObsoleteFitModel::setInputDataPath(const QString &path) {
    if (auto *item = getInputData()) {
        item->setItemValue(ObsoleteInputDataItem::P_PATH, path);
    }
}

void ObsoleteFitModel::dataChangedProxy(const QModelIndex & topLeft, const QModelIndex & bottomRight,
                           const QVector<int> & roles)
{
    emit dataChanged(topLeft, bottomRight, roles);
}
