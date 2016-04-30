bin_PROGRAMS = demo
demo_SOURCES = Screen.h Screen.cpp ScreenX11.h ScreenX11.cpp ScreenFactory.h ScreenFactory.cpp main.cpp
demo_CPPFLAGS = $(PTHREAD_CFLAGS) $(CPPFLAGS)
demo_CFLAGS =  $(PTHREAD_CFLAGS) $(X11_CFLAGS) $(XCB_CFLAGS) $(CFLAGS)

# PTHREAD_LDFLAGS is not defined by AX_PTHREAD so I created this shunt by using PTHREAD_CFLAGS
demo_LDFLAGS = $(PTHREAD_CFLAGS) $(BOOST_LOG_LDFLAGS) $(LDFLAGS)

demo_LDADD =  $(PTHREAD_LIBS) $(BOOST_LOG_LIB) $(X11_LIBS) $(XCB_LIBS) $(LIBS)
