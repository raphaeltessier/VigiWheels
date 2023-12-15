# generated from rosidl_generator_py/resource/_idl.py.em
# with input from interfaces:msg/EmergencyAlertFire.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_EmergencyAlertFire(type):
    """Metaclass of message 'EmergencyAlertFire'."""

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
                'interfaces.msg.EmergencyAlertFire')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__emergency_alert_fire
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__emergency_alert_fire
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__emergency_alert_fire
            cls._TYPE_SUPPORT = module.type_support_msg__msg__emergency_alert_fire
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__emergency_alert_fire

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class EmergencyAlertFire(metaclass=Metaclass_EmergencyAlertFire):
    """Message class 'EmergencyAlertFire'."""

    __slots__ = [
        '_fire_detected',
        '_ir_front_right',
        '_ir_front_left',
        '_ir_rear_right',
        '_ir_rear_left',
    ]

    _fields_and_field_types = {
        'fire_detected': 'boolean',
        'ir_front_right': 'boolean',
        'ir_front_left': 'boolean',
        'ir_rear_right': 'boolean',
        'ir_rear_left': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.fire_detected = kwargs.get('fire_detected', bool())
        self.ir_front_right = kwargs.get('ir_front_right', bool())
        self.ir_front_left = kwargs.get('ir_front_left', bool())
        self.ir_rear_right = kwargs.get('ir_rear_right', bool())
        self.ir_rear_left = kwargs.get('ir_rear_left', bool())

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
        if self.fire_detected != other.fire_detected:
            return False
        if self.ir_front_right != other.ir_front_right:
            return False
        if self.ir_front_left != other.ir_front_left:
            return False
        if self.ir_rear_right != other.ir_rear_right:
            return False
        if self.ir_rear_left != other.ir_rear_left:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def fire_detected(self):
        """Message field 'fire_detected'."""
        return self._fire_detected

    @fire_detected.setter
    def fire_detected(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'fire_detected' field must be of type 'bool'"
        self._fire_detected = value

    @builtins.property
    def ir_front_right(self):
        """Message field 'ir_front_right'."""
        return self._ir_front_right

    @ir_front_right.setter
    def ir_front_right(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'ir_front_right' field must be of type 'bool'"
        self._ir_front_right = value

    @builtins.property
    def ir_front_left(self):
        """Message field 'ir_front_left'."""
        return self._ir_front_left

    @ir_front_left.setter
    def ir_front_left(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'ir_front_left' field must be of type 'bool'"
        self._ir_front_left = value

    @builtins.property
    def ir_rear_right(self):
        """Message field 'ir_rear_right'."""
        return self._ir_rear_right

    @ir_rear_right.setter
    def ir_rear_right(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'ir_rear_right' field must be of type 'bool'"
        self._ir_rear_right = value

    @builtins.property
    def ir_rear_left(self):
        """Message field 'ir_rear_left'."""
        return self._ir_rear_left

    @ir_rear_left.setter
    def ir_rear_left(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'ir_rear_left' field must be of type 'bool'"
        self._ir_rear_left = value
