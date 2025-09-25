#include "athletes_widget.h"
#include "athletes_model.h"
#include "project.h"

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTreeView>

#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMenu>


athletes_widget::athletes_widget (project &proj, QWidget *parent)
    : QWidget (parent)
{
    m_model = new athletes_model (proj, this);

    m_table_view = new QTableView;
    m_table_view->setModel (m_model);
    m_table_view->setMinimumWidth (600);
    m_table_view->setColumnWidth (0, 300);
    auto *delegate = new combo_box_delegate (this);
    m_table_view->setItemDelegateForColumn (1, delegate);
    auto *time_delegate = new spin_box_delegate (this);
    for (int i = 3; i < 7; i++)
      {
        m_table_view->setItemDelegateForColumn (i, time_delegate);
      }
    //table_view->setAllColumnsShowFocus (true);
    m_table_view->setSelectionMode (QAbstractItemView::ExtendedSelection);
    m_table_view->setSelectionBehavior (QAbstractItemView::SelectRows);
    m_table_view->setStyleSheet ("QTableView {selection-background-color: lightblue; selection-color: black;}");
    //table_view->itemDelegateForColumn ()
    m_table_view->viewport ()->setAttribute (Qt::WA_Hover);
//    table_view->setEditTriggers (QAbstractItemView::CurrentChanged);
    m_table_view->setEditTriggers (QAbstractItemView::DoubleClicked);
    m_table_view->setContextMenuPolicy (Qt::ContextMenuPolicy::CustomContextMenu);
    QObject::connect (m_table_view, &QWidget::customContextMenuRequested , this, &athletes_widget::on_menu);
    //table_view->setSortingEnabled (true);

    //table_view->horizontalHeader()->setSectionResizeMode (QHeaderView::Stretch);
    //table_view->verticalHeader()->setSectionResizeMode (QHeaderView::Stretch);
    m_model->setParent (m_table_view);

    auto *main_layout = new QVBoxLayout;
    main_layout->addWidget (m_table_view);
    //table_view->resizeColumnsToContents ();

    auto *button_layout = new QHBoxLayout;
    button_layout->addWidget (m_add_but = new QPushButton ("Add", this));
    button_layout->addWidget (m_del_but = new QPushButton ("Del", this));
    m_add_but->hide ();
    m_del_but->hide ();

    main_layout->addLayout(button_layout);

    setLayout (main_layout);
}

void athletes_widget::on_menu (const QPoint &pos)
{
  QMenu menu;
  auto index = m_table_view->indexAt (pos);
  if (index.row () < m_model->rowCount () - 1)
    menu.addAction ("Delete Row", [this, index]()
    {
      m_model->delete_row (index);
    });
  menu.exec (QCursor::pos());
}
