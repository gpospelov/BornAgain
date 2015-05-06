#include "qcustomplot.h"

class ParameterizedItem;
class AwesomePropertyEditor;

class DistributionPlotWidget :public QWidget
{
    Q_OBJECT

public:
    DistributionPlotWidget(QWidget *parent = 0);
    virtual ~DistributionPlotWidget() {}

    QCustomPlot *getPlot() const;
private:
    QCustomPlot *m_plot;

};
