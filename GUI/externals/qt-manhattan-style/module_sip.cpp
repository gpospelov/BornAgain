#include <boost/python.hpp>
#include <boost/tuple/tuple.hpp>

#include <sip.h>
#include <iostream>
#include <QWidget>
#include <QObject>
#include <QAction>
#include <QIcon>
#include <QString>
#include <QColor>
#include <QWebView>

#include "manhattanstyle.h"
#include "fancytabwidget.h"

using namespace boost::python;

/**
 * Initialize the SIP API
 */
const sipAPIDef *sip_API = 0;

bool init_sip_api()
{
  // import the sip module
  object sip_module = import("sip");
  if (!sip_module.ptr()) {
    std::cout << "Could not import sip python module." << std::endl;
    return false;
  }

  // get the dictionary
  dict sip_dict = extract<dict>(sip_module.attr("__dict__"));
  if (!sip_dict.ptr()) {
    std::cout << "Could not find the __dict__ attribute in the sip python module." << std::endl;
    return false;
  }
  
  // get the _C_API object from the dictionary
  object sip_capi_obj = sip_dict.get("_C_API");
  if (!sip_capi_obj.ptr()) {
    std::cout << "Could not find the _C_API entry in the sip python module dictionary." << std::endl;
    return false;
  }
  
#ifdef SIP_USE_PYCAPSULE
  if (!PyCapsule_IsValid(sip_capi_obj.ptr(), "sip._C_API")) {
#else
  if (!PyCObject_Check(sip_capi_obj.ptr())) {
#endif
    std::cout << "The _C_API object in the sip python module is invalid." << std::endl;
    return false;
  }

#ifdef SIP_USE_PYCAPSULE
  sip_API =
      reinterpret_cast<const sipAPIDef*>(PyCapsule_GetPointer(sip_capi_obj.ptr(),
                                                              "sip._C_API"));
#else
  sip_API =
      reinterpret_cast<const sipAPIDef*>(PyCObject_AsVoidPtr(sip_capi_obj.ptr()));
#endif
  return true;
}

/**
 * MetaData helper templates. While this information is available 
 * (QObject::metaObject) for objects derived from QObject, not 
 * all classes are derived from it. To make all classes work with 
 * the same templates we do it this way.
 * 
 */

// these are used by the toPyQt function,
template <typename T> struct MetaData;

// used by toPyQt(...)
template <> struct MetaData<Manhattan::FancyTabWidget> { static const char* className() { return "QWidget";} };
template <> struct MetaData<ManhattanStyle> { static const char* className() { return "QStyle";} };

template <> struct MetaData<QObject> { static const char* className() { return "QObject";} };
template <> struct MetaData<QWidget> { static const char* className() { return "QWidget";} };
template <> struct MetaData<QIcon> { static const char* className() { return "QIcon";} };
template <> struct MetaData<QColor> { static const char* className() { return "QColor";} };
template <> struct MetaData<QAction> { static const char* className() { return "QAction";} };
template <> struct MetaData<QWebView> { static const char* className() { return "QWebView";} };
//template <> struct MetaData<QString> { static const char* className() { return "QString";} };


/**
 *  QWidget* <--> PyQt object
 *  QAction* <--> PyQt object
 *  ...
 */
template <typename T>
struct QClass_converters
{

  struct QClass_to_PyQt
  {
    static PyObject* convert(const T& object)
    {
#if SIP_API_MAJOR_NR >=4
      const sipTypeDef *type = sip_API->api_find_type(MetaData<T>::className());
#else
      sipWrapperType *type = sip_API->api_find_class(MetaData<T>::className());
#endif
      if (!type)
        return incref(Py_None);
      
#if SIP_API_MAJOR_NR >=4
      PyObject *sip_obj = sip_API->api_convert_from_type((void*)(&object), type, 0);
#else
      PyObject *sip_obj = sip_API->api_convert_from_instance((void*)(&object), type, 0);
#endif
      if (!sip_obj)
        return incref(Py_None);

      return incref(sip_obj);
    }
 
    static PyObject* convert(T* object)
    {
      if (!object)
        return incref(Py_None);
 
#if SIP_API_MAJOR_NR >=4
      const sipTypeDef *type = sip_API->api_find_type(MetaData<T>::className());
#else     
      sipWrapperType *type = sip_API->api_find_class(MetaData<T>::className());
#endif
      if (!type)
        return incref(Py_None);
      
#if SIP_API_MAJOR_NR >=4
      PyObject *sip_obj = sip_API->api_convert_from_type(object, type, 0);
#else
      PyObject *sip_obj = sip_API->api_convert_from_instance(object, type, 0);
#endif
      if (!sip_obj)
        return incref(Py_None);

      return incref(sip_obj);
    }

    static PyObject* convert(const T* object)
    {
      return convert((T*)object);
    }

  };

  static void* QClass_from_PyQt(PyObject *obj_ptr)
  {
#if SIP_API_MAJOR_NR >=4
      std::cout << "XXX 1.1" << std::endl;
    if (!PyObject_TypeCheck(obj_ptr, sip_API->api_wrapper_type)) {
#else
      std::cout << "XXX 1.2" << std::endl;
    if (!sip_API->api_wrapper_check(obj_ptr)) {
#endif
      std::cout << "Error - already set in QClass_from_PyQt.." << std::endl;
      //throw_error_already_set();
    }
    
    // transfer ownership from python to C++
#if SIP_API_MAJOR_NR >=4
    std::cout << "XXX 2.1" << std::endl;
    sip_API->api_transfer_to(obj_ptr, 0);
#else
    sip_API->api_transfer(obj_ptr, 1);
#endif

    // reinterpret to sipWrapper
#if SIP_API_MAJOR_NR >= 4
    sipSimpleWrapper *wrapper = reinterpret_cast<sipSimpleWrapper*>(obj_ptr);
#else
    sipWrapper *wrapper = reinterpret_cast<sipWrapper*>(obj_ptr);
#endif

#if (SIP_API_MAJOR_NR == 8 && SIP_API_MINOR_NR >= 1) || SIP_API_MAJOR_NR > 8
    return sip_API->api_get_address(wrapper);
#elif SIP_API_MAJOR_NR == 8
    return wrapper->data;
#else
    return wrapper->u.cppPtr;
#endif
  }
    
  QClass_converters()
  {
    // example: PyQt object --> C++ pointer
    converter::registry::insert( &QClass_from_PyQt, type_id<T>() );
    // example: const QColor* -> PyQt object
    to_python_converter<const T*, QClass_to_PyQt>();
    // example: QUndoCommand* Extension::performAction(...) --> PyQt object
    to_python_converter<T*, QClass_to_PyQt>();
    // example: QColor GLWidget::background() --> PyQt object
    to_python_converter<T, QClass_to_PyQt>();
  }
  
};

/**
 *  Special case QList<QAction*> --> PyQt object
 */
 struct QList_QAction_to_python_list_PyQt
 {
   typedef QList<QAction*>::const_iterator iter;

   static PyObject* convert(const QList<QAction*> &qList)
   {
 #if SIP_API_MAJOR_NR >=4
     const sipTypeDef *type = sip_API->api_find_type("QAction");
 #else
     sipWrapperType *type = sip_API->api_find_class("QAction");
 #endif
     if (!type)
       return incref(Py_None);

     boost::python::list pyList;

     foreach (QAction *action, qList) {
 #if SIP_API_MAJOR_NR >=4
       PyObject *sip_obj = sip_API->api_convert_from_type(action, type, 0);
 #else
       PyObject *sip_obj = sip_API->api_convert_from_instance(action, type, 0);
 #endif
       if (!sip_obj)
         continue;
       boost::python::object real_obj = object(handle<>(sip_obj));
       pyList.append(real_obj);
     }

     return boost::python::incref(pyList.ptr());
   }
 };

 struct QList_QAction_from_python_list_PyQt
 {
   QList_QAction_from_python_list_PyQt()
   {
     converter::registry::push_back( &convertible, &construct, type_id< QList<QAction*> >() );
   }

   static void* convertible(PyObject *obj_ptr)
   {

     //is this a tuple type?
     if (PyTuple_Check(obj_ptr)) {
       //check the tuple elements... - convert to a boost::tuple object
       boost::python::tuple t( handle<>(borrowed(obj_ptr)) );

       //how many elements are there?
       int n = PyTuple_Size(obj_ptr);

       //can they all be converted to type 'T'?
       for (int i=0; i<n; ++i) {
         if (!boost::python::extract<QAction*>(t[i]).check())
           return 0;
       }

       //the tuple is ok!
       return obj_ptr;
     }
     //is this a list type?
     else if (PyList_Check(obj_ptr)) {
       //check that all of the list elements can be converted to the right type
       boost::python::list l( handle<>(borrowed(obj_ptr)) );

       //how many elements are there?
       int n = PyList_Size(obj_ptr);

       //return obj_ptr;

       //can all of the elements be converted to type 'T'?
       for (int i=0; i<n; ++i) {
         if (!boost::python::extract<QAction*>(l[i]).check())
           return 0;
       }

       //the list is ok!
       return obj_ptr;
     }

     //could not recognise the type...
     return 0;
   }

   static void construct(PyObject *obj_ptr, converter::rvalue_from_python_stage1_data *data)
   {
     if (PyTuple_Check(obj_ptr)) {
       //convert the PyObject to a boost::python::object
       boost::python::tuple t( handle<>(borrowed(obj_ptr)) );

       //locate the storage space for the result
       void* storage = ((converter::rvalue_from_python_storage< QList<QAction*> >*)data)->storage.bytes;

       //create the T container
       new (storage) QList<QAction*>();

       QList<QAction*> *container = static_cast< QList<QAction*>* >(storage);

       //add all of the elements from the tuple - get the number of elements in the tuple
       int n = PyTuple_Size(obj_ptr);

       for (int i=0; i<n; ++i) {
         QAction *action = boost::python::extract<QAction*>(t[i]);
         container->append( action );
       }

       data->convertible = storage;
     }
     else if (PyList_Check(obj_ptr)) {
       //convert the PyObject to a boost::python::object
       boost::python::list l( handle<>(borrowed(obj_ptr)) );

       //locate the storage space for the result
       void* storage = ((converter::rvalue_from_python_storage< QList<QAction*> >*)data)->storage.bytes;

       //create the T container
       new (storage) QList<QAction*>();

       QList<QAction*> *container = static_cast< QList<QAction*>* >(storage);

       //add all of the elements from the tuple - get the number of elements in the tuple
       int n = PyList_Size(obj_ptr);

       for (int i=0; i<n; ++i) {
         QAction *action = boost::python::extract<QAction*>(l[i]);
         container->append( action );
       }

       data->convertible = storage;
     }
   }

 };


/**
 *  The toPyQt implementation
 */
template <typename T>
PyObject* toPyQt(T *obj)
{
  if (!obj) {
    std::cout << "toPyQt: null pointer object";
    return incref(Py_None);
  }
      
#if SIP_API_MAJOR_NR >=4
  const sipTypeDef *type = sip_API->api_find_type(MetaData<T>::className());
#else
  sipWrapperType *type = sip_API->api_find_class(MetaData<T>::className());
#endif
  if (!type) {
    std::cout << "toPyQt: could not determine type";
    return incref(Py_None);
  }
      
#if SIP_API_MAJOR_NR >=4
  PyObject *sip_obj = sip_API->api_convert_from_type(obj, type, 0);
#else
  PyObject *sip_obj = sip_API->api_convert_from_instance(obj, type, 0);
#endif
  if (!sip_obj) {
    return incref(Py_None);
    std::cout << "toPyQt: could not convert";
  }

  return incref(sip_obj);
}

void export_sip()
{
  if (!init_sip_api()) {
    std::cout << "Could not initialize SIP API !" << std::endl;
    return;
  } 

  // toPyQt functions
  def("toPyQt", &toPyQt<Manhattan::FancyTabWidget>);
  def("toPyQt", &toPyQt<ManhattanStyle>);

  // QClass* <--> PyQt objects 
  QClass_converters<QColor>();
  QClass_converters<QObject>();
  QClass_converters<QWidget>(); // from python
  QClass_converters<QAction>(); // from/to python
  QClass_converters<QIcon>();
  QClass_converters<QWebView>();
  //QClass_converters<QString>();
  //QClass_converters<QColor>();


  // special case 
   to_python_converter<QList<QAction*>, QList_QAction_to_python_list_PyQt>();
   QList_QAction_from_python_list_PyQt();
}
