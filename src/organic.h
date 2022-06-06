#pragma once

// https://en.wikipedia.org/wiki/Plant_anatomy#/media/File:Plant_Anatomy.svg


class Organic
{
public:
    Organic(float initialEnergy, float energyInputRate = 0.0f, float energyOutputRate = 0.0f)
        : _energyStored(initialEnergy)
        , _energyInputRate(energyInputRate)
        , _energyOutputRate(energyOutputRate)
    {
    }

    float TransferEnergy(Organic& receiver, float amount)
    {
        // Return effectively transferred energy
        return receiver.GiveEnergy(TakeEnergy(amount));
    }

    float GiveEnergy(float energyGiven)
    {
        float unusedEnergy = 0.0f;

        if (energyGiven <= _energyInputRate || _energyInputRate == 0.0f)
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

    float TakeEnergy(float energyRequested)
    {
        if(_energyOutputRate != 0.0f && energyRequested <= _energyOutputRate)
        {
            energyRequested = _energyOutputRate;
        }

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

    float GetEnergy() const
    {
        return _energyStored;
    }

private:
    float _energyStored;
    float _energyInputRate;
    float _energyOutputRate;
};
