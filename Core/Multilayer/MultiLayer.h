// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/MultiLayer.h
//! @brief     Defines class MultiLayer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
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

    virtual void accept(INodeVisitor* visitor) const final override { visitor->visit(this); }

    size_t numberOfLayers() const { return m_layers.size(); }
    size_t numberOfInterfaces() const { return m_interfaces.size(); }

    //! Adds object to multilayer
    void addLayer(const Layer& p_child);

    //! Adds layer with top roughness
    void addLayerWithTopRoughness(const Layer& layer, const LayerRoughness& roughness);

    //! Returns layer with given index
    const Layer* layer(size_t i_layer) const { return m_layers[check_layer_index(i_layer)]; }

    //! Returns layer with given index
    const LayerInterface* layerInterface(size_t i_interface) const {
        return m_interfaces[check_interface_index(i_interface)]; }

    //! Returns z-coordinate of the layer's bottom
    double layerTopZ(size_t i_layer) const;

    //! Returns z-coordinate of the layer's bottom
    double layerBottomZ(size_t i_layer) const;

    //! Returns thickness of layer
    double layerThickness(size_t i_layer) const;

    //! Returns top interface of layer
    const LayerInterface* layerTopInterface(size_t i_layer) const;

    //! Returns bottom interface of layer
    const LayerInterface* layerBottomInterface(size_t i_layer) const;

    //! Returns layer material
    HomogeneousMaterial layerMaterial(size_t i_layer) const;

    //! Changes a layer's material
    void setLayerMaterial(size_t i_layer, HomogeneousMaterial material);

    //! Returns a clone of multilayer with clones of all layers and recreated
    //! interfaces between layers
    MultiLayer* clone() const final override;

    //! Returns a clone with inverted magnetic fields
    MultiLayer* cloneInvertB() const;

    //! Returns a clone of multilayer where the original layers may be sliced into several sublayers
    //! for usage with the graded layer approximation
    MultiLayer* cloneSliced(bool use_average_layers) const;

    //! Sets cross correlation length of roughnesses between interfaces
    void setCrossCorrLength(double crossCorrLength);

    //! Returns cross correlation length of roughnesses between interfaces
    double crossCorrLength() const { return m_crossCorrLength; }

    //! Fourier transform of the correlation function of roughnesses between
    //! the interfaces
    double crossCorrSpectralFun(const kvector_t kvec, size_t j, size_t k) const;

    //! returns layer index
    int indexOfLayer(const Layer* p_layer) const;

    //! returns true if contains magnetic materials and matrix calculations are required
    bool requiresMatrixRTCoefficients() const;

    //! returns layer index corresponding to given global z coordinate
    //! The top interface position of a layer is considered to belong to the layer above
    size_t bottomZToLayerIndex(double z_value) const;

    //! returns layer index corresponding to given global z coordinate
    //! The top interface position of a layer is considered to belong to the layer beneath
    size_t topZToLayerIndex(double z_value) const;

    bool containsMagneticMaterial() const;

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

    //! Shared implementation for different clones
    MultiLayer* cloneGeneric(const std::function<Layer*(const Layer*)>& layer_clone) const;

    //! Calculates the z-region in each layer that holds particles
    std::vector<ZLimits> calculateLayerZLimits() const;

    //! stack of layers [nlayers]
    SafePointerVector<Layer> m_layers;
    //! coordinate of layer's bottoms [nlayers]
    std::vector<double> m_layers_bottomz;
    //! stack of layer interfaces [nlayers-1]
    SafePointerVector<LayerInterface> m_interfaces;
    //! cross correlation length (in z direction) between different layers
    double m_crossCorrLength;
};

#endif // MULTILAYER_H
