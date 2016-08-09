// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/InfoPanelToolBar.h
//! @brief     Defines class InfoPanelToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef INFOPANELTOOLBAR_H
#define INFOPANELTOOLBAR_H

#include "StyledToolBar.h"

class QToolButton;

//! The InfoPanelToolBar class represents a toolbar for InfoPanel

class BA_CORE_API_ InfoPanelToolBar : public StyledToolBar
{
    Q_OBJECT

public:
    explicit InfoPanelToolBar(QWidget *parent = 0);

signals:
    void expandButtonClicked();
    void closeButtonClicked();

public slots:
    void setExpandStatus(bool status);

protected slots:
    void onExpandButtonClicked();

private:
    QToolButton *m_expandButton;
    QToolButton *m_closeButton;
    bool m_expanded;
};


#endif // INFOPANELTOOLBAR_H
