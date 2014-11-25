#ifndef COMBOWIDGET_H
#define COMBOWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class QComboBox;
class QLabel;
class QSpinBox;
class QDoubleSpinBox;
class QGridLayout;

class BA_CORE_API_ ComboWidget : public QWidget
{
    Q_OBJECT

public:
    ComboWidget(QString title, QGridLayout *layout = 0, QWidget *parent = 0);

};

#endif
