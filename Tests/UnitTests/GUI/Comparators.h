#ifndef COMPARATORS_H
#define COMPARATORS_H

//! Helper class to register custom variants comparators and to report
//! unit tests if comparators should be tested.

class Comparators
{
public:
    static void registerComparators();
    static bool registered();

private:
    static bool m_is_registered;
};

#endif  // COMPARATORS_H
