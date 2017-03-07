// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceCanvas.h
//! @brief     Defines class RealSpaceCanvas
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef REALSPACECANVAS_H
#define REALSPACECANVAS_H

#include "WinDllMacros.h"
#include <QObject>
#include <QModelIndex>

class SampleModel;

//! Provides 3D object generation for RealSpaceWidget.

class BA_CORE_API_ RealSpaceCanvas : public QObject
{
    Q_OBJECT

public:
    RealSpaceCanvas(QObject* parent = 0);

    void setModel(SampleModel* model);

public slots:
    void onSelectionChanged(const QModelIndex& selected);

private:
    void updateScene();

    SampleModel* m_model;
    QModelIndex m_rootIndex;
};

#endif // REALSPACESCENE_H
