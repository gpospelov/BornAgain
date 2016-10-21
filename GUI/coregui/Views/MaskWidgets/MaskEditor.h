// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/MaskEditor.h
//! @brief     Defines class MaskEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef MASKEDITOR_H
#define MASKEDITOR_H

#include "WinDllMacros.h"
#include <QMainWindow>
#include <QModelIndex>
#include <QWidget>

class MaskEditorPropertyPanel;
class MaskEditorActions;
class MaskEditorToolBar;
class MaskEditorCanvas;
class SessionModel;
class IntensityDataItem;
namespace Manhattan { class MiniSplitter; }

//! Main class to draw masks on top of intensity data map

class BA_CORE_API_ MaskEditor : public QMainWindow
{
    Q_OBJECT
public:
    MaskEditor(QWidget *parent = 0);

public slots:
    //! Main method to setup context for mask editing
    //! @par model The model which will hold all masks
    //! @par maskContainerIndex Index of top level MaskContainerItem in the model to hold masks
    //! @par intensityItem IntensityDataItem which will be used as background for Mask drawing
    void setMaskContext(SessionModel *model, const QModelIndex &maskContainerIndex,
                        IntensityDataItem *intensityItem);

    void onPropertyPanelRequest();

    QList<QAction *> topToolBarActions();

protected:
    void contextMenuEvent(QContextMenuEvent *event);

private:
    void setup_connections();

    MaskEditorActions *m_editorActions;
    MaskEditorToolBar *m_toolBar;
    MaskEditorPropertyPanel *m_editorPropertyPanel;
    MaskEditorCanvas *m_editorCanvas;
    Manhattan::MiniSplitter *m_splitter;
};


#endif // MASKEDITOR_H
