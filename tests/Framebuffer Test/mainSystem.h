/* 
 * File:   mainSystem.h
 * Author: miles
 *
 * Created on November 21, 2014, 10:43 PM
 */

#ifndef MAINSYSTEM_H
#define	MAINSYSTEM_H

#include "lightsky/game/gameSystem.h"
#include "display.h"
#include "context.h"

class mainSystem final : virtual public ls::game::system {
    public:
        mainSystem();
        
        mainSystem(const mainSystem&) = delete;
        
        mainSystem(mainSystem&&);
        
        virtual ~mainSystem();
        
        mainSystem& operator=(const mainSystem&) = delete;
        
        mainSystem& operator=(mainSystem&&);
        
        bool onStart() override;
        
        void onRun() override;
        
        void onPause() override;
        
        void onStop() override;
};

#endif	/* MAINSYSTEM_H */

