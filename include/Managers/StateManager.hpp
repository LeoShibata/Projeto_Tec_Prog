#ifndef CONTEXT_HPP
#define CONTEXT_HPP
#include "../Managers/GraphicManager.hpp"
#include "States/StatePlaying.hpp"
#include "States/StateMenu.hpp"
#include "States/StatePause.hpp"

#include <stack>
#include <iostream>
//reference refactoring guro, GOFI, gege video 11 and ascent git hub;
namespace Managers{
class StateManager{ //basically the "context" in gofi
//Singleton 
private:
    std::stack<States::State*> stateStack;
    static StateManager* pStateManager; 
    
private:
    StateManager();

public:
    ~StateManager();

    static StateManager* getStateManager();
    void execute();
    States::State* getAtualState();
    void addState(const int stateType);
    void removeState(const int size); //remove more than 1 state
    void removeState(); //overloading remove atual state
    States::State* getSpecificState(const int qtd);
    
    

};
}
#endif