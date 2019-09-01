
/*
 * File:   MainState.h
 * Author: miles
 *
 * Created on February 9, 2016, 12:59 AM
 */

#ifndef MAINSTATE_H
#define MAINSTATE_H

#include <chrono>

#include "lightsky/utils/Pointer.h"
#include "lightsky/game/Game.h"

#include "Context.h"



namespace chrono = std::chrono;

typedef chrono::steady_clock hr_clock;
typedef hr_clock::time_point hr_time;
typedef std::chrono::duration<float> hr_duration;
typedef chrono::seconds hr_prec;



/*-----------------------------------------------------------------------------
 * Forward Declarations
-----------------------------------------------------------------------------*/
class Display;



/*-----------------------------------------------------------------------------
 * Objects global to the main program state
-----------------------------------------------------------------------------*/
namespace global {
    extern ls::utils::Pointer<Display> pDisplay;
}



/*-----------------------------------------------------------------------------
 * Example System Object
-----------------------------------------------------------------------------*/
class MainState final : virtual public ls::game::GameState {
  private:
    Context renderContext;

    hr_duration::rep tickTime = 0.f;
    hr_time prevTime = hr_clock::now();
    hr_duration frameTime{};
    unsigned currFrames = 0;
    unsigned totalFrames = 0;
    float currSeconds = 0.f;
    float totalSeconds = 0.f;
    
    bool bootstrap_subsystems();
    
    bool setup_substates();

  public:
    MainState();

    MainState(const MainState&) = delete;

    MainState(MainState&&);

    virtual ~MainState();

    MainState& operator=(const MainState&) = delete;

    MainState& operator=(MainState&&);

  protected:
    virtual bool on_start() override;

    virtual void on_run() override;

    virtual void on_stop() override;
};

#endif /* MAINSTATE_H */
