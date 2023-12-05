#pragma once

struct GameState
{
    GameState() : AmountInBank(0), AutoClickersAmount(0) {}
    
    int AmountInBank;
    int AutoClickersAmount;
    // Add new fields for each building
};
