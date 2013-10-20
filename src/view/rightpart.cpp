#include "rightpart.h"

RightPart::RightPart(QWidget* parent)
{
    setParent(parent);
    setObjectName("rightPart");

    logosFrame = new ConsoLogos(this);
    cartDisplay = new CartDisplay(this);
    productsChoices = new ProductsChoices(this);
    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(logosFrame, 0, 0, 1, 2);
    layout->addWidget(cartDisplay, 0, 2, 1, 3);
    layout->addWidget(productsChoices, 1, 0, 3, 5);
    layout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(layout);
}

void RightPart::updateSize()
{
    productsChoices->updateSize();
    cartDisplay->updateSize();
}
