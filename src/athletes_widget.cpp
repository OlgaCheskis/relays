#include "athletes_widget.h"
#include "athletes_model.h"
#include "project.h"

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QHeaderView>

athletes_widget::athletes_widget(project &proj, QWidget *parent)
    : QWidget(parent)
{
    m_model = new athletes_model (proj, this);

    auto *table_view = new QTableView;
    table_view->setModel (m_model);
    table_view->setMinimumWidth (600);
    //table_view->setAllColumnsShowFocus (true);
    table_view->setSelectionMode (QAbstractItemView::ExtendedSelection);
    table_view->viewport ()->setAttribute (Qt::WA_Hover);

    //table_view->horizontalHeader()->setSectionResizeMode (QHeaderView::Stretch);
    //table_view->verticalHeader()->setSectionResizeMode (QHeaderView::Stretch);
    m_model->setParent (table_view);

    auto *main_layout = new QVBoxLayout;
    main_layout->addWidget (table_view);
    //table_view->resizeColumnsToContents ();

    auto *button_layout = new QHBoxLayout;
    button_layout->addWidget (m_add_but = new QPushButton ("Add", this));
    button_layout->addWidget (m_del_but = new QPushButton ("Del", this));
    m_add_but->hide ();
    m_del_but->hide ();

    main_layout->addLayout(button_layout);

    setLayout (main_layout);
}
