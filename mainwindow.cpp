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
    if(ui->comboBox_7->currentText() == "Manual"){
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
    ui->groupBox_histogram->hide();
    ui->groupBox_debug->hide();
    this->m_cam_controller = new HttpCameraController(QString("http://192.168.137.16:8080/api/camera/"));

    this->progressDialog = new QProgressDialog("processing...", QString(), 0, 1, this);
    this->progressDialog->hide();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_update_time()));
    timer->start(1000);

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

    for (QString str : AWB_SCENE_OPTIONS){
        ui->comboBox_wb_scene->addItem(str);
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
    this->m_cam_controller->startPreview();
}



void MainWindow::on_pushButton_take_photo_clicked()
{
//    this->m_cam_controller->cameraIfDirect(0x0, 0xb, 0x3);
    this->progressDialog->show();
    this->setDisabled(true);
    this->m_cam_controller->capturePic();
    this->setDisabled(false);
    this->progressDialog->hide();
}




void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    this->progressDialog->show();
    this->setDisabled(true);
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
    this->setDisabled(false);
    this->progressDialog->hide();
}



void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    this->progressDialog->show();
    this->setDisabled(true);
    this->m_cam_controller->cameraIfDirect(0xb, 0x6, value);
    ui->label_4->setText(QString(std::to_string(value).c_str()));
    this->setDisabled(false);
    this->progressDialog->hide();
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    this->progressDialog->show();
    this->setDisabled(true);
    float zoom = 1.0f + 3.0f * value / 100;
    this->m_cam_controller->setDZoom(zoom);
    this->setDisabled(false);
    this->progressDialog->hide();
}


void MainWindow::on_horizontalSlider_x_valueChanged(int value)
{
    this->progressDialog->show();
    this->setDisabled(true);
    float x = 1.0f * value / 100;
    this->m_cam_controller->cameraIfDirect(0x1, 0x22, *(uint32_t *)&x);
    this->setDisabled(false);
    this->progressDialog->hide();
}


void MainWindow::on_verticalSlider_Y_valueChanged(int value)
{
    this->progressDialog->show();
    this->setDisabled(true);
    float y = 1.0f * value / 100;
    this->m_cam_controller->cameraIfDirect(0x1, 0x23, *(uint32_t *)&y);
    this->setDisabled(false);
    this->progressDialog->hide();
}


void MainWindow::on_pushButton_clicked()
{
    this->progressDialog->show();
    this->setDisabled(true);

    this->m_cam_controller->setAEMode(ui->comboBox_7->currentText());

    this->m_cam_controller->setISO(ui->comboBox_iso->currentText().toInt());

    this->m_cam_controller->setShutter(ui->comboBox_shutter->currentText());

    int iso_value = get_iso_value(ui->comboBox_iso->currentText().toInt());
    float m_gain = (log2(0.32f * iso_value) - 4) * 6;
    this->m_cam_controller->setSensorGain(m_gain);

    float ev = ui->comboBox_ev->currentIndex() - 2;
    this->m_cam_controller->setEV(ev);

    this->setDisabled(false);
    this->progressDialog->hide();
}


void MainWindow::on_comboBox_7_activated(int index)
{
    this->switchAEUIMode(index);
    this->setDisabled(false);
    this->progressDialog->hide();
//    this->m_cam_controller->setAEMode(index);
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
    this->progressDialog->show();
    this->setDisabled(true);
    file_dialog->show();
    this->setDisabled(false);
    this->progressDialog->hide();
}

void MainWindow::setLocalJpegPath(QString path){
    ui->label_jpeg_path->setText(path);
    jpeg_path = path;
}

void MainWindow::onJpegDownloaded(QString full_path){
    QString link_url = "<a href=\"" + full_path + "\" style=\"color:rgb(85, 170, 255) \">" + full_path;
    ui->label_local_file_name->setText(link_url);
    this->m_webView->load(QUrl(full_path));
}

//void MainWindow::

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    this->progressDialog->show();
    this->setDisabled(true);
    this->m_cam_controller->setMShutter(arg1 != 0);
    this->setDisabled(false);
    this->progressDialog->hide();
}

void MainWindow::on_update_time(){
    ui->label_time->setText(QDate::currentDate().toString("yyyy-MM-dd") + QTime::currentTime().toString(" hh:mm:ss"));
}

void MainWindow::on_pushButton_sync_time_clicked()
{
    this->progressDialog->show();
    this->setDisabled(true);
    this->m_cam_controller->syncTime(QDate::currentDate().toString("yyyy-MM-dd") + QTime::currentTime().toString(" hh:mm:ss"));
    this->setDisabled(false);
    this->progressDialog->hide();
}

void MainWindow::on_comboBox_wb_scene_activated(int index)
{
    this->progressDialog->show();
    this->setDisabled(true);
    this->m_cam_controller->setAWBScene(index, 0);
    this->setDisabled(false);
    this->progressDialog->hide();
}


void MainWindow::on_comboBox_mode_activated(int index)
{
    this->progressDialog->show();
    this->setDisabled(true);
    this->m_cam_controller->setAWBMode(index);
    this->setDisabled(false);
    this->progressDialog->hide();
}

