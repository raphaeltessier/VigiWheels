// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from interfaces:msg/FireSensor.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "interfaces/msg/detail/fire_sensor__struct.h"
#include "interfaces/msg/detail/fire_sensor__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool interfaces__msg__fire_sensor__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[39];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("interfaces.msg._fire_sensor.FireSensor", full_classname_dest, 38) == 0);
  }
  interfaces__msg__FireSensor * ros_message = _ros_message;
  {  // ir_sensor1
    PyObject * field = PyObject_GetAttrString(_pymsg, "ir_sensor1");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->ir_sensor1 = (int16_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // ir_sensor2
    PyObject * field = PyObject_GetAttrString(_pymsg, "ir_sensor2");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->ir_sensor2 = (int16_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // ir_sensor3
    PyObject * field = PyObject_GetAttrString(_pymsg, "ir_sensor3");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->ir_sensor3 = (int16_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // ir_sensor4
    PyObject * field = PyObject_GetAttrString(_pymsg, "ir_sensor4");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->ir_sensor4 = (int16_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // smoke_sensor1
    PyObject * field = PyObject_GetAttrString(_pymsg, "smoke_sensor1");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->smoke_sensor1 = (int16_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // smoke_sensor2
    PyObject * field = PyObject_GetAttrString(_pymsg, "smoke_sensor2");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->smoke_sensor2 = (int16_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * interfaces__msg__fire_sensor__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of FireSensor */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("interfaces.msg._fire_sensor");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "FireSensor");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  interfaces__msg__FireSensor * ros_message = (interfaces__msg__FireSensor *)raw_ros_message;
  {  // ir_sensor1
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->ir_sensor1);
    {
      int rc = PyObject_SetAttrString(_pymessage, "ir_sensor1", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // ir_sensor2
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->ir_sensor2);
    {
      int rc = PyObject_SetAttrString(_pymessage, "ir_sensor2", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // ir_sensor3
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->ir_sensor3);
    {
      int rc = PyObject_SetAttrString(_pymessage, "ir_sensor3", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // ir_sensor4
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->ir_sensor4);
    {
      int rc = PyObject_SetAttrString(_pymessage, "ir_sensor4", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // smoke_sensor1
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->smoke_sensor1);
    {
      int rc = PyObject_SetAttrString(_pymessage, "smoke_sensor1", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // smoke_sensor2
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->smoke_sensor2);
    {
      int rc = PyObject_SetAttrString(_pymessage, "smoke_sensor2", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
