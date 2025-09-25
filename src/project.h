#ifndef PROJECT_H
#define PROJECT_H

#include<string>
#include<vector>

#include "team.h"
#include "athlete.h"

class project
{
public:
  project ();

  int add_athlete (const std::string &name,
               int age,
               gender_t gender,
               double,
               double,
               double,
               double
               );
  int add_temporary_athlete ();
  void remove_athlete (int id);

  //const std::vector<std::pair<athlete_t, bool>> &get_athletes () const {return m_athletes;}
  //std::vector<athlete_t> &get_athletes () {return m_athletes;}

  int size_of_athletes () const {return m_athletes.size ();}
  const std::vector<std::unique_ptr<team_item>> &get_team_tree () const {return m_team_tree;}
  std::vector<std::unique_ptr<team_item>> &get_team_tree () {return m_team_tree;}
  void set_team_tree (std::vector<std::unique_ptr<team_item>> &&teams)
  {
    m_team_tree = std::move (teams);
  }

  const athlete_t &athlete (int id) const;
  bool athlete_is_used (int id) const;
  std::pair<athlete_t, bool> &athlete_p (int id);

private:
  std::pair<athlete_t, bool> m_temporary_athlete = {{}, true};
  std::vector<std::pair<athlete_t, bool>>  m_athletes;
  std::vector<std::unique_ptr<team_item>>  m_team_tree;
};

#endif
