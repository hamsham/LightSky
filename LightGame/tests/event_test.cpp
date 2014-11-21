/* 
 * File:   event_test.cpp
 * Author: miles
 *
 * Created on Nov 20, 2014, 10:31:55 PM
 */

#include <iostream>

#include "lightsky/game/event.h"
#include "lightsky/game/subscriber.h"
#include "lightsky/game/dispatcher.h"

/*-------------------------------------
 * Test Subscriber Class
-------------------------------------*/
class testSubscriber final : virtual public ls::game::subscriber {
    public:
        virtual ~testSubscriber() {}
    
    private:
        virtual void handleEvent(const ls::game::event&) {
            std::cout << "Hello World!" << std::endl;
        }
};

/*-------------------------------------
 * Main
-------------------------------------*/
int main() {
    ls::game::event testEvent;
    testSubscriber subscriber{};
    ls::game::dispatcher dispatcher{};
    
    dispatcher.assignSubscriber(subscriber);
    dispatcher.pushEvent(testEvent);
    dispatcher.dispatchEvents();
    
    std::cin.get();
    
    return 0;
}

