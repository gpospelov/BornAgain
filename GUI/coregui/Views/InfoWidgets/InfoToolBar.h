// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InfoWidgets/InfoToolBar.h
//! @brief     Defines class InfoToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INFOTOOLBAR_H
#define INFOTOOLBAR_H

#include "WinDllMacros.h"
#include <QWidget>
#include <QToolBar>

class QToolButton;

//! The InfoToolBar is a tool bar for InfoWidget
class BA_CORE_API_ InfoToolBar : public QToolBar
{
    Q_OBJECT

signals:
    void expandButtonClicked();
    void closeButtonClicked();

protected slots:
    void onExpandButtonClicked();

public:
    explicit InfoToolBar(QWidget *parent = 0);

private:
    QToolButton *m_expandButton;
    QToolButton *m_closeButton;
};

#endif
