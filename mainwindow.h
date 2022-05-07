#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include "httpcameracontroller.h"
#include <QWebEngineView>
#include <camerawebview.h>
#include "messagereceiver.h"
#include <QFileDialog>
#include <QProgressDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void switchAEUIMode(int mode);
    void setLocalJpegPath(QString path);
    void onJpegDownloaded(QString full_path);

    void on_pushButton_9_clicked();


    void on_pushButton_take_photo_clicked();



    void on_comboBox_2_currentIndexChanged(int index);


    void on_horizontalSlider_2_valueChanged(int value);

    void on_horizontalSlider_valueChanged(int value);

    void on_horizontalSlider_x_valueChanged(int value);

    void on_verticalSlider_Y_valueChanged(int value);

    void on_pushButton_clicked();

    void on_comboBox_7_activated(int index);

    void onMqMsgReceived(QString msg);
    void on_pushButton_2_clicked();
    void on_update_time();

    void on_checkBox_stateChanged(int arg1);

    void on_pushButton_sync_time_clicked();

    void on_comboBox_wb_scene_activated(int index);

    void on_comboBox_mode_activated(int index);

private:
    Ui::MainWindow *ui;
    HttpCameraController *m_cam_controller;
//    QWebEngineView *m_webView;
    CameraWebView *m_webView;
    MessageReceiver *receiver;
    QFileDialog *file_dialog;
    QString jpeg_path;
    QProgressDialog *progressDialog;
};
#endif // MAINWINDOW_H
