#include "QArduino.h"
#include <QDebug>

QArduino::QArduino(QString bluetoothName, QObject *parent) : QObject(parent)
{

    deviceNameToConnect = bluetoothName;

    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    connect(socket, SIGNAL(connected()), this, SLOT(handleSocketConnected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(handleSocketDisconnected()));
    connect(socket, SIGNAL(error(QBluetoothSocket::SocketError)),
            this, SLOT(handleSocketError(QBluetoothSocket::SocketError)));
    connect(socket, SIGNAL(readyRead()), this, SLOT(handleSocketReadyRead()));

    discovery = new QBluetoothServiceDiscoveryAgent();
    connect(discovery, SIGNAL(error(QBluetoothServiceDiscoveryAgent::Error)),
            this, SLOT(handleServiceDiscoveryError(QBluetoothServiceDiscoveryAgent::Error)));

    connect(discovery, SIGNAL(serviceDiscovered(QBluetoothServiceInfo)),
            this, SLOT(handleServiceDiscovered(QBluetoothServiceInfo)));
    discovery->start();
}


void QArduino::handleSocketConnected()
{
    qDebug() << "QArduino::handleSocketConnected";
}

void QArduino::handleSocketDisconnected()
{
    qDebug() << "QArduino::handleSocketDisconnected";
}

void QArduino::handleSocketError(QBluetoothSocket::SocketError error)
{
    qDebug() << "QArduino::handleSocketError error:" << error;
}

void QArduino::handleSocketReadyRead()
{
    qDebug() << "QArduino::handleSocketReadyRead";
    readBuffer += socket->readAll();

    if(readBuffer.count() >= 2)
    {
        bool ok;
        uint16_t fullLength = readBuffer.mid(0,2).toUInt(&ok);
        if( ok &&
            ((readBuffer.count() -2 ) >= fullLength))
        {
            //Remove the fullLength
            readBuffer.remove(0, 2);
            uint8_t nameLength = (uint8_t)readBuffer.at(0);
            if( (nameLength -1) > readBuffer.count())
            {
                qDebug() << "Error (nameLength -1) > readBuffer.count()";
                return;
            }
            QString name = QString::fromLocal8Bit(readBuffer.mid(1, nameLength));
            readBuffer.remove(0, 1+nameLength);
            if(readBuffer.count() < 2)
            {
                qDebug() << "Error readBuffer.count() < 2";
            }
            uint8_t dataType = (uint8_t)readBuffer.at(0);
            uint8_t dataLength = (uint8_t)readBuffer.at(1);


        }
        //else data for this packet haven't arrive in buffer
    }

    //uint16 fulllength
    //uint8 name length
    //QString name 1-256 char
    //uint8 dataType
    //0 bool
    //1 uint8
    //2 uint16
    //3 uint32
    //4 int8
    //5 int16
    //6 int32
    //7 float32
    //8 string
    //data length 1byte
    //data
}

void QArduino::handleServiceDiscovered(QBluetoothServiceInfo service)
{
    qDebug() << "QArduino::handleServiceDiscovered name:" << service.device().name();
    if( (service.device().name() == deviceNameToConnect) &&
        !deviceNameToConnect.isEmpty() &&
        (service.socketProtocol() == QBluetoothServiceInfo::RfcommProtocol))
    {
        qDebug() << "QArduino::handleServiceDiscovered connectToService";
        socket->connectToService(service);
    }
}

void QArduino::handleServiceDiscoveryError(QBluetoothServiceDiscoveryAgent::Error error)
{
    qDebug() << "QArduino::handleServiceDiscoveryError error:" << error;
}
