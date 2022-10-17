#include "BackpackModel.h"
#include <QRandomGenerator>
#include <QtMath>
#include <QDebug>

BackpackModel::BackpackModel(QObject *parent) : QObject(parent)
{
    _timer.setInterval(1000);
    _timer.start();
    connect(&_timer, &QTimer::timeout, this, &BackpackModel::onTimerTicked);

}

void BackpackModel::startNewGame(int size)
{
    _elapsedTime = 0;
    _things.clear();
    _backpackThings.clear();
    _elemSize = size;
    _backpackCapacity = 5;
    _backpackRemainingCapacity = 5;

    for(int i = 0; i < _elemSize; i++) {
        Thing randomThing = (Thing)QRandomGenerator::global()->bounded(0, 6);
        _things.push_back(randomThing);
    }

    for(int i = 0; i < _elemSize; i++) {
        _backpackThings.push_back(none);
    }

    emit gameCreated();
}

void BackpackModel::thingButtonPressed(int n) {
    Thing tempThing = _things[n];

    if (_backpackRemainingCapacity - vols[(int)tempThing] >= 0 && tempThing != none) {
        for (int i = 0; i < _elemSize; i++) {
            if (_backpackThings[i] == none) {
                _backpackThings[i] = tempThing;
                _things[n] = none;
                _backpackRemainingCapacity -= vols[(int)tempThing];
                break;
            }
        }
        emit gameUpdated();
    }
}

void BackpackModel::backpackButtonPressed(int n) {
    Thing tempThing = _backpackThings[n];

    if (tempThing != none) {
        for (int i = 0; i < _elemSize; i++) {
            if (_things[i] == none) {
                _things[i] = tempThing;
                _backpackThings[n] = none;
                _backpackRemainingCapacity += vols[(int)tempThing];
                break;
            }
        }
        emit gameUpdated();
    }
}

int BackpackModel::getContainedElementsValue() {
    int val = 0;
    for (int i = 0; i < _elemSize; i++) {
        val += vals[(int)_backpackThings[i]];
    }
    return val;
}

int BackpackModel::getContainedElementsVolume() {
    int vol = 0;
    for (int i = 0; i < _elemSize; i++) {
        vol += vols[(int)_backpackThings[i]];
    }
    return vol;
}

int BackpackModel::getElemSize() const {
    return _elemSize;
}

int BackpackModel::getBackpackCapacity() const
{
    return _backpackCapacity;
}

int BackpackModel::getBackpackRemainingCapacity()
{
    return _backpackRemainingCapacity;
}

Thing BackpackModel::getThing(int i)
{
    return _things[i];
}

Thing BackpackModel::getBackpackThing(int i)
{
    return _backpackThings[i];
}

int BackpackModel::getElapsedTime()
{
    return _elapsedTime;
}

void BackpackModel::onTimerTicked()
{
    _elapsedTime++;
    emit timerTick();
}
