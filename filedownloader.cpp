#include "filedownloader.h"
#include <QFile>

FileDownloader::FileDownloader(QUrl imageUrl, QString filePath, QObject *parent) :
 QObject(parent)
{
    this->filePath = filePath;
 connect(
  &m_WebCtrl, SIGNAL (finished(QNetworkReply*)),
  this, SLOT (fileDownloaded(QNetworkReply*))
 );

 QNetworkRequest request(imageUrl);
 m_WebCtrl.get(request);
}

FileDownloader::~FileDownloader() { }

void FileDownloader::fileDownloaded(QNetworkReply* pReply) {
 m_DownloadedData = pReply->readAll();
 QFile file(this->filePath);
 file.open(QFile::ReadWrite);
 file.write(m_DownloadedData);
 file.close();
 //emit a signal
 pReply->deleteLater();
 emit downloaded(this->filePath);
}

QByteArray FileDownloader::downloadedData() const {
 return m_DownloadedData;
}
