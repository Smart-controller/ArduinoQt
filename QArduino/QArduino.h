#ifndef QARDUINO_H
#define QARDUINO_H

#include <QObject>
#include <QtBluetooth>

class QArduino : public QObject
{
    Q_OBJECT

    typedef struct{
        QString name;
        QVariant value;
    } arduinoAttribute;
public:
    explicit QArduino( QString bluetoothName, QObject *parent = 0);

    QList<arduinoAttribute> attributeList();
    arduinoAttribute attribute(QString attributeName);

signals:
    void connectionStatus(bool status);

    void attributeReceived(QString name, QVariant value);
    void attributeReceived(QString name, int value);
    void attributeReceived(QString name, QString value);
    void attributeReceived(arduinoAttribute attribute);
public slots:

private slots:
    void handleSocketConnected();
    void handleSocketDisconnected();
    void handleSocketError(QBluetoothSocket::SocketError error);
    void handleSocketReadyRead();

    void handleServiceDiscovered(QBluetoothServiceInfo service);
    void handleServiceDiscoveryError(QBluetoothServiceDiscoveryAgent::Error error);

private:
    QBluetoothSocket *socket;
    QBluetoothServiceDiscoveryAgent *discovery;
    QString deviceNameToConnect;
    QByteArray readBuffer;
};

#endif // QARDUINO_H
