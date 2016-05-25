bin_PROGRAMS = testall
testtargetsources = ../src/ScreenXCB.hpp ../src/ScreenXCB.cpp ../src/ScreenInfoRgb.hpp ../src/ScreenInfoRgb.cpp
testall_SOURCES = $(testtargetsources) Main_test.cpp ScreenXCB_test.cpp

testall_CPPFLAGS = $(PTHREAD_CFLAGS) $(CPPFLAGS) -I../src/
testall_CFLAGS =  $(PTHREAD_CFLAGS) $(X11_CFLAGS) $(XCB_CFLAGS) $(CFLAGS)

# PTHREAD_LDFLAGS is not defined by AX_PTHREAD so I created this shunt by using PTHREAD_CFLAGS
testall_LDFLAGS = $(PTHREAD_CFLAGS) $(BOOST_LOG_LDFLAGS) $(LDFLAGS)

testall_LDADD =  $(PTHREAD_LIBS) $(BOOST_LOG_LIB) $(X11_LIBS) $(XCB_LIBS) $(LIBS)
