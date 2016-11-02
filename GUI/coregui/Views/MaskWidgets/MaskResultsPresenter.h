// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/MaskResultsPresenter.h
//! @brief     Defines class MaskResultsPresenter
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef MASKRESULTSPRESENTER_H
#define MASKRESULTSPRESENTER_H

#include "MaskEditorFlags.h"
#include "WinDllMacros.h"
#include <QModelIndex>
#include <QObject>
#include <memory>

class SessionModel;
class ColorMapPlot;
class IntensityDataItem;
template<class T> class OutputData;

//! Updates bin values inside IntensityData to display current mask state. Returns IntensityData
//! to original state when requested.

class BA_CORE_API_ MaskResultsPresenter : public QObject
{
public:
    MaskResultsPresenter(QWidget *parent = 0);

    void setMaskContext(SessionModel *maskModel, const QModelIndex &maskContainerIndex,
                        IntensityDataItem *intensityItem);

    void updatePresenter(MaskEditorFlags::PresentationType mode);

private:
    void setShowMaskMode();
    void setOriginalMode();
    void backup_data();
    OutputData<double> *createMaskPresentation() const;

    SessionModel *m_maskModel;
    QModelIndex m_maskContainerIndex;
    IntensityDataItem *m_intensityDataItem;
    std::unique_ptr<OutputData<double>> m_dataBackup;
    bool m_interpolation_flag_backup;
};

#endif // MASKRESULTSPRESENTER_H

