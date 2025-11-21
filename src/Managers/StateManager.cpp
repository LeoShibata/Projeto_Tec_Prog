#include "Managers/StateManager.hpp"
#include "States/State.hpp"

using namespace std;

namespace Managers{
StateManager* StateManager::pStateManager=nullptr;

StateManager::StateManager(){

}

StateManager::~StateManager(){
    while(!(stateStack.empty())){
        delete(stateStack.top());
        stateStack.top() = nullptr;
        stateStack.pop();
    }
}

StateManager* StateManager::getStateManager(){
    if(pStateManager == nullptr) {
        pStateManager = new StateManager();
    }   
    return pStateManager;
}

void StateManager::execute(){
    if(!(stateStack.empty())){
        stateStack.top()->execute();
    }else{
        cout << "Stack is alraedy empty. EXECUTE" << endl;
    }
}

States::State* StateManager::getAtualState(){
    if(!(stateStack.empty()))
        return stateStack.top();
    cout << "stack is already empty. GET ATUAL STATE" << endl;
    return nullptr;
}

void StateManager::addState(const int idStateType){
    States::State* newState = nullptr;
    if(idStateType == 1 || idStateType == 2){
        newState = static_cast<States::State*>(new States::StatePlaying(idStateType));
    }else if (idStateType == 3){
        newState = static_cast<States::State*>(new States::StateMenu());
    }else if (idStateType == 4){
        newState = static_cast<States::State*>(new States::StatePause());
    }
    
    cout <<" added state: STATEMANAGER" << endl;

    stateStack.push(newState);
}

void StateManager::removeState(const int qtd){
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

    if ((stateStack.empty())){
        Managers::GraphicManager* pGraphic = pGraphic->getGraphicManager();
        pGraphic->closeWindow();
    }
}

void StateManager::removeState(){
    if((stateStack.top() != nullptr) && !(stateStack.empty())){
        delete (stateStack.top());
        stateStack.top() = nullptr;
        stateStack.pop();
    }
    if (!(stateStack.empty())){
        Managers::GraphicManager* pGraphic = pGraphic->getGraphicManager();
        pGraphic->closeWindow();
    }


}
States::State* StateManager::getSpecificState(const int idRemove){
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