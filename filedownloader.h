#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class FileDownloader : public QObject
{
 Q_OBJECT
 public:
  explicit FileDownloader(QUrl imageUrl, QString filePath, QObject *parent);
  virtual ~FileDownloader();
  QByteArray downloadedData() const;

 signals:
  void downloaded(QString path);

 private slots:
  void fileDownloaded(QNetworkReply* pReply);
  private:
  QNetworkAccessManager m_WebCtrl;
  QByteArray m_DownloadedData;
  QString filePath;
};

#endif // FILEDOWNLOADER_H
