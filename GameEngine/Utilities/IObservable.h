#pragma once
#include <string>
#include <unordered_map>
#include "IClickObserver.h"

class IObservable
{
public:
    virtual void AddObserver(const std::string& id, IClickObserver* observer) = 0;

    virtual void RemoveObserver(const std::string& id) = 0;

    virtual void NotifyObserver(const std::string& id) = 0;

    virtual void NotifyAll() = 0;

protected:
    std::unordered_map<std::string, IClickObserver*> observers;
};
