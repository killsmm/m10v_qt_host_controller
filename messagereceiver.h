#ifndef MESSAGERECEIVER_H
#define MESSAGERECEIVER_H

#include <QObject>
#include "zmq.hpp"
#include <QThread>

#define MUTIMEDIA_SERVER_MQ "tcp://192.168.137.16:8101"

class MessageReceiver : public QObject
{
    Q_OBJECT
public:
    explicit MessageReceiver( QObject *parent = nullptr);
    void start_receive();
    void stop_receive();
    class MsgRecvThread : public QThread {
    public:
        MsgRecvThread(MessageReceiver *receiver, QObject *parent = nullptr);
        void setThreadAbort(bool is_abort);
    private:
        MessageReceiver *receiver;
        void run();
        bool threadAbort;
        zmq::context_t *zmqContext;
    } *msgRecvThread;
signals:
    void messageReceived(QString msg);
};

#endif // MESSAGERECEIVER_H
