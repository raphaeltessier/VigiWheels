// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from interfaces:msg/FireSensor.idl
// generated code does not contain a copyright notice
#include "interfaces/msg/detail/fire_sensor__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
interfaces__msg__FireSensor__init(interfaces__msg__FireSensor * msg)
{
  if (!msg) {
    return false;
  }
  // ir_sensor1
  // ir_sensor2
  // ir_sensor3
  // ir_sensor4
  // smoke_sensor1
  // smoke_sensor2
  return true;
}

void
interfaces__msg__FireSensor__fini(interfaces__msg__FireSensor * msg)
{
  if (!msg) {
    return;
  }
  // ir_sensor1
  // ir_sensor2
  // ir_sensor3
  // ir_sensor4
  // smoke_sensor1
  // smoke_sensor2
}

bool
interfaces__msg__FireSensor__are_equal(const interfaces__msg__FireSensor * lhs, const interfaces__msg__FireSensor * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // ir_sensor1
  if (lhs->ir_sensor1 != rhs->ir_sensor1) {
    return false;
  }
  // ir_sensor2
  if (lhs->ir_sensor2 != rhs->ir_sensor2) {
    return false;
  }
  // ir_sensor3
  if (lhs->ir_sensor3 != rhs->ir_sensor3) {
    return false;
  }
  // ir_sensor4
  if (lhs->ir_sensor4 != rhs->ir_sensor4) {
    return false;
  }
  // smoke_sensor1
  if (lhs->smoke_sensor1 != rhs->smoke_sensor1) {
    return false;
  }
  // smoke_sensor2
  if (lhs->smoke_sensor2 != rhs->smoke_sensor2) {
    return false;
  }
  return true;
}

bool
interfaces__msg__FireSensor__copy(
  const interfaces__msg__FireSensor * input,
  interfaces__msg__FireSensor * output)
{
  if (!input || !output) {
    return false;
  }
  // ir_sensor1
  output->ir_sensor1 = input->ir_sensor1;
  // ir_sensor2
  output->ir_sensor2 = input->ir_sensor2;
  // ir_sensor3
  output->ir_sensor3 = input->ir_sensor3;
  // ir_sensor4
  output->ir_sensor4 = input->ir_sensor4;
  // smoke_sensor1
  output->smoke_sensor1 = input->smoke_sensor1;
  // smoke_sensor2
  output->smoke_sensor2 = input->smoke_sensor2;
  return true;
}

interfaces__msg__FireSensor *
interfaces__msg__FireSensor__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  interfaces__msg__FireSensor * msg = (interfaces__msg__FireSensor *)allocator.allocate(sizeof(interfaces__msg__FireSensor), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(interfaces__msg__FireSensor));
  bool success = interfaces__msg__FireSensor__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
interfaces__msg__FireSensor__destroy(interfaces__msg__FireSensor * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    interfaces__msg__FireSensor__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
interfaces__msg__FireSensor__Sequence__init(interfaces__msg__FireSensor__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  interfaces__msg__FireSensor * data = NULL;

  if (size) {
    data = (interfaces__msg__FireSensor *)allocator.zero_allocate(size, sizeof(interfaces__msg__FireSensor), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = interfaces__msg__FireSensor__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        interfaces__msg__FireSensor__fini(&data[i - 1]);
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
interfaces__msg__FireSensor__Sequence__fini(interfaces__msg__FireSensor__Sequence * array)
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
      interfaces__msg__FireSensor__fini(&array->data[i]);
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

interfaces__msg__FireSensor__Sequence *
interfaces__msg__FireSensor__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  interfaces__msg__FireSensor__Sequence * array = (interfaces__msg__FireSensor__Sequence *)allocator.allocate(sizeof(interfaces__msg__FireSensor__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = interfaces__msg__FireSensor__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
interfaces__msg__FireSensor__Sequence__destroy(interfaces__msg__FireSensor__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    interfaces__msg__FireSensor__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
interfaces__msg__FireSensor__Sequence__are_equal(const interfaces__msg__FireSensor__Sequence * lhs, const interfaces__msg__FireSensor__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!interfaces__msg__FireSensor__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
interfaces__msg__FireSensor__Sequence__copy(
  const interfaces__msg__FireSensor__Sequence * input,
  interfaces__msg__FireSensor__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(interfaces__msg__FireSensor);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    interfaces__msg__FireSensor * data =
      (interfaces__msg__FireSensor *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!interfaces__msg__FireSensor__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          interfaces__msg__FireSensor__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!interfaces__msg__FireSensor__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
