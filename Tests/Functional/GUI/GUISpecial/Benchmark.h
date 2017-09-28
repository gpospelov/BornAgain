// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/GUIPerformanceTest/Benchmark.h
//! @brief     Defines Benchmark class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <functional>
#include <QString>
#include <QVector>

//! Measures execution time of given function and stores result in database.

class Benchmark
{
public:
    Benchmark();

    void test(const QString& name, std::function<void(void)> f, int ntries);

    QString report() const;

private:
    struct Measurement {
        QString name;     //!< measurement name
        qint64 wall_time; //!< in msec
    };

    QVector<Measurement> m_measurements;
};

#endif // GUIPERFORMANCETEST_H
