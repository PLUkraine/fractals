#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    sierpinski(new SierpinskiFractal()),
    dragon(new HeighwayDragon()),
    ui(new Ui::MainWindow),
    v(new FractalView(dragon, this)),
    statusLabel(new QLabel())
{
    ui->setupUi(this);
    ui->centralWidget->layout()->addWidget(v);
    this->setWindowTitle(tr("Fractals"));

    statusLabel->setText("Ready");
    ui->statusBar->addPermanentWidget(statusLabel);

    //v->setGeometry(30,40,200,200);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_stepBox_valueChanged(int arg1)
{
    this->blockSignals(true);
    ui->stepSlider->setValue(arg1);
    v->setLevel(arg1);
    this->blockSignals(false);
}

void MainWindow::on_stepSlider_sliderMoved(int position)
{
    this->blockSignals(true);
    ui->stepBox->setValue(position);
    this->blockSignals(false);
}

void MainWindow::on_actionHeighway_Dragon_triggered()
{
    ui->stepBox->setMaximum(17);
    ui->stepSlider->setMaximum(17);
    v->setFractalBuilder(dragon);
    update();
}

void MainWindow::on_actionSierpinski_Fractal_triggered()
{
    ui->stepBox->setMaximum(10);
    ui->stepSlider->setMaximum(10);
    v->setFractalBuilder(sierpinski);
    update();
}

void MainWindow::on_goButton_clicked()
{
    statusLabel->setText(tr("Processing..."));
    v->startPainting();
    statusLabel->setText(tr("Ready"));
}

void MainWindow::on_stopButton_clicked()
{
    v->stopPainting();
}

void MainWindow::on_pauseButton_clicked()
{
    v->pausePainting();
}

void MainWindow::on_actionSet_background_color_triggered()
{

    QColor color = QColorDialog::getColor(v->backgroundColor(),this, tr("Background"));
    if (color.isValid())
    {
        v->setBackgroundColor(color);
    }
}

void MainWindow::on_actionTimer_delay_triggered()
{
    bool ok;
    int delay = QInputDialog::getInt(this, tr("Enter new delay in miliseconds"), tr("Delay"), v->timerDelay(), 0, 7000,1 ,&ok);
    if (ok)
        v->setTimerDelay(delay);
}

void MainWindow::on_actionLines_color_triggered()
{
    QPen pen = v->linePen();
    QColor color = QColorDialog::getColor(pen.color() ,this, tr("Background"));
    pen.setColor(color);
    v->setLinePen(pen);
}

void MainWindow::on_actionAbout_me_triggered()
{
    QMessageBox::about(this, tr("About me"), tr("PLUkraine, github page: https://github.com/PLUkraine"));
}
