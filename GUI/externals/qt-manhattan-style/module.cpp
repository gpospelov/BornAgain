#include <boost/python.hpp>
using namespace boost::python;

#include "fancytabwidget.h"
#include "manhattanstyle.h"
#include "stylehelper.h"

#include <iostream>


void export_sip();
void export_QString();

BOOST_PYTHON_MODULE(libManhattanStyle)
{

    try { import("PyQt4.QtCore"); } catch(...) {} // needed for toPyQt(...)
    try { import("PyQt4.QtGui"); } catch(...) {} // needed for toPyQt(...)
    try { import("PyQt4.QtOpenGL"); } catch(...) {} // needed for toPyQt(...)

    export_sip();
    export_QString();
    
//    class_<QObject, QObject*, boost::noncopyable>("QObject", no_init)
//    ;

//    class_<QWidget, bases<QObject>, QWidget*, boost::noncopyable>("QWidget")
//    ;
        
//    class_<Manhattan::FancyTabWidget, bases<QWidget>, Manhattan::FancyTabWidget*, boost::noncopyable>("FancyTabWidget")
//            .def("insertTab",&Manhattan::FancyTabWidget::insertTab)
//    ;


    class_<Manhattan::FancyTabWidget, boost::noncopyable, std::auto_ptr<Manhattan::FancyTabWidget> >("FancyTabWidget")
        .def("insertTab",&Manhattan::FancyTabWidget::insertTab)
    ;

    //    class_<Manhattan::FancyTabWidget, bases<QWidget>, Manhattan::FancyTabWidget*, boost::noncopyable>("FancyTabWidget")
    class_<ManhattanStyle, ManhattanStyle*, boost::noncopyable >("ManhattanStyle", init<QString>())
    //class_<ManhattanStyle, boost::noncopyable, std::auto_ptr<ManhattanStyle> >("ManhattanStyle", init<QString>())
    ;

    class_< Manhattan::Utils::StyleHelper, Manhattan::Utils::StyleHelper*, boost::noncopyable >( "StyleHelper" )
        .def("setBaseColor",&Manhattan::Utils::StyleHelper::setBaseColor).staticmethod( "setBaseColor" )
    ;
//        .staticmethod( "setBaseColor" );
//    .def(
//        "setBaseColor"
//        , (void (*)( const QColor &))( &Manhattan::Utils::StyleHelper::setBaseColor )
//        , ( arg("color") ) )
//    .staticmethod( "setBaseColor" );

}
