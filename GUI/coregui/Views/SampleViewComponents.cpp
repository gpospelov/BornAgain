#include "SampleViewComponents.h"
#include "widgetbox.h"
#include "SampleDesigner.h"


SampleWidgetBox *SampleViewComponents::createWidgetBox(
        SampleDesignerInterface *core, QWidget *parent)
{
    return new SampleWidgetBox(core, parent);
}

SamplePropertyEditor *SampleViewComponents::createPropertyEditor(
        QItemSelectionModel *selection_model, QWidget *parent)
{
    return new SamplePropertyEditor(selection_model, parent);
}

ItemTreeView *SampleViewComponents::createTreeView(
        SampleModel *sampleModel, QWidget *parent)
{
    ItemTreeView *tree_view = new ItemTreeView(parent);
    tree_view->setModel(sampleModel);
    return tree_view;
}

SampleInfoStreamInterface *SampleViewComponents::createInfoStream(
        QWidget *parent)
{
    return new SampleInfoStreamInterface(parent);
}

