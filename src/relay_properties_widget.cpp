#include "relay_properties_widget.h"
#include "project.h"
#include "relay_properties_enums.h"

#include <QtWidgets/QHBoxLayout>
#include <QComboBox>

relay_properties_widget::relay_properties_widget (project &proj, QWidget *parent)
    : QWidget (parent)
{
  auto *main_layout = new QHBoxLayout (this);
  m_pool_length = new QComboBox (this);
  m_gender_type = new QComboBox (this);
  m_relay_type = new QComboBox (this);
  m_relay_distance = new QComboBox (this);
  main_layout->addWidget (m_pool_length);
  main_layout->addWidget (m_gender_type);
  main_layout->addWidget (m_relay_type);
  main_layout->addWidget (m_relay_distance);

  setLayout (main_layout);

  for (auto i = 0; i < (int)type_of_relay::COUNT; i++)
    {
      m_relay_type->addItem (enum_to_string ((type_of_relay)i));
    }

  for (auto i = 0; i < (int)gender_type_of_relay::COUNT; i++)
    {
      m_gender_type->addItem (enum_to_string ((gender_type_of_relay)i));
    }
}

type_of_relay relay_properties_widget::get_type_of_relay ()
{
  auto ind = m_relay_type->currentIndex ();
  return (type_of_relay)ind;
}

gender_type_of_relay relay_properties_widget::get_gender_type_of_relay ()
{
  auto ind = m_gender_type->currentIndex ();
  return (gender_type_of_relay)ind;
}



