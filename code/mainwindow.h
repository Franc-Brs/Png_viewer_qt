#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#include <QImage> //agg
#include <QMouseEvent> //aggiunto per mouse
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //function to change img
    void cambia_immagine (QString nome_file);

    //function to switch on/off RGB
    void manage_cband (QString col_r, QString col_g, QString col_b);

    //test, don't take into account
    //void manage_cband_2 (QString col_r="", QString col_g="", QString col_b="");

private slots:
    //load pic
    void on_pushButton_clicked();

    //checkbox
    void on_checkBox_R_stateChanged(int arg1);
    void on_checkBox_G_stateChanged(int arg1);
    void on_checkBox_B_stateChanged(int arg1);

    //zoom
    void on_actionZoomInOut_triggered();
    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;

    //for pic viz
    QGraphicsScene *scena;
    //pic viz
    QGraphicsPixmapItem *immagine_gi;

    //by me
    QImage nimage, c_image;

protected:
    void mousePressEvent(QMouseEvent * event);
};
#endif // MAINWINDOW_H
