#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "algo.h"
#include <cmath>
#include <algorithm>


#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ApplyModel();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::ApplyModel() {
    size_t size_deque = deque_model_.items.size();
    ui->txt_size->setText(QString::number(size_deque));

    if (size_deque == 0) {
        ui->pb_pop_back->setDisabled(true);
        ui->pb_erase->setDisabled(true);
        ui->pb_pop_front->setDisabled(true);
    } else {
        ui->pb_pop_back->setDisabled(false);
        ui->pb_erase->setDisabled(false);
        ui->pb_pop_front->setDisabled(false);
    }

    auto preserve_iter = deque_model_.iterator;

    ui->list_widget->clear();
    for (size_t i = 0; i < size_deque; ++i) {
        ui->list_widget->addItem(QString::number(i) + ": " + QString::fromStdString(deque_model_.items[i]));
    }
    ui->list_widget->addItem("end");

    deque_model_.iterator = preserve_iter;
    ApplyIterator();
}

void MainWindow::ApplyIterator() {
    size_t distance = abs(std::distance(deque_model_.iterator, deque_model_.items.begin()));

    ui->list_widget->setCurrentRow(distance);

    if (distance == deque_model_.items.size()) {
        ui->btn_edit->setDisabled(true);
        ui->pb_erase->setDisabled(true);
        ui->pb_plusplus->setDisabled(true);
        ui->txt_elem_content->clear();
    } else {
        ui->btn_edit->setDisabled(false);
        ui->pb_erase->setDisabled(false);
        ui->pb_plusplus->setDisabled(false);
        ui->txt_elem_content->setText(QString::fromStdString(*deque_model_.iterator));
    }

    if (distance == 0) {
        ui->btn_dec->setDisabled(true);
    } else {
        ui->btn_dec->setDisabled(false);
    }
}

void MainWindow::SetRandomGen(const std::mt19937 &random_gen)
{
    std::random_device rd;
    random_gen_ = random_gen;
}

