#include "httpcameracontroller.h"
#include <QJsonObject>


const std::vector<float> SHUTTER_VALUE = {0.00025f, 0.0005f, 0.000625f, 0.0008f, 0.001f, 0.00125f, 0.0015625f, 0.002f, 0.004f, 0.008f, 0.016f, 0.032f};
const std::vector<int> ISO_VALUE_INDEX = {0, 1, 2, 3, 4, 5, 6, 7};
//const std::vector<int> ISO_VALUE_INDEX = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};



HttpCameraController::HttpCameraController(QString api, QObject *parent)
    : QObject{parent}
{
    this->m_api = api;
    m_networkManager = new QNetworkAccessManager();
}

QNetworkReply *HttpCameraController::cameraIfDirect(uint32_t cmd_set, uint32_t cmd, uint32_t value){
    qDebug() << value;
    QJsonObject json(
    {
        {"arg1", std::to_string(cmd_set).c_str()},
        {"arg2", std::to_string(cmd).c_str()},
        {"arg3", std::to_string(value).c_str()}
    });
    return this->post(API_CAMERA_IF_DIRECT, json);
}

QNetworkReply *HttpCameraController::post(QString api_name, QJsonObject json){
    QUrl url(this->m_api + api_name);
    qDebug() << url.toString();
    QNetworkRequest request(url);
    request.setRawHeader("User-Agent", "MyOwnBrowser 1.0");
    qDebug() << QJsonDocument(json).toJson();
    return m_networkManager->post(request, QJsonDocument(json).toJson());
}

QNetworkReply *HttpCameraController::setAEMode(int mode) {
    return cameraIfDirect(0x3, 0x1, mode);
}


QNetworkReply *HttpCameraController::setISO(int index) {
    return cameraIfDirect(0x3, 0x4, index);
}

QNetworkReply *HttpCameraController::setShutter(float shutter_sec) {
    return cameraIfDirect(0x3, 0x8, *(uint32_t *)&shutter_sec);
}

QNetworkReply *HttpCameraController::setSensorGain(float gain) {
    return cameraIfDirect(0x3, 0x7, *(uint32_t *)&gain);
}
