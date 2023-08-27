#ifndef __SUBJECT_HPP__
#define __SUBJECT_HPP__

#include "utils/imports.hpp"
#include "Listener.hpp"

/**
 * Abstract class that represents a view. It is used to notify the controllers when there are changes. 
 * Each view has is own controller. All view inherit from the class.
 */
class Subject{
    
    public:

        virtual void addListener(void* listener)=0;
        virtual void removeListener()=0;
        virtual void notify(const char* buttonLabel)=0;
    
    protected:
    
        vector <Listener*> listeners;

};

#endif