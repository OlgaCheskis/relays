#ifndef ATHLETE_H
#define ATHLETE_H

#include <string>
#include <optional>
class QVariant;
class QString;

const double novalid_time = 1000;
enum class gender_t
{
  male,
  female,
};

struct athlete_t
{
  athlete_t (const std::string &name,
             int age,
             gender_t gender,
             double back,
             double breast,
             double fly,
             double free);
  athlete_t () {};

  std::string m_name;
  int m_age = 0;
  gender_t m_gender;
  double m_back = novalid_time;
  double m_breast = novalid_time;
  double m_fly = novalid_time;
  double m_free = novalid_time;
};

#endif //ATHLETE_H

