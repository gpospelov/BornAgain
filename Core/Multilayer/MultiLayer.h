// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/MultiLayer.h
//! @brief     Defines class MultiLayer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef MULTILAYER_H
#define MULTILAYER_H

#include "ISample.h"
#include "SafePointerVector.h"
#include "Vectors3D.h"
#include "ZLimits.h"

#include <functional>

class ILayout;
class Layer;
class LayerInterface;
class LayerRoughness;

//! Our sample model: a stack of layers one below the other.
//! @ingroup samples

//! Example of system of 4 layers (3 interfaces):
//!
//!  ambience    layer #0        z=getLayerBottomZ(0)=0.0
//!  ---------   interface #0
//!  Fe, 20A     layer #1        z=getLayerBottomZ(1)=-20.0
//!  ---------   interface #1
//!  Cr, 40A     layer #2        z=getLayerBottomZ(2)=-60.0
//!  ---------   interface #2
//!  substrate   layer #3        z=getLayerBottomZ(3)=-60.0

class BA_CORE_API_ MultiLayer : public ISample
{
public:
    MultiLayer();
    virtual ~MultiLayer();

    void accept(INodeVisitor* visitor) const final override { visitor->visit(this); }

    size_t numberOfLayers() const { return m_layers.size(); }
    size_t numberOfInterfaces() const { return m_interfaces.size(); }

    //! Adds object to multilayer
    void addLayer(const Layer& layer);

    //! Adds layer with top roughness
    void addLayerWithTopRoughness(const Layer& layer, const LayerRoughness& roughness);

    //! Returns layer with given index
    const Layer* layer(size_t i_layer) const { return m_layers[check_layer_index(i_layer)]; }

    //! Returns layer with given index
    const LayerInterface* layerInterface(size_t i_interface) const {
        return m_interfaces[check_interface_index(i_interface)]; }

    //! Returns thickness of layer
    double layerThickness(size_t i_layer) const;

    //! Returns top roughness of layer
    const LayerRoughness* layerTopRoughness(size_t i_layer) const;

    //! Returns top interface of layer
    const LayerInterface* layerTopInterface(size_t i_layer) const;

    //! Returns bottom interface of layer
    const LayerInterface* layerBottomInterface(size_t i_layer) const;

    //! Returns a clone of multilayer with clones of all layers and recreated
    //! interfaces between layers
    MultiLayer* clone() const final override;

    //! Sets cross correlation length of roughnesses between interfaces
    void setCrossCorrLength(double crossCorrLength);

    //! Returns cross correlation length of roughnesses between interfaces
    double crossCorrLength() const { return m_crossCorrLength; }

    //! Sets the external field applied to the multilayer (units: A/m)
    void setExternalField(kvector_t ext_field);

    //! Returns the external field applied to the multilayer (units: A/m)
    kvector_t externalField() const { return m_ext_field; }

    //! returns layer index
    size_t indexOfLayer(const Layer* p_layer) const;

    bool containsMagneticMaterial() const;

    //! Returns true if the multilayer contains non-default materials of one type only
    bool containsCompatibleMaterials() const;

    //! precalculate the magnetic B fields in each layer
    void initBFields();

    bool hasRoughness() const;

    size_t totalNofLayouts() const;

    std::vector<const INode*> getChildren() const final override;

private:
    //! Registers some class members for later access via parameter pool
    void init_parameters();

    //! Adds the layer with simultaneous registration in parent class
    void addAndRegisterLayer(Layer* child);

    //! Adds the interface with simultaneous registration in parent class
    void addAndRegisterInterface(LayerInterface* child);

    //! Handles correct registration of layer thicknesses (not needed for top and bottom layer)
    void handleLayerThicknessRegistration();

    //! Checks index of layer w.r.t. vector length
    size_t check_layer_index(size_t i_layer) const;

    //! Checks index of interface w.r.t. vector length
    size_t check_interface_index(size_t i_interface) const;

    //! stack of layers [nlayers]
    SafePointerVector<Layer> m_layers;
    //! stack of layer interfaces [nlayers-1]
    SafePointerVector<LayerInterface> m_interfaces;
    //! cross correlation length (in z direction) between different layers
    double m_crossCorrLength;
    //! external magnetic field (in A/m)
    kvector_t m_ext_field;
};

#endif // MULTILAYER_H
