#include "Managers/StateManager.hpp"
#include "States/State.hpp"

#include "States/StateMenu.hpp"
#include "States/PlayerSelectState.hpp"
#include "States/StageSelectState.hpp"
#include "States/StatePlaying.hpp"
#include "States/StatePause.hpp"
#include "States/GameOverState.hpp"

using namespace std;

namespace Managers {

StateManager* StateManager::pStateManager=nullptr;


StateManager::StateManager() {

}


StateManager::~StateManager() {
    while(!(stateStack.empty())){
        delete(stateStack.top());
        stateStack.top() = nullptr;
        stateStack.pop();
    }
}


StateManager* StateManager::getStateManager() {
    if(pStateManager == nullptr) {
        pStateManager = new StateManager();
    }   
    return pStateManager;
}


void StateManager::execute() {
    if(!(stateStack.empty())){
        stateStack.top()->execute();
    }else{
        cout << "Stack is alraedy empty. EXECUTE" << endl;
    }
}


States::State* StateManager::getAtualState() {
    if(!(stateStack.empty()))
        return stateStack.top();
    cout << "stack is already empty. GET ATUAL STATE" << endl;
    return nullptr;
}


void StateManager::addState(const int idStateType) {
    States::State* newState = nullptr;
    switch(idStateType) {
        case 0:
            newState = new States::StateMenu(); // ID 0: Menu Principal
            break;
        case 1: 
            newState = new States::StatePlaying(1); // ID 1: Fase 1 (Graveyard)
            break;
        case 2: 
            newState = new States::StatePlaying(2); // ID 2: Fase 2 (Castle)
            break; 
        case 3:
            newState = new States::StatePause();
            break;
        case 4: 
            newState = new States::PlayerSelectState();
            break;
        case 5: 
            newState = new States::StageSelectState();
            break;
        case 6: 
            newState = new States::GameOverState();
            break;
        
        default:
            break;  
    }

    // if(idStateType == 1 || idStateType == 2){
    //     newState = static_cast<States::State*>(new States::StatePlaying(idStateType));
    // }else if (idStateType == 3){
    //     newState = static_cast<States::State*>(new States::StateMenu());
    // }else if (idStateType == 4){
    //     newState = static_cast<States::State*>(new States::StatePause());
    // }
    
    // cout <<" added state: STATEMANAGER" << endl;

    if(newState) {
        stateStack.push(newState);
    }
}


void StateManager::removeState(const int qtd) {
    int i = 0;
    while(!(stateStack.empty()) && (i < qtd)){
        States::State* auxState = stateStack.top();
        if(auxState != nullptr){
            delete (auxState);
            auxState = nullptr;
        }
        stateStack.pop();
        i++;
    }

    if (stateStack.empty()){
        Managers::GraphicManager* pGraphic = pGraphic->getGraphicManager();
        pGraphic->closeWindow();
    }
}


void StateManager::removeState() {
    if((stateStack.top() != nullptr) && !(stateStack.empty())){
        delete (stateStack.top());
        stateStack.top() = nullptr;
        stateStack.pop();
    }
    if (stateStack.empty()) {
        Managers::GraphicManager* pGraphic = pGraphic->getGraphicManager();
        pGraphic->closeWindow();
    }
}


States::State* StateManager::getSpecificState(const int idRemove) {
    stack<States::State*> auxStateStack = stateStack; 
    
    int i = 0;
    if(!(auxStateStack.empty())){
        while(i < idRemove){
            stateStack.pop();
            i++;
        }
        if(!(auxStateStack.empty()))
            return auxStateStack.top();
        cout << "deleted too much states" << endl;
    }else{
        cout << "stateStack is empty. GET SPECIFIC STATE" << endl;
    }

    return nullptr;
}

}