#include "httpcameracontroller.h"
#include <QJsonObject>


const std::vector<float> SHUTTER_VALUE = {0.00025f, 0.0005f, 0.000625f, 0.0008f, 0.001f, 0.00125f, 0.0015625f, 0.002f, 0.004f, 0.008f, 0.016f, 0.032f};
const std::vector<int> ISO_VALUE_INDEX = {0, 1, 2, 3, 4, 5, 6, 7};



const std::vector<FLIP_MIRROR_MODE> FLIP_MIRROR_MODE_OPTIONS = {
    FLIP_MIRROR_MODE_OFF,
    FLIP_MIRROR_MODE_MIRROR,
    FLIP_MIRROR_MODE_FLIP,
    FLIP_MIRROR_MODE_FLIP_MIRROR
};
//const std::vector<int> ISO_VALUE_INDEX = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

const std::vector<QString> AWB_SCENE_OPTIONS = {
    "-",
    "cloud",
    "daylight",
    "flash",
    "coolwhite",
    "tungsten",
    "candlelight",
    "horizon"
};


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
    return this->post(API_CAMERA_IF_DIRECT, &json);
}


QNetworkReply *HttpCameraController::post(QString api_name, QJsonObject *json){
    QEventLoop loop;
    QUrl url(this->m_api + api_name);
    qDebug() << url.toString();
    QNetworkRequest request(url);
    request.setRawHeader("User-Agent", "MyOwnBrowser 1.0");
    QNetworkReply * reply;
    if (json == NULL){
        reply = m_networkManager->post(request, (QIODevice *)NULL);
    }else {
        reply = m_networkManager->post(request, QJsonDocument(*json).toJson());
    }

    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    qDebug() << "loop over";
    reply->deleteLater();
    return reply;
}

QNetworkReply *HttpCameraController::syncTime(QString time){
    QJsonObject json{
        {"date", time}
    };
    return this->post(API_SYNC_TIME, &json);
}


QNetworkReply *HttpCameraController::setAEMode(QString mode) {
    QJsonObject json{
        {"mode", mode}
    };
    return this->post(API_AE_MODE, &json);
}


QNetworkReply *HttpCameraController::setISO(int iso) {
    QJsonObject json{
        {"value", iso}
    };
    this->post(API_MANUAL_ISO, &json);
    return this->post(API_AUTO_ISO, &json);
}

QNetworkReply *HttpCameraController::setShutter(QString shutter) {
    QJsonObject json{
        {"value", shutter}
    };
    return this->post(API_SHUTTER_SPEED, &json);
}

QNetworkReply *HttpCameraController::setSensorGain(float gain) {
//    return cameraIfDirect(0x3, 0x7, *(uint32_t *)&gain);
    return NULL;
}

QNetworkReply *HttpCameraController::setFlipMirrorMode(FLIP_MIRROR_MODE mode){
    return cameraIfDirect(0x1, 0x24, mode);
}


QNetworkReply *HttpCameraController::setMShutter(bool m_shutter){
    return cameraIfDirect(0xb, 0x7, m_shutter ? 1 : 0);
}

QNetworkReply *HttpCameraController::setEV(float ev){
    return cameraIfDirect(0x3, 0x6, *(uint32_t *)&ev);
}

QNetworkReply *HttpCameraController::startPreview(){
    return cameraIfDirect(0x0, 0xb, 0x2);
}

QNetworkReply *HttpCameraController::setAWBScene(int scene, int value){
    return cameraIfDirect(0x6, 0x4, scene);
}

QNetworkReply *HttpCameraController::setAWBMode(int mode){
    return cameraIfDirect(0x6, 0x0, mode);
}

QNetworkReply *HttpCameraController::setDZoom(float zoom){
    QJsonObject json{
        {"value", QString::number(zoom)}
    };
    return this->post(API_DIGITAL_ZOOM, &json);
}

QNetworkReply *HttpCameraController::capturePic(){
    return this->post(API_TAKE_PHOTO, NULL);
}

QNetworkReply *HttpCameraController::setJpegResolution(){
    //todo
    return NULL;
}

QNetworkReply *HttpCameraController::setPhotoPath(QString path, QString prefix){
    QJsonObject obj
    {
        {"cmd","PhotoStorage"},
        {"data", ""}
    };

    obj["data"] = QJsonObject
    {
        {"path", path},
        {"prefix", prefix}
    };
    return nullptr;
}

