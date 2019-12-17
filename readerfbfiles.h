#ifndef READERFBFILES_H
#define READERFBFILES_H

#include <QObject>
#include <QtCore>
#include <QtGui/private/qzipwriter_p.h>
#include <QtGui/private/qzipreader_p.h>

class ReaderFBFiles : public QObject
{
    Q_OBJECT
public:
    explicit ReaderFBFiles(QObject *parent = nullptr);
    static bool readFBFile(QString fileName, QString *book, QStringList *content, int aFontSize);
    static bool UnZip(QString name, QString path);
};

#endif // READERFBFILES_H
