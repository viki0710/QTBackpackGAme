#ifndef BACKPACKWINDOW_H
#define BACKPACKWINDOW_H

#include "BackpackModel.h"

#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QWidget>

class BackpackWindow : public QWidget
{
    Q_OBJECT

public:
    BackpackWindow(QWidget *parent = nullptr);
    ~BackpackWindow();
private:
    BackpackModel* _model;
    QVBoxLayout* _mainLayout;
    QGridLayout* _thingButtonLayout;
    QGridLayout* _backpackButtonLayout;
    QHBoxLayout* _newGameRow;
    QHBoxLayout* _infoRow;
    QLabel* _infoLabel;
    QVector<QPushButton*> _thingsButtonVector;
    QVector<QPushButton*> _backpackButtonVector;
    QPushButton* _newGameButton;

    void setButtonStyle(QPushButton* button, Thing thing);
private slots:
    void onGameCreated();
    void onGameUpdated();
    void onTimerTick();
};
#endif // BACKPACKWINDOW_H
