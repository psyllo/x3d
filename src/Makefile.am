bin_PROGRAMS = demo
demo_SOURCES = main.cpp \
Application.hpp \
ApplicationX11.cpp \
ApplicationX11.hpp \
Dispatcher.hpp \
DispatcherX11.cpp \
DispatcherX11.hpp \
EventSource.hpp \
FactoryManager.cpp \
FactoryManager.hpp \
PipelineDemo.cpp \
PipelineDemo.hpp \
Pipeline.hpp \
Polygon2D.hpp \
Polygon2D.cpp \
Rasterizer.hpp \
Rasterizer.cpp \
Screen.hpp \
ScreenInfo.hpp \
ScreenX11.cpp \
ScreenX11.hpp

demo_CPPFLAGS = $(PTHREAD_CFLAGS) $(CPPFLAGS)
demo_CFLAGS = $(PTHREAD_CFLAGS) $(X11_CFLAGS) $(XCB_CFLAGS) $(CFLAGS)

# PTHREAD_LDFLAGS is not defined by AX_PTHREAD so I created this shunt by using PTHREAD_CFLAGS
demo_LDFLAGS = $(PTHREAD_CFLAGS) $(BOOST_LOG_LDFLAGS) $(LDFLAGS)

demo_LDADD = $(PTHREAD_LIBS) $(BOOST_LOG_LIB) $(X11_LIBS) $(XCB_LIBS) $(LIBS)
