// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DataItemView.h
//! @brief     Defines class DataItemView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef DATAITEMVIEW_H
#define DATAITEMVIEW_H

#include "SessionItem.h"

class DataItem;
class DataPresentationProperties;
class Data1DPresentationProperties;
template<class T> class OutputData;

//! Base for DataItem1DView and DataItem2DView

class BA_CORE_API_ DataItemView : public SessionItem
{
    static const QString T_CHILDREN;

public:
    ~DataItemView() override = default;

    virtual void addItem(DataItem* data_item) = 0;

    template<class T = DataPresentationProperties>
    std::vector<T*> propertyItems();

    template<class T = DataPresentationProperties>
    T* propertyItem(size_t i) const;

protected:
    DataItemView(const QString& model_type);
    std::vector<DataItem*> dataItems();
    DataItem* dataItem(size_t i) const;
    const OutputData<double>* getOutputData(size_t i) const;
};

extern template std::vector<DataPresentationProperties*> DataItemView::propertyItems();
extern template std::vector<Data1DPresentationProperties*> DataItemView::propertyItems();
extern template DataPresentationProperties* DataItemView::propertyItem(size_t) const;
extern template Data1DPresentationProperties* DataItemView::propertyItem(size_t) const;

#endif // DATAITEMVIEW_H
