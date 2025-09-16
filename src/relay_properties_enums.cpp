#include "relay_properties_enums.h"

const char *enum_to_string (pool_length_t type)
{
  switch (type)
    {
      case pool_length_t::short_course:
        return "short course";
      case pool_length_t::long_course:
        return "long course";
      case pool_length_t::COUNT:
        break;
    }
  return "";
}

const char *enum_to_string (type_of_relay type)
{
  switch (type)
    {
      case type_of_relay::free:
        return "free";
      case type_of_relay::medley:
        return "medley";
      case type_of_relay::COUNT:
        break;
    }
  return "";
}

const char *enum_to_string (gender_type_of_relay type)
{
  switch (type)
    {
      case gender_type_of_relay::male:
        return "male";
      case gender_type_of_relay::female:
        return "female";
      case gender_type_of_relay::mixed:
        return "mixed";
      case gender_type_of_relay::COUNT:
        break;
    }
  return "";
}

const char *enum_to_string (relay_distance_t type)
{
  switch (type)
    {
      case relay_distance_t::fifty:
        return "fifty";
      case relay_distance_t::hundred:
        return "hundred";
      case relay_distance_t::two_hundred:
        return "two_hundred";
      case relay_distance_t::COUNT:
        break;
    }
  return "";
}

