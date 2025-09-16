#include "relay_calculator.h"
#include <algorithm>
#include <cmath>
#include "project.h"
#include "team.h"
#include "relay_properties_enums.h"

bool compare_teams (const team_t &a, const team_t &b)
{
  if (a.get_points () > b.get_points ())
    return true;
  else if (a.get_points () == b.get_points () &&
           a.get_age () >= b.get_age ())
    return true;

  return false;
}

bool compare (const team_item *a, const team_item *b)
{
  return compare_teams (a->get_team (), b->get_team ());
}

bool compare1 (const std::unique_ptr<team_item> &a, const std::unique_ptr<team_item> &b)
{
  return compare (a.get(), b.get());
}

bool compare2 (const std::unique_ptr<team_item> &a, const std::unique_ptr<team_item> &b)
{
  if (a->get_total_points () > b->get_total_points ())
    return true;

  else if (a->get_total_points () == b->get_total_points () &&
           a->get_team ().get_age () >= b->get_team ().get_age ())
    return true;

  return false;
}

std::vector<int> vector_minus (const std::vector<int> &ids1, const std::vector<int> &ids2)
{
  std::vector<int> result;

  for (auto &id1: ids1)
    {
      bool add = true;
      for (auto &id2: ids2)
        {
          if (id1 == id2)
            {
              add = false;
              break;
            }
        }
      if (add)
        result.push_back (id1);
    }

  return result;
}

std::vector<int> vector_plus (const std::vector<int> &ids1, const std::vector<int> &ids2)
{
  std::vector<int> result;

  for (auto &id1: ids1)
    {
      result.push_back (id1);
    }
  for (auto &id2: ids2)
    {
      result.push_back (id2);
    }

  return result;
}

/////////////////////////////////////////////////////////////////////////////////////

sample_generator::sample_generator (std::vector<int>::const_iterator first_it,
                                    std::vector<int>::const_iterator last_it,
                                    int sample_size)
  : m_cur_it (first_it), m_last_it (last_it), m_sample_size (sample_size)
{
  if (m_sample_size > 1)
    m_cur_sample.reset (new sample_generator (++first_it, last_it, m_sample_size - 1));
}

bool sample_generator::next ()
{
  if (!m_cur_sample || !m_cur_sample->next ())
    {
      ++m_cur_it;
      if (m_cur_it == m_last_it)
        return false;
      if (m_cur_sample)
        {
          m_cur_sample.reset (new sample_generator (m_cur_it + 1, m_last_it, m_sample_size - 1));
          if (!m_cur_sample->is_valid ())
            return false;
        }
    }

  return true;
}

std::vector<int> sample_generator::get () const
{
  std::vector<int> result;

  if (m_cur_sample)
    result = m_cur_sample->get ();

  result.insert (result.begin (), *m_cur_it);
  return result;
}

bool sample_generator::is_valid () const
{
  return (m_cur_it != m_last_it && (!m_cur_sample || m_cur_sample->is_valid ()));
}

/////////////////////////////////////////////////////////////////////////////////////

relay_calculator::relay_calculator (project &proj,
                                    type_of_relay relay_type,
                                    gender_type_of_relay gender_type)

  : m_project (proj), m_relay_type (relay_type), m_gender_type (gender_type)
{
}

void relay_calculator::calculate (team_item *parent_item)
{
  if (parent_item && parent_item->children_is_calculated ())
    return;

  auto athlete_m_ids = make_gender_ids (gender_t::male);
  auto athlete_f_ids = make_gender_ids (gender_t::female);

  for (const auto *item = parent_item; item != nullptr; item = item->get_parent ())
    {
      athlete_m_ids = vector_minus (athlete_m_ids, item->get_team ().get_members ());
      athlete_f_ids = vector_minus (athlete_f_ids, item->get_team ().get_members ());
    }

  std::vector<std::unique_ptr<team_item>> results;

  if (m_gender_type == gender_type_of_relay::mixed)
    results = generate_mixed_teams (athlete_m_ids, athlete_f_ids, parent_item);
  else if (m_gender_type == gender_type_of_relay::male)
    results = (generate_teams (athlete_m_ids, parent_item));
  else
    results = (generate_teams (athlete_f_ids, parent_item));

  if (!parent_item)
    m_project.set_team_tree (std::move (results));
  else
    {
      parent_item->set_children (std::move (results));
      //parent_item->set_children_is_calculated ();
    }
}

