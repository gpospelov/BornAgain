// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InfoWidgets/InfoToolBar.h
//! @brief     Declares class InfoToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef INFOTOOLBAR_H
#define INFOTOOLBAR_H

#include "StyledToolBar.h"

class QToolButton;

//! The InfoToolBar class represents a toolbar for InfoWidget

class BA_CORE_API_ InfoToolBar : public StyledToolBar
{
    Q_OBJECT

public:
    explicit InfoToolBar(QWidget *parent = 0);

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

#endif
