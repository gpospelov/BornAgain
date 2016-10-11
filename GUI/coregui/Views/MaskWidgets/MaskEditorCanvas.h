// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/MaskEditorCanvas.h
//! @brief     Defines class MaskEditorCanvas
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef MASKEDITORCANVAS_H
#define MASKEDITORCANVAS_H

#include "MaskEditorFlags.h"
#include <QWidget>

class MaskGraphicsScene;
class MaskGraphicsView;
class SessionModel;
class QItemSelectionModel;
class QModelIndex;
class MaskResultsPresenter;
class IntensityDataItem;
class ColorMapLabel;
class IntensityDataItem;

//! Painting widget for MaskEditor, contains graphics scene and graphics view

class MaskEditorCanvas : public QWidget
{
    Q_OBJECT
public:
    MaskEditorCanvas(QWidget *parent = 0);

    void setMaskContext(SessionModel *model, const QModelIndex &maskContainerIndex, IntensityDataItem *intensityItem);
    void setSelectionModel(QItemSelectionModel *model);

    MaskGraphicsScene *getScene();

signals:
    void changeActivityRequest(MaskEditorFlags::Activity);

public slots:
    void onPresentationTypeRequest(MaskEditorFlags::PresentationType presentationType);
    void onSavePlotRequest();
    void onResetViewRequest();

private:
    bool isAxisRangeMatchData() const;
    void setZoomToROI();

    MaskGraphicsScene *m_scene;
    MaskGraphicsView *m_view;
    IntensityDataItem *m_intensityDataItem;
    ColorMapLabel *m_statusLabel;
    MaskResultsPresenter *m_resultsPresenter;
};


#endif // MASKEDITORCANVAS_H
