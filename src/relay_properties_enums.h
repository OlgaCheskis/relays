#ifndef RELAY_PROPERTIES_ENUMS_H
#define RELAY_PROPERTIES_ENUMS_H

enum class pool_length_t
{
  short_course = 0,
  long_course,

  COUNT
};

const char *enum_to_string (pool_length_t type);

enum class type_of_relay
{
  free = 0,
  medley,

  COUNT
};

const char *enum_to_string (type_of_relay type);

enum class gender_type_of_relay
{
  male = 0,
  female,
  mixed,

  COUNT
};

const char *enum_to_string (gender_type_of_relay type);

enum class relay_distance_t
{
  fifty = 0,
  hundred,
  two_hundred,

  COUNT
};

const char *enum_to_string (relay_distance_t type);

#endif // RELAY_PROPERTIES_ENUMS_H
