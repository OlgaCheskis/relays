#include "relay_widget.h"
#include "relay_item_model.h"
#include "project.h"
#include "relay_properties_widget.h"

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QPushButton>
#include <QtWidgets/QTreeView>
//#include <QtWidgets/QHeaderView>

relay_widget::relay_widget (project &proj, QWidget *parent)
    : QWidget (parent)
{
  m_model = new relay_item_model (proj, this);

  m_tree_view = new QTreeView (this);
  m_tree_view->setModel (m_model);
  m_tree_view->setMinimumWidth (600);
  m_tree_view->setHeaderHidden (false);
  m_model->setParent (m_tree_view);

  auto *main_layout = new QVBoxLayout (this);
  main_layout->addWidget (m_relay_properties_widget = new relay_properties_widget (proj, this));
  main_layout->addWidget (m_tree_view);
  auto calc_but = new QPushButton ("Calculate", this);
  main_layout->addWidget (calc_but);
  QObject::connect(calc_but, &QPushButton::clicked, [this] ()
  {
    m_model->calculate (m_relay_properties_widget->get_type_of_relay (), m_relay_properties_widget->get_gender_type_of_relay ());
    m_tree_view->resizeColumnToContents (0);
  });
//  tree_view->resizeColumnsToContents ();

  setLayout (main_layout);
}


