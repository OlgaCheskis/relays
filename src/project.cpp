#include "project.h"
#include "athlete.h"

project::project ()
{
  add_athlete ("Мирзабекян Александр", 49, gender_t::male, 35, 36, novalid_time, 28.5);
  add_athlete ("Федоров Владимир", 52, gender_t::male, novalid_time, 36., 33., 30.);
  add_athlete ("Циркин Артем", 37, gender_t::male, novalid_time, 33., 29., 26.);
  add_athlete ("Жигарева Анастасия", 37, gender_t::female, novalid_time, 42, novalid_time, 33.);
  add_athlete ("Ермишин Леонид", 48, gender_t::male, 32, 38, 27.5, 26.5);
  add_athlete ("Кузякин Олег", 58, gender_t::male, 34., 36., 33., 28.5);
  add_athlete ("Лунев Георгий", 47, gender_t::male, 33, novalid_time, 30, 28);
  add_athlete ("Левинас Эдуард", 54, gender_t::male, novalid_time, novalid_time, novalid_time, 28);
  add_athlete ("Сарамутин Юрий", 49, gender_t::male, 35, 33, 30, 28);

}


int project::add_athlete (const std::string &name,
                          int age,
                          gender_t gender,
                          double back,
                          double breast,
                          double fly,
                          double free
             )
{
  athlete_t athlete = {name,
                       age,
                       gender,
                       back,
                       breast,
                       fly,
                       free};

  m_athletes.push_back ({athlete, true});
  return m_athletes.size ();
}

int project::add_temporary_athlete ()
{
  m_athletes.push_back (m_temporary_athlete);
  m_temporary_athlete = {};
  return m_athletes.size ();
}

void project::remove_athlete (int id)
{
//  Q_ASSERT (id >= 0 && id < m_athletes.size ());
  m_athletes.erase (m_athletes.begin () + id);
}

const athlete_t &project::athlete (int id) const
{
  return m_athletes[id].first;
}
//athlete_t &athlete (int id);
bool project::athlete_is_used (int id) const
{
  return m_athletes[id].second;
}

std::pair<athlete_t, bool> &project::athlete_p (int id)
{
  if (id >= (int)m_athletes.size())
    return m_temporary_athlete;

  return m_athletes[id];
}

