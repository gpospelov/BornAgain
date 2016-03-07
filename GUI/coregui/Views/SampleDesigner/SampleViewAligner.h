// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/SampleDesigner/SampleViewAligner.h
//! @brief     Defines class SampleViewAligner
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SAMPLEVIEWALIGNER_H
#define SAMPLEVIEWALIGNER_H

#include "WinDllMacros.h"
#include <QMap>
#include <QModelIndex>
#include <QPointF>
class DesignerScene;
class IView;
class SessionItem;


//! Makes alignment of sample droped on graphics scene.
//! Implements additional algorithm for smart alignment.
class BA_CORE_API_ SampleViewAligner
{
public:
    SampleViewAligner(DesignerScene *scene);

    void alignSample(SessionItem *item, QPointF reference = QPointF(), bool force_alignment = false);
    void alignSample(const QModelIndex & parentIndex, QPointF reference = QPointF(), bool force_alignment = false);

    void smartAlign();
    void updateViews(const QModelIndex & parentIndex = QModelIndex());
    void updateForces();
    void calculateForces(IView *view);
    void advance();

private:
    IView *getViewForIndex(const QModelIndex &index);
    QList<IView *> getConnectedViews(IView *view);

    DesignerScene *m_scene;
    QList<IView *> m_views; //!< list of all views which are subject to smart align
    QMap<IView *, QPointF> m_viewToPos;
};


#endif

