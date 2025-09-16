TEMPLATE = app
INCLUDEPATH += .

HEADERS     = project.h athlete.h athletes_model.h athletes_widget.h main_window.h \
  relay_calculator.h \
  relay_item_model.h \
  relay_properties_enums.h \
  relay_properties_widget.h \
  relay_widget.h \
  team.h
RESOURCES   = relays.qrc
SOURCES     = main.cpp project.cpp athlete.cpp athletes_model.cpp athletes_widget.cpp main_window.cpp \
  relay_calculator.cpp \
  relay_item_model.cpp \
  relay_properties_enums.cpp \
  relay_properties_widget.cpp \
  relay_widget.cpp \
  team.cpp

QT += widgets widgets
requires(qtConfig(tableview))

QMAKE_CXXFLAGS += -std=gnu++11

##target.path = $$[QT_INSTALL_EXAMPLES]/sql/books
##INSTALLS += target
