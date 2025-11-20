#include "States/StatePlaying.hpp"

using namespace States;

StatePlaying::StatePlaying(int idStage): 
idStage(idStage),
stages(){
    createStage();

}
StatePlaying::~StatePlaying(){
    while (!(stages.empty()))
    {
        delete(stages.front());
        stages.front() = nullptr;
        stages.pop();
    }
    
}
void StatePlaying::createStage(){
    if(idStage == 1){
        Stages::Stage* newStage = static_cast<Stages::Stage*>(new Stages::Graveyard());
        stages.push(newStage);
        // cout <<" added newstage" << endl;
    }else{
        Stages::Stage* newStage = static_cast<Stages::Stage*>(new Stages::Castle());
        stages.push(newStage);
        // cout <<" added newstage" << endl;
    }
}
void StatePlaying::loadStage(){

}
void StatePlaying::execute(){
    // cout <<" executed state" << stages.front() <<endl;
    if(stages.empty()) {
        // cout << "No stages available!" << endl;
        return;
    }
    stages.front()->execute();
    pGraphic->clearWindow(); 

    stages.front()->draw(pGraphic->getWindow());
}