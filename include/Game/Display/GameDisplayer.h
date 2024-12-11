#ifndef GAME_DISPLAYER_H
#define GAME_DISPLAYER_H

#include "../GameState.h"
#include "../../Field.h"
#include "../../ShipManager.h"
#include "../../AbilityManager.h"

// DISPLAYER INTERFACE
class IGameDisplayer
{
public:
    virtual void writeName(std::string name) = 0;
    virtual void drawField(Field& userField, Field& botField) = 0;
};



// CONCRETE DISPLAYER REALIZATION, REQUIRING AN OTPUT DEVICE

template<typename DispT>
concept DisplayerConcept = requires(DispT displayer, Field& firstField, Field& secondField, std::string name)
{
    {displayer.writeName(name)} -> std::same_as<void>;
    {displayer.drawField(firstField, secondField)} ->std::same_as<void>;
};

template <DisplayerConcept Displayer>
class GameDisplayer : public IGameDisplayer
{
private:
    Displayer displayer;
public:
    template<typename ... Args>
    GameDisplayer(Args&& ... args) : displayer(std::forward<Args>(args)...) {}
    ~GameDisplayer() {}
    void writeName(std::string name)
    {
        displayer.writeName(name);
    }
    void drawField(Field& userField, Field& botField)
    {
        displayer.drawField(userField, botField);
    }

};


// WRAPPER FOR CONCRETE REALIZATION

template <typename Displayer>
class GameDisplayerWrapper : public IGameDisplayer
{
private:
    GameDisplayer<Displayer> unwrappedDisplayer;
public:
    template<typename ... Args>
    GameDisplayerWrapper(Args&& ... args) : unwrappedDisplayer(std::forward<Args>(args)...) {}
    void writeName(std::string name)
    {
        unwrappedDisplayer.writeName(name);
    }
    void drawField(Field& userField, Field& botField)
    {
        unwrappedDisplayer.drawField(userField, botField);
    }
};




#endif