#ifndef MASKTOOLBAR_H
#define MASKTOOLBAR_H

#include <QToolBar>
class QToolButton;

class MaskToolBar : public QToolBar
{
    Q_OBJECT
public:
    MaskToolBar(QWidget *parent = 0);
    virtual ~MaskToolBar() {}

signals:
    void rectangleButtonPressed();
    void ellipseButtonPressed();
    void polygonButtonPressed();
    void changeToSelectionMode();
    void panMode(bool);
    void deleteSelectedItem();
    void bringToFrontClicked();
    void sendToBackClicked();
    void includeClicked();
    void excludeClicked();
    void changeToDrawingMode();

private slots:
    void onRectangleButtonPressed();
    void onChangeToSelectionMode();
    void selectSelectionMode();
    void onPanMode(bool isActive);
    void onEllipseButtonPressed();
    void onPolygonButtonPressed();
    void onBringToFrontClicked();
    void onSendToBackClicked();
    void onIncludeClicked();
    void onExcludeClicked();

private:
    QToolButton *m_selectionButton;
    QToolButton *m_panButton;
    QToolButton *m_rectangleButton;
    QToolButton *m_ellipseButton;
    QToolButton *m_polygonButton;
    QToolButton *m_bringToFrontButton;
    QToolButton *m_sendToBackButton;
    QToolButton *m_includeButton;
    QToolButton *m_excludeButton;

};

#endif
