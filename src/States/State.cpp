#include "States/State.hpp"
#include "Managers/GraphicManager.hpp"
#include "Managers/StateManager.hpp"

namespace States{

State::State() : 
    pGraphic(Managers::GraphicManager::getGraphicManager()),
    pStateManager(Managers::StateManager::getStateManager()),
    remove(false)
{
            
}


State::~State() { }


void State::draw() {
    
}


void State::setRemove(bool remove) {
    this->remove = remove;
}


const bool State::getRemove() const {
    return remove;
}

}
