[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/XUCedPox)
# Clicker $^2$ 

## Design Patterns

### Pool
In order to minimise the creation and destruction of memory, we opted to use object pooling ([Pool.h](https://github.com/FG22-GP/214-design-patterns-assignment-cl-jb-jk-ow/blob/main/GameEngine/Utilities/Pool.h)) to support various visual effects.
These effects included click feedback ([ClickVFX.h](https://github.com/FG22-GP/214-design-patterns-assignment-cl-jb-jk-ow/blob/main/GameEngine/VFX/ClickVFX.h)) and raining squares ([CubeRain.h](https://github.com/FG22-GP/214-design-patterns-assignment-cl-jb-jk-ow/blob/main/GameEngine/Utilities/CubeRain.h)).

### Observer Pattern
The input manager ([InputManager.h](https://github.com/FG22-GP/214-design-patterns-assignment-cl-jb-jk-ow/blob/main/GameEngine/Input/InputManager.h)) keeps a vector of observers ([IObservable.h](https://github.com/FG22-GP/214-design-patterns-assignment-cl-jb-jk-ow/blob/main/GameEngine/Utilities/IObservable.h)) and their unique ids.
The input manager can then notify a set of observers.
The observers being notified will then call their implementation of OnNotify which is specific to the individual observer-derived classes.
For example, cube button ([CubeButton.cpp](https://github.com/FG22-GP/214-design-patterns-assignment-cl-jb-jk-ow/blob/main/GameEngine/ConcreteObjects/CubeButton.cpp)) inherits from the click observer class ([IClickObserver.h](https://github.com/FG22-GP/214-design-patterns-assignment-cl-jb-jk-ow/blob/main/GameEngine/Utilities/IClickObserver.h)).
