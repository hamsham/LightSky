/* 
 * File:   game/dispatcher.h
 * Author: miles
 *
 * Created on November 20, 2014, 10:27 PM
 */

#ifndef __LS_GAME_DISPATCHER_H__
#define	__LS_GAME_DISPATCHER_H__

#include <vector>
#include <unordered_map>

#include "lightsky/game/event.h"

namespace ls {
namespace game {

/**----------------------------------------------------------------------------
 * @brief Event dispatcher object
 * 
 * The dispatcher class contains a queue of events and a table of subscription
 * objects to pass the events to. Events can be pushed to a dispatcher's event
 * queue, then dispatched to all subscribers. Subscribers are automatically
 * dereferenced if this object goes out of their scope (i.e. if a call to
 * "delete" is made or an instance is destroyed).
-----------------------------------------------------------------------------*/
class dispatcher {
    friend class subscriber;
    
    private:
        /**
         * @brief eventList_t
         * 
         * A typedef to the underlying storage type which will contain event
         * objects to be dispatched to subscribers.
         */
        typedef std::vector<event> eventList_t;
        
        /**
         * @brief subscriberMap_t
         * 
         * A typedef to the underlying storage type which will map subscriber
         * object ID's (in this cast, their location in memory) to the
         * subscriber object.
         */
        typedef std::unordered_map<subscriber*, subscriber*> subscriberMap_t;
        
        /**
         * @brief events
         * 
         * An array of event objects that will be passed to *this object's
         * list of subscribers.
         */
        eventList_t events;
        
        /**
         * @brief subscribers
         * 
         * A map of identifications to subscriber objects. In most cases, the
         * ID at which a subscriber is identified will be a pointer to the
         * subscriber itself. Subscribers are mapped in a table in order to
         * make element access much easier during insertion and deletion.
         */
        subscriberMap_t subscribers;
        
    public:
        /**
         * @brief Destructor
         * 
         * Calls "setDispatcher(NULL)" and severs the connection to the parent
         * object. This effectively calls "clearSubscribers()."
         */
        virtual ~dispatcher();
        
        /**
         * @brief Constructor
         * 
         * Constructs *this with an empty event queue and subscriber list.
         */
        dispatcher();
        
        /**
         * @brief Copy Constructor - DELETED
         * 
         * The copy constructor has been deleted due to the fact that
         * subscribers can only have one parent (for reduced memory usage).
         */
        dispatcher(const dispatcher& d) = delete;
        
        /**
         * @brief Move Constructor
         * 
         * The move constructor moves all data from the input dispatch object
         * into *this. All child subscribers are then reassigned to *this.
         * 
         * @param d
         * An-value reference to another dispatch object who's data will be
         * moved into *this.
         */
        dispatcher(dispatcher&& d);
        
        /**
         * @brief Copy Operator -- DELETED
         * 
         * The copy operator has been deleted due to the fact that subscribers
         * can only have one parent (for reduced memory usage).
         */
        dispatcher& operator=(const dispatcher& d) = delete;
        
        /**
         * @brief Move Operator
         * 
         * The move operator moves all data from the input dispatch object into
         * *this. All child subscribers are then reassigned to *this.
         * 
         * @param d
         * An-value reference to another dispatch object who's data will be
         * moved into *this.
         * 
         * @return a reference to *this.
         */
        dispatcher& operator=(dispatcher&& d);
        
        /**
         * @brief Assign a subscriber object to receive events from *this.
         * 
         * Once a subscriber has been assigned to *this, that connection will
         * be retained until either *this or the subscriber has gone out of
         * scope.
         * 
         * @param s
         * A reference to the subscriber object which is to handle events
         * passed by *this.
         */
        void assignSubscriber(subscriber& s);
        
        /**
         * @brief Unassign a subscriber from being passed events by *this.
         * 
         * @param s
         * A reference to the subscriber object which is to be removed from
         * *this objects event list.
         */
        void unassignSubscriber(subscriber& s);
        
        /**
         * @brief Determine if a subscriber is being passed events from *this.
         * 
         * @param s
         * A constant reference to a subscriber object.
         * 
         * @return TRUE if *this is passing events to the input parameter,
         * FALSE if otherwise.
         */
        bool hasSubscriber(const subscriber& s) const;
        
        /**
         * @brief Remove all subscribers from *this object's distribution list.
         * 
         * Calling this method will sever the connection between *this and all
         * subscribers referenced by *this.
         */
        void clearSubscribers();
        
        /**
         * @brief dispatch all events contained within *this objects event
         * queue.
         * 
         * All events contained within *this object's event queue are sent to
         * each of the subscribers referenced by *this. Once the events are
         * dispatched, the event queue is cleared.
         * This method should be called frequently in order to avoid memory
         * leaks.
         */
        void dispatchEvents();
        
        /**
         * @brief Push an event into *this object's event queue.
         * 
         * @param e
         * A constant reference to an event object which will be added to the
         * event queue in *this.
         */
        void pushEvent(const event& e);
        
        /**
         * @brief Retrieve the number of events that are queued in *this.
         * 
         * @return an unsigned integral type, representing the number of events
         * that *this object can distribute to its subscribers.
         */
        unsigned getNumEventsQueued() const;
        
        /**
         * Get the number of subscribers that are receiving events from *this.
         * 
         * @return an unsigned integral type, representing the number of
         * subscriber objects that are receiving events from *this.
         */
        unsigned getNumSubscribers() const;
};

} // end game namespace
} // end ls namespace

#endif	/* __LS_GAME_DISPATCHER_H__ */

