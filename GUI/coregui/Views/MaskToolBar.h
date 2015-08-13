#ifndef MASKTOOLBAR_H
#define MASKTOOLBAR_H

#include <QToolBar>
class QToolButton;

class MaskToolBar : public QToolBar
{
    Q_OBJECT
public:
    MaskToolBar(QWidget *parent = 0);
    virtual ~MaskToolBar()
    {
    }

signals:
    //! signal is emitted when rectangle button pressed
    void rectangleButtonPressed();

    //! signal is emitted when ellipse button pressed
    void ellipseButtonPressed();

    //! signal is emitted when polygon button pressed
    void polygonButtonPressed();

    //! signal is emitted when selection button pressed
    void changeToSelectionMode();

    //! signal is emitted when pan button pressed
    void panMode(bool);

    //! signal is emitted when bring to front button pressed
    void bringToFrontClicked();

    //! signal is emitted when send to back button pressed
    void sendToBackClicked();

    //! signal is emitted when include button pressed
    void includeClicked();

    //! signal is emitted when exclude button pressed
    void excludeClicked();

private slots:
    //! emits signal when rectangle button pressed
    void onRectangleButtonPressed();

    //! emits signal when selection button pressed
    void onChangeToSelectionMode();

    //! from scene if item is drawn
    //! This works if emit isDrawn is uncommented in MaskGraphicsScene
    void selectSelectionMode();

    //! emits signal when pan button pressed
    void onPanMode(bool isActive);

    //! emits signal when ellipse button pressed
    void onEllipseButtonPressed();

    //! emits signal when polygon button pressed
    void onPolygonButtonPressed();

    //! emits signal when bring to front button pressed
    void onBringToFrontClicked();

    //! emits signal when send to back button pressed
    void onSendToBackClicked();

    //! emits signal when include button pressed
    void onIncludeClicked();

    //! emits signal when exclude button pressed
    void onExcludeClicked();

private:
    QToolButton *m_selectionButton;    //!< selection button
    QToolButton *m_panButton;          //!<pan button
    QToolButton *m_rectangleButton;    //!< rectangle button
    QToolButton *m_ellipseButton;      //!< ellipse button
    QToolButton *m_polygonButton;      //!< polygon button
    QToolButton *m_bringToFrontButton; //!< bring to front button
    QToolButton *m_sendToBackButton;   //!< send to back button
    QToolButton *m_includeButton;      //!< include button
    QToolButton *m_excludeButton;      //!< exclude button
};

#endif