std::vector<std::unique_ptr<team_item>> relay_calculator::generate_teams (const std::vector<int> &athlete_ids,
                                                                          team_item *parent_item)
{
  sample_generator s_gen (athlete_ids.begin (), athlete_ids.end (), 4);
  std::vector<std::unique_ptr<team_item>> results;

  for ( ;s_gen.is_valid (); s_gen.next ())
    {
      auto sample = s_gen.get ();
      std::unique_ptr<team_item> item (create_team_item (sample, parent_item));
      if (!item)
        continue;
      //if (parent_item && !compare (parent_item, item.get()))
      //  {
      //    broken_branch = true;
      //    return {};
      //  }

//      item->set_children (generate_teams (vector_minus (athlete_ids, sample), item.get (), broken_branch));
//      item->set_row (results.size ());
      results.push_back (std::move (item));
    }

  std::sort (results.begin(), results.end(), compare1);

  for (int i = 0; i < (int)results.size (); i++)
    {
      results[i]->set_row (i);
    }

  return results;
}

std::vector<std::unique_ptr<team_item>> relay_calculator::generate_mixed_teams (const std::vector<int> &athlete_m_ids,
                                                              const std::vector<int> &athlete_f_ids,
                                                              team_item *parent_item)
{
  sample_generator s_gen_m (athlete_m_ids.begin (), athlete_m_ids.end (), 2);
  std::vector<std::unique_ptr<team_item>> results;

  for ( ;s_gen_m.is_valid (); s_gen_m.next ())
    {
      sample_generator s_gen_f (athlete_f_ids.begin (), athlete_f_ids.end (), 2);
      for ( ;s_gen_f.is_valid (); s_gen_f.next ())
        {
          auto sample_m = s_gen_m.get ();
          auto sample_f = s_gen_f.get ();
          std::unique_ptr<team_item> item (create_team_item (vector_plus (sample_m, sample_f), parent_item));
          if (!item)
            continue;
//          if (parent_item && !compare (parent_item, item.get()))
//            {
//              broken_branch = true;
//              return {};
//            }

//          item->set_children (generate_mixed_teams (
//                vector_minus (athlete_m_ids, sample_m),
//                vector_minus (athlete_f_ids, sample_f),
//                item.get (), broken_branch));

 //        if (!broken_branch)
 //          {
              item->set_row (results.size ());
              results.push_back (std::move (item));
 //           }
        }
    }

  std::sort (results.begin(), results.end(), compare1);

  for (int i = 0; i < (int)results.size (); i++)
    {
      results[i]->set_row (i);
    }

  return results;
}


team_item *relay_calculator::create_team_item (const std::vector<int> &sample,
                                               team_item *parent_item) const
{
  if (m_relay_type == type_of_relay::free)
    {
      team_t team (m_project, sample, m_relay_type, m_gender_type);
      if (team.get_time () > novalid_time)
        return nullptr;
      return new team_item ({team}, parent_item);
    }

  // if (relay_type == type_of_relay::medley)
  std::vector<team_t> perm_teams;
  for (auto p_sample = sample; std::next_permutation (p_sample.begin(), p_sample.end()); )
    {
      team_t team (m_project, p_sample, m_relay_type, m_gender_type);
      if (team.get_time () < novalid_time)
        perm_teams.push_back (team);
    }

  if (perm_teams.empty ())
    return nullptr;

  std::sort (perm_teams.begin (), perm_teams.end (), compare_teams);

  return new team_item (std::move (perm_teams), parent_item);
}

std::vector<int> relay_calculator::make_gender_ids (gender_t gender)
{
  std::vector<int> athlete_ids;
  for (int id = 0; id < m_project.size_of_athletes (); id++)
    {
      if (m_project.athlete_is_used (id) && m_project.athlete (id).m_gender == gender)
        athlete_ids.push_back (id);
    }

  return athlete_ids;
}
