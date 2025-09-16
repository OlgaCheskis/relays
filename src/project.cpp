#include "project.h"
#include "athlete.h"

project::project ()
{

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

const athlete_t &project::athlete (int id) const
{
  return m_athletes[id].first;
}
//athlete_t &athlete (int id);
bool project::athlete_is_used (int id) const
{
  return m_athletes[id].second;
}
