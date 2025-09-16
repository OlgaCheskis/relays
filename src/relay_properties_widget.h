#ifndef RELAY_PROPERTIES_WIDGET_H
#define RELAY_PROPERTIES_WIDGET_H

#include "relay_properties_enums.h"
#include <QtWidgets/QWidget>

class project;
class QComboBox;

class relay_properties_widget : public QWidget
{
public:
  relay_properties_widget (project &proj, QWidget *parent = 0);

  type_of_relay get_type_of_relay ();
  gender_type_of_relay get_gender_type_of_relay ();

private:
  QComboBox *m_pool_length = nullptr;
  QComboBox *m_gender_type = nullptr;
  QComboBox *m_relay_type = nullptr;
  QComboBox *m_relay_distance = nullptr;
};

#endif // RELAY_PROPERTIES_WIDGET_H
