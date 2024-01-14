# generated from rosidl_generator_py/resource/_idl.py.em
# with input from interfaces:msg/FireSensor.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_FireSensor(type):
    """Metaclass of message 'FireSensor'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'interfaces.msg.FireSensor')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__fire_sensor
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__fire_sensor
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__fire_sensor
            cls._TYPE_SUPPORT = module.type_support_msg__msg__fire_sensor
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__fire_sensor

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class FireSensor(metaclass=Metaclass_FireSensor):
    """Message class 'FireSensor'."""

    __slots__ = [
        '_ir_sensor1',
        '_ir_sensor2',
        '_ir_sensor3',
        '_ir_sensor4',
        '_smoke_sensor1',
        '_smoke_sensor2',
    ]

    _fields_and_field_types = {
        'ir_sensor1': 'int16',
        'ir_sensor2': 'boolean',
        'ir_sensor3': 'int16',
        'ir_sensor4': 'boolean',
        'smoke_sensor1': 'int16',
        'smoke_sensor2': 'int16',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int16'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('int16'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('int16'),  # noqa: E501
        rosidl_parser.definition.BasicType('int16'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.ir_sensor1 = kwargs.get('ir_sensor1', int())
        self.ir_sensor2 = kwargs.get('ir_sensor2', bool())
        self.ir_sensor3 = kwargs.get('ir_sensor3', int())
        self.ir_sensor4 = kwargs.get('ir_sensor4', bool())
        self.smoke_sensor1 = kwargs.get('smoke_sensor1', int())
        self.smoke_sensor2 = kwargs.get('smoke_sensor2', int())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.ir_sensor1 != other.ir_sensor1:
            return False
        if self.ir_sensor2 != other.ir_sensor2:
            return False
        if self.ir_sensor3 != other.ir_sensor3:
            return False
        if self.ir_sensor4 != other.ir_sensor4:
            return False
        if self.smoke_sensor1 != other.smoke_sensor1:
            return False
        if self.smoke_sensor2 != other.smoke_sensor2:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def ir_sensor1(self):
        """Message field 'ir_sensor1'."""
        return self._ir_sensor1

    @ir_sensor1.setter
    def ir_sensor1(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'ir_sensor1' field must be of type 'int'"
            assert value >= -32768 and value < 32768, \
                "The 'ir_sensor1' field must be an integer in [-32768, 32767]"
        self._ir_sensor1 = value

    @builtins.property
    def ir_sensor2(self):
        """Message field 'ir_sensor2'."""
        return self._ir_sensor2

    @ir_sensor2.setter
    def ir_sensor2(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'ir_sensor2' field must be of type 'bool'"
        self._ir_sensor2 = value

    @builtins.property
    def ir_sensor3(self):
        """Message field 'ir_sensor3'."""
        return self._ir_sensor3

    @ir_sensor3.setter
    def ir_sensor3(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'ir_sensor3' field must be of type 'int'"
            assert value >= -32768 and value < 32768, \
                "The 'ir_sensor3' field must be an integer in [-32768, 32767]"
        self._ir_sensor3 = value

    @builtins.property
    def ir_sensor4(self):
        """Message field 'ir_sensor4'."""
        return self._ir_sensor4

    @ir_sensor4.setter
    def ir_sensor4(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'ir_sensor4' field must be of type 'bool'"
        self._ir_sensor4 = value

    @builtins.property
    def smoke_sensor1(self):
        """Message field 'smoke_sensor1'."""
        return self._smoke_sensor1

    @smoke_sensor1.setter
    def smoke_sensor1(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'smoke_sensor1' field must be of type 'int'"
            assert value >= -32768 and value < 32768, \
                "The 'smoke_sensor1' field must be an integer in [-32768, 32767]"
        self._smoke_sensor1 = value

    @builtins.property
    def smoke_sensor2(self):
        """Message field 'smoke_sensor2'."""
        return self._smoke_sensor2

    @smoke_sensor2.setter
    def smoke_sensor2(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'smoke_sensor2' field must be of type 'int'"
            assert value >= -32768 and value < 32768, \
                "The 'smoke_sensor2' field must be an integer in [-32768, 32767]"
        self._smoke_sensor2 = value
