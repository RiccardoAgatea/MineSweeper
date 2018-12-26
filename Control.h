#ifndef CONTROL_H
#define CONTROL_H

#include <QWidget>

class MineSweeper;
class View;

class Control : public QWidget
{
    Q_OBJECT
private:
    MineSweeper *mine_sweeper;
    View *view;
public:
    explicit Control(View *parent);
    void newGame(const QString &difficulty);

signals:

public slots:
};

#endif // CONTROL_H
