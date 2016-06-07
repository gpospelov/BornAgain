// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/MultiLayer.h
//! @brief     Declares class MultiLayer.
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

#include "Layer.h"
#include "LayerInterface.h"
#include "LayerRoughness.h"
#include "MultiLayerDWBASimulation.h"
#include <vector>


//! @class MultiLayer
//! @ingroup samples
//! @brief Stack of layers one below the other
//!
//! Example of system of 4 layers (3 interfaces):
//!
//!  ambience    layer #0        z=getLayerBottomZ(0)=0.0
//!  ---------   interface #0
//!  Fe, 20A     layer #1        z=getLayerBottomZ(1)=-20.0
//!  ---------   interface #1
//!  Cr, 40A     layer #2        z=getLayerBottomZ(2)=-60.0
//!  ---------   interface #2
//!  substrate   layer #3        z=getLayerBottomZ(3)=-60.0


class BA_CORE_API_ MultiLayer : public ICompositeSample
{
public:
    MultiLayer();
    virtual ~MultiLayer();

    //! calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *visitor) const;

    //! Returns number of layers in multilayer
    size_t getNumberOfLayers() const;

    //! Returns number of interfaces in multilayer
    size_t getNumberOfInterfaces() const;

    //! Adds object to multilayer, overrides from ISample
    void addLayer(const Layer& p_child);

    //! Adds layer with top roughness
    void addLayerWithTopRoughness(const Layer& layer, const LayerRoughness& roughness);

    //! Returns layer with given index
    const Layer *getLayer(size_t i_layer) const;

    //! Returns layer with given index
    const LayerInterface *getLayerInterface(size_t i_interface) const;

    //! Returns z-coordinate of the layer's bottom
    double getLayerBottomZ(size_t i_layer) const;

    //! Returns thickness of layer
    double getLayerThickness(size_t i_layer) const;

    //! Returns top interface of layer
    const LayerInterface *getLayerTopInterface(size_t i_layer) const;

    //! Returns bottom interface of layer
    const LayerInterface *getLayerBottomInterface(size_t i_layer) const;

    //! Destructs allocated objects
    void clear();

    //! Returns alone of multilayer with clones of all layers and recreated
    //! interfaces between layers
    virtual MultiLayer *clone() const;

    //! Returns a clone with inverted magnetic fields
    virtual MultiLayer *cloneInvertB() const;

    //! Sets cross correlation length of roughnesses between interfaces
    void setCrossCorrLength(double crossCorrLength);

    //! Returns cross correlation length of roughnesses between interfaces
    double getCrossCorrLength() const;

    ///! correlation function of roughnesses between the interfaces
    //double getCrossCorrFun(const kvector_t k, int j, int k) const;

    //! Fourier transform of the correlation function of roughnesses between
    //! the interfaces
    double getCrossCorrSpectralFun(
        const kvector_t kvec, size_t j, size_t k) const;

    //! Sets thickness of layer.
    void setLayerThickness(size_t i_layer, double thickness);

    //! Prints class
    friend std::ostream& operator << (std::ostream& ostr, const MultiLayer& m)
    { m.print(ostr); return ostr; }

    //! look for the presence of DWBA terms (e.g. included particles) and return
    //! ISimulation if needed
    virtual MultiLayerDWBASimulation *createDWBASimulation() const;

    //! returns layer index
    int getIndexOfLayer(const Layer *layer) const;

    //! returns true if contains magnetic materials and matrix calculations are required
    bool requiresMatrixRTCoefficients() const;

    //! returns layer index corresponding to given global z coordinate
    size_t zToLayerIndex(double z_value);

protected:
    //! Registers some class members for later access via parameter pool
    virtual void init_parameters();
    //! Prints class
    void print(std::ostream& ostr) const;

private:
    //! Adds the layer with simultaneous registration in parent class
    void addAndRegisterLayer(Layer *child);

    //! Adds the interface with simultaneous registration in parent class
    void addAndRegisterInterface(LayerInterface *child);

    void setNLayersInLayers() const;

    //! Checks index of layer w.r.t. vector length
    size_t check_layer_index(size_t i_layer) const;

    //! Checks index of interface w.r.t. vector length
    size_t check_interface_index(size_t i_interface) const;

    //! stack of layers [nlayers]
    std::vector<Layer *> m_layers;
    //! coordinate of layer's bottoms [nlayers]
    std::vector<double > m_layers_z;
    //! stack of layer interfaces [nlayers-1]
    std::vector<LayerInterface *> m_interfaces;
    //! cross correlation length (in z direction) between different layers
    double m_crossCorrLength;
};

inline size_t MultiLayer::getNumberOfLayers() const
{
    return m_layers.size();
}

inline size_t MultiLayer::getNumberOfInterfaces() const
{
    return m_interfaces.size();
}

inline const Layer *MultiLayer::getLayer(size_t i_layer) const
{
    return m_layers[ check_layer_index(i_layer) ];
}

inline const LayerInterface *MultiLayer::getLayerInterface(size_t i_interface) const
{
    return m_interfaces[ check_interface_index(i_interface) ];
}

inline double MultiLayer::getLayerBottomZ(size_t i_layer) const
{
    return m_layers_z[ check_layer_index(i_layer) ];
}

inline double MultiLayer::getLayerThickness(size_t i_layer) const
{
    return m_layers[ check_layer_index(i_layer) ]->getThickness();
}

inline void MultiLayer::setCrossCorrLength(double crossCorrLength)
{
    if(crossCorrLength<0.0)
        throw LogicErrorException("Attempt to set crossCorrLength to negative value");
    m_crossCorrLength = crossCorrLength;
}

inline double MultiLayer::getCrossCorrLength() const
{
    return m_crossCorrLength;
}

#endif // MULTILAYER_H


