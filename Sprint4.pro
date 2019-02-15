TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    LinkedInManager.cpp \
    runcatchtests.cpp \
    main.cpp

HEADERS += \
    catch.hpp \
    Graph.h \
    iteratorPtr.h \
    LinkedInManager.h \
    linkedlist.h \
    node.h \
    stack.h \
    VectorData.h

DISTFILES += \
    ../build-Sprint4-Desktop_Qt_5_11_2_GCC_64bit-Debug/flights.txt \
    ../build-Sprint4-Desktop_Qt_5_11_2_GCC_64bit-Debug/output.out \
    ../build-Sprint4-Desktop_Qt_5_11_2_GCC_64bit-Debug/reqPaths.txt
