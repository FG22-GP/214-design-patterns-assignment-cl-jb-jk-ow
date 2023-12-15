[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/XUCedPox)
# Clicker $^{2}$ 

## Contributors

Carl Lindstedt, Joakim Karbing, Oskar Wistedt, Joseph Binns

## Description

Our team made a clicker game featuring upgrades, save game and flashy VFX.
Clicking gives you currency, which can be spent in the shop to buy upgrades which increase your currency over time.
As you make more "money" (cubes) the VFX gets more intense.

<img alt="Gameplay gif" width="965" src="https://github.com/FG22-GP/214-design-patterns-assignment-cl-jb-jk-ow/blob/main/Screenshots/square-clicker.gif"/>

## Design Patterns

### Object Pool Pattern

In order to minimise the creation and destruction of memory, we opted to use object pooling ([Pool.h](https://github.com/FG22-GP/214-design-patterns-assignment-cl-jb-jk-ow/blob/main/GameEngine/Utilities/Pool.h)) to support various visual effects.
These effects included click feedback ([ClickVFX.h](https://github.com/FG22-GP/214-design-patterns-assignment-cl-jb-jk-ow/blob/main/GameEngine/VFX/ClickVFX.h)) and raining squares ([CubeRain.h](https://github.com/FG22-GP/214-design-patterns-assignment-cl-jb-jk-ow/blob/main/GameEngine/Utilities/CubeRain.h)).

### Observer Pattern

To manage references in a modular fashion, we used the observer pattern.
The input manager ([InputManager.h](https://github.com/FG22-GP/214-design-patterns-assignment-cl-jb-jk-ow/blob/main/GameEngine/Input/InputManager.h)) keeps a vector of observers ([IObservable.h](https://github.com/FG22-GP/214-design-patterns-assignment-cl-jb-jk-ow/blob/main/GameEngine/Utilities/IObservable.h)) and their unique ids.
The input manager can then notify a set of observers.
The observers being notified will then call their implementation of OnNotify which is specific to the individual observer-derived classes.
For example, cube button ([CubeButton.cpp](https://github.com/FG22-GP/214-design-patterns-assignment-cl-jb-jk-ow/blob/main/GameEngine/ConcreteObjects/CubeButton.cpp)) inherits from the click observer class ([IClickObserver.h](https://github.com/FG22-GP/214-design-patterns-assignment-cl-jb-jk-ow/blob/main/GameEngine/Utilities/IClickObserver.h)).

### Smart Pointers

After some testing, we discovered that the build had memory leak.
This was largely inpart due to our use of raw pointers.
We switched to using smart pointers wherever possible, and added our own precautions to avoid additive memory allocation in the Update loop.

## Screenshots
<img alt="Screenshot before" width="480" src="https://github.com/FG22-GP/214-design-patterns-assignment-cl-jb-jk-ow/blob/main/Screenshots/square-clicker-0.png"/> <img alt="Screenshot after" width="480" src="https://github.com/FG22-GP/214-design-patterns-assignment-cl-jb-jk-ow/blob/main/Screenshots/square-clicker-1.png"/>
