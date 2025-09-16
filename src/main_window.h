#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtWidgets>

class project;

class main_window: public QMainWindow
{
    Q_OBJECT
public:
    main_window ();

private slots:
    void about();

private:
    project *m_project = nullptr;
    void create_menu_bar();
};

#endif
