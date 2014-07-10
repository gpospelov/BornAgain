#ifndef SAMPLETOOLBAR_H
#define SAMPLETOOLBAR_H

#include <QToolBar>

class QAction;
class QToolButton;
class QToolBar;
class QComboBox;
class QString;
class QButtonGroup;

//! main tool bar on top of SampleView window
class SampleToolBar : public QToolBar
{
    Q_OBJECT

public:
    explicit SampleToolBar(QWidget *parent = 0);

signals:
    void deleteItems();
    void selectionMode(int);
    void centerView();
    void smartAlign();
    void changeScale(double);
    void zoomIn();
    void zoomOut();

public slots:
    void onViewSelectionMode(int);
    void onScaleComboChanged(const QString &);
    void onMaterialEditorCall();

private:
    QButtonGroup *m_pointerModeGroup;
    QToolButton *m_removeButton;
    QToolButton *m_centerViewButton;
    QToolButton *m_alignItemsButton;
    QComboBox *m_scaleCombo;
    QToolButton *m_materialEditorButton;
    QAction *m_zoomInAction;
    QAction *m_zoomOutAction;
};


#endif // SAMPLETOOLBAR_H
