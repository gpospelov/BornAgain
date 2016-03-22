// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/NJobModel.h
//! @brief     Defines class NJobModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //
#ifndef FITMODEL_H
#define FITMODEL_H

#include "SessionModel.h"
#include <QVector>

class QModelIndex;
class SampleModel;
class InstrumentModel;
class FitParameterContainer;
class FitSelectionItem;
class SessionModel;
class MinimizerSettingsItem;
class InputDataItem;


class BA_CORE_API_ FitModel : public SessionModel
{
    Q_OBJECT

public:
    //! constructs model with pointers to Sample- und InstrumentModels (read-only access)
    explicit FitModel(SampleModel *samples, InstrumentModel *instruments, QObject *parent = 0);

    //! returns child of type FitParameterContainer
    FitParameterContainer *getFitParameterContainer();

    //! returns child fo type FitSelectionItem
    FitSelectionItem *getFitSelection();

    InputDataItem *getInputData();

    //! returns displayName of currently selected sample, "" when nothing selected
    QString getSelectedSampleName();

    //! returns displayName of currently selected instrument
    QString getSelectedInstrumentName();

    //! returns a list of all sample displaynames
    QStringList getSampleNames();

    //! returns a list of all instrument displaynames
    QStringList getInstrumentNames();

    //! returning selected MultiLayerItem from SampleModel
    SessionItem *getSelectedMultiLayerItem();

    //! returning selected InstrumentItem from InstrumentModel
    SessionItem *getSelectedInstrumentItem();

    //! set sample selection
    void setSelectedSample(const QString &displayName);

    //! set instrument selection
    void setSelectedInstrument(const QString &displayName);

    //! get item name when display name is known
    QString getSampleItemNameForDisplayName(const QString &displayName);
    QString getInstrumentItemNameForDisplayName(const QString &displayName);

    //! return minimizer settings item
    MinimizerSettingsItem *getMinimizerSettings();

    QString getMinimizerAlgorithm();

    QString getInputDataPath();

    void setInputDataPath(const QString &path);
public slots:
    //! callback for changes made on children of root_item, propagate forward
    void dataChangedProxy(const QModelIndex &topLeft, const QModelIndex &bottomRight,
                          const QVector<int> &roles = QVector<int> ());

private:
    SampleModel *m_sampleModel;
    InstrumentModel *m_instrumentModel;

    //! get a list of display names for given model - we use them to identify items
    QStringList retrieveDisplayNames(SessionModel *model, const QString &type);
};

#endif
