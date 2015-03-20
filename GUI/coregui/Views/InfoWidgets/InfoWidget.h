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

class QTextEdit;

class BA_CORE_API_ InfoWidget : public QWidget
{
public:
    explicit InfoWidget(QWidget *parent = 0);

private:
    QTextEdit *m_textEdit;
};

#endif
