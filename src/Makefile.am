bin_PROGRAMS = demo
demo_SOURCES = main.cpp \
Application.hpp \
ApplicationXCB.cpp \
ApplicationXCB.hpp \
Dispatcher.hpp \
DispatcherXCB.cpp \
DispatcherXCB.hpp \
EventSource.hpp \
FactoryManager.cpp \
FactoryManager.hpp \
PipelineXCBdemo.cpp \
PipelineXCBdemo.hpp \
Pipeline.hpp \
Polygon2D.hpp \
Polygon2D.cpp \
Rasterizer.hpp \
Rasterizer.cpp \
Screen.hpp \
ScreenInfo.hpp \
ScreenInfoRgb.hpp \
ScreenInfoRgb.cpp \
ScreenXCB.cpp \
ScreenXCB.hpp

demo_CPPFLAGS = $(PTHREAD_CFLAGS) $(CPPFLAGS)
demo_CFLAGS = $(PTHREAD_CFLAGS) $(X11_CFLAGS) $(XCB_CFLAGS) $(XCB_SHM_CFLAGS) $(XCB_IMAGE_CFLAGS) $(CFLAGS)

# PTHREAD_LDFLAGS is not defined by AX_PTHREAD so I created this shunt by using PTHREAD_CFLAGS
demo_LDFLAGS = $(PTHREAD_CFLAGS) $(BOOST_LOG_LDFLAGS) $(LDFLAGS)

demo_LDADD = $(PTHREAD_LIBS) $(BOOST_LOG_LIB) $(X11_LIBS) $(XCB_LIBS) $(XCB_SHM_LIBS) $(XCB_IMAGE_LIBS) $(LIBS)
