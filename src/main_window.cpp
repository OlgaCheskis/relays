#include "main_window.h"
#include "athletes_widget.h"
#include "relay_widget.h"
#include "project.h"

#include <QTabWidget>

main_window::main_window()
{
  m_project = new project ();
  QWidget *central_widget = new QWidget (this);
  auto *main_layout = new QVBoxLayout;
  auto *tab_widget = new QTabWidget (central_widget);
  main_layout->addWidget (tab_widget);
  tab_widget->addTab (new athletes_widget (*m_project, central_widget), "Athletes");
  tab_widget->addTab (new relay_widget (*m_project, central_widget), "Relays");
  central_widget->setLayout (main_layout);
  setCentralWidget (central_widget);

  create_menu_bar ();
  showMaximized ();
}


void main_window::create_menu_bar ()
{
//    QAction *quitAction = new QAction(tr("&Quit"), this);
//    QAction *aboutAction = new QAction(tr("&About"), this);
//    QAction *aboutQtAction = new QAction(tr("&About Qt"), this);
//
//    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
//    fileMenu->addAction(quitAction);
//
//    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
//    helpMenu->addAction(aboutAction);
//    helpMenu->addAction(aboutQtAction);
//
//    connect(quitAction, &QAction::triggered, this, &Window::close);
//    connect(aboutAction, &QAction::triggered, this, &Window::about);
//    connect(aboutQtAction, &QAction::triggered, qApp, &QApplication::aboutQt);
}

void main_window::about ()
{}
