#include "athlete.h"
#include "QString"
#include "QVariant"

athlete_t::athlete_t (const std::string &name,
           int age,
           gender_t gender,
           double back,
           double breast,
           double fly,
           double free):
  m_name (name), m_age (age), m_gender (gender), m_back (back), m_breast (breast),
  m_fly (fly), m_free (free)
{
}


