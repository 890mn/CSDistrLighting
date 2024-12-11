#ifndef SIMCONTROLLER_H
#define SIMCONTROLLER_H

#include <QObject>
#include <QDebug>

class SimController : public QObject
{
    Q_OBJECT
public:
    explicit SimController(QObject *parent = nullptr) : QObject(parent) {}

public slots:
    void startSimulation() {
        // Your simulation logic here
        qDebug() << "Simulation started!";
    }
};

#endif // SIMCONTROLLER_H