void MainWindow::on_pb_clear_clicked()
{
    deque_model_.items.clear();
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_pb_pop_back_clicked()
{
    deque_model_.items.pop_back();
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_pb_push_back_clicked()
{
    string new_elem_string = ui->txt_elem_content->text().toStdString();
    deque_model_.items.push_back(new_elem_string);
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_list_widget_currentRowChanged(int currentRow)
{
    if (currentRow < 0) {
        currentRow = 0;
        deque_model_.iterator = deque_model_.items.begin();
        ApplyIterator();
        return;
    }
    deque_model_.iterator = deque_model_.items.begin() + currentRow;
    ApplyIterator();
}


void MainWindow::on_pb_begin_clicked()
{
    deque_model_.iterator = deque_model_.items.begin();
    ApplyIterator();
}


void MainWindow::on_pb_end_clicked()
{
    deque_model_.iterator = deque_model_.items.end();
    ApplyIterator();
}


void MainWindow::on_pb_plusplus_clicked()
{
    if(deque_model_.iterator + 1 > deque_model_.items.end()) {
        deque_model_.iterator = deque_model_.items.end();
        ApplyIterator();
        return;
    }
    ++deque_model_.iterator;
    ApplyIterator();
}


void MainWindow::on_btn_dec_clicked()
{
    if(deque_model_.iterator == deque_model_.items.begin()) {
        deque_model_.iterator = deque_model_.items.begin();
        ApplyIterator();
        return;
    }
    --deque_model_.iterator;
    ApplyIterator();
}


void MainWindow::on_btn_edit_clicked()
{
    std::string text = ui->txt_elem_content->text().toStdString();
    *deque_model_.iterator = text;
    ApplyModel();
}


void MainWindow::on_pb_erase_clicked()
{
    deque_model_.items.erase(deque_model_.iterator);
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_pb_insert_clicked()
{
    string text = ui->txt_elem_content->text().toStdString();
    deque_model_.items.insert(deque_model_.iterator,text);
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_pb_resize_clicked()
{
    size_t size = ui->txt_size->text().toInt();

    if (size > 1000) {
        size = 1000;
    }

    deque_model_.items.resize(size);
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();

}


void MainWindow::on_pb_find_clicked()
{
    string text = ui->txt_elem_content->text().toStdString();
    deque_model_.iterator = std::find(deque_model_.items.begin(),deque_model_.items.end(),text);
    ApplyIterator();
}


void MainWindow::on_pb_count_clicked()
{
    string text = ui->le_count->text().toStdString();
    int pieces = count(deque_model_.items.begin(),deque_model_.items.end(),text);
    ui->lbl_count->setText(QString::number(pieces));
    ApplyIterator();
}


void MainWindow::on_pb_min_element_clicked()
{
    deque_model_.iterator = min_element(deque_model_.items.begin(), deque_model_.items.end(), [&](std::string lhs, std::string rhs) {
        return lhs < rhs;
    });
    ApplyIterator();
}


void MainWindow::on_pb_max_element_clicked()
{
    deque_model_.iterator = max_element(deque_model_.items.begin(), deque_model_.items.end());
    ApplyIterator();
}

void MainWindow::on_pb_reverse_clicked()
{
    reverse(deque_model_.items.begin(),deque_model_.items.end());
    ApplyModel();
}


void MainWindow::on_pb_shuffle_clicked()
{
    random_device rd;
    mt19937 gen_shuffle(rd());
    shuffle(deque_model_.items.begin(), deque_model_.items.end(), random_gen_);
    SetRandomGen(gen_shuffle);
    ApplyModel();
}


void MainWindow::on_pb_unique_clicked()
{
    if (is_sorted(deque_model_.items.begin(), deque_model_.items.end())) {
        auto iter = unique(deque_model_.items.begin(),deque_model_.items.end());
        deque_model_.items.erase(iter, deque_model_.items.end());
        deque_model_.iterator = deque_model_.items.begin();
        ApplyModel();
    }
}


void MainWindow::on_pb_merge_sort_clicked()
{
    auto comp = [](string lhs,string rhs) {
        QString q_lhs = QString::fromStdString(lhs);
        QString q_rhs = QString::fromStdString(rhs);
        return QString::compare(q_lhs,q_rhs,Qt::CaseSensitive) < 0;
    };

    deque_model_.items = MergeSort(deque_model_.items, comp);
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_pb_merge_sOrT_clicked()
{
    auto comp = [](string lhs,string rhs) {
        QString q_lhs = QString::fromStdString(lhs);
        QString q_rhs = QString::fromStdString(rhs);
        return QString::compare(q_lhs,q_rhs,Qt::CaseInsensitive) < 0;
    };

    deque_model_.items = MergeSort(deque_model_.items, comp);
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_pb_lower_bound_clicked()
{
    if (!is_sorted(deque_model_.items.begin(),deque_model_.items.end())) {
        return;
    }
    string text = ui->txt_elem_content->text().toStdString();
    deque_model_.iterator = lower_bound(deque_model_.items.begin(),deque_model_.items.end(),text);
    ApplyIterator();
}

void MainWindow::on_pb_upper_bound_clicked()
{
    if (!is_sorted(deque_model_.items.begin(),deque_model_.items.end())) {
        return;
    }
    string text = ui->txt_elem_content->text().toStdString();
    deque_model_.iterator = upper_bound(deque_model_.items.begin(),deque_model_.items.end(),text);
    ApplyIterator();
}


void MainWindow::on_pb_pop_front_clicked()
{
    deque_model_.items.pop_front();
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_pb_push_front_clicked()
{
    string text = ui->txt_elem_content->text().toStdString();
    deque_model_.items.push_front(text);
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_pb_tea_clicked()
{
    deque_model_.items = tea;
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_pb_cakes_clicked()
{
    deque_model_.items = cakes;
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

