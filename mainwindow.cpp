#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMediaPlayer>
#include "httpcameracontroller.h"
#include "messagereceiver.h"
#include <QDir>
#include "filedownloader.h"
#include "QDesktopServices"

static int get_iso_value(int index){
    if(index == 0){
        return 100;
    }else if (index == 1){
        return 50;
    }else {
        return (pow(2, (index - 2)) * 100);
    }
}

void MainWindow::switchAEUIMode(int mode){
    if(ui->comboBox_7->currentText() == "Mannual"){
        ui->label_shutter->show();
        ui->comboBox_shutter->show();
        ui->label_ev->hide();
        ui->comboBox_ev->hide();
    }else{
        ui->label_shutter->hide();
        ui->comboBox_shutter->hide();
        ui->label_ev->show();
        ui->comboBox_ev->show();
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->m_cam_controller = new HttpCameraController(QString("http://192.168.137.16:8080/api/camera/"));
    QObject::connect(this->m_cam_controller->m_networkManager,
                     &QNetworkAccessManager::finished,
                     this, [=](QNetworkReply *reply){
        ui->textEdit->append(reply->readAll());
        reply->deleteLater();
    });
    jpeg_path = QDir::currentPath();
    file_dialog = new QFileDialog(nullptr, "select path to restore images");
    file_dialog->setFileMode(QFileDialog::Directory);
    file_dialog->setOption(QFileDialog::ShowDirsOnly, true);
    QObject::connect(this->file_dialog, SIGNAL(fileSelected(QString)), this, SLOT(setLocalJpegPath(QString)));

    this->m_webView = new CameraWebView();
    ui->widget->parentWidget()->layout()->replaceWidget(ui->widget, this->m_webView);
    this->m_webView->show();

    for (float v : SHUTTER_VALUE){
        ui->comboBox_shutter->addItem(QString("1/%1").arg(1 / v));
    }

    for (int i : ISO_VALUE_INDEX){
        if(i == 0){
            ui->comboBox_iso->addItem(QString("auto"));
        }else{
            ui->comboBox_iso->addItem(QString::number(get_iso_value(i)));
        }
    }

    switchAEUIMode(ui->comboBox_7->currentIndex());

    receiver = new MessageReceiver();
    QObject::connect(receiver, SIGNAL(messageReceived(QString)), this, SLOT(onMqMsgReceived(QString)));
    receiver->start_receive();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_cam_controller;
    delete m_webView;
}



void MainWindow::on_pushButton_9_clicked()
{
    this->m_cam_controller->cameraIfDirect(0x0, 0xb, 0x2);
}



void MainWindow::on_pushButton_take_photo_clicked()
{
    this->m_cam_controller->cameraIfDirect(0x0, 0xb, 0x3);
}




void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    switch (index){
    case 1:
        this->m_cam_controller->cameraIfDirect(0x1, 0xc, E_FJ_MOVIE_VIDEO_SIZE_3840_2160);
        this->m_cam_controller->cameraIfDirect(0x1, 0xe, E_FJ_MOVIE_VIDEO_SIZE_3840_2160);
        this->m_cam_controller->cameraIfDirect(0x1, 0xf, E_FJ_MOVIE_VIDEO_SIZE_3840_2160);
        this->m_cam_controller->cameraIfDirect(0xb, 0x0, 4000);
        this->m_cam_controller->cameraIfDirect(0xb, 0x1, 3000);
        break;
    case 2:
        this->m_cam_controller->cameraIfDirect(0x1, 0xc, E_FJ_MOVIE_VIDEO_SIZE_3840_2160);
        this->m_cam_controller->cameraIfDirect(0x1, 0xe, E_FJ_MOVIE_VIDEO_SIZE_3840_2160);
        this->m_cam_controller->cameraIfDirect(0x1, 0xf, E_FJ_MOVIE_VIDEO_SIZE_3840_2160);
        this->m_cam_controller->cameraIfDirect(0xb, 0x0, 3840);
        this->m_cam_controller->cameraIfDirect(0xb, 0x1, 2160);
        break;
    case 3:
        this->m_cam_controller->cameraIfDirect(0x1, 0xc, E_FJ_MOVIE_VIDEO_SIZE_3840_2160);
        this->m_cam_controller->cameraIfDirect(0x1, 0xe, E_FJ_MOVIE_VIDEO_SIZE_3840_2160);
        this->m_cam_controller->cameraIfDirect(0x1, 0xf, E_FJ_MOVIE_VIDEO_SIZE_3840_2160);
        this->m_cam_controller->cameraIfDirect(0xb, 0x0, 1920);
        this->m_cam_controller->cameraIfDirect(0xb, 0x1, 1080);
        break;
    case 4:
        this->m_cam_controller->cameraIfDirect(0x1, 0xc, E_FJ_MOVIE_VIDEO_SIZE_3840_2160);
        this->m_cam_controller->cameraIfDirect(0x1, 0xe, E_FJ_MOVIE_VIDEO_SIZE_3840_2160);
        this->m_cam_controller->cameraIfDirect(0x1, 0xf, E_FJ_MOVIE_VIDEO_SIZE_3840_2160);
        this->m_cam_controller->cameraIfDirect(0xb, 0x0, 1280);
        this->m_cam_controller->cameraIfDirect(0xb, 0x1, 720);
        break;
    case 5:
        this->m_cam_controller->cameraIfDirect(0x1, 0xc, E_FJ_MOVIE_VIDEO_SIZE_3840_2160);
        this->m_cam_controller->cameraIfDirect(0x1, 0xe, E_FJ_MOVIE_VIDEO_SIZE_3840_2160);
        this->m_cam_controller->cameraIfDirect(0x1, 0xf, E_FJ_MOVIE_VIDEO_SIZE_3840_2160);
        this->m_cam_controller->cameraIfDirect(0xb, 0x0, 5472);
        this->m_cam_controller->cameraIfDirect(0xb, 0x1, 3648);
        break;
    case 6:
        this->m_cam_controller->cameraIfDirect(0x1, 0xc, E_FJ_MOVIE_VIDEO_SIZE_3840_2160);
        this->m_cam_controller->cameraIfDirect(0x1, 0xe, E_FJ_MOVIE_VIDEO_SIZE_3840_2160);
        this->m_cam_controller->cameraIfDirect(0x1, 0xf, E_FJ_MOVIE_VIDEO_SIZE_3840_2160);
        this->m_cam_controller->cameraIfDirect(0xb, 0x0, 6144);
        this->m_cam_controller->cameraIfDirect(0xb, 0x1, 4096);
        break;
    }
}



