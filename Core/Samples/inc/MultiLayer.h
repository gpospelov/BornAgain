#ifndef MULTILAYER_H
#define MULTILAYER_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   MultiLayer.h
//! @brief  Definition of MultiLayer class
//! @author Scientific Computing Group at FRM II
//! @date   01.04.2012

#include <vector>
#include "ICompositeSample.h"
#include "Layer.h"
#include "LayerInterface.h"
#include "LayerRoughness.h"
#include "MultiLayerDWBASimulation.h"


//- -------------------------------------------------------------------
//! @class MultiLayer
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
//!
//- -------------------------------------------------------------------
class MultiLayer : public ICompositeSample
{
public:
    MultiLayer();
    ~MultiLayer();

    //! return number of layers in multilayer
    inline size_t getNumberOfLayers() const { return m_layers.size(); }

    //! return number of interfaces in multilayer
    inline size_t getNumberOfInterfaces() const { return m_interfaces.size(); }

    //! add object to multilayer, overrides from ISample
    void addLayer(const Layer &p_child);

    //! add layer with top roughness
    void addLayerWithTopRoughness(const Layer &layer, const LayerRoughness &roughness);

    //! return layer with given index
    inline const Layer *getLayer(size_t i_layer) const { return m_layers[ check_layer_index(i_layer) ]; }

    //! return layer with given index
    inline const LayerInterface *getLayerInterface(size_t i_interface) const { return m_interfaces[ check_interface_index(i_interface) ]; }

    //! return z-coordinate of the layer's bottom
    inline double getLayerBottomZ(size_t i_layer) const { return m_layers_z[ check_layer_index(i_layer) ]; }

    //! return thickness of layer
    inline double getLayerThickness(size_t i_layer) const { return m_layers[ check_layer_index(i_layer) ]->getThickness(); }

    //! return top interface of layer
    const LayerInterface *getLayerTopInterface(size_t i_layer) const;

    //! return bottom interface of layer
    const LayerInterface *getLayerBottomInterface(size_t i_layer) const;

    //! destruct allocated objects
    void clear();

    //! return clone of multilayer with clones of all layers and recreated interfaces between layers
    virtual MultiLayer *clone() const;

    //! set cross correlation length of roughnesses between interfaces
    inline void   setCrossCorrLength(double crossCorrLength) { crossCorrLength!=0 ? m_crossCorrLength = crossCorrLength : throw LogicErrorException("Attempt to set crossCorrLength to zero"); }

    //! return cross correlation length of roughnesses between interfaces
    inline double getCrossCorrLength() const { return m_crossCorrLength; }

    ///! correlation function of roughnesses between the interfaces
    //double getCrossCorrFun(const kvector_t &k, int j, int k) const;

    //! fourier transform of the correlation function of roughnesses between the interfaces
    double getCrossCorrSpectralFun(const kvector_t &kvec, size_t j, size_t k) const;

    //! change thickness of layer
    void setLayerThickness(size_t i_layer, double thickness);

    //! print class
    friend std::ostream &operator<<(std::ostream &ostr, const MultiLayer &m) { m.print(ostr); return ostr; }

    //! look for the presence of DWBA terms (e.g. included particles) and return ISimulation if needed
    virtual MultiLayerDWBASimulation *createDWBASimulation() const;

private:
    //! copy constructor and assignment operator are hidden since there is a clone method
    MultiLayer(const MultiLayer &);
    MultiLayer &operator=(const MultiLayer &);

    //! adding the layer with simultaneous registration in parent class
    void addAndRegisterLayer(Layer *child)
    {
        m_layers.push_back(child);
        registerChild(child);
    }

    //! adding the interface with simultaneous registration in parent class
    void addAndRegisterInterface(LayerInterface *child)
    {
        m_interfaces.push_back(child);
        registerChild(child);
    }

    //! check index of layer w.r.t. vector length
    inline size_t check_layer_index(size_t i_layer) const { return i_layer < m_layers.size() ? i_layer : throw OutOfBoundsException("Layer index is out of bounds"); }

    //! check index of interface w.r.t. vector length
    inline size_t check_interface_index(size_t i_interface) const { return i_interface < m_interfaces.size() ? i_interface : throw OutOfBoundsException("Interface index is out of bounds"); }

    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

    //! print class
    void print(std::ostream &ostr) const;

    std::vector<Layer *> m_layers;                ///< stack of layers [nlayers]
    std::vector<double > m_layers_z;              ///< coordinate of layer's bottoms [nlayers]
    std::vector<LayerInterface *> m_interfaces;   ///< stack of layer interfaces [nlayers-1]
    double m_crossCorrLength;                     //!< cross correlation length (in z direction) between different layers
};

#endif // MULTILAYER_H

