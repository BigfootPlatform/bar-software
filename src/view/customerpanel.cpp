#include "customerpanel.h"

CustomerPanel::CustomerPanel(QWidget *parent) :
    QFrame(parent)
{
    VIEW.customerPanel = this;
    setObjectName("customerPanel");

    photoFrame = new QFrame(this);
    infosFrame = new QFrame(this);
    optionsFrame = new QFrame(this);
    layout = new QGridLayout(this);
    optionsLayout = new QGridLayout(optionsFrame);
    layout->addWidget(photoFrame, 0, 0, 2, 1);
    layout->addWidget(infosFrame, 0, 1);
    layout->addWidget(optionsFrame, 1, 1);
    layout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(layout);

    //###### PHOTO ######
    photo = new QLabel(photoFrame);
    photoLayout = new QGridLayout(photoFrame);
    photoLayout->addWidget(photo, 0, 0);
    photoLayout->setContentsMargins(0, 0, 0, 0);
    photoFrame->setLayout(photoLayout);

    //###### INFOS ########
    infosLayout = new QGridLayout(infosFrame);
    nameLabel = new QLabel("Nom ", infosFrame);
    firstNameLabel = new QLabel("Prénom ", infosFrame);
    loginLabel = new QLabel("Login ", infosFrame);
    categorieLabel = new QLabel("Cat. ", infosFrame);
    balanceLabel = new QLabel("Solde ", infosFrame);
    name = new QLabel(infosFrame);
    firstName = new QLabel(infosFrame);
    login = new QLabel(infosFrame);
    categorie = new QLabel(infosFrame);
    balance = new QLabel(infosFrame);
    futurBalance = new QLabel(infosFrame);
    calculator = new QPushButton(optionsFrame);
    history = new QPushButton(optionsFrame);
    editCustomer = new QPushButton(optionsFrame);
    deleteCustomer = new QPushButton(optionsFrame);

    QFont bold, normal;
    bold.setBold(true);
    normal.setPixelSize(14);
    bold.setPixelSize(14);
    name->setFont(bold);
    firstName->setFont(bold);
    login->setFont(bold);
    categorie->setFont(bold);
    balance->setFont(bold);
    futurBalance->setFont(bold);
    nameLabel->setFont(normal);
    firstNameLabel->setFont(normal);
    loginLabel->setFont(normal);
    categorieLabel->setFont(normal);
    balanceLabel->setFont(normal);
    photo->setPixmap(GLOBAL_PATH + "resources/photos/no_photo.jpg");
    photo->setMaximumSize(150, 220);

    infosLayout->addWidget(nameLabel, 0, 0);
    infosLayout->addWidget(name, 0, 1, 1, 1, Qt::AlignLeft);
    infosLayout->addWidget(firstNameLabel, 1, 0);
    infosLayout->addWidget(firstName, 1, 1, 1, 1, Qt::AlignLeft);
    infosLayout->addWidget(loginLabel, 2, 0);
    infosLayout->addWidget(login, 2, 1, 1, 1, Qt::AlignLeft);
    infosLayout->addWidget(categorieLabel, 3, 0);
    infosLayout->addWidget(categorie, 3, 1, 1, 1, Qt::AlignLeft);
    infosLayout->addWidget(balanceLabel, 4, 0);
    infosLayout->addWidget(balance, 4, 1, 1, 1, Qt::AlignLeft);
    infosLayout->addWidget(futurBalance, 5, 1, 1, 1, Qt::AlignLeft);
    infosLayout->setContentsMargins(0, 30, 0, 0);
    infosFrame->setLayout(infosLayout);


    // an empty button is created to take the empty place generated with different photos, and let the option icon to be always at the same place
    //QLabel* emptyButton = new Q(optionsFrame);
    //emptyButton->setFlat(true);
    //emptyButton->setUpdatesEnabled(false);
    calculator->setIcon(QIcon(GLOBAL_PATH + "resources/pictures/calculator.png"));
    calculator->setFlat(true);
    calculator->setIconSize(QSize(32,32));
    calculator->setToolTip("Calculatrice (donner ou retirer de l'argent à un client)");
    history->setText("H");
    history->setToolTip("Historique du client");
    editCustomer->setText("edit");
    editCustomer->setToolTip("Editer les informations du client");
    deleteCustomer->setText("suppr");
    deleteCustomer->setToolTip("Supprimer ce client");

    QObject::connect(calculator, SIGNAL(clicked()), this, SLOT(launchCalculator()));
    QObject::connect(history, SIGNAL(clicked()), this, SLOT(launchIndividualHistory()));
    QObject::connect(editCustomer, SIGNAL(clicked()), this, SLOT(launchEditCustomer()));
    QObject::connect(deleteCustomer, SIGNAL(clicked()), this, SLOT(launchDeleteCustomer()));

    //optionsLayout->addWidget(emptyButton, 0,0);
    optionsLayout->addWidget(calculator, 0,1);
    optionsLayout->addWidget(history, 0,2);
    optionsLayout->addWidget(editCustomer, 0, 3);
    optionsLayout->addWidget(deleteCustomer, 0, 4);
    optionsLayout->setColumnStretch(0, 1);
    optionsLayout->setSpacing(0);
    optionsLayout->setContentsMargins(0,0,0,0);
    optionsFrame->setLayout(optionsLayout);

    // ###### TEST #########
    //std::tuple<QString, QString, QString, QString, float> toto("Rousseau", "Woody", "wrousseau", "2015", -3.5);
    //setCustomer(toto);
}

