#include "Detector.h"
#include "Exceptions.h"

Detector::Detector()
{
}

Detector::~Detector()
{
}

void Detector::addAxis(const NamedVector<double> &axis)
{
	m_axes.push_back(axis);
}

NamedVector<double>& Detector::getAxis(size_t index)
{
	if (isCorrectAxisIndex(index)) {
		return m_axes[index];
	}
	throw OutOfBoundsException("Not so many axes in this detector.");
}

void Detector::clear()
{
    m_axes.clear();
}

