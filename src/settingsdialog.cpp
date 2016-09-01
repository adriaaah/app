/***************************************************************************
 SocNetV: Social Network Visualizer
 version: 2.0
 Written in Qt

                         settingsdialog.cpp  -  description
                             -------------------
    copyright            : (C) 2005-2015 by Dimitris B. Kalamaras
    email                : dimitris.kalamaras@gmail.com
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

#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QFileDialog>
#include <QColorDialog>
#include <QSpinBox>
#include <QTextStream>
#include <QMap>
#include <QtDebug>

SettingsDialog::SettingsDialog(
        QMap<QString, QString> &appSettings,
        QWidget *parent) :
    QDialog(parent),
    m_appSettings(appSettings),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

   // m_appSettings = appSettings; //only use if var passed by pointer

    //data export
    ui->dataDirEdit->setText(  (m_appSettings)["dataDir"]);

    //debugging
    ui->printDebugChkBox->setChecked(
                (appSettings["printDebug"] == "true") ? true:false
            );

    ui->progressBarsChkBox->setChecked(
                (appSettings["showProgressBar"] == "true") ? true:false
                );

    /**
     * canvas options
     */
    ui->antialiasingChkBox->setChecked(
                (appSettings["antialiasing"] == "true") ? true:false
                );
    ui->printLogoChkBox->setChecked(
                (appSettings["printLogo"] == "true") ? true:false
                );

    m_bgColor = QColor (m_appSettings["initBackgroundColor"]);
    m_pixmap = QPixmap(60,20) ;
    m_pixmap.fill( m_bgColor );
    ui->bgColorButton->setIcon(QIcon(m_pixmap));

    ui->bgImageSelectEdit->setText((m_appSettings)["initBackgroundImage"]);

    /**
     * window options
     */
    ui->leftPanelChkBox->setChecked(
                ( appSettings["showLeftPanel"] == "true") ? true:false
                );

    ui->rightPanelChkBox->setChecked(
                ( appSettings["showRightPanel"] == "true") ? true:false
                );

    /**
     * node options
     */
    m_nodeColor = QColor (m_appSettings["initNodeColor"]);
    m_pixmap = QPixmap(60,20) ;
    m_pixmap.fill( m_nodeColor );
    ui->nodeColorBtn->setIcon(QIcon(m_pixmap));

    if (m_appSettings["initNodeShape"] == "box") {
        ui->nodeShapeRadioBox->setChecked(true);
    }
    else if (m_appSettings["initNodeShape"] == "circle") {
        ui->nodeShapeRadioCircle->setChecked(true);
    }
    else if (m_appSettings["initNodeShape"] == "diamond") {
        ui->nodeShapeRadioDiamond->setChecked(true);
    }
    else if (m_appSettings["initNodeShape"] == "ellipse") {
        ui->nodeShapeRadioEllipse->setChecked(true);
    }
    else if (m_appSettings["initNodeShape"] == "triangle") {
        ui->nodeShapeRadioTriangle->setChecked(true);
    }
    else { // default
       ui->nodeShapeRadioCircle->setChecked(true);
    }

    ui->nodeSizeSpin->setValue( m_appSettings["initNodeSize"].toInt(0, 10) );

    ui->nodeNumbersChkBox->setChecked(
                ( m_appSettings["initNodeNumbersVisibility"] == "true") ? true : false
                );

    ui->nodeNumbersInsideChkBox->setChecked(
                (m_appSettings["initNodeNumbersInside"] == "true" ) ? true:false
                );

    m_nodeNumberColor = QColor (m_appSettings["initNodeNumberColor"]);
    m_pixmap = QPixmap(60,20) ;
    m_pixmap.fill( m_nodeNumberColor );
    ui->nodeNumberColorBtn->setIcon(QIcon(m_pixmap));

    ui->nodeNumberSizeSpin->setValue( m_appSettings["initNodeNumberSize"].toInt(0, 10) );
    ui->nodeNumberDistanceSpin->setValue( m_appSettings["initNodeNumberDistance"].toInt(0, 10) );


    ui->nodeLabelsChkBox->setChecked(
                ( m_appSettings["initNodeLabelsVisibility"] == "true") ? true : false
                );

    ui->nodeLabelSizeSpin->setValue( m_appSettings["initNodeLabelSize"].toInt(0, 10) );

    m_nodeLabelColor = QColor (m_appSettings["initNodeLabelColor"]);
    m_pixmap = QPixmap(60,20) ;
    m_pixmap.fill( m_nodeLabelColor );
    ui->nodeLabelColorBtn->setIcon(QIcon(m_pixmap));


    /**
     * edge options
     */

    ui->edgesChkBox-> setChecked(
                (m_appSettings["initEdgeVisibility"] == "true") ? true: false
                                                                  );
    if (m_appSettings["initEdgeShape"] == "line") {
        ui->edgeShapeRadioStraightLine->setChecked(true);
    }
    else if (m_appSettings["initEdgeShape"] == "bezier") {
        ui->edgeShapeRadioBezier->setChecked(true);
    }
    else {
        ui->edgeShapeRadioStraightLine->setChecked(true);
    }

    /**
     * dialog signals to slots
     */
    connect (ui->dataDirSelectButton, &QToolButton::clicked,
             this, &SettingsDialog::getDataDir);

    connect (ui->printDebugChkBox, &QCheckBox::stateChanged,
             this, &SettingsDialog::setDebugMsgs);

    connect (ui->antialiasingChkBox, &QCheckBox::stateChanged,
             this, &SettingsDialog::setAntialiasing);

    connect (ui->printLogoChkBox, &QCheckBox::stateChanged,
             this, &SettingsDialog::setPrintLogo);

    connect (ui->bgColorButton, &QToolButton::clicked,
             this, &SettingsDialog::getBgColor);

    connect (ui->bgImageSelectButton, &QToolButton::clicked,
             this, &SettingsDialog::getBgImage);

    connect (ui->progressBarsChkBox, &QCheckBox::stateChanged,
             this, &SettingsDialog::setProgressBars);

    connect (ui->showToolBarChkBox, &QCheckBox::stateChanged,
             this, &SettingsDialog::setToolBar);

    connect (ui->showStatusBarChkBox, &QCheckBox::stateChanged,
             this, &SettingsDialog::setStatusBar);

    connect (ui->leftPanelChkBox, &QCheckBox::stateChanged,
             this, &SettingsDialog::setLeftPanel);

    connect (ui->rightPanelChkBox, &QCheckBox::stateChanged,
             this, &SettingsDialog::setRightPanel);

    connect (ui->nodeShapeRadioBox, &QRadioButton::clicked,
             this, &SettingsDialog::getNodeShape);
    connect (ui->nodeShapeRadioCircle, &QRadioButton::clicked,
             this, &SettingsDialog::getNodeShape);
    connect (ui->nodeShapeRadioDiamond, &QRadioButton::clicked,
             this, &SettingsDialog::getNodeShape);
    connect (ui->nodeShapeRadioEllipse, &QRadioButton::clicked,
             this, &SettingsDialog::getNodeShape);
    connect (ui->nodeShapeRadioTriangle, &QRadioButton::clicked,
             this, &SettingsDialog::getNodeShape);


    connect(ui->nodeSizeSpin, SIGNAL(valueChanged(int)),
            this, SLOT(getNodeSize(int)) );

    connect ( ui->buttonBox, &QDialogButtonBox::accepted,
              this, &SettingsDialog::validateSettings );

    connect (ui->nodeColorBtn, &QToolButton::clicked,
             this, &SettingsDialog::getNodeColor);


    connect (ui->nodeNumbersChkBox, &QCheckBox::stateChanged,
                     this, &SettingsDialog::getNodeNumbersVisibility);
    connect (ui->nodeNumbersInsideChkBox, &QCheckBox::stateChanged,
             this,  &SettingsDialog::getNodeNumbersInside);
    connect (ui->nodeNumberColorBtn, &QToolButton::clicked,
             this, &SettingsDialog::getNodeNumberColor);
    connect(ui->nodeNumberSizeSpin, SIGNAL(valueChanged(int)),
            this, SLOT(getNodeNumberSize(int)) );
    connect(ui->nodeNumberDistanceSpin, SIGNAL(valueChanged(int)),
            this, SLOT(getNodeNumberDistance(int)) );

    connect (ui->nodeLabelsChkBox, &QCheckBox::stateChanged,
                     this, &SettingsDialog::getNodeLabelsVisibility);
    connect(ui->nodeLabelSizeSpin, SIGNAL(valueChanged(int)),
                this, SLOT(getNodeLabelSize(int)) );
    connect (ui->nodeLabelColorBtn, &QToolButton::clicked,
             this, &SettingsDialog::getNodeLabelColor);


    connect (ui->edgeShapeRadioStraightLine, &QRadioButton::clicked,
             this, &SettingsDialog::getEdgeShape);
    connect (ui->edgeShapeRadioBezier, &QRadioButton::clicked,
             this, &SettingsDialog::getEdgeShape);



}


