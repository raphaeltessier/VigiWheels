# generated from rosidl_generator_py/resource/_idl.py.em
# with input from interfaces:msg/ObstaclesOrder.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_ObstaclesOrder(type):
    """Metaclass of message 'ObstaclesOrder'."""

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
                'interfaces.msg.ObstaclesOrder')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__obstacles_order
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__obstacles_order
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__obstacles_order
            cls._TYPE_SUPPORT = module.type_support_msg__msg__obstacles_order
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__obstacles_order

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'FRONT_OBJECT__DEFAULT': False,
            'REAR_OBJECT__DEFAULT': False,
        }

    @property
    def FRONT_OBJECT__DEFAULT(cls):
        """Return default value for message field 'front_object'."""
        return False

    @property
    def REAR_OBJECT__DEFAULT(cls):
        """Return default value for message field 'rear_object'."""
        return False


class ObstaclesOrder(metaclass=Metaclass_ObstaclesOrder):
    """Message class 'ObstaclesOrder'."""

    __slots__ = [
        '_front_object',
        '_rear_object',
    ]

    _fields_and_field_types = {
        'front_object': 'boolean',
        'rear_object': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.front_object = kwargs.get(
            'front_object', ObstaclesOrder.FRONT_OBJECT__DEFAULT)
        self.rear_object = kwargs.get(
            'rear_object', ObstaclesOrder.REAR_OBJECT__DEFAULT)

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
        if self.front_object != other.front_object:
            return False
        if self.rear_object != other.rear_object:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def front_object(self):
        """Message field 'front_object'."""
        return self._front_object

    @front_object.setter
    def front_object(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'front_object' field must be of type 'bool'"
        self._front_object = value

    @builtins.property
    def rear_object(self):
        """Message field 'rear_object'."""
        return self._rear_object

    @rear_object.setter
    def rear_object(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'rear_object' field must be of type 'bool'"
        self._rear_object = value
