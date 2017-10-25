// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/InstrumentViewActions.cpp
//! @brief     Implements class InstrumentViewActions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "InstrumentViewActions.h"
#include "SessionModel.h"
#include <QAction>
#include <QItemSelectionModel>
#include <QMenu>
#include <QModelIndex>

InstrumentViewActions::InstrumentViewActions(QWidget* parent)
    : QObject(parent)
    , m_addInstrumentAction(nullptr)
    , m_removeInstrumentAction(nullptr)
    , m_cloneInstrumentAction(nullptr)
    , m_model(nullptr)
    , m_selectionModel(nullptr)
{
    m_addInstrumentAction = new QAction(QIcon(":/images/toolbar16dark_newitem.svg"),
            "Add new instrument", this);

    m_removeInstrumentAction = new QAction(QIcon(":/images/toolbar16dark_recycle.svg"),
            "Remove this instrument", this);

    m_cloneInstrumentAction  = new QAction(QIcon(":/images/toolbar16dark_cloneitem.svg"),
            "Clone this instrument", this);

    connect(m_addInstrumentAction, SIGNAL(triggered()), this, SLOT(onAddInstrument()));
    connect(m_removeInstrumentAction, SIGNAL(triggered()), this, SLOT(onRemoveInstrument()));
    connect(m_cloneInstrumentAction, SIGNAL(triggered()), this, SLOT(onCloneInstrument()));
}

void InstrumentViewActions::setModel(SessionModel* model) { m_model = model; }

void InstrumentViewActions::setSelectionModel(QItemSelectionModel* selectionModel)
{
    m_selectionModel = selectionModel;
}

void InstrumentViewActions::onAddInstrument()
{
    SessionItem* instrument = m_model->insertNewItem(Constants::InstrumentType);
    instrument->setItemName(suggestInstrumentName("Default GISAS"));
    updateSelection();
}

void InstrumentViewActions::onRemoveInstrument()
{
    QModelIndex currentIndex = m_selectionModel->currentIndex();

    if (currentIndex.isValid())
        m_model->removeRows(currentIndex.row(), 1, QModelIndex());

    updateSelection();
}

void InstrumentViewActions::onCloneInstrument()
{
    QModelIndex currentIndex = m_selectionModel->currentIndex();

    if (currentIndex.isValid()) {
        SessionItem* item  = m_model->itemForIndex(currentIndex);
        QString nameOfClone = suggestInstrumentName(item->itemName());
        SessionItem *clone = m_model->copyParameterizedItem(item);
        clone->setItemName(nameOfClone);
    }
}

void InstrumentViewActions::onContextMenuRequest(const QPoint& point,
                                                 const QModelIndex& indexAtPoint)
{
    QMenu menu;

    setAllActionsEnabled(indexAtPoint.isValid());

    m_addInstrumentAction->setEnabled(true);

    menu.addAction(m_cloneInstrumentAction);
    menu.addAction(m_removeInstrumentAction);
    menu.addSeparator();
    menu.addAction(m_addInstrumentAction);
    menu.exec(point);
}

void InstrumentViewActions::setAllActionsEnabled(bool value)
{
    m_addInstrumentAction->setEnabled(value);
    m_removeInstrumentAction->setEnabled(value);
    m_cloneInstrumentAction->setEnabled(value);
}

void InstrumentViewActions::updateSelection()
{
    if (!m_selectionModel->hasSelection()) {
        // select last item
        QModelIndex itemIndex
            = m_model->index(m_model->rowCount(QModelIndex()) - 1, 0, QModelIndex());
        m_selectionModel->select(itemIndex, QItemSelectionModel::ClearAndSelect);
    }
}

QString InstrumentViewActions::suggestInstrumentName(const QString& currentName)
{
    auto map_of_names = mapOfNames();

    int ncopies = map_of_names[currentName];
    if (ncopies == 0) {
        map_of_names[currentName] = 1;
        return currentName;
    } else {
        map_of_names[currentName]++;
        return QString("%1 (%2)").arg(currentName).arg(map_of_names[currentName]);
    }
}

QMap<QString, int> InstrumentViewActions::mapOfNames()
{
    QMap<QString, int> result;

    QModelIndex parentIndex;
    for (int i_row = 0; i_row < m_model->rowCount(parentIndex); ++i_row) {
        QModelIndex itemIndex = m_model->index(i_row, 0, parentIndex);
        QString name = m_model->itemForIndex(itemIndex)->itemName();
        int ncopy(1);
        QRegExp regexp("\\((.*)\\)");
        if (regexp.indexIn(name) >= 0) {
            ncopy = regexp.cap(1).toInt();
        }
        name.replace(regexp.cap(0), "");
        name = name.trimmed();
        result[name] = ncopy;
    }

    return result;
}
