#include "athletes_model.h"
#include "athlete.h"
#include "project.h"

athlete_wrapper::athlete_wrapper (std::pair<athlete_t, bool> &athlete):
  m_athlete (athlete)
{
}

QVariant athlete_wrapper::get_data_by_section (int section) const
{
  QVariant res;

  auto convert_to_strng = [](gender_t gender)
    {
      if (gender == gender_t::male)
        return QString ("male");
      else
        return QString ("female");
    };
  switch (section)
    {
    case 0:
      res = {m_athlete.first.m_name.c_str()};
      break;
    case 1:
      res = {convert_to_strng (m_athlete.first.m_gender)};
      break;
    case 2:
      res = {m_athlete.first.m_age};
      break;
    case 3:
      if (m_athlete.first.m_back < novalid_time) res = {m_athlete.first.m_back};
      break;
    case 4:
      if (m_athlete.first.m_breast < novalid_time) res = {m_athlete.first.m_breast};
      break;
    case 5:
      if (m_athlete.first.m_fly < novalid_time) res = {m_athlete.first.m_fly};
      break;
    case 6:
      if (m_athlete.first.m_free < novalid_time) res = {m_athlete.first.m_free};
      break;
    }

  return res;
}

void athlete_wrapper::set_data_by_section (int section, QVariant data)
{
  auto convert_to_time = [](QVariant data)
  {
    if (data.toString () == "")
      return novalid_time;
    return data.toDouble ();
  };

  auto convert_to_gender = [](QVariant data)
  {
    if (data.toString () == "male")
      return gender_t::male;
    else if (data.toString () == "female")
      return gender_t::female;
    return gender_t::male;
  };

  switch (section)
    {
    case 0:
      m_athlete.first.m_name = data.toString ().toStdString ();
      break;
    case 1:
      m_athlete.first.m_gender = convert_to_gender (data);
      break;
    case 2:
      m_athlete.first.m_age = data.toInt ();
      break;
    case 3:
      m_athlete.first.m_back = convert_to_time (data);
      break;
    case 4:
      m_athlete.first.m_breast = convert_to_time (data);
      break;
    case 5:
      m_athlete.first.m_fly = convert_to_time (data);
      break;
    case 6:
      m_athlete.first.m_free = convert_to_time (data);
      break;
    }
}

QString athlete_wrapper::get_string_by_section (int section)
{
  switch (section)
    {
    case 0:
      return {"name"};
    case 1:
      return {"gender"};
    case 2:
      return {"age"};
    case 3:
      return {"back"};
    case 4:
      return {"breast"};
    case 5:
      return {"fly"};
    case 6:
      return {"free"};
    default:
      return {};
    }

  return {};
}

QVariant athlete_wrapper::checked ()
{
  if (m_athlete.second)
    return  Qt::Checked;
  else
    return  Qt::Unchecked;
}

void athlete_wrapper::set_is_checked (QVariant variant)
{
  if (variant == Qt::Checked)
    m_athlete.second = true;
  else
    m_athlete.second = false;
}


athletes_model::athletes_model (project &proj, QObject *parent):
    QAbstractTableModel(parent), m_project (proj)
{
}

athletes_model::~athletes_model ()
{
}

int athletes_model::rowCount (const QModelIndex &parent) const
{
    Q_UNUSED (parent)
    return m_project.size_of_athletes ();
}

int athletes_model::columnCount (const QModelIndex &parent) const
{
    Q_UNUSED (parent)
    return m_column_count;
}

QVariant athletes_model::headerData (int section, Qt::Orientation orientation, int role) const
{
  if (role != Qt::DisplayRole)
      return QVariant();

  if (orientation == Qt::Horizontal)
    return athlete_wrapper::get_string_by_section (section);
  else
    return section;

  return {};
}

QVariant athletes_model::data (const QModelIndex &index, int role) const
{
  if (!index.isValid ())
      return {};

  if (index.column () == 0 && role == Qt::CheckStateRole)
    {
      return athlete_wrapper (m_project.athlete_p (index.row())).checked ();
    }

  if (role == Qt::DisplayRole || role == Qt::EditRole)
    return athlete_wrapper (m_project.athlete_p (index.row())).get_data_by_section (index.column());

  return QVariant ();
}

bool athletes_model::setData (const QModelIndex &index, const QVariant &value, int role)
{
  if (!index.isValid ())
    return false;

  athlete_wrapper athlete = athlete_wrapper (m_project.athlete_p (index.row()));

  if (index.column () == 0 && role == Qt::CheckStateRole)
    {
      athlete.set_is_checked (value);
      emit dataChanged (index,  index);
      return true;
    }
  if (role == Qt::EditRole)
    {
      athlete_wrapper (m_project.athlete_p (index.row())).set_data_by_section (index.column(), value);
      emit dataChanged (index,  index);
      return true;
    }

  return false;
}

Qt::ItemFlags athletes_model::flags (const QModelIndex &index) const
{
  return //QAbstractItemModel::flags (index)
     Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsUserCheckable;//  Qt::ItemIsSelectable;
}
