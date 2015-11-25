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
#include "DetectorMask.h"
#include <QWidget>
#include <QModelIndex>

template <class T> class OutputData;

class SessionModel;
class ColorMapPlot;
class IntensityDataItem;

//! Shows resulting masked area of IntensityDataItem in two-color ColorMapPlot

class BA_CORE_API_ MaskResultsPresenter : public QWidget
{
public:
    MaskResultsPresenter(QWidget *parent = 0);
    void setModel(SessionModel *maskModel, const QModelIndex &rootIndex);

    void updatePresenter();

private:
    OutputData<double > *createMaskPresentation();

    SessionModel *m_maskModel;
    QModelIndex m_rootIndex;
    ColorMapPlot *m_colorMapPlot;

    SessionModel *m_resultModel;
    DetectorMask m_detectorMask;

};


#endif

