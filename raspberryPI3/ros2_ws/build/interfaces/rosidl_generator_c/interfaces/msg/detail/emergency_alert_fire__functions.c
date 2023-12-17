// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from interfaces:msg/EmergencyAlertFire.idl
// generated code does not contain a copyright notice
#include "interfaces/msg/detail/emergency_alert_fire__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
interfaces__msg__EmergencyAlertFire__init(interfaces__msg__EmergencyAlertFire * msg)
{
  if (!msg) {
    return false;
  }
  // fire_detected
  // ir_front_right
  // ir_front_left
  // ir_rear_right
  // ir_rear_left
  // smoke_left
  // smoke_right
  return true;
}

void
interfaces__msg__EmergencyAlertFire__fini(interfaces__msg__EmergencyAlertFire * msg)
{
  if (!msg) {
    return;
  }
  // fire_detected
  // ir_front_right
  // ir_front_left
  // ir_rear_right
  // ir_rear_left
  // smoke_left
  // smoke_right
}

bool
interfaces__msg__EmergencyAlertFire__are_equal(const interfaces__msg__EmergencyAlertFire * lhs, const interfaces__msg__EmergencyAlertFire * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // fire_detected
  if (lhs->fire_detected != rhs->fire_detected) {
    return false;
  }
  // ir_front_right
  if (lhs->ir_front_right != rhs->ir_front_right) {
    return false;
  }
  // ir_front_left
  if (lhs->ir_front_left != rhs->ir_front_left) {
    return false;
  }
  // ir_rear_right
  if (lhs->ir_rear_right != rhs->ir_rear_right) {
    return false;
  }
  // ir_rear_left
  if (lhs->ir_rear_left != rhs->ir_rear_left) {
    return false;
  }
  // smoke_left
  if (lhs->smoke_left != rhs->smoke_left) {
    return false;
  }
  // smoke_right
  if (lhs->smoke_right != rhs->smoke_right) {
    return false;
  }
  return true;
}

bool
interfaces__msg__EmergencyAlertFire__copy(
  const interfaces__msg__EmergencyAlertFire * input,
  interfaces__msg__EmergencyAlertFire * output)
{
  if (!input || !output) {
    return false;
  }
  // fire_detected
  output->fire_detected = input->fire_detected;
  // ir_front_right
  output->ir_front_right = input->ir_front_right;
  // ir_front_left
  output->ir_front_left = input->ir_front_left;
  // ir_rear_right
  output->ir_rear_right = input->ir_rear_right;
  // ir_rear_left
  output->ir_rear_left = input->ir_rear_left;
  // smoke_left
  output->smoke_left = input->smoke_left;
  // smoke_right
  output->smoke_right = input->smoke_right;
  return true;
}

interfaces__msg__EmergencyAlertFire *
interfaces__msg__EmergencyAlertFire__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  interfaces__msg__EmergencyAlertFire * msg = (interfaces__msg__EmergencyAlertFire *)allocator.allocate(sizeof(interfaces__msg__EmergencyAlertFire), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(interfaces__msg__EmergencyAlertFire));
  bool success = interfaces__msg__EmergencyAlertFire__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
interfaces__msg__EmergencyAlertFire__destroy(interfaces__msg__EmergencyAlertFire * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    interfaces__msg__EmergencyAlertFire__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
interfaces__msg__EmergencyAlertFire__Sequence__init(interfaces__msg__EmergencyAlertFire__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  interfaces__msg__EmergencyAlertFire * data = NULL;

  if (size) {
    data = (interfaces__msg__EmergencyAlertFire *)allocator.zero_allocate(size, sizeof(interfaces__msg__EmergencyAlertFire), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = interfaces__msg__EmergencyAlertFire__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        interfaces__msg__EmergencyAlertFire__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
interfaces__msg__EmergencyAlertFire__Sequence__fini(interfaces__msg__EmergencyAlertFire__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      interfaces__msg__EmergencyAlertFire__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

interfaces__msg__EmergencyAlertFire__Sequence *
interfaces__msg__EmergencyAlertFire__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  interfaces__msg__EmergencyAlertFire__Sequence * array = (interfaces__msg__EmergencyAlertFire__Sequence *)allocator.allocate(sizeof(interfaces__msg__EmergencyAlertFire__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = interfaces__msg__EmergencyAlertFire__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
interfaces__msg__EmergencyAlertFire__Sequence__destroy(interfaces__msg__EmergencyAlertFire__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    interfaces__msg__EmergencyAlertFire__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
interfaces__msg__EmergencyAlertFire__Sequence__are_equal(const interfaces__msg__EmergencyAlertFire__Sequence * lhs, const interfaces__msg__EmergencyAlertFire__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!interfaces__msg__EmergencyAlertFire__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
interfaces__msg__EmergencyAlertFire__Sequence__copy(
  const interfaces__msg__EmergencyAlertFire__Sequence * input,
  interfaces__msg__EmergencyAlertFire__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(interfaces__msg__EmergencyAlertFire);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    interfaces__msg__EmergencyAlertFire * data =
      (interfaces__msg__EmergencyAlertFire *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!interfaces__msg__EmergencyAlertFire__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          interfaces__msg__EmergencyAlertFire__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!interfaces__msg__EmergencyAlertFire__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
