#ifndef SELECTIONLISTMODEL_H_
#define SELECTIONLISTMODEL_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   SelectionListModel.h
//! @brief  Definition of SelectionListModel template
//! @author Scientific Computing Group at FRM II
//! @date   Feb 19, 2013

#include "SafePointerVector.h"

//- -------------------------------------------------------------------
//! @class SelectionListModel
//! @brief Definition of a templated list with a selected element
//! \tparam <T> type of the contained elements
//- -------------------------------------------------------------------
template <class T> class SelectionListModel : public SafePointerVector<T>
{
public:
    SelectionListModel();
    virtual ~SelectionListModel() {}

    //! get the currently selected entry
    T *getSelectedEntry();

    //! get the current selection index
    size_t getCurrentIndex() const { return m_selected_index; }

    //! set the selection to the indicated entry
    void setSelection(size_t index);
private:
    bool indexInAllowedRange(size_t index) const;
    size_t m_selected_index;
};

template<class T>
inline SelectionListModel<T>::SelectionListModel()
: m_selected_index(0)
{
}

template<class T>
inline T* SelectionListModel<T>::getSelectedEntry()
{
    if (indexInAllowedRange(m_selected_index)) {
        return (*this)[m_selected_index];
    }
    return 0;
}

template<class T>
inline void SelectionListModel<T>::setSelection(size_t index)
{
    if (indexInAllowedRange(index)) {
        m_selected_index = index;
    }
}

template<class T>
inline bool SelectionListModel<T>::indexInAllowedRange(size_t index) const
{
    return index < this->size();
}

#endif /* SELECTIONLISTMODEL_H_ */
