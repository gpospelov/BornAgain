// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI2_MODEL_MATERIALITEMS_H
#define BORNAGAIN_GUI2_MODEL_MATERIALITEMS_H

//! materialitems.h
//! Collection of materials to populate MaterialModel.

#include "darefl_export.h"
#include "mvvm/model/compounditem.h"

namespace ModelView {
class ExternalProperty;
}

namespace gui2 {

//! Container to hold MaterialItems.

class DAREFLCORE_EXPORT MaterialContainerItem : public ModelView::CompoundItem {
public:
    static inline const std::string T_MATERIALS = "T_MATERIALS";
    MaterialContainerItem();
};

//! Base class with all materials with name and color defined.

class DAREFLCORE_EXPORT MaterialBaseItem : public ModelView::CompoundItem {
public:
    static inline const std::string P_COLOR = "P_COLOR";
    static inline const std::string P_NAME = "P_NAME";
    static inline const std::string P_H_X = "P_H_X";
    static inline const std::string P_H_Y = "P_H_Y";
    static inline const std::string P_H_Z = "P_H_Z";

    ModelView::ExternalProperty external_property() const;

protected:
    MaterialBaseItem(const std::string& model_type);
    void init_magnetic_field();
};

//! Represents material based on scattering length density.

class DAREFLCORE_EXPORT SLDMaterialItem : public MaterialBaseItem {
public:
    static inline const std::string P_SLD_REAL = "P_SLD_REAL";
    static inline const std::string P_SLD_IMAG = "P_SLD_IMAG";

    SLDMaterialItem();

    void set_properties(const std::string& name, const QColor& color, double real, double imag);
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_MODEL_MATERIALITEMS_H
