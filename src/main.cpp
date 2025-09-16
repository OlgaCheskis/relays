#include "main_window.h"

#include <QtWidgets>
#include <stdlib.h>


int main(int argc, char * argv[])
{
    Q_INIT_RESOURCE(relays);

    QApplication app(argc, argv);

    main_window win;
    win.show ();

    return app.exec();
}
