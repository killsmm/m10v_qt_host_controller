#ifndef CAMERAWEBVIEW_H
#define CAMERAWEBVIEW_H

#include <QWidget>
#include "QWebEngineView"

class CameraWebView : public QWebEngineView
{
    Q_OBJECT
public:
    explicit CameraWebView(QWidget *parent = nullptr);
    QWebEngineView *createWindow(QWebEnginePage::WebWindowType type) override;
signals:

};

#endif // CAMERAWEBVIEW_H
