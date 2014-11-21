/* 
 * File:   game/subscriber.h
 * Author: miles
 *
 * Created on November 20, 2014, 10:24 PM
 */

#ifndef __LS_GAME_SUBSCRIBER_H__
#define	__LS_GAME_SUBSCRIBER_H__

#include "lightsky/game/event.h"

namespace ls {
namespace game {

/**----------------------------------------------------------------------------
 * @brief Event Subscription Object (abstract)
 * 
 * The Subscription object is a simple event handler which will receive events
 * from a dispatcher. When a dispatch object is passed into *this, a connection
 * will remain until either the dispatcher or subscriber has been deleted.
 * This permits events to be safely passed around without worrying about
 * scoping issues.
 * 
 * Event subscribers must be derived and have the virtual "handleEvent()"
 * function overridden.
-----------------------------------------------------------------------------*/
class subscriber {
    friend class dispatcher;
    
    private:
        /**
         * @brief pParent is a pointer to the dispatcher to which this
         * subscriber is receiving events from.
         */
        mutable dispatcher* pParent = nullptr;
        
    protected:
        /**
         * @brief The HandleEvents function allows derived subscriber objects
         * to determine what to do upon receiving an event.
         * 
         * @param evt
         * A constant reference to an event object, sent by a call to *this
         * object's parent dispatcher.
         */
        virtual void handleEvent(const event& evt) = 0;
        
    public:
        /**
         * @brief Destructor
         * 
         * Calls "setDispatcher(NULL)" and severs the connection to the parent
         * object.
         */
        virtual ~subscriber() = 0;
        
        /**
         * @brief Constructor
         * 
         * Constructs all members in *this to NULL.
         */
        subscriber();
        
        /**
         * @brief Copy Constructor
         * 
         * This constructor will retrieve the parent system from the input
         * parameter and assign *this as a subscriber. This function does
         * nothing if the input parameter has no parent object.
         * 
         * @param s
         * A constant reference to another subscriber object who's parent
         * dispatcher will be shared with *this.
         */
        subscriber(const subscriber& s);
        
        /**
         * @brief Move Constructor
         * 
         * This method will make the parent dispatcher unassign the input
         * parameter and assign *this instead. This function does nothing if
         * the input parameter has no parent object.
         * 
         * @param s
         * An-value reference to another subscriber object who's parent
         * dispatcher will be reassigned to *this.
         */
        subscriber(subscriber&& s);
        
        /**
         * @brief Copy Operator
         * 
         * This Operator will retrieve the parent system from the input
         * parameter and assign *this as a subscriber. This function does
         * nothing if the input parameter has no parent object.
         * 
         * @param s
         * A constant reference to another subscriber object who's parent
         * dispatcher will be shared with *this.
         * 
         * @return a reference to *this.
         */
        subscriber& operator=(const subscriber& s);
        
        /**
         * @brief Move Operator
         * 
         * This method will make the parent dispatcher unassign the input
         * parameter and assign *this instead. This function does nothing if
         * the input parameter has no parent object.
         * 
         * @param s
         * An-value reference to another subscriber object who's parent
         * dispatcher will be reassigned to *this.
         * 
         * @return a reference to *this.
         */
        subscriber& operator=(subscriber&& s);
        
        /**
         * @brief Set the parent dispatcher for *this.
         * 
         * This function will create a connection to a dispatcher object in
         * order to receive events from it.
         * 
         * @param pDispatcherAfter
         * Calling this function with a valid pointer to a dispatcher causes
         * events to will be sent to *this each time the parent dispatcher
         * calls "dispatchEvents()." Pass NULL as a parameter in order to
         * sever the connection with the parent object.
         */
        void setDispatcher(dispatcher* const pDispatcher = nullptr);
        
        /**
         * @brief Determine if *this is subscribed to a dispatcher.
         * 
         * @param d
         * A constant reference to a dispatcher object.
         * 
         * @return TRUE if *this is subscribed to the input dispatcher, FALSE
         * if otherwise.
         */
        bool isSubscribed(const dispatcher& d) const;
};

} // end game namespace
} // end ls namespace

#endif	/* __LS_GAME_SUBSCRIBER_H__ */

