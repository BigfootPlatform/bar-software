#ifndef POPUP_H
#define POPUP_H

#include <QWidget>
#include <QShortcut>
#include <QRegExp>
#include <QErrorMessage>

class Popup : public QWidget
{
    Q_OBJECT
public:
    explicit Popup(QWidget *parent = 0);
    bool isBalanceCorrect(QString value);
    
signals:
    
private:
    QShortcut *Enter;
    QShortcut *Return;
    QShortcut *Escape;

    QErrorMessage* error;

public slots:
    virtual void validate(){};
    virtual void cancel(){};
    
};

#endif // POPUP_H
