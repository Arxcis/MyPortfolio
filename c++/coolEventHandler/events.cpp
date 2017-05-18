//
// @author Jonas Solsvik
// @created 09.05.17
// @brief Example of staticly binding of lambda expressions(EventHandlers) to an event-egine,
//         The engine dynamicly maps events to stored EventHandlers
//

#include <vector>
#include <cassert>

//
// EventCode
//
enum EventCode {
    BUTTONPRESSX,
    BUTTONPRESSA,
};

//
// EventEngine
//
class EventEngine {

private:

    class IExecuteable {
    public:
        virtual void execute()=0;
        virtual ~IExecuteable(){};
    };

    template<class Func>
    class EventHandler : public IExecuteable {  
    private:
        Func handler;
    public:
        EventHandler(Func handler_):handler(handler_){}
        virtual ~EventHandler(){}
        virtual void execute() {
            handler();
        }
    };

    static const unsigned size = 2;
    std::vector<IExecuteable*> handlerCollection;

public:
    EventEngine()
    :handlerCollection([this]() {
        std::vector<IExecuteable*> init;

        init.reserve(this->size);
        for (unsigned i = 0; i < this->size; i++) 
            init.push_back(nullptr);

        return init;
    }())
    {}

    ~EventEngine () { 
        for (auto* handler: handlerCollection)
            delete handler;
    }

    template<class Func>
    void OnButtonPressX(Func onButtonPressXHandler) {
        handlerCollection[BUTTONPRESSX] = 
            (static_cast<IExecuteable*>(new EventHandler<Func>{onButtonPressXHandler})); 
    }

    template<class Func>
    void OnButtonPressA(Func onButtonPressAHandler) {
        handlerCollection[BUTTONPRESSA] = 
            (static_cast<IExecuteable*>(new EventHandler<Func>{onButtonPressAHandler})); 
    }

    void process(std::vector<EventCode> eventCodes) {
        for (auto e: eventCodes) {
            handlerCollection[e]->execute(); // @unsafe, Relying That all events have been registered.
        }
    }

    bool safetyCheck() {
        bool isSafe = true;
        for (auto* handler: handlerCollection) {
            if(!handler) {
                isSafe = false;
                break;
            }
        }
        return isSafe;
    }
};

class PunchGuy 
{
public:
    void punch() {
        printf("Punching.....\n");
    }

    void jump() {
        printf("jumping......\n");
    }
};

int main() 
{
    EventEngine eventEngine;
    PunchGuy    punchGuy;

    eventEngine.OnButtonPressA(
        [&punchGuy]() {
            punchGuy.jump();
        }
    );

    eventEngine.OnButtonPressX(
        [&punchGuy]() {
            punchGuy.punch();
        }
    );

    assert(eventEngine.safetyCheck());  // Checking if all events are hooked up

    eventEngine.process({
        BUTTONPRESSX,
        BUTTONPRESSX,
        BUTTONPRESSA,
        BUTTONPRESSX,
        BUTTONPRESSA,
        BUTTONPRESSA,
    });
}