#ifndef OUTPUTDATAWIDGET_H
#define OUTPUTDATAWIDGET_H

#include <QWidget>
#include "OutputData.h"
#include "qcustomplot.h"
#include "OutputDataItem.h"

class PlotWidget;
class PropertyWidget;
class OutputDataToolBar;


class BA_CORE_API_ OutputDataWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OutputDataWidget(QWidget *parent = 0, bool isCreateToolBar = false, bool isCreatePropertyWidget = false, bool isProjections = false);

    void setCurrentItem(OutputDataItem *item);

public slots:

    void resetTriggered();
    void togglePropertyPanel();
    void savePlot();
    void toggleProjections();
    void projectionsChanged(bool projection);
    void gradientChanged(QCPColorGradient gradient);
    void setPropertyPanelVisible(bool visible);

private:
    void Draw(const OutputData<double> *data);

    PlotWidget *m_plotWidget;
    const OutputData<double > *m_data;

    PropertyWidget *m_propertyWidget;
    OutputDataToolBar *m_toolBar;
    QCPColorGradient m_gradient;
    OutputDataItem *m_currentOutputDataItem;
    QVBoxLayout *m_mainLayout;
    QHBoxLayout *m_layout;

    bool m_isProjectionsVisible;
    void connectToobarSignals();
};




#endif