void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    this->m_cam_controller->cameraIfDirect(0xb, 0x6, value);
    ui->label_4->setText(QString(std::to_string(value).c_str()));
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    float zoom = 1.0f + 3.0f * value / 100;
    this->m_cam_controller->cameraIfDirect(0x1, 0x21, *(uint32_t *)&zoom);
}


void MainWindow::on_horizontalSlider_x_valueChanged(int value)
{
    float x = 1.0f * value / 100;
    this->m_cam_controller->cameraIfDirect(0x1, 0x22, *(uint32_t *)&x);
}


void MainWindow::on_verticalSlider_Y_valueChanged(int value)
{
    float y = 1.0f * value / 100;
    this->m_cam_controller->cameraIfDirect(0x1, 0x23, *(uint32_t *)&y);
}


void MainWindow::on_pushButton_clicked()
{
    int iso_index = ui->comboBox_iso->currentIndex();
    this->m_cam_controller->setISO(iso_index);

    int shutter_index = ui->comboBox_shutter->currentIndex();
    float m_shutter = SHUTTER_VALUE[shutter_index];
    this->m_cam_controller->setShutter(m_shutter);

    int iso_value = get_iso_value(iso_index);
    float m_gain = (log2(0.32f * iso_value) - 4) * 6;
    this->m_cam_controller->setSensorGain(m_gain);
    qDebug() << "gain = " << m_gain << " shutter = " << m_shutter;
}


void MainWindow::on_comboBox_7_activated(int index)
{
    this->switchAEUIMode(index);
    this->m_cam_controller->setAEMode(index);
}

void MainWindow::onMqMsgReceived(QString msg){
    qDebug() << "msg received" << msg;
    QString url = "http://192.168.137.16/" + msg.remove(QRegExp("jpeg: /run/SD/mmcblk0p1/"));
    qDebug() << url;
    QString localFileName = jpeg_path + "/" + ui->lineEdit_prefix->text() + QDate::currentDate().toString("yyyyMMdd") +
                                            QTime::currentTime().toString("hhmmss") + ".jpg";
    qDebug() << localFileName;
    FileDownloader *downloader = new FileDownloader(url, localFileName, this);
    connect(downloader, SIGNAL(downloaded(QString)), this, SLOT(onJpegDownloaded(QString)));
}

void MainWindow::on_pushButton_2_clicked()
{
    file_dialog->show();
}

void MainWindow::setLocalJpegPath(QString path){
    ui->label_jpeg_path->setText(path);
    jpeg_path = path;
}

void MainWindow::onJpegDownloaded(QString full_path){
    QString link_url = "<a href=\"" + full_path + "\">" + full_path;
    ui->label_local_file_name->setText(link_url);
    this->m_webView->load(QUrl(full_path));
}

//void MainWindow::
