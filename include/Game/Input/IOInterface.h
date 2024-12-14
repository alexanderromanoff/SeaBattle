#ifndef IOINTERFACE_H
#define IOINTERFACE_H

#include <string>
#include <iostream>
#include <map>
#include "../../Battleship.h"
#include "../../AbilityManager.h"
#include <sstream>


class IOInterface
{
public:
    virtual std::pair<int, int> readFieldSize() = 0;
    virtual std::map<int, int> readShipsMap() = 0;
    virtual std::pair<int, int> readCoordinates() = 0;
    virtual Battleship::Orientation readOrientation() = 0;
    virtual std::string readCommand() = 0;
    //virtual int readShipIndex()= 0;
    virtual void writeInfo(std::string info) = 0;
};

template<typename InputerT>
concept InputerConcept = requires(InputerT inputer, std::string info)
{
    {inputer.readFieldSize()}->std::same_as<std::pair<int, int>>;
    {inputer.readShipsMap()}->std::same_as<std::map<int, int>>;
    {inputer.readCoordinates()}->std::same_as<std::pair<int, int>>;
    {inputer.readOrientation()}->std::same_as<Battleship::Orientation>;
    {inputer.readCommand()}->std::same_as<std::string>;
    {inputer.writeInfo(info)}->std::same_as<void>;
};
template<InputerConcept Inputer>
class IODevice : public IOInterface
{
private:
    Inputer inpDevice;
public:
    template<typename ... Args>
    IODevice(Args&& ... args) : inpDevice(std::forward<Args>(args)...)  {}
    std::pair<int, int> readFieldSize()
    {
        return inpDevice.readFieldSize();
    }
    std::map<int, int> readShipsMap()
    {
        return inpDevice.readShipsMap();
    }
    std::pair<int, int> readCoordinates()
    {
        return inpDevice.readCoordinates();
    }
    Battleship::Orientation readOrientation()
    {
        return inpDevice.readOrientation();
    }
    std::string readCommand()
    {
        return inpDevice.readCommand();
    }
    void writeInfo(std::string info)
    {
        return inpDevice.writeInfo(info);
    }

};

template<typename Device>
class IODeviceWrapper : public IOInterface
{
private:
    IODevice<Device> unwrappedInpDevice;
public:
    template<typename ... Args>
    IODeviceWrapper(Args&& ... args) : unwrappedInpDevice(std::forward<Args>(args)...)  {}
    std::pair<int, int> readFieldSize()
    {
        return unwrappedInpDevice.readFieldSize();
    }
    std::map<int, int> readShipsMap()
    {
        return unwrappedInpDevice.readShipsMap();
    }
    std::pair<int, int> readCoordinates()
    {
        return unwrappedInpDevice.readCoordinates();
    }
    Battleship::Orientation readOrientation()
    {
        return unwrappedInpDevice.readOrientation();
    }
    std::string readCommand()
    {
        return unwrappedInpDevice.readCommand();
    }
    void writeInfo(std::string info)
    {
        return unwrappedInpDevice.writeInfo(info);
    }

};

#endif
