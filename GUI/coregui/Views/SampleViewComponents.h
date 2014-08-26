#ifndef SAMPLEVIEWCOMPONENTS_H
#define SAMPLEVIEWCOMPONENTS_H

#include <QWidget>
#include "ItemTreeView.h"
#include "widgetbox.h"

#include "SamplePropertyEditor.h"
#include "SampleWidgetBox.h"
#include "SampleModel.h"


class BA_CORE_API_ SampleInfoStreamInterface : public QWidget
{
public:
    explicit SampleInfoStreamInterface(QWidget *parent = 0) : QWidget(parent)
    {
        setMinimumSize(128, 128);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    }
};


class BA_CORE_API_ SampleViewComponents
{
public:
    static SampleWidgetBox *createWidgetBox(
            SampleDesignerInterface *core, QWidget *parent);
    static SamplePropertyEditor *createPropertyEditor(
            QItemSelectionModel *selection_model, QWidget *parent);
    static ItemTreeView *createTreeView(
            SampleModel *sample_model, QWidget *parent);
    static SampleInfoStreamInterface *createInfoStream(QWidget *parent);
};

#endif // SAMPLEVIEWCOMPONENTS_H
