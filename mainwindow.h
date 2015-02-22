#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QColorDialog>
#include <QInputDialog>
#include "fractalview.h"
#include "Fractals/sierpinskifractal.h"
#include "Fractals/heighwaydragon.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_stepBox_valueChanged(int arg1);

    void on_stepSlider_sliderMoved(int position);

    void on_actionHeighway_Dragon_triggered();

    void on_actionSierpinski_Fractal_triggered();

    void on_goButton_clicked();

    void on_stopButton_clicked();

    void on_pauseButton_clicked();

    void on_actionSet_background_color_triggered();

    void on_actionTimer_delay_triggered();

    void on_actionLines_color_triggered();

    void on_actionAbout_me_triggered();

private:
    SierpinskiFractal* sierpinski;
    HeighwayDragon* dragon;
    Ui::MainWindow *ui;
    FractalView * v;
    QLabel *statusLabel;
};

#endif // MAINWINDOW_H
