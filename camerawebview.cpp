#include "camerawebview.h"


CameraWebView::CameraWebView(QWidget *parent)
    :QWebEngineView(parent)
{
    this->setContextMenuPolicy(Qt::ContextMenuPolicy::NoContextMenu);

}

QWebEngineView *CameraWebView::createWindow(QWebEnginePage::WebWindowType type){
    qDebug() << type;
    if(type == QWebEnginePage::WebWindowType::WebBrowserTab){
        delete this->page();
        QWebEnginePage *page = new QWebEnginePage();
        this->setPage(page);
    }
    return this;
}
