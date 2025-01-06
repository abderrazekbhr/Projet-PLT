#include "StateEvent.h"

namespace state {

    StateEvent::StateEvent(StateEventId idEvent) : stateEvent(idEvent) {}

    StateEventId StateEvent::getStateEventId() {

        return stateEvent;
    }

    void StateEvent::setStateEventId(StateEventId id) {
    
        stateEvent = id;
    }

}
