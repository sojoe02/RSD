#ifndef OEEWIDGET_H
#define OEEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

class OEEWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OEEWidget(QWidget *parent = 0);
    
signals:
    void error(int i);
    
public slots:
    void inputErr();

private:
    QPushButton *button;
    QLabel *label;
    QVBoxLayout *layout;
    
};

#endif // OEEWIDGET_H
