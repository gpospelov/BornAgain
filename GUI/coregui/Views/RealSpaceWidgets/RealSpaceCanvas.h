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

// Class for holding size and thickness information of layers
class SceneGeometry
{
public:
    SceneGeometry(double size = 50.0, double top_thickness = 25.0,
                  double bottom_thickness = 25.0, double min_thickness = 2.0)
    {
        l_size = size;                              // layer size
        l_top_thickness = top_thickness;            // top layer thickness
        l_bottom_thickness = bottom_thickness;      // bottom layer thickness
        l_min_thickness = min_thickness;            // minimum layer thickness
    }

    double layer_size() const {return l_size;}
    double layer_top_thickness() const {return l_top_thickness;}
    double layer_bottom_thickness() const {return l_top_thickness;}
    double layer_min_thickness() const {return l_min_thickness;}

    void set_layer_size(double size) {l_size = size;}
    void set_layer_top_thickness(double top_thickness) {l_top_thickness = top_thickness;}
    void set_layer_bottom_thickness(double bottom_thickness) {l_top_thickness = bottom_thickness;}

private:
    double l_size;
    double l_top_thickness;
    double l_bottom_thickness;
    double l_min_thickness;
};


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
    void lockViewUnchecked(const QItemSelection &);

public slots:
    void onSelectionChanged(const QItemSelection &selection, const QItemSelection &);
    void updateToSelection(const QItemSelection &selection);

    void onDefaultViewAction();
    void onSideViewAction();
    void onTopViewAction();
    void onLockViewAction(bool view_locked);
    void onChangeLayerSizeAction(double layer_size_scale);

private slots:
    void updateScene();
    void resetScene();

    void defaultView();
    void sideView();
    void topView();

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
    SceneGeometry* m_sceneGeometry;
};

#endif // REALSPACESCENE_H
