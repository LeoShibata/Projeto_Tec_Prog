#ifndef STATES_HPP
#define STATES_HPP

//#include "Managers/EventManager.hpp"
#include "utils/json.hpp"
#include <SFML/Graphics.hpp>
namespace Managers{ //foward declaration
    class GraphicManager;
    class StateManager;
}

namespace States {
    enum class StateType{
        //add menu after 
        none = 0,
        stage1,
        stage2
    };


    class State{
    private:
        bool remove;
        Managers::StateManager* pStateManager;//doing context paper, state interface
        StateType stateType;
    protected:
        Managers::GraphicManager* pGraphic;

    public:
        State(); //ID system, 
        virtual ~State();
        virtual void execute() = 0;
        virtual void draw();
        void setRemove(const bool remove);
        const bool getRemove() const;
        
    };

}





#endif