#ifndef BACKPACKMODEL_H
#define BACKPACKMODEL_H

#include <QObject>
#include <QTimer>
#include <QVector>

enum Thing
{
    pen, pencil, book, phone, keys, notebook, none
};

class BackpackModel : public QObject
{
    Q_OBJECT
public:
    explicit BackpackModel(QObject *parent = nullptr);
    void startNewGame(int size);
    void thingButtonPressed(int i);
    void backpackButtonPressed(int i);
    int getElemSize() const;
    int getBackpackCapacity() const;
    int getBackpackRemainingCapacity(); //const?
    int getContainedElementsValue();
    int getContainedElementsVolume();
    Thing getThing(int i);
    Thing getBackpackThing(int i);
    int getElapsedTime();

private:
    QVector<int> vals = {2, 1, 4, 5, 2, 3, 0};
    QVector<int> vols = {1, 1, 4, 2, 2, 3, 0};
    int _elemSize;
    int _backpackCapacity;
    int _backpackRemainingCapacity;
    QVector<Thing> _things;
    QVector<Thing> _backpackThings;
    int _elapsedTime;
    QTimer _timer;

signals:
    void gameCreated();
    void gameUpdated();
    void timerTick();

private slots:
    void onTimerTicked();
};

#endif // BACKPACKMODEL_H
