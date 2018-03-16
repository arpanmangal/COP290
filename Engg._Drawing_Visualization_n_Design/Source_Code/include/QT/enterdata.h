#ifndef ENTERDATA_H
#define ENTERDATA_H

#include <QWidget>

namespace Ui {
class EnterData;
}

class EnterData : public QWidget
{
    Q_OBJECT

public:
    explicit EnterData(QWidget *parent, int mode);
    ~EnterData();

private:
    Ui::EnterData *ui;

    QWidget *my_parent;
    int mode;
};

#endif // ENTERDATA_H
