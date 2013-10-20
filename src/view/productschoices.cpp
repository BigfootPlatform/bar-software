#include "productschoices.h"

ProductsChoices::ProductsChoices(QWidget *parent) :
    MultiList(parent, 4, 0)
{
    setObjectName("productChoices");
    QTableWidgetItem *headers = new QTableWidgetItem[columns];
    headers[0].setText("Consommation");
    headers[1].setText("Volume");
    headers[2].setText("Prix");
    headers[3].setText("Id");
    for(int i=0 ; i < columns ; i++)
        list->setHorizontalHeaderItem(i, &headers[i]);

    list->horizontalHeader()->setDefaultSectionSize(70);
    list->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    list->horizontalHeader()->setSectionHidden(3, true);

    // ####### TEST #######
    std::queue< std::tuple< QString, QString, float, unsigned > > toto;
    std::tuple< QString, QString, float, unsigned > titi("Duvel", "0.33L", 1.9, 1);
    std::tuple< QString, QString, float, unsigned > titi2("Super Bock", "0.25L", 0.9, 2);
    toto.push(titi);
    toto.push(titi2);
    this->setProductsChoices(toto);
    // ####### FIN TEST #######
}

void ProductsChoices::setProductsChoices(std::queue< std::tuple< QString, QString, float, unsigned > > & queue)
{
    // TUPLE : QString conso, QString Volume, float price, unsigned id
    std::tuple< QString, QString, float, unsigned > tuple;

    // Deleting old results
    for(int i = 0 ; i<rows ; i++)
    {
        delete itemList[i];
    }
    if(isInitialised && rows !=0)
        delete itemList;
    else
        isInitialised = true;

    // Inserting new results
    unsigned numberOfElements = queue.size();
    setRows(numberOfElements);
    // Creating our matrix representing table
    itemList = new QTableWidgetItem*[numberOfElements];
    for(unsigned i = 0 ; i<numberOfElements ; i++)
    {
        itemList[i] = new QTableWidgetItem[columns];
    }
    // Setting it up to table
    for(unsigned i=0 ; i<numberOfElements ; i++)
    {
        tuple = queue.front();
        queue.pop();
        itemList[i][0].setText(std::get<0>(tuple));
        itemList[i][1].setText(std::get<1>(tuple));
        itemList[i][2].setText(QString::number(std::get<2>(tuple)));
        itemList[i][3].setText(QString::number(std::get<3>(tuple)));
        for(int j=0 ; j < columns ; j++)
            list->setItem(i, j, &itemList[i][j]);
    }
    list->sortItems(0, Qt::AscendingOrder);
    return;
}
