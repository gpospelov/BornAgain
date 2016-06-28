// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/InfoPanel.h
//! @brief     Declares class InfoPanel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef INFOPANEL_H
#define INFOPANEL_H

#include "WinDllMacros.h"
#include <QFrame>

class QStackedWidget;
class InfoPanelToolBar;

//! The InfoPanel class serves as a widget container with tool bar on top, with
//! collapse/expand button functionality. Intended for QDockWindow, to be able to quickly
//! minimize/maximize its appearance.

//! Used in JobMessagePanel.

class BA_CORE_API_ InfoPanel : public QFrame
{
    Q_OBJECT
public:
    explicit InfoPanel(QWidget *parent);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

signals:
    void widgetHeightRequest(int);

protected slots:
    void onExpandButtonClicked();
    void onCloseButtonClicked();
    void setContentVisible(bool editor_status, bool dock_notify = false);

protected:
    bool isContentVisible();

    InfoPanelToolBar *m_toolBar;
    QStackedWidget *m_stackedWidget;
    int m_cached_height;
};

#endif