/**
 * @brief SettingsDialog::validateSettings
 * Validates form data and signals saveSettings to MW
 */
void SettingsDialog::validateSettings(){
    emit saveSettings();

}

void SettingsDialog::getDataDir(){

    QString m_dataDir = QFileDialog::getExistingDirectory(this, tr("Select a new data dir"),
                                                    ui->dataDirEdit->text(),
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    if (!m_dataDir.isEmpty()) {
        if (!m_dataDir.endsWith( QDir::separator() )) {
            m_dataDir += QDir::separator();
        }
       ui->dataDirEdit->setText(m_dataDir);
       m_appSettings["dataDir"]= m_dataDir;
    }

}


/**
 * @brief SettingsDialog::getBgColor
 * Opens a QColorDialog for the user to select a new bg color
 */
void SettingsDialog::getBgColor(){

    m_bgColor = QColorDialog::getColor(
                m_bgColor, this, tr("Select default canvas background color") );
    if ( m_bgColor.isValid()) {
        m_pixmap.fill(m_bgColor);
        ui->bgColorButton->setIcon(QIcon(m_pixmap));
        ui->bgImageSelectEdit->setText("");
        (m_appSettings)["initBackgroundColor"] = m_bgColor.name();
        emit setBgColor(m_bgColor);
    }
    else {
        // user pressed Cancel
    }

}



/**
 * @brief SettingsDialog::getBgImage
 */
void SettingsDialog::getBgImage(){
    QString m_bgImage = QFileDialog::getOpenFileName(
                this, tr("Select default canvas background image "), (m_appSettings)["lastUsedDirPath"],
                tr("All (*);;PNG (*.png);;JPG (*.jpg)")
                );
    if (!m_bgImage.isEmpty() ) {
        (m_appSettings)["initBackgroundImage"] = m_bgImage ;
        ui->bgImageSelectEdit->setText((m_appSettings)["initBackgroundImage"]);
        emit setBgImage();
    }
    else { //user pressed Cancel

    }

}


/**
 * @brief SettingsDialog::getNodeColor
 * * Opens a QColorDialog for the user to select a new node color
 */
void SettingsDialog::getNodeColor(){
    m_nodeColor = QColorDialog::getColor(
                m_nodeColor, this, tr("Select default node color") );
    if ( m_nodeColor.isValid()) {
        m_pixmap.fill(m_nodeColor);
        ui->nodeColorBtn->setIcon(QIcon(m_pixmap));
        (m_appSettings)["initNodeColor"] = m_nodeColor.name();
        emit setNodeColor(m_nodeColor);
    }
    else {
        // user pressed Cancel
    }
}


/**
 * @brief SettingsDialog::getNodeShape
 */
void SettingsDialog::getNodeShape(){

    QString nodeShape;
    if ( ui->nodeShapeRadioBox->isChecked () ){
       m_appSettings["initNodeShape"]  = "box";
    }
    else if ( ui->nodeShapeRadioCircle->isChecked() ){
       m_appSettings["initNodeShape"]  = "circle";
    }
    else if ( ui->nodeShapeRadioDiamond->isChecked() ){
       m_appSettings["initNodeShape"]  = "diamond";
    }
    else if ( ui->nodeShapeRadioEllipse->isChecked() ){
        m_appSettings["initNodeShape"]  = "ellipse";
    }
    else if ( ui->nodeShapeRadioTriangle->isChecked() ){
        m_appSettings["initNodeShape"]  = "triangle";
    }
    else {
        m_appSettings["initNodeShape"] = "box";
    }
    qDebug()<< "SettingsDialog::getNodeShape() - new default shape " << nodeShape;
    emit setNodeShape(m_appSettings["initNodeShape"], 0);
}


/**
 * @brief SettingsDialog::getNodeSize
 * @param size
 */
void SettingsDialog::getNodeSize( int size) {
    m_appSettings["initNodeSize"]= QString::number(size);
    emit setNodeSize(size);
}


/**
 * @brief SettingsDialog::getNodeNumbersVisibility
 * @param toggle
 */
void SettingsDialog::getNodeNumbersVisibility (bool toggle){
    m_appSettings["initNodeNumbersVisibility"]= (toggle) ? "true" : "false";
    emit setNodeNumbersVisibility(toggle);
}

/**
 * @brief SettingsDialog::getNodeNumbersInside
 * @param toggle
 */
void SettingsDialog::getNodeNumbersInside(bool toggle) {
    m_appSettings["initNodeNumbersInside"]= (toggle) ? "true" : "false";
    ui->nodeNumbersChkBox->setChecked(true);
    emit setNodeNumbersInside(toggle);
}

/**
 * @brief SettingsDialog::getNodeNumberSize
 * @param size
 */
void SettingsDialog::getNodeNumberSize( const int size) {
    m_appSettings["initNodeNumberSize"]= QString::number(size);
    emit setNodeNumberSize(0, size);
}


void SettingsDialog::getNodeNumberDistance(const int distance) {
    m_appSettings["initNodeNumberDistance"]= QString::number(distance);
    emit setNodeNumberDistance(0, distance);
}

/**
 * @brief SettingsDialog::getNodeNumberColor
 * * Opens a QColorDialog for the user to select a new node number color
 */
void SettingsDialog::getNodeNumberColor(){
    m_nodeNumberColor = QColorDialog::getColor(
                m_nodeColor, this, tr("Select default node number color") );
    if ( m_nodeNumberColor.isValid()) {
        m_pixmap.fill(m_nodeNumberColor);
        ui->nodeNumberColorBtn->setIcon(QIcon(m_pixmap));
        (m_appSettings)["initNodeNumberColor"] = m_nodeNumberColor.name();
        emit setNodeNumberColor(m_nodeNumberColor);
    }
    else {
        // user pressed Cancel
    }
}




/**
 * @brief SettingsDialog::getNodeLabelsVisibility
 * @param toggle
 */
void SettingsDialog::getNodeLabelsVisibility (bool toggle){
    m_appSettings["initNodeLabelsVisibility"]= (toggle) ? "true" : "false";
    emit setNodeLabelsVisibility(toggle);
}


/**
 * @brief SettingsDialog::getNodeLabelColor
 * * Opens a QColorDialog for the user to select a new node Label color
 */
void SettingsDialog::getNodeLabelColor(){
    m_nodeLabelColor = QColorDialog::getColor(
                m_nodeColor, this, tr("Select default node Label color") );
    if ( m_nodeLabelColor.isValid()) {
        m_pixmap.fill(m_nodeLabelColor);
        ui->nodeLabelColorBtn->setIcon(QIcon(m_pixmap));
        (m_appSettings)["initNodeLabelColor"] = m_nodeLabelColor.name();
        emit setNodeLabelColor(m_nodeLabelColor);
    }
    else {
        // user pressed Cancel
    }
}

/**
 * @brief SettingsDialog::getNodeLabelSize
 * @param size
 */
void SettingsDialog::getNodeLabelSize( const int size) {
    m_appSettings["initNodeLabelSize"]= QString::number(size);
    emit setNodeLabelSize(0, size);
}




/**
 * @brief SettingsDialog::getEdgeShape
 */
void SettingsDialog::getEdgeShape(){

    if ( ui->edgeShapeRadioStraightLine->isChecked () ){
       m_appSettings["initEdgeShape"]  = "line";
    }
    else if ( ui->edgeShapeRadioBezier->isChecked() ){
       m_appSettings["initEdgeShape"]  = "bezier";
    }
    qDebug()<< "SettingsDialog::getEdgeShape() - new default shape " <<
               m_appSettings["initEdgeShape"];
    emit setEdgeShape(m_appSettings["initEdgeShape"], 0);
}



SettingsDialog::~SettingsDialog()
{
    delete ui;
}
