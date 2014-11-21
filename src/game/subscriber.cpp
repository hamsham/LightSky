/* 
 * File:   game/subscriber.cpp
 * Author: miles
 * 
 * Created on November 20, 2014, 10:24 PM
 */

#include "lightsky/game/event.h"
#include "lightsky/game/subscriber.h"
#include "lightsky/game/dispatcher.h"

namespace ls {
namespace game {

/*-------------------------------------
 * Destructor
-------------------------------------*/
subscriber::~subscriber() {
    setDispatcher(nullptr);
}

/*-------------------------------------
 * Constructor
-------------------------------------*/
subscriber::subscriber() {
}

/*-------------------------------------
 * Copy Constructor
-------------------------------------*/
subscriber::subscriber(const subscriber& s) {
    setDispatcher(s.pParent);
}

/*-------------------------------------
 * Move Constructor
-------------------------------------*/
subscriber::subscriber(subscriber&& s) {
    setDispatcher(s.pParent);
    s.setDispatcher(nullptr);
}

/*-------------------------------------
 * Copy Operator
-------------------------------------*/
subscriber& subscriber::operator=(const subscriber& s) {
    setDispatcher(s.pParent);
    return *this;
}

/*-------------------------------------
 * Move Operator
-------------------------------------*/
subscriber& subscriber::operator=(subscriber&& s) {
    setDispatcher(s.pParent);
    s.setDispatcher(nullptr);
    return *this;
}

/*-------------------------------------
 * Set the parent dispatcher
-------------------------------------*/
void subscriber::setDispatcher(dispatcher* const pDispatcher) {
    if (pParent == pDispatcher) {
        return;
    }
    
    if (pParent != nullptr) {
        pParent->unassignSubscriber(*this);
    }
    
    pParent = pDispatcher;
    if (pParent != nullptr) {
        pParent->assignSubscriber(*this);
    }
}

/*-------------------------------------
 * Confirm a parent dispatcher
-------------------------------------*/
bool subscriber::isSubscribed(const dispatcher& d) const {
    return pParent == &d;
}

} // end game namespace
} // end ls namespace
