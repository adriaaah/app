/***************************************************************************
 SocNetV: Social Network Visualizer
 version: 2.5
 Written in Qt

                         dialogexportpdf.h  -  description
                             -------------------
    copyright         : (C) 2005-2018 by Dimitris B. Kalamaras
    project site      : http://socnetv.org

 ***************************************************************************/

/*******************************************************************************
*     This program is free software: you can redistribute it and/or modify     *
*     it under the terms of the GNU General Public License as published by     *
*     the Free Software Foundation, either version 3 of the License, or        *
*     (at your option) any later version.                                      *
*                                                                              *
*     This program is distributed in the hope that it will be useful,          *
*     but WITHOUT ANY WARRANTY; without even the implied warranty of           *
*     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
*     GNU General Public License for more details.                             *
*                                                                              *
*     You should have received a copy of the GNU General Public License        *
*     along with this program.  If not, see <http://www.gnu.org/licenses/>.    *
********************************************************************************/

#ifndef DIALOGEXPORTPDF_H
#define DIALOGEXPORTPDF_H

#include <QDialog>
#include <QPrinter>


namespace Ui {
class DialogExportPDF;
}


class DialogExportPDF : public QDialog
{
    Q_OBJECT
public:
    explicit DialogExportPDF (QWidget *parent = nullptr );
    ~DialogExportPDF();
public slots:
    void checkFilename(const QString &fileName = QString::null);
    void getFilename();
    void getPrinterMode(const QString &mode);
    void getUserChoices ();
signals:
    void userChoices( QString &filename,
                      const QPrinter::Orientation &orientation,
                      const int &dpi,
                      const QPrinter::PrinterMode printerMode);
private:
    QString m_fileName;
    int m_dpi;
    QPrinter::Orientation m_orientation;
    QPrinter::PrinterMode m_printerMode;
    Ui::DialogExportPDF *ui;


};

#endif // DIALOGEXPORTPDF_H
