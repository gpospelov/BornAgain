#include "MaterialBySLDBuilder.h"
#include "MaterialFactoryFuncs.h"
#include "Layer.h"
#include "MultiLayer.h"

MaterialBySLDBuilder::MaterialBySLDBuilder()
    : m_number_of_layers(10)
    , m_si {4.1491e-6, 4.99e+1} // [nm, nm^{-3}]
    , m_ti {-3.438e-6, 5.67e+1} // [nm, nm^{-3}]
    , m_ni {1.3e-5, 9.15e+1}    // [nm, nm^{-3}]
    , m_thick_ti(3.0) // nm
    , m_thick_ni(7.0) //nm
{}

MultiLayer* MaterialBySLDBuilder::buildSample() const
{
    std::unique_ptr<MultiLayer> multi_layer(new MultiLayer());

    Material vacuum_material = MaterialBySLD();
    Material substrate_material = MaterialBySLD("Si_substrate", m_si.product(), 0.0);
    Material ni_material = MaterialBySLD("Ni", m_ni.product(), 0.0);
    Material ti_material = MaterialBySLD("Ti", m_ti.product(), 0.0);

    Layer vacuum_layer(vacuum_material, 0);
    Layer ni_layer(ni_material, m_thick_ni);
    Layer ti_layer(ti_material, m_thick_ti);
    Layer substrate_layer(substrate_material, 0);

    multi_layer->addLayer(vacuum_layer);
    for (size_t i = 0; i < m_number_of_layers; ++i) {
	multi_layer->addLayer(ti_layer);
	multi_layer->addLayer(ni_layer);
    }
    multi_layer->addLayer(substrate_layer);
    return multi_layer.release();
}

