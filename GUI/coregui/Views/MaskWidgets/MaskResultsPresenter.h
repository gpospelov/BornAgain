// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskResultsPresenter.h
//! @brief     Defines class MaskResultsPresenter
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MASKRESULTSPRESENTER_H
#define MASKRESULTSPRESENTER_H

#include "WinDllMacros.h"
#include "MaskEditorFlags.h"
#include <QObject>
#include <QModelIndex>
#include <boost/scoped_ptr.hpp>

template <class T> class OutputData;

class SessionModel;
class ColorMapPlot;
class IntensityDataItem;

//! Updates bin values inside IntensityData to display current mask state. Returns IntensityData
//! to original state when requested.

class BA_CORE_API_ MaskResultsPresenter : public QObject
{
public:
    MaskResultsPresenter(QWidget *parent = 0);

    void setModel(SessionModel *maskModel, const QModelIndex &rootIndex);

    void updatePresenter(MaskEditorFlags::PresentationType mode);

private:
    void setShowMaskMode();
    void setOriginalMode();
    void backup_data();
    OutputData<double> *createMaskPresentation() const;

    SessionModel *m_maskModel;
    QModelIndex m_rootIndex;
    boost::scoped_ptr<OutputData<double> > m_dataBackup;
    bool m_interpolation_flag_backup;
};


#endif

