#ifndef MAINWINDOW_H
#define MAINWINDOW_H

extern "C" {
#include "../Backend/s21_calculator.h"
}

#include <QDialog>
#include <QIntValidator>
#include <QMainWindow>
#include <QMessageBox>
#include <QVector>
#include <QWidget>

#include "qcustomplot.h"
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  double x_begin, x_end, y_begin, y_end, h;
  int N;
 private slots:
  void digits_numbers();
  void on_pushButton_dot_clicked();
  void positive();
  void minus();
  void button_arrow();
  void button_delete();
  void LR();
  void when_func();
  void total();
  void press_graph();
  void press_cred();
  void press_depos();

 private:
  void removeLastCharacterFromText(QString &text);
  int div_rate(int *period_viplat, double *deposit_term);
  double tax_calc(double final_percent_sum, double tax_rate);
};

#endif  // MAINWINDOW_H
