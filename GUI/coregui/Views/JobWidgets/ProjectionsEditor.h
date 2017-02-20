// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/ProjectionsEditor.h
//! @brief     Defines class ProjectionsEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef PROJECTIONSEDITOR_H
#define PROJECTIONSEDITOR_H

#include "WinDllMacros.h"
#include <QMainWindow>

class SessionModel;
class QModelIndex;
class IntensityDataItem;
class ProjectionsToolBar;
class ProjectionsEditorActions;
class ProjectionsActions;
class ProjectionsEditorCanvas;
class ProjectionsPropertyPanel;
class ProjectionsWidget;
class QSplitter;
namespace Manhattan { class MiniSplitter; }

//! Editor to draw projections on top of intensity plot. Part of

class BA_CORE_API_ ProjectionsEditor : public QMainWindow
{
    Q_OBJECT

public:
    ProjectionsEditor(QWidget* parent = 0);

    void setContext(SessionModel* model, const QModelIndex& shapeContainerIndex,
                    IntensityDataItem* intensityItem);

private:
    ProjectionsEditorActions* m_editorActions;
    ProjectionsToolBar* m_toolBar; //! main tool bar with bottoms at the right
    ProjectionsEditorCanvas* m_projectionsCanvas; //! canvas with color map at the top
    ProjectionsWidget* m_projectionsWidget; //! bottom widget to draw projections plot
    ProjectionsPropertyPanel* m_propertyPanel; //! pannel at the right with properties
    Manhattan::MiniSplitter* m_rightSplitter;
    QSplitter* m_bottomSplitter;
};

#endif // PROJECTIONSEDITOR_H
