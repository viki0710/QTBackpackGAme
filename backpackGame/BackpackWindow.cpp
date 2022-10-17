#include "BackpackWindow.h"

#include <QMessageBox>

BackpackWindow::BackpackWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Color game");
    setFixedSize(500, 560);

    _mainLayout = new QVBoxLayout();
    setLayout(_mainLayout);

    _newGameRow = new QHBoxLayout();
    _newGameButton = new QPushButton("New game");
    _newGameButton->setFixedHeight(60);
    _newGameRow->addWidget(_newGameButton);
    _mainLayout->addLayout(_newGameRow);

    _thingButtonLayout = new QGridLayout();
    _mainLayout->addLayout(_thingButtonLayout);

    _backpackButtonLayout = new QGridLayout();
    _mainLayout->addLayout(_backpackButtonLayout);

    _infoRow = new QHBoxLayout();
    _infoRow->setAlignment(Qt::AlignLeft);
    _infoLabel = new QLabel("Contents value:\nContents volume:\nBackpack capacity:\nRemaining space:");
    _infoRow->addWidget(_infoLabel);
    _mainLayout->addLayout(_infoRow);

    _model = new BackpackModel(this);

    connect(_model, &BackpackModel::gameCreated, this, &BackpackWindow::onGameCreated);
    connect(_model, &BackpackModel::gameUpdated, this, &BackpackWindow::onGameUpdated);
    connect(_newGameButton, &QPushButton::clicked, this, [this](){ _model->startNewGame(3); });
    connect(_model, &BackpackModel::timerTick, this, &BackpackWindow::onTimerTick);
    _model->startNewGame(3);
}

BackpackWindow::~BackpackWindow()
{
}

void BackpackWindow::setButtonStyle(QPushButton *button, Thing thing)
{
    switch(thing) {
        case Thing::pen:
            button->setStyleSheet("background-color: red");
            button->setText("Pen, val:2, vol:1");
            break;
        case Thing::pencil:
            button->setStyleSheet("background-color: blue");
            button->setText("Pencil, val:1, vol:1");
            break;
        case Thing::book:
            button->setStyleSheet("background-color: yellow");
            button->setText("Book, val:4, vol:4");
            break;
        case Thing::phone:
            button->setStyleSheet("background-color: green");
            button->setText("Phone, val:5, vol:2");
            break;
        case Thing::keys:
            button->setStyleSheet("background-color: orange");
            button->setText("Keys, val:2, vol:2");
            break;
        case Thing::notebook:
            button->setStyleSheet("background-color: purple");
            button->setText("Notebook, val:3, vol:3");
            break;
        case Thing::none:
            button->setStyleSheet("background-color: white");
            button->setText("");
            break;
    }
}

void BackpackWindow::onGameCreated()
{
    while(QLayoutItem* item = _thingButtonLayout->takeAt(0)) {
        delete item->widget();
        delete item;
    }
    _thingsButtonVector.clear();

    while(QLayoutItem* item = _backpackButtonLayout->takeAt(0)) {
        delete item->widget();
        delete item;
    }
    _backpackButtonVector.clear();

    _infoLabel->setText("Time: " + QString::number(_model->getElapsedTime()) + "\nContents value: " + QString::number(_model->getContainedElementsValue()) + "\nContents volume: " +  QString::number(_model->getContainedElementsVolume()) + "\nBackpack capacity:" +  QString::number(_model->getBackpackCapacity()) + "\nRemaining space: " +  QString::number(_model->getBackpackRemainingCapacity()));

    int size = _model->getElemSize();

    for(int i = 0; i < size; i++) {
        QPushButton* button = new QPushButton();
        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        Thing thing = _model->getThing(i);
        setButtonStyle(button, thing);

        connect(button, &QPushButton::clicked, this, [i, this](){ _model->thingButtonPressed(i); });

        _thingButtonLayout->addWidget(button, 0, i);
        _thingsButtonVector.append(button);
    }

    for(int i = 0; i < size; i++) {
        QPushButton* button = new QPushButton();
        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        Thing thing = _model->getBackpackThing(i);
        setButtonStyle(button, thing);

        connect(button, &QPushButton::clicked, this, [i, this](){ _model->backpackButtonPressed(i); });

        _backpackButtonLayout->addWidget(button, 0, i);
        _backpackButtonVector.append(button);
    }
}

void BackpackWindow::onGameUpdated()
{
    int size = _model->getElemSize();
    for(int i = 0; i < size; i++) {
        Thing thing = _model->getThing(i);
        setButtonStyle(_thingsButtonVector[i], thing);
    }

    for(int i = 0; i < size; i++) {
        Thing thing = _model->getBackpackThing(i);
        setButtonStyle(_backpackButtonVector[i], thing);
    }

    _infoLabel->setText("Time: " + QString::number(_model->getElapsedTime()) + "\nContents value: " + QString::number(_model->getContainedElementsValue()) + "\nContents volume: " +  QString::number(_model->getContainedElementsVolume()) + "\nBackpack capacity:" +  QString::number(_model->getBackpackCapacity()) + "\nRemaining space: " +  QString::number(_model->getBackpackRemainingCapacity()));
}

void BackpackWindow::onTimerTick(){
    _infoLabel->setText("Time: " + QString::number(_model->getElapsedTime()) + "\nContents value: " + QString::number(_model->getContainedElementsValue()) + "\nContents volume: " +  QString::number(_model->getContainedElementsVolume()) + "\nBackpack capacity:" +  QString::number(_model->getBackpackCapacity()) + "\nRemaining space: " +  QString::number(_model->getBackpackRemainingCapacity()));
}

