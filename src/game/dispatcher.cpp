/* 
 * File:   game/dispatcher.cpp
 * Author: miles
 * 
 * Created on November 20, 2014, 10:27 PM
 */

#include "lightsky/game/event.h"
#include "lightsky/game/subscriber.h"
#include "lightsky/game/dispatcher.h"

namespace ls {
namespace game {

/*-------------------------------------
 * Destructor
-------------------------------------*/
dispatcher::~dispatcher() {
    clearSubscribers();
}

/*-------------------------------------
 * Constructor
-------------------------------------*/
dispatcher::dispatcher() :
    events{},
    subscribers{}
{}

/*-------------------------------------
 * Move Constructor
-------------------------------------*/
dispatcher::dispatcher(dispatcher&& d) :
    events{std::move(d.events)},
    subscribers{std::move(d.subscribers)}
{
    typename subscriberMap_t::iterator iter = subscribers.begin();
    while (iter != subscribers.end()) {
        subscriber* const pSubscriber = iter->second;
        pSubscriber->pParent = this;
        ++iter;
    }
}

/*-------------------------------------
 * Move Operator
-------------------------------------*/
dispatcher& dispatcher::operator=(dispatcher&& d) {
    events = std::move(d.events);
    subscribers = std::move(d.subscribers);
    
    typename subscriberMap_t::iterator iter = subscribers.begin();
    while (iter != subscribers.end()) {
        subscriber* const pSubscriber = iter->second;
        pSubscriber->pParent = this;
        ++iter;
    }
    return *this;
}

/*-------------------------------------
 * Assign a subscriber
-------------------------------------*/
void dispatcher::assignSubscriber(subscriber& s) {
    subscriber* const pSubscriber = &s;
    pSubscriber->pParent = this;
    subscribers[pSubscriber] = pSubscriber;
}

/*-------------------------------------
 * Remove a subscriber
-------------------------------------*/
void dispatcher::unassignSubscriber(subscriber& s) {
    if (subscribers.erase(&s) != 0) { // insurance
        s.pParent = nullptr;
    }
}

/*-------------------------------------
 * Check if dispatching to a subscriber
-------------------------------------*/
bool dispatcher::hasSubscriber(const subscriber& s) const {
    return s.pParent == this;
}

/*-------------------------------------
 * remove all subscribers from the distribution list
-------------------------------------*/
void dispatcher::clearSubscribers() {
    typename subscriberMap_t::iterator iter = subscribers.begin();
    
    while (iter != subscribers.end()) {
        subscriber* const pSubscriber = iter->second;
        pSubscriber->pParent = nullptr;
        ++iter;
    }
    subscribers.clear();
}

/*-------------------------------------
 * dispatch events to subscribers
-------------------------------------*/
void dispatcher::dispatchEvents() {
    const unsigned sentinel = events.size();
    
    for (unsigned i = 0; i < sentinel; ++i) {
        typename subscriberMap_t::iterator iter = subscribers.begin();
        while (iter != subscribers.end()) {
            subscriber* const pSubscriber = iter->second;
            pSubscriber->handleEvent(events[i]);
            ++iter;
        }
    }
    events.erase(events.begin(), events.begin()+sentinel);
}

/*-------------------------------------
 * push an event to the event queue
-------------------------------------*/
void dispatcher::pushEvent(const event& t) {
    events.push_back(t);
}


/*-------------------------------------
 * get the number of queued events
-------------------------------------*/
unsigned dispatcher::getNumEventsQueued() const {
    return events.size();
}

/*-------------------------------------
 * get the number of subscribers
-------------------------------------*/
unsigned dispatcher::getNumSubscribers() const {
    return subscribers.size();
}

} // end game namespace
} // end ls namespace
