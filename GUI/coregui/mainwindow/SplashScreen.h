// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/mainwindow/SplashScreen.h
//! @brief     Defines class SplashScreen
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QSplashScreen>
#include "WinDllMacros.h"

class BA_CORE_API_ SplashScreen : public QSplashScreen
{
    Q_OBJECT
public:
    explicit SplashScreen(QWidget *parent = 0);


public slots:
    void setProgress(int value);

protected:
    void drawContents(QPainter *painter);
private:
    int m_width, m_height;
    int m_progress;

};

#endif
