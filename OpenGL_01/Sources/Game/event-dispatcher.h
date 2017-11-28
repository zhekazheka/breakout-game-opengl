//
//  event-dispatcher.hpp
//  OpenGL_01
//
//  Created by zhekazheka on 11/28/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#ifndef event_dispatcher_h
#define event_dispatcher_h

#include "safe_event.h"

class EventDispatcher
{
public:
    ~EventDispatcher() {}
    
    static EventDispatcher& GetInstance()
    {
        static EventDispatcher instace;
        return instace;
    }
    
    se::dispatcher Dispatcher;
    
private:
    EventDispatcher() {}
};

#endif /* event_dispatcher_h */
