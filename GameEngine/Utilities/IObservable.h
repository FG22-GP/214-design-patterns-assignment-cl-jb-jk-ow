#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include "IClickObserver.h"

class IObservable
{
public:
    virtual void AddObserver(const std::string& id, std::shared_ptr<IClickObserver> observer) = 0;

    virtual void RemoveObserver(const std::string& id) = 0;

    virtual void NotifyObserver(const std::string& id) = 0;

    virtual void NotifyAll() = 0;

protected:
    std::unordered_map<std::string, std::shared_ptr<IClickObserver>> observers;
};
