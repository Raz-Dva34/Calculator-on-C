#include "mainwindow.h"

#include "qcustomplot.h"
#include "ui_mainwindow.h"

double num_check;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  QValidator *validator = new QIntValidator(this);
  QLineEdit *lineEdits[] = {
      ui->lineEdit_vklad,        ui->lineEdit_srok,
      ui->lineEdit_stavka_proc,  ui->lineEdit_stavka_nal,
      ui->lineEdit_popol_sum,    ui->lineEdit_zabral_sum,
      ui->lineEdit_popol_mounth, ui->lineEdit_zabral_mounth,
      ui->lineEdit_summa,        ui->lineEdit_percent,
      ui->lineEdit_srok_credita};
  for (QLineEdit *lineEdit : lineEdits) {
    lineEdit->setValidator(validator);
  }
  ui->result_show->setText("");
  for (auto it : ui->buttonGroupNumbers->buttons()) {
    connect(it, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  }
  for (auto it : ui->buttonGroupFunc->buttons()) {
    connect(it, SIGNAL(clicked()), this, SLOT(when_func()));
  }
  for (auto it : ui->buttonGroup_positive->buttons()) {
    connect(it, SIGNAL(clicked()), this, SLOT(positive()));
  }
  for (auto it : ui->buttonGroupLR->buttons()) {
    connect(it, SIGNAL(clicked()), this, SLOT(LR()));
  }
  connect(ui->pushButton_clean, SIGNAL(clicked()), this, SLOT(button_delete()));
  connect(ui->pushButton_arrow, SIGNAL(clicked()), this, SLOT(button_arrow()));
  connect(ui->pushButton_graph, SIGNAL(clicked()), this, SLOT(press_graph()));
  connect(ui->pushButton_Deposit, SIGNAL(clicked()), this, SLOT(press_depos()));
  connect(ui->pushButton_credit, SIGNAL(clicked()), this, SLOT(press_cred()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(minus()));
  connect(ui->pushButton_total, SIGNAL(clicked()), this, SLOT(total()));
  ui->pushButton_divide->setCheckable(true);
  ui->pushButton_plus->setCheckable(true);
  ui->pushButton_mult->setCheckable(true);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_numbers() {
  QPushButton *button = qobject_cast<QPushButton *>(sender());

  if (button) {
    QString currentText = ui->result_show->text();
    QString buttonText = button->text();
    ui->result_show->setText(currentText + buttonText);
  }
}

void MainWindow::on_pushButton_dot_clicked() {
  QString currentText = ui->result_show->text();
  if (currentText.endsWith('+') || currentText.endsWith('-') ||
      currentText.endsWith('*') || currentText.endsWith('/')) {
    ui->result_show->setText(currentText + "0.");
  } else {
    int len = currentText.length();
    bool canAddDot = true;
    for (int i = len - 1; i >= 0; i--) {
      QChar ch = currentText.at(i);
      if (!ch.isDigit() && ch != '.') {
        break;
      }
      if (ch == '.') {
        canAddDot = false;
        break;
      }
    }

    if (canAddDot) {
      ui->result_show->setText(currentText + ".");
    }
  }
}

void MainWindow::positive() {
  QPushButton *button = qobject_cast<QPushButton *>(sender());

  if (button) {
    QString currentText = ui->result_show->text();
    QString buttonText = button->text();

    if (buttonText == "+" || buttonText == "-" || buttonText == "*" ||
        buttonText == "÷") {
      ui->result_show->setText(currentText + buttonText);
    } else {
      num_check = currentText.toDouble();
      double all_numbers;
      QString new_label;
      all_numbers = (currentText + buttonText).toDouble();
      new_label = QString::number(all_numbers);
      ui->result_show->setText(new_label);
    }
  }
}

void MainWindow::minus() {
  QPushButton *button = qobject_cast<QPushButton *>(sender());
  if (button) {
    QString currentText = ui->result_show->text();
    QString buttonText = button->text();
    if (currentText.isEmpty() || currentText == "-") {
      ui->result_show->setText("-");
    } else {
      ui->result_show->setText(currentText + buttonText);
    }
  }
}

void MainWindow::removeLastCharacterFromText(QString &text) {
  if (!text.isEmpty()) {
    text.chop(1);
  }
}

void MainWindow::button_arrow() {
  if (ui->result_show) {
    QString str = ui->result_show->text();
    removeLastCharacterFromText(str);
    ui->result_show->setText(str);
  }
}

void MainWindow::button_delete() {
  if (ui->result_show) {
    ui->result_show->setText("");
  }
}

void MainWindow::LR() {
  QPushButton *button = qobject_cast<QPushButton *>(sender());
  if (button) {
    QString buttonText = button->text();
    ui->result_show->setText(ui->result_show->text() + buttonText);
  }
}

void MainWindow::when_func() {
  QPushButton *button = (QPushButton *)sender();
  ui->result_show->setText(ui->result_show->text() + button->text() + "(");
}

void MainWindow::total() {
  double resultat = 0.0;
  double x = 0.0;
  int error_code = 0;
  if (ui->lineEdit_znX->text() != "") {
    x = ui->lineEdit_znX->text().toDouble();
  }

  std::string str_t = ui->result_show->text().toStdString();
  const char *str = str_t.c_str();
  if (!s21_checking_validity_string(str)) {
    resultat = s21_calculate_with_error((char *)str, &error_code, x);
    if (error_code == 1) {
      ui->result_show->setText("ERROR");
    } else if (error_code == 2) {
      ui->result_show->setText("ERROR INPUT");
    } else {
      ui->result_show->setText(QString::number(resultat, 'g', 15));
    }
  } else {
    ui->result_show->setText("ERROR INPUT");
  }
}

void MainWindow::press_graph() {
  ui->widget->clearGraphs();

  std::string str1 = ui->result_show->text().toStdString();
  const char *str = str1.c_str();
  double x_begin = ui->spinBox_min_x->text().toDouble();
  double x_end = ui->spinBox_max_x->text().toDouble();
  double y_begin = ui->spinBox_min_y->text().toDouble();
  double y_end = ui->spinBox_max_y->text().toDouble();
  ui->widget->xAxis->setRange(x_begin, x_end);
  ui->widget->yAxis->setRange(y_begin, y_end);
  if (x_begin < x_end && y_begin < y_end) {
    double h = 0.01;
    int N = static_cast<int>((x_end - x_begin) / h) + 2;
    QVector<double> x(N), y(N);
    int i = 0;
    int error = 0;
    for (int j = 0; j < N; j++) {
      double X_Gr =
          x_begin + j * h;  // Вычисление X_Gr на основе целочисленного индекса
      double res = 0.0;
      res = s21_calculate_with_error((char *)str, &error, X_Gr);
      if (error == 0) {
        x[i] = X_Gr;
        y[i] = res;
        i++;
      }
    }
    if (error == 0) {
      ui->widget->addGraph();
      ui->widget->graph(0)->setData(x, y);
      ui->widget->graph(0)->setPen(QColor(143, 240, 164));
      ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
      ui->widget->graph(0)->setScatterStyle(
          QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
      ui->widget->replot();
      x.clear();
      y.clear();
    } else
      ui->result_show->setText("error");
  }
}

void MainWindow::press_cred() {
  // Извлечение входных данных из элементов интерфейса
  double amount_of_credit = ui->lineEdit_summa->text().toDouble();
  double percent = ui->lineEdit_percent->text().toDouble();
  double time = ui->lineEdit_srok_credita->text().toDouble();
  // Проверка наличия входных данных и выбранного типа кредита
  if (amount_of_credit <= 0 || percent <= 0 || time <= 0) {
    // Если одно из полей не заполнено или значение меньше или равно нулю,
    // выводим сообщение об ошибке
    ui->lineEdit_pay_mes->setText("Ошибка: Проверьте входные данные");
    ui->lineEdit_dolg_proc->setText("");
    ui->lineEdit_pereplata->setText("");
    return;  // Прекращаем выполнение функции из-за ошибки
  }
  if (ui->radioButton_annuent->isChecked()) {
    // Расчет для аннуитетного кредита
    double month_stavka = percent / 12 / 100;
    double month_pay =
        amount_of_credit *
        (month_stavka + (month_stavka / (pow((1 + month_stavka), time) - 1)));
    double total_pay = month_pay * time;
    double pereplata = total_pay - amount_of_credit;
    // Вывод результатов на интерфейс
    ui->lineEdit_pay_mes->setText(QString::number(month_pay, 'f', 2));
    ui->lineEdit_dolg_proc->setText(QString::number(total_pay, 'f', 2));
    ui->lineEdit_pereplata->setText(QString::number(pereplata, 'f', 2));
  } else if (ui->radioButton_deff->isChecked()) {
    // Расчет для дифференцированного кредита
    double month_stavka = percent / 12 / 100;
    double total_pay = 0.0;
    double res = 0.0, month = 0.0;
    for (int i = 0; i < time; i++) {
      month = amount_of_credit / time +
              (amount_of_credit - (amount_of_credit / time) * i) * month_stavka;
      if (i == 0) res = month;
      total_pay += month;
    }
    double pereplata = total_pay - amount_of_credit;
    // Вывод результатов на интерфейс
    ui->lineEdit_pay_mes->setText(QString::number(res, 'f', 2) + "..." +
                                  QString::number(month, 'f', 2));
    ui->lineEdit_pereplata->setText(QString::number(pereplata, 'f', 2));
    ui->lineEdit_dolg_proc->setText(QString::number(total_pay, 'f', 2));
  }
}

void MainWindow::press_depos() {
  double sum = ui->lineEdit_vklad->text().toDouble();
  double time = ui->lineEdit_srok->text().toDouble();
  double percent_rate = ui->lineEdit_stavka_proc->text().toDouble();
  double taxes_rate = 0.0;
  if (ui->lineEdit_stavka_nal->text().isEmpty()) {
    taxes_rate = 0.0;
  } else {
    taxes_rate = ui->lineEdit_stavka_nal->text().toDouble();
  }
  double sum_popolnenie = ui->lineEdit_popol_sum->text().toDouble();
  double sum_sniatie = ui->lineEdit_zabral_sum->text().toDouble();

  double month_popolnenie = ui->lineEdit_popol_mounth->text().toInt();
  double month_sniatie = ui->lineEdit_zabral_mounth->text().toInt();
  int capitalization = 0;
  if (ui->radioButton_kapital->isChecked()) {
    capitalization = 1;
  }
  int count = ui->comboBox->currentIndex();
  int interval_viplat = 0;
  if (count == 0)
    interval_viplat = 1;
  else if (count == 1)
    interval_viplat = 2;
  else if (count == 2)
    interval_viplat = 3;
  double percent = 0.0;
  double sum_nalog = 0.0;
  double percent_month = 0.0;
  double timer_monthes = 1.0;
  int div = div_rate(&interval_viplat, &time);
  if (sum > 0 && time > 0 && percent_rate > 0 && taxes_rate > 0) {
    for (int i = 1; i <= time; i++) {
      percent_month = sum * percent_rate / 100 / div;
      percent += percent_month;
      if (month_popolnenie > 0 && month_popolnenie == timer_monthes &&
          sum_popolnenie > 0) {
        sum += sum_popolnenie;
      }
      if (month_sniatie > 0 && month_sniatie == timer_monthes &&
          sum_sniatie > 0) {
        sum -= sum_sniatie;
      }
      if (capitalization == 1) {
        sum += percent_month;
      }
      if (interval_viplat == 1) {
        timer_monthes += 0.5;
      } else if (interval_viplat == 2) {
        timer_monthes += 0.25;
      } else if (interval_viplat == 3) {
        timer_monthes += 1;
      }
    }
    sum_nalog = tax_calc(percent, taxes_rate);
    ui->lineEdit_procent_bonus->setText(QString::number(percent, 'f', 2));
    ui->lineEdit_nalog_bonus->setText(QString::number(sum_nalog, 'f', 2));
    ui->lineEdit_total_bonus->setText(QString::number(sum, 'f', 2));
  }
}

int MainWindow::div_rate(int *period_viplat, double *deposit_term) {
  int div_rate = 0;
  if (*period_viplat == 1) {
    (*deposit_term) *= 30.65;
    div_rate = 365;
  } else if (*period_viplat == 2) {
    (*deposit_term) *= 4.33;
    div_rate = 52;
  } else if (*period_viplat == 3) {
    (*deposit_term) *= 1;
    div_rate = 12;
  }
  return div_rate;
}

double MainWindow::tax_calc(double final_percent_sum, double tax_rate) {
  double tax_amount = 0;
  double percent_stavka = 0.12;
  double neoblagaemaya_summa = 1000000 * percent_stavka;
  if (final_percent_sum > neoblagaemaya_summa) {
    double x = final_percent_sum - neoblagaemaya_summa;
    tax_amount = x * (tax_rate / 100);
  } else {
    tax_amount = 0.0;
  }
  return tax_amount;
}
