#ifndef HTTPCAMERACONTROLLER_H
#define HTTPCAMERACONTROLLER_H

#include <QObject>
#include <QtNetwork>

#define API_CAMERA_IF_DIRECT "camera_if_direct"
typedef enum {
    E_FJ_MOVIE_VIDEO_SIZE_4000_3000	= 0,	/**< 4000x3000 */
    E_FJ_MOVIE_VIDEO_SIZE_4096_2304	= 1,	/**< 4096x2304 */
    E_FJ_MOVIE_VIDEO_SIZE_4096_2160	= 2,	/**< 4096x2160 */
    E_FJ_MOVIE_VIDEO_SIZE_4096_2048	= 3,	/**< 4096x2048 */
    E_FJ_MOVIE_VIDEO_SIZE_3840_2160	= 4,	/**< 3840x2160 */
    E_FJ_MOVIE_VIDEO_SIZE_3840_1920	= 5,	/**< 3840x1920 */
    E_FJ_MOVIE_VIDEO_SIZE_3000_3000	= 6,	/**< 3000x3000 */
    E_FJ_MOVIE_VIDEO_SIZE_2704_2028	= 7,	/**< 2704x2028 */
    E_FJ_MOVIE_VIDEO_SIZE_2704_1520	= 8,	/**< 2704x1520 */
    E_FJ_MOVIE_VIDEO_SIZE_2560_1920	= 9,	/**< 2560x1920 */
    E_FJ_MOVIE_VIDEO_SIZE_1920_1440	= 10,	/**< 1920x1440 */
    E_FJ_MOVIE_VIDEO_SIZE_1920_1080	= 11,	/**< 1920x1080 */
    E_FJ_MOVIE_VIDEO_SIZE_1920_960	= 12,	/**< 1920x960 */
    E_FJ_MOVIE_VIDEO_SIZE_1504_1504	= 13,	/**< 1504x1504 */
    E_FJ_MOVIE_VIDEO_SIZE_1440_1080	= 14,	/**< 1440x1080 */
    E_FJ_MOVIE_VIDEO_SIZE_1440_720	= 15,	/**< 1440x 720 */
    E_FJ_MOVIE_VIDEO_SIZE_1280_960	= 16,	/**< 1280x 960 */
    E_FJ_MOVIE_VIDEO_SIZE_1280_720	= 17,	/**< 1280x 720 */
    E_FJ_MOVIE_VIDEO_SIZE_960_480	= 18,	/**<  960x 480 */
    E_FJ_MOVIE_VIDEO_SIZE_864_480	= 19,	/**<  864x 480 */
    E_FJ_MOVIE_VIDEO_SIZE_848_480	= 20,	/**<  848x 480 */
    E_FJ_MOVIE_VIDEO_SIZE_720_480	= 21,	/**<  720x 480 */
    E_FJ_MOVIE_VIDEO_SIZE_640_480	= 22,	/**<  640x 480 */
    E_FJ_MOVIE_VIDEO_SIZE_640_360	= 23,	/**<  640x 360 */
    E_FJ_MOVIE_VIDEO_SIZE_432_240	= 24,	/**<  432x 240 */
    E_FJ_MOVIE_VIDEO_SIZE_320_240	= 25,	/**<  320x 240 */
    E_FJ_MOVIE_VIDEO_SIZE_720_576	= 26,
    E_FJ_MOVIE_VIDEO_SIZE_1024_768	= 27,
    E_FJ_MOVIE_VIDEO_SIZE_1280_768	= 28,
    E_FJ_MOVIE_VIDEO_SIZE_1280_1024	= 29,
    E_FJ_MOVIE_VIDEO_SIZE_800_600	= 30,
    E_FJ_MOVIE_VIDEO_SIZE_2560_1440	= 31,	/**< 2560x1440 */
    E_FJ_MOVIE_VIDEO_SIZE_960_540	= 32,
    E_FJ_MOVIE_VIDEO_SIZE_480_270	= 33,
    E_FJ_MOVIE_VIDEO_SIZE_1600_896	= 34,
    E_FJ_MOVIE_VIDEO_SIZE_1024_576	= 35,
    E_FJ_MOVIE_VIDEO_SIZE_800_448	= 36,
    E_FJ_MOVIE_VIDEO_SIZE_352_288	= 37,
    E_FJ_MOVIE_VIDEO_SIZE_2592_1944	= 38,
    E_FJ_MOVIE_VIDEO_SIZE_2304_1296	= 39,
    E_FJ_MOVIE_VIDEO_SIZE_1920_1280 = 40,
    E_FJ_MOVIE_VIDEO_SIZE_640_512 = 41,
    E_FJ_MOVIE_VIDEO_SIZE_384_288 = 42,
    E_FJ_MOVIE_VIDEO_SIZE_5472_3648 = 43,
    E_FJ_MOVIE_VIDEO_SIZE_3150_2100 = 44,
} E_FJ_MOVIE_VIDEO_SIZE;


extern const std::vector<float> SHUTTER_VALUE;
extern const std::vector<int> ISO_VALUE_INDEX;


class HttpCameraController : public QObject
{
    Q_OBJECT
public:
    explicit HttpCameraController(QString api, QObject *parent = nullptr);
    QNetworkReply *cameraIfDirect(uint32_t cmd_set, uint32_t cmd, uint32_t value);
    QNetworkReply *setAEMode(int mode);
    QNetworkReply *setISO(int index);
    QNetworkReply *setShutter(float shutter_sec);
    QNetworkReply *setSensorGain(float gain);
    QNetworkAccessManager *m_networkManager;

public slots:

private:
    QNetworkReply *post(QString api_name, QJsonObject json);
    QString m_api;
signals:

};

#endif // HTTPCAMERACONTROLLER_H
