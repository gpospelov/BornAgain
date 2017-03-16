// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/GUIPerformanceTest/Benchmark.cpp
//! @brief     Implements Benchmark class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "Benchmark.h"
#include <QElapsedTimer>
#include <QDebug>

//! Do useless calculations to warmUp

Benchmark::Benchmark()
{
}

void Benchmark::test(const QString& name, std::function<void ()> f, int ntries)
{
    // warming up
    for(int i=0; i<ntries/10; ++i)
        f();

    QElapsedTimer timer;
    timer.start();

    for(int i=0; i<ntries; ++i)
        f();

    qDebug() << name << timer.elapsed();
}
