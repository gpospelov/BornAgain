#include <boost/python.hpp>
using namespace boost::python;

#include <QObject>
#include <QWidget>
#include <QColor>
#include <QIcon>

#include "fancytabwidget.h"
#include "manhattanstyle.h"
#include "stylehelper.h"

#include <iostream>


//void export_sip();
//void export_QString();

long int unwrap(QObject* ptr) {
return reinterpret_cast<long int>(ptr);
}

template <typename T>
T* wrap(long int ptr) {
return reinterpret_cast<T*>(ptr);
}


BOOST_PYTHON_MODULE(libManhattanStyle)
{

    try { import("PyQt4.QtCore"); } catch(...) {} // needed for toPyQt(...)
    try { import("PyQt4.QtGui"); } catch(...) {} // needed for toPyQt(...)
    try { import("PyQt4.QtOpenGL"); } catch(...) {} // needed for toPyQt(...)


    class_<QObject, QObject*, boost::noncopyable>("QObject", no_init)
    .def("unwrap", unwrap)
    .def("wrap", make_function( wrap<QObject>, return_value_policy<return_by_value>() ))
    .staticmethod("wrap");

    class_<QWidget, bases<QObject>, QWidget*, boost::noncopyable>("QWidget")
    .def("wrap", make_function( wrap<QWidget>, return_value_policy<return_by_value>() ))
    .staticmethod("wrap");

    class_<QColor, QColor*, boost::noncopyable>("QColor")
    .def("wrap", make_function( wrap<QColor>, return_value_policy<return_by_value>() ))
    .staticmethod("wrap");

    class_<QString, QString*, boost::noncopyable>("QString")
    .def("wrap", make_function( wrap<QString>, return_value_policy<return_by_value>() ))
    .staticmethod("wrap");

    class_<QIcon, QIcon*, boost::noncopyable>("QIcon")
    .def("wrap", make_function( wrap<QIcon>, return_value_policy<return_by_value>() ))
    .staticmethod("wrap");

    class_<QProxyStyle, QProxyStyle*, boost::noncopyable>("QProxyStyle")
    .def("wrap", make_function( wrap<QProxyStyle>, return_value_policy<return_by_value>() ))
    .staticmethod("wrap");


//    export_sip();
//    export_QString();

    
//    class_<QObject, QObject*, boost::noncopyable>("QObject", no_init)
//    ;

//    class_<QWidget, bases<QObject>, QWidget*, boost::noncopyable>("QWidget")
//    ;
        
    class_<Manhattan::FancyTabWidget, bases<QWidget>, Manhattan::FancyTabWidget*, boost::noncopyable>("FancyTabWidget")
            .def("insertTab",&Manhattan::FancyTabWidget::insertTab)
    ;


    class_<ManhattanStyle, bases<QProxyStyle>, ManhattanStyle*, boost::noncopyable >("ManhattanStyle", init<QString>())
    ;


//    class_<Manhattan::FancyTabWidget, boost::noncopyable, std::auto_ptr<Manhattan::FancyTabWidget> >("FancyTabWidget")
//        .def("insertTab",&Manhattan::FancyTabWidget::insertTab)
//    ;

//    //    class_<Manhattan::FancyTabWidget, bases<QWidget>, Manhattan::FancyTabWidget*, boost::noncopyable>("FancyTabWidget")
//    class_<ManhattanStyle, ManhattanStyle*, boost::noncopyable >("ManhattanStyle", init<QString>())
//    //class_<ManhattanStyle, boost::noncopyable, std::auto_ptr<ManhattanStyle> >("ManhattanStyle", init<QString>())
//    ;

    class_< Manhattan::Utils::StyleHelper >( "StyleHelper" )
        .def("setBaseColor",&Manhattan::Utils::StyleHelper::setBaseColor)
        .staticmethod( "setBaseColor" );
////    .def(
////        "setBaseColor"
////        , (void (*)( const QColor &))( &Manhattan::Utils::StyleHelper::setBaseColor )
////        , ( arg("color") ) )
////    .staticmethod( "setBaseColor" );

}
