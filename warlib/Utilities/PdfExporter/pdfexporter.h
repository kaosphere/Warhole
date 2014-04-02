#ifndef PDFEXPORTER_H
#define PDFEXPORTER_H

#include <QtCore>
#include <QTextDocument>
#include <QtPrintSupport/QPrinter>
#include <Utilities/QLogger/QLogger.h>

class PdfExporter
{
public:
    PdfExporter();

    static bool exportHtmlToPdfFile(QString &fileName, QString &html);
    static void initPdfExporter();

private:
    static const QString LOG_ID_TRACE;
    static const QString LOG_ID_INFO;
    static const QString LOG_ID_WARN;
    static const QString LOG_ID_ERR;
};

#endif // PDFEXPORTER_H
