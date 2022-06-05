#pragma once

class Organic
{
public:
    Organic(float initialEnergy, float energyInputRate = 10.0f, float energyOutputRate = 0.0f)
        : _energyStored(initialEnergy)
        , _energyInputRate(energyInputRate)
        , _energyOutputRate(energyOutputRate)
    {
    }

    float GiveEnergy(const float energyGiven)
    {
        float unusedEnergy = 0.0f;
        if(energyGiven <= _energyInputRate)
        {
            _energyStored += energyGiven;
        }
        else
        {
            _energyStored += _energyInputRate;
            unusedEnergy = energyGiven - _energyInputRate;
        }
        return unusedEnergy;
    }

    float TakeEnergy(const float energyRequested)
    {
        float energyTaken = energyRequested;
        if(energyRequested <= _energyStored)
        {
            _energyStored -= energyRequested;
        }
        else
        {
            energyTaken = _energyStored;
            _energyStored = 0.0f;
        }
        return energyTaken;
    }

    float Update()
    {
        float energyLost = _energyStored;
        if(_energyStored <= _energyOutputRate)
        {
            _energyStored = 0.0f;
        }
        else
        {
            _energyStored -= _energyOutputRate;
            energyLost = _energyOutputRate;
        }
        return energyLost;
    }

    float GetEnergy() const
    {
        return _energyStored;
    }

private:
    float _energyStored;
    float _energyInputRate;
    float _energyOutputRate;
};
