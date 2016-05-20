#ifndef __APPLICATION_HPP
#define __APPLICATION_HPP

namespace x3d {
  class Application {
    virtual void createWindow() = 0;
    //virtual void ask_to_be_notified_of_interesting_events(void); // TODO: register for events
    virtual void eventLoop() = 0;
  public:
    virtual void execute() = 0;
    virtual ~Application() {}
  };
}

#endif
