#ifndef HISTORY_H
#define HISTORY_H

#include "multilist.h"
#include "controller.h"
#include "structures.h"
extern ViewObjects VIEW;

class Controller;
class History : public MultiList
{
    Q_OBJECT
public:
    explicit History(QWidget *parent = 0);

    // Revceive history from controller
    void setHistory( std::queue < std::tuple < QString, QString, QString, float, QString > > & queue);
    
private:



signals:
    
public slots:
    
};

#endif // HISTORY_H
