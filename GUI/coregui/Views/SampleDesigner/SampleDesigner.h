// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/SampleDesigner/SampleDesigner.h
//! @brief     Declares class SampleDesigner
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef SAMPLEEDITOR_H
#define SAMPLEEDITOR_H

#include <QObject>
#include <QStackedWidget>
#include "DesignerView.h"
#include "DesignerScene.h"

class DesignerScene;
class DesignerWidgetFactory;
class InstrumentModel;
class SampleModel;
class FilterPropertyProxy;

//! sample designer interface
class BA_CORE_API_ SampleDesignerInterface : public QObject
{
    Q_OBJECT

public:
    SampleDesignerInterface(QObject *parent = 0) : QObject(parent){}
    virtual ~SampleDesignerInterface() { }

//    virtual DesignerScene *getScene() const = 0;
//    virtual DesignerView *getView() const = 0;

};


//! sample designer provide central window with graphic scene to drag and drop
class BA_CORE_API_ SampleDesigner: public SampleDesignerInterface
{
    Q_OBJECT

public:
    SampleDesigner(QWidget *parent = 0);
    virtual ~SampleDesigner();

    DesignerScene *getScene() const { return m_designerScene; }
    DesignerView *getView() const { return m_designerView; }

    QWidget *getCentralWidget() { return m_designerView; }

    void setSampleModel(SampleModel *sampleModel);
    void setInstrumentModel(InstrumentModel *instrumentModel);
    void setSelectionModel(QItemSelectionModel *model, FilterPropertyProxy *proxy);

public slots:
    void onSmartAlign();

private:
    DesignerScene *m_designerScene; //! scene which holds all objects
    DesignerView *m_designerView;   //! graphical representation of scene with object
};



#endif // SAMPLEEDITOR_H
