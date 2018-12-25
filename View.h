#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QMainWindow>

class Control;

class View : public QWidget
{
    Q_OBJECT
private:
    Control *control;
    QMainWindow *window;
public:
    View(Control *cont, QWidget *parent = nullptr);

signals:

public slots:
    //void show();
};

#endif // VIEW_H
