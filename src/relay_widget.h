#ifndef RELAY_WIDGET_H
#define RELAY_WIDGET_H

#include <QtWidgets/QWidget>
class relay_item_model;
class project;
class QTreeView;
class relay_properties_widget;

class relay_widget : public QWidget
{
public:
  relay_widget (project &proj, QWidget *parent = 0);

private:
  relay_item_model *m_model = nullptr;
  QTreeView *m_tree_view = nullptr;
  relay_properties_widget *m_relay_properties_widget = nullptr;
};


#endif // RELAY_WIDGET_H
