#include "MaterialBySLDBuilder.h"
#include "MaterialFactoryFuncs.h"
#include "Layer.h"
#include "MultiLayer.h"
#include "Units.h"

MaterialBySLDBuilder::MaterialBySLDBuilder()
    : m_number_of_layers(10)
    , m_si {4.1491e-6, 4.99e+1, 0.171 * Units::barn} // [nm, nm^{-3}, nm^2]
    , m_ti {-3.438e-6, 5.67e+1, 6.09 * Units::barn * 1e+4} // [nm, nm^{-3}, nm^2]
    , m_ni {1.3e-5, 9.15e+1, 4.49 * Units::barn}    // [nm, nm^{-3}, nm^2]
    , m_thick_ti(3.0) // nm
    , m_thick_ni(7.0) //nm
{}

MultiLayer* MaterialBySLDBuilder::buildSample() const
{
    std::unique_ptr<MultiLayer> multi_layer(new MultiLayer());

    Material vacuum_material = MaterialBySLD();
    Material substrate_material = MaterialByAbsCX("Si_substrate", m_si.sld(), m_si.abs_term());
    Material ni_material = MaterialByAbsCX("Ni", m_ni.sld(), m_ni.abs_term());
    Material ti_material = MaterialByAbsCX("Ti", m_ti.sld(), m_ti.abs_term());

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

