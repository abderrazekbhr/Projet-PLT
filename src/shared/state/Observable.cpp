#include "Observable.h"
#include "Observer.h"
#include "StateEvent.h"
#include <iostream>
#include "algorithm"

using namespace state;

    void Observable::registerObserver(Observer* observer){
        observers.push_back(observer);
    }

    void Observable::notifyObserver(StateEvent& event, State* state){
        for(auto observer:observers){
            observer->StateChanged(event,*state);
        }
    }

    void const Observable::unregisterObserverver(Observer* o) {

        auto it = std::find(observers.begin(), observers.end(), o);
    
        if (it != observers.end()) {
            observers.erase(it);
    }
}
    void const Observable::unregisterObservers(){
        observers.clear();
    }