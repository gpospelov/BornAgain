#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include "fancymainwindow.h"

namespace Manhattan {
    class FancyTabWidget;
}

class TaskSelectorWidget;
class WelcomeManager;
class SampleManager;
class ExperimentManager;
class SimulationManager;
class FitManager;

class MainWindow : public QMainWindow
//class MainWindow : public FancyMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    //TaskSelectorWidget *m_tabWidget;
    Manhattan::FancyTabWidget  *m_tabWidget;
    WelcomeManager *m_welcomeManager;
    SampleManager *m_sampleManager;
    ExperimentManager *m_expManager;
    SimulationManager *m_simulManager;
    FitManager * m_fitManager;
};

#endif // MAINWINDOW_H
