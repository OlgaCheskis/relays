#include "team.h"
#include "athlete.h"
#include "project.h"
#include <QString>
#include <QStringList>

#include <array>
#include "relay_properties_enums.h"


team_t::team_t (const project &proj, const std::vector<int> &members, type_of_relay type, gender_type_of_relay gtype) :
  m_members (members), m_type (type), m_gtype (gtype)
{
  switch (type)
    {
    case type_of_relay::free:
      for (auto &id: m_members)
        {
          m_time += proj.athlete(id).m_free;
          m_age += proj.athlete(id).m_age;
        }
      m_time -= 1.5;
      break;
    case type_of_relay::medley:
      m_time += proj.athlete (m_members[0]).m_back;
      m_time += proj.athlete (m_members[1]).m_breast;
      m_time += proj.athlete (m_members[2]).m_fly;
      m_time += proj.athlete (m_members[3]).m_free;

      for (auto &id: m_members)
        {
          m_age += proj.athlete (id).m_age;
        }
      m_time -= 1.5;
      break;
    case type_of_relay::COUNT:
      break;
    }
 }

QString team_t::get_short_name (const project &proj) const
{
  QString res = QString ("%1:%2:%3").arg (get_points()).arg (m_time).arg (m_age);

  for (auto &id: m_members)
    {
      res += ' ';
      auto str = QString (proj.athlete (id).m_name.c_str()).split(" ")[0];
      res += str;
    }

  return res;
}

QString team_t::get_long_name (const project &proj) const
{
  QString res = QString ("%1:%2\n").arg (m_time).arg (m_age);

  for (auto &id: m_members)
    {
      res += '\n';
      res += proj.athlete (id).m_name.c_str ();
      res += ':';
      res += QString (proj.athlete (id).m_name.c_str())[0];

    }

  return res;
}

int team_t::get_points () const
{
  if (m_points < 0)
    calc_points ();

  return m_points;
}
//25m
//static std::array<std::array<std::array<double,8>,3>,2> base_points =
//{
//  std::array<std::array<double,8>,3>{
//    std::array<double,8>{ 92.78,  92.76,  96.00, 101.16, 107.44, 121.44, 153.96, 323.71},
//    std::array<double,8>{109.80, 110.28, 111.27, 118.84, 128.62, 155.36, 198.08, 311.70},
//    std::array<double,8>{101.21, 100.70, 102.52, 108.16, 115.94, 133.17, 166.57, 280.19}
//  },
//  std::array<std::array<double,8>,3>{
//    std::array<double,8>{102.56, 100.76, 106.38, 112.54, 120.59, 137.45, 177.69, 340.46},
//    std::array<double,8>{120.56, 122.21, 125.08, 134.35, 144.90, 174.94, 229.42, 341.74},
//    std::array<double,8>{110.64, 109.18, 114.28, 120.05, 134.39, 154.01, 196.37, 354.25}
//  }
//};
//50m 2023
//static std::array<std::array<std::array<double,8>,3>,2> base_points =
//{
//  std::array<std::array<double,8>,3>{
//    std::array<double,8>{ 95.33,  94.41,  97.12, 102.02, 108.41, 120.50, 146.83, 286.99},
//    std::array<double,8>{111.26, 110.44, 111.29, 119.31, 126.52, 150.02, 191.19, 348.38},
//    std::array<double,8>{102.82, 102.02, 104.30, 107.94, 116.03, 132.23, 163.43, 239.50},
//  },
//  std::array<std::array<double,8>,3>{
//    std::array<double,8>{105.39, 103.98, 107.63, 114.02, 121.81, 137.99, 173.78, 322.94},
//    std::array<double,8>{124.16, 124.25, 126.82, 133.95, 144.12, 171.04, 213.61, 353.02},
//    std::array<double,8>{115.37, 112.40, 116.49, 122.23, 130.28, 148.89, 191.77, 308.43}
//  }
//};

//50m 2025
static std::array<std::array<std::array<double,8>,3>,2> base_points =
{
  std::array<std::array<double,8>,3>{
    std::array<double,8>{ 95.33,  94.41,  97.12, 102.02, 108.41, 120.50, 146.83, 286.99},
    std::array<double,8>{111.26, 110.44, 111.29, 119.31, 126.52, 150.02, 191.19, 348.38},
    std::array<double,8>{102.82, 102.02, 104.30, 107.94, 116.03, 132.23, 163.43, 239.50},
  },
  std::array<std::array<double,8>,3>{
    std::array<double,8>{105.39, 103.98, 107.63, 114.02, 121.81, 137.99, 173.78, 322.94},
    std::array<double,8>{124.16, 124.25, 126.82, 133.95, 144.12, 171.04, 213.61, 353.02},
    std::array<double,8>{115.37, 112.40, 116.49, 122.23, 130.28, 148.89, 191.77, 308.43}
  }
};

void team_t::calc_points () const
{
  int age_ind = (m_age - 80) / 40;
  auto base_time = base_points[(int)m_type][(int)m_gtype][age_ind];
  auto retime = base_time / m_time;
  auto points = (retime * retime * retime) * 1000.;
  m_points = points;
}

void team_item::calculate_total_points () const
{
  m_total_points = get_team ().get_points ();
  if (m_children.size() > 0)
    m_total_points += m_children[0]->get_team ().get_points ();
}

int team_item::get_total_points () const
{
  if (m_total_points < 0)
    calculate_total_points ();

  return m_total_points;
}
