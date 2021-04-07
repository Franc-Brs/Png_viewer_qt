#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QDir>
#include <QGraphicsPixmapItem>


#include <QMessageBox> //test for checkbox
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //create scene
    scena = new QGraphicsScene (0,0,1000,1000);

    //add img
    //immagine_gi = scena -> addPixmap(QPixmap("C:/Users/franc/Desktop/prova2.png"));
    immagine_gi = scena -> addPixmap(QPixmap(""));

    //aadd view to the scene
    ui->graphicsView->setScene(scena);

    //activate view
    ui->graphicsView->show();

    //store new image (nimage)
    QImage nimage;

    ui->checkBox_R->setChecked(true);
    ui->checkBox_G->setChecked(true);
    ui->checkBox_B->setChecked(true);

    ui->horizontalSlider->valueChanged(ui->horizontalSlider->value());
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scena;
}

void MainWindow::cambia_immagine(QString nome_file)
{
    //QImage
    nimage.load(nome_file);
    //changing the format
    nimage = nimage.convertToFormat(QImage::Format_RGB32);
    //nimage= nimage.scaledToWidth(ui->graphicsView->width(),Qt::SmoothTransformation);
    immagine_gi->setPixmap(QPixmap::fromImage(nimage));
}


void MainWindow::on_pushButton_clicked()
{
    //QFileDialog *dialog=new QFileDialog{this, "Choose Image",QDir::currentPath() ,"*.png"};
    //dialog -> exec();
    QString nome_file = QFileDialog::getOpenFileName(this,tr("Choose Image"), "", tr("Image Files (*.png)"));
    if (!nome_file.isEmpty())
            {
                cambia_immagine(nome_file);
            }

}



void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        int pos_x = event->x();
        int pos_y = event->y();

        //position modify the lbl_pos
        //ui->lbl_pos->setText( QString("X = %1, Y = %2").arg(pos_x).arg(pos_y) );

        QRgb rgbValue = nimage.pixel(pos_x, pos_y);
        ui->lbl_pos->setText( QString("R = %1    G = %2    B = %3").arg(qRed(rgbValue)).arg(qGreen(rgbValue)).arg(qBlue(rgbValue)));

        //another way of doin' it
        //QColor clrCurrent( nimage.pixel(pos_x, pos_y) );
        //ui->lbl_pos->setText( QString("R = %1    G = %2    B = %3").arg(clrCurrent.red()).arg(clrCurrent.green()).arg(clrCurrent.blue()));
    }
}






void MainWindow::on_checkBox_R_stateChanged(int arg1)
{
    if (!arg1)
    {
        QString col_r="red_d";
        manage_cband(col_r,"","");
    } else {
        QString col_r="";
        manage_cband(col_r,"","");
        //immagine_gi->setPixmap(QPixmap::fromImage(nimage));
    }
}

void MainWindow::on_checkBox_G_stateChanged(int arg1)
{
    if (!arg1)
    {
        QString col_g="green_d";
        manage_cband("",col_g,"");
    } else {

        QString col_g="";
        manage_cband("",col_g,"");
        //immagine_gi->setPixmap(QPixmap::fromImage(nimage));
    }
}

void MainWindow::on_checkBox_B_stateChanged(int arg1)
{
    if (!arg1)
    {
        QString col_b="blue_d";
        manage_cband("","",col_b);
    } else {
        QString col_b="";
        manage_cband("","",col_b);
        //immagine_gi->setPixmap(QPixmap::fromImage(nimage));
    }
}

void MainWindow::on_actionZoomInOut_triggered()
{
    immagine_gi->setScale(ui->horizontalSlider->value()/10.0);
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->sliderValueLBL->setText( QString::number(value*10)+ "%");
    ui->actionZoomInOut->trigger();
}

void MainWindow::manage_cband (QString col_r, QString col_g, QString col_b)
{
    QImage c_image(nimage.size(), QImage::Format_RGB32); // a new image with the same size
        for (int row = 0; row < nimage.height(); ++row) {
          for (int col = 0; col < nimage.width(); ++col) {

            const auto color = nimage.pixelColor(col, row);

            const auto r = color.red();
            const auto g = color.green();
            const auto b = color.blue();

            c_image.setPixelColor(col, row, QColor(col_r =="red_d"? 0:r, col_g =="green_d"? 0:g, col_b =="blue_d"? 0:b));
          }
        }

    immagine_gi->setPixmap(QPixmap::fromImage(c_image));
}

/*
void MainWindow::manage_cband_2 (QString col_r, QString col_g, QString col_b)
{

    QList<QCheckBox *> allckbox = ui->groupBox->findChildren<QCheckBox *>();

    QList<QString> list1 = { "red_d", "green_d", "blue_d" };
    QList<QString> list2 = { col_r, col_g, col_b };

    for(int i = 0; i < allckbox.size(); ++i)
    {
        if(allckbox.at(i)->isChecked())
        {
            list2[i]=list1.at(i);
        }
    }


    QImage c_image(nimage.size(), QImage::Format_RGB32); // a new image with the same size
        for (int row = 0; row < nimage.height(); ++row) {
          for (int col = 0; col < nimage.width(); ++col) {

            const auto color = nimage.pixelColor(col, row);

            const auto r = color.red();
            const auto g = color.green();
            const auto b = color.blue();

            c_image.setPixelColor(col, row, QColor(list2.at(1) =="red_d"? 0:r, list2.at(2) =="green_d"? 0:g, list2.at(3) =="blue_d"? 0:b));
          }
        }

    immagine_gi->setPixmap(QPixmap::fromImage(c_image));
}

*/
