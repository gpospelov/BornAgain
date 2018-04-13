// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceCanvas.h
//! @brief     Defines class RealSpaceCanvas
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef REALSPACECANVAS_H
#define REALSPACECANVAS_H

#include "WinDllMacros.h"
#include <QWidget>
#include <QModelIndex>
#include <memory>

#include <QItemSelectionModel>

class SampleModel;
class RealSpaceView;
class RealSpaceModel;

//! Provides 3D object generation for RealSpaceWidget.

class BA_CORE_API_ RealSpaceCanvas : public QWidget
{
    Q_OBJECT

public:
    RealSpaceCanvas(QWidget* parent = 0);
    ~RealSpaceCanvas();

    void setModel(SampleModel* sampleModel = nullptr,
                  QItemSelectionModel* selectionModel = nullptr);

signals:
    void lockViewUnchecked(const QItemSelection &, const QItemSelection &);

public slots:
    void onSelectionChanged(const QItemSelection &selected, const QItemSelection &);

    void onDefaultViewAction();
    void onEdgeViewAction();
    void onFaceViewAction();
    void onLockViewAction(bool view_locked);

private slots:
    void updateScene();
    void resetScene();

    void defaultView();
    void edgeView();
    void faceView();

protected:
    virtual void showEvent(QShowEvent*);
    virtual void hideEvent(QHideEvent*);

private:
    void setConnected(SampleModel* model, bool makeConnected);

    SampleModel* m_sampleModel;
    QModelIndex m_currentSelection;
    RealSpaceView* m_view;
    std::unique_ptr<RealSpaceModel> m_realSpaceModel;

    QItemSelectionModel* m_selectionModel;
    bool m_view_locked;
};

#endif // REALSPACESCENE_H
