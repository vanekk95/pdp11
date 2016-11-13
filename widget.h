#ifndef WIDGET_H
#define WIDGET_H


#include <QWidget>
#include "tablemodel.h"
#include "process.h"
#include <QTableView>
#include "formain.h"
#include "styleddelegate.h"

namespace Ui {
class Widget;
}

enum State {
    StateInit,
    StateRun,
    StateStop
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0, Arg *arg = NULL);
    ~Widget();

private:
    Ui::Widget *ui;
    QTimer *timer;
    SharedMem *sharedMem;
    CallList *callList;
    TableModel *tableModel;

    void setEnableButton(State state);

private slots:
    void slotButtonRun();
    void slotButtonContinue();
    void slotButtonStop();
    void slotButtonReset();
    void slotButtonStep();
    void slotUpdateRegister();
    void userClicked(QModelIndex index);
};


#endif // WIDGET_H
