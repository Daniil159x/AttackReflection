TARGET = AttackReflection_Game
TEMPLATE = app


CONFIG += console
CONFIG += thread
CONFIG += precompile_header

CONFIG -= app_bundle
CONFIG -= qt


QMAKE_CXXFLAGS += -std=c++17
DEFINES += USING_PCH
#DEFINES += BOOST_ENABLE_ASSERT_HANDLER


SOURCES += \
        main.cpp \
    eventcontroller.cpp \
    game.cpp \
    utilities.cpp \
    mob.cpp \
    disappearing.cpp \
    bullet.cpp \
    button.cpp

HEADERS += \
    extinclusions.hpp \
    allinclusions.hpp \
    allinclusions.hpp \
    extinclusions.hpp \
    eventcontroller.hpp \
    utilities.hpp \
    game.hpp \
    mob.hpp \
    disappearing.hpp \
    bullet.hpp \
    button.hpp

PRECOMPILED_HEADER += extinclusions.hpp


#   SFML
INCLUDEPATH += /home/daniil/Dev/SFML-2.4.2/include
LIBS += -L/home/daniil/Dev/SFML-2.4.2/lib/ -lsfml-graphics -lsfml-window -lsfml-system

#   boost
LIBS += -lboost_filesystem -lboost_system