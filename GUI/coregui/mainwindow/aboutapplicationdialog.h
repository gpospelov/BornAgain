// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/mainwindow/aboutapplicationdialog.h
//! @brief     Defines class AboutApplicationDialog
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ABOUTAPPLICATIONDIALOG_H
#define ABOUTAPPLICATIONDIALOG_H

#include "WinDllMacros.h"
#include <QDialog>
#include <QString>


class QLabel;
class QPushButton;
class QStatusBar;
class QPalette;


//! new project dialog window
class BA_CORE_API_ AboutApplicationDialog : public QDialog
{
    Q_OBJECT
public:
    AboutApplicationDialog(QWidget *parent = 0);


private:
    QPushButton *m_closeButton;
};


#endif