CustomerPanel::~CustomerPanel()
{
    /*delete photo;
    delete name;
    delete firstName;
    delete categorie;
    delete balance;
    delete photoFrame;
    delete infosFrame;
    delete optionsFrame;
    delete layout;
    delete photoLayout;
    delete infosLayout;
    delete nameLabel;
    delete firstNameLabel;
    delete categorieLabel;
    delete balanceLabel;*/
}

void CustomerPanel::setController(Controller* controllerPar)
{
    controller = controllerPar;
}

void CustomerPanel::setCustomer(view_customerTuple & tuple)
{
    //We put such information in the curCoustomer of the controller
   controller->setCurCustomer(tuple);

    // std::tuple<QString name, QString firstName, QString login, QString categorie, float balance>
    ID = tuple.getCustomerId();
    name->setText(tuple.getCustomerName());
    firstName->setText(tuple.getCustomerFirstName());
    login->setText(tuple.getCustomerLogin());
    categorie->setText(QString::number(tuple.getCustomerCategory()));
    balance->setText(QString::number(tuple.getCustomerBalance()) + " €");


    if(tuple.getCustomerBalance() < 0)
        balance->setStyleSheet("color: #FF0000;");
    else
        balance->setStyleSheet("color: black;");

    // if login is not defined, we take the name to search for the photo
    QString tmpLogin(tuple.getCustomerLogin().toLower());
    if(tmpLogin == "null")
        tmpLogin = tuple.getCustomerName().toLower();

    if(QFile::exists(GLOBAL_PATH + "resources/photos/"+ tmpLogin + ".jpg"))
        photo->setPixmap(GLOBAL_PATH + "resources/photos/"+ tmpLogin + ".jpg");
    else
        photo->setPixmap(GLOBAL_PATH + "resources/photos/no_photo.jpg");
}

void CustomerPanel::setFuturBalance(float nextBalance, bool on)
{
    if(!on)
    {
        futurBalance->clear();
        return;
    }
    futurBalance->setText("-> " + QString::number(nextBalance) + " €");
    if(nextBalance < 0)
        futurBalance->setStyleSheet("color: #FF0000;");
    else
        futurBalance->setStyleSheet("color: black;");
}


void CustomerPanel::launchCalculator()
{
    controller->newClic_Calculator();
}

void CustomerPanel::launchIndividualHistory()
{
    controller->newClic_IndividualHistory(ID);
}

void CustomerPanel::launchEditCustomer()
{
    controller->newClic_EditCustomer();
}

void CustomerPanel::launchDeleteCustomer()
{
    controller->newClic_DeleteCustomer();
}
