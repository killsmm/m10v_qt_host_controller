#include "messagereceiver.h"
#include "QtDebug"


MessageReceiver::MsgRecvThread::MsgRecvThread(MessageReceiver *receiver, QObject *parent){
    this->receiver = receiver;
}

void MessageReceiver::MsgRecvThread::run(){
    zmqContext = new zmq::context_t();
    zmq::socket_t zmqSocket(*zmqContext, zmq::socket_type::sub);
    zmqSocket.connect(MUTIMEDIA_SERVER_MQ);
    char filter[] = "jpeg";
//    zmqSocket.setsockopt(ZMQ_SUBSCRIBE, filter, strlen(filter));
    zmqSocket.set(zmq::sockopt::subscribe, filter);
    zmq::message_t msg;

    while (!this->threadAbort) {
        if(zmqSocket.recv(msg, zmq::recv_flags::dontwait)){
            qDebug() << "msg received " << msg.size();
            emit receiver->messageReceived(QString(static_cast<const char*>(msg.data()))) ;
        }
    }
    zmqSocket.close();
    zmqContext->close();
}

void MessageReceiver::MsgRecvThread::setThreadAbort(bool is_abort){
    this->threadAbort = is_abort;
}

MessageReceiver::MessageReceiver(QObject *parent) : QObject(parent)
{

}




void MessageReceiver::start_receive()
{
    msgRecvThread = new MsgRecvThread(this);
    msgRecvThread->setThreadAbort(false);
    msgRecvThread->start();
}

void MessageReceiver::stop_receive()
{
    msgRecvThread->setThreadAbort(true);
    msgRecvThread->wait();
}
