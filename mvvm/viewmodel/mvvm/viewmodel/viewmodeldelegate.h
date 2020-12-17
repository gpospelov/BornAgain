//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/viewmodel/mvvm/viewmodel/viewmodeldelegate.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEWMODEL_MVVM_VIEWMODEL_VIEWMODELDELEGATE_H
#define BORNAGAIN_MVVM_VIEWMODEL_MVVM_VIEWMODEL_VIEWMODELDELEGATE_H

#include "mvvm/viewmodel_export.h"
#include <QStyledItemDelegate>
#include <memory>

namespace ModelView {

class EditorFactoryInterface;
class CellDecoratorInterface;

//! Model delegate to provide editing/painting for custom variants.

class MVVM_VIEWMODEL_EXPORT ViewModelDelegate : public QStyledItemDelegate {
    Q_OBJECT

public:
    explicit ViewModelDelegate(QObject* parent = nullptr);
    ~ViewModelDelegate() override;

    void setEditorFactory(std::unique_ptr<EditorFactoryInterface> editor_factory);
    void setCellDecoration(std::unique_ptr<CellDecoratorInterface> cell_decoration);

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
                          const QModelIndex& index) const override;

    void setEditorData(QWidget* editor, const QModelIndex& index) const override;
    void setModelData(QWidget* editor, QAbstractItemModel* model,
                      const QModelIndex& index) const override;

    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;

    void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option,
                              const QModelIndex& index) const override;

public slots:
    void onCustomEditorDataChanged();

protected:
    void initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index) const override;

    std::unique_ptr<EditorFactoryInterface> m_editor_factory;
    std::unique_ptr<CellDecoratorInterface> m_cell_decoration;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEWMODEL_MVVM_VIEWMODEL_VIEWMODELDELEGATE_H
