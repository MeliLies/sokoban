#ifndef __LISTENER_HPP__
#define __LISTENER_HPP__

#include "utils/imports.hpp"

/**
 * Abstract class that represents a controller. It is used to control the views by handling the user actions. 
 * Each view has is own controller. All controller inherit from the class.
 */
class Listener {

    public:
        virtual void handleEvent(const char *event)=0;
};

#endif