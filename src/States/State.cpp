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


void State::resetView() { // reseta camera para menus (camera acompanha o personagem)
    sf::View defaultView = pGraphic->getWindow()->getDefaultView();
    pGraphic->getWindow()->setView(defaultView);
}


void State::draw() {
    
}


void State::setRemove(bool remove) {
    this->remove = remove;
}


const bool State::getRemove() const {
    return remove;
}

}
