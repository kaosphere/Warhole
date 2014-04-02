#include "pdfexporter.h"

using namespace QLogger;

const QString PdfExporter::LOG_ID_INFO = "PdfExporter_info";
const QString PdfExporter::LOG_ID_TRACE = "PdfExporter_trace";
const QString PdfExporter::LOG_ID_WARN = "PdfExporter_warm";
const QString PdfExporter::LOG_ID_ERR = "PdfExporter_err";

PdfExporter::PdfExporter()
{
}

void PdfExporter::initPdfExporter()
{

}

bool PdfExporter::exportHtmlToPdfFile(QString& fileName, QString& html)
{
    QTextDocument doc;
    QLog_Info(LOG_ID_INFO, html);
    if (!fileName.endsWith(".pdf"))
    {
        QLog_Error(LOG_ID_ERR, "exportHtmlToPdfFile : File name doesn't end with .pdf");
        return false;
    }

    doc.setHtml(html);
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFileName(fileName);
    printer.setOutputFormat(QPrinter::PdfFormat);
    doc.print(&printer);
    return true;
}
