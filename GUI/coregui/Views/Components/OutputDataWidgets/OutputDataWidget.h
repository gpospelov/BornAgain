#ifndef OUTPUTDATAWIDGET_H
#define OUTPUTDATAWIDGET_H

#include <QWidget>
#include "OutputData.h"
#include "qcustomplot.h"
#include "OutputDataItem.h"

class PlotWidget;
class PropertyWidget;
class QSplitter;
class OutputDataToolBar;


class OutputDataWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OutputDataWidget(QWidget *parent = 0, bool isCreateToolBar = true);

    void setCurrentItem(OutputDataItem *item);

    void setPropertyPanelVisible(bool visible);

public slots:

    void resetTriggered();
    void togglePropertyPanel();
    void savePlot();
    void toggleProjections();
    void projectionsChanged(bool projection);
    void gradientChanged(QCPColorGradient gradient);
    void onPropertySplitterMoved(int pos, int index);

private:
    void Draw(const OutputData<double> *data);

    PlotWidget *m_plotWidget;
    const OutputData<double > *m_data;

    PropertyWidget *m_propertyWidget;
    QSplitter *m_splitter;
    OutputDataToolBar *m_toolBar;
    QCPColorGradient m_gradient;
    OutputDataItem *m_currentOutputDataItem;


    QVBoxLayout *m_mainLayout;

    bool m_isPropertyWidgetVisible;
    bool m_isProjectionsVisible;

    void connectToobarSignals();
    //void connectPropertyWidgetSignals(bool isConnect);
    int m_currentPropertyWidgetWidth;

};




#endif
