// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobWidgets/JobRealTimeToolBar.h
//! @brief     Defines class JobRealTimeToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef JOBREALTIMETOOLBAR_H
#define JOBREALTIMETOOLBAR_H

#include <QToolBar>
#include "WinDllMacros.h"

class QToolButton;

//! The JobRealTimeToolBar contains buttons needed for JobRealTimeWidget
class BA_CORE_API_ JobRealTimeToolBar : public QToolBar
{
    Q_OBJECT

public:
    explicit JobRealTimeToolBar(QWidget *parent = 0);

signals:
    void resetParameters();

private:
    QToolButton *m_resetParametersButton;
    QToolButton *m_exportParametersButton;
};


#endif

