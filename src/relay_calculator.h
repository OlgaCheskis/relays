#ifndef RELAY_CALCULATOR_H
#define RELAY_CALCULATOR_H

#include<vector>
#include<array>
#include<memory>

class project;
class sample_generator;
class team_item;
enum class type_of_relay;
enum class gender_type_of_relay;
enum class gender_t;
enum class compare_type_t
{
  by_time,
  by_points,
};

class sample_generator
{
public:
  sample_generator (std::vector<int>::const_iterator first_it, std::vector<int>::const_iterator last_it, int sample_size);
  bool next ();
  std::vector<int> get () const;
  bool is_valid () const;

private:
  std::vector<int>::const_iterator m_cur_it;
  std::vector<int>::const_iterator m_last_it;
  int m_sample_size = 0;
  std::unique_ptr<sample_generator> m_cur_sample;
};

class relay_calculator
{
public:
  relay_calculator (project &proj,
                    type_of_relay relay_type,
                    gender_type_of_relay gender_type);

  void calculate (team_item *parent_item = nullptr);

private:
  project &m_project;
  type_of_relay m_relay_type;
  gender_type_of_relay m_gender_type;

  std::vector<std::unique_ptr<team_item>> generate_teams (const std::vector<int> &athlete_ids,
                                                          team_item *parent_item);

  std::vector<std::unique_ptr<team_item>> generate_mixed_teams (const std::vector<int> &athlete_m_ids,
                                                                const std::vector<int> &athlete_f_ids,
                                                                team_item *parent_item);

  std::vector<int> make_gender_ids (gender_t gender);
  team_item *create_team_item (const std::vector<int> &sample,
                               team_item *parent_item) const;
};

#endif //RELAY_CALCULATOR_H
