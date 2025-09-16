#ifndef ATHLETES_WIDGET_H
#define ATHLETES_WIDGET_H

#include <QtWidgets/QWidget>
//class athletes_model;
#include "athletes_model.h"
class project;

class QPushButton;

class athletes_widget : public QWidget
{
    Q_OBJECT
public:
    athletes_widget (project &proj, QWidget *parent = 0);

private:
    athletes_model *m_model = nullptr;
    QPushButton *m_add_but = nullptr;
    QPushButton *m_del_but = nullptr;
};

#endif // ATHLETES_WIDGET_H
