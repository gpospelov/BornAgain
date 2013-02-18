#ifndef FITMANAGER_H
#define FITMANAGER_H

#include <QWidget>

class TQtWidget;
class QLineEdit;
class TObject;
class TCanvas;

class FitManager : public QWidget
{
    Q_OBJECT

public:
    FitManager(QWidget *parent = 0);
    virtual ~FitManager(){}

public slots:
    void CanvasEvent(TObject *obj,unsigned int event,TCanvas *);
    void print_something();

private:
    TQtWidget *m_qcanvas;
    QLineEdit *m_lineEdit;
};


#endif // FITMANAGER_H
