// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InfoWidgets/InfoWidget.h
//! @brief     Defines class InfoWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INFOWIDGET_H
#define INFOWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class InfoToolBar;
class SampleModel;
class InstrumentModel;
class PySampleWidget;

//! The InfoWidget resides at the bottom of SampleView and displays a Python script
class BA_CORE_API_ InfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InfoWidget(QWidget *parent = 0);

    void setSampleModel(SampleModel *sampleModel);
    void setInstrumentModel(InstrumentModel *instrumentModel);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

signals:
    void widgetHeightRequest(int);
    void widgetCloseRequest();

public slots:
    void onDockVisibilityChange(bool is_visible);

private slots:
    void onExpandButtonClicked();

    void setEditorVisible(bool editor_status, bool dock_notify = false);

protected:
    void resizeEvent(QResizeEvent *);
    bool isEditorVisible();

private:
    InfoToolBar *m_infoToolBar;
    PySampleWidget *m_pySampleWidget;
    QWidget *m_placeHolder;
    int m_cached_height;
};

#endif
