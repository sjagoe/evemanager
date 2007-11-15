#include <QApplication>

#include "main.hh"

#include <QMessageBox>

#include <QString>
#include <QMap>

Window::Window( QWidget* parent )
    : QWidget( parent )
{
    this->_btn = new QPushButton("Test!");

    connect( this->_btn, SIGNAL(clicked()), this, SLOT(run()));

    QVBoxLayout* l = new QVBoxLayout;
    l->addWidget(this->_btn);

    this->setLayout(l);

    connect( &this->_api,
        SIGNAL(requestComplete( QString, QDomDocument, QString )),
        this, SLOT(requestComplete( QString, QDomDocument, QString )) );
    connect( &this->_api,
        SIGNAL(requestFailed( QString, QString, QString )),
        this, SLOT(requestFailed( QString, QString, QString )) );
}

void Window::run()
{
    QMap<QString, QString> params;
    params.insert( QString("userID"), QString("695163") );
    params.insert( QString("characterID"), QString("767637297") );
    params.insert( QString("apiKey"), QString("VhNtTIJbptLoberHr0RcYFhmusa8aMllvXrqp8D0udzXFly9Xc3EBSmWoSy3clJ3") );
    //QMessageBox::information(this, "button", "clicked", QMessageBox::Ok);
    QString result = this->_api.character().skillInTraining( params );
    QMessageBox::information(this, "request", result, QMessageBox::Ok);
}

void Window::requestComplete( QString id, QDomDocument result, QString httpResponse )
{
    QString resultEmpty = " - empty Doc - ";
    if (!result.isNull())
    {
        resultEmpty = " - not empty Doc - ";
    }
    resultEmpty = resultEmpty.prepend( id );
    resultEmpty = resultEmpty.append( httpResponse );
    QMessageBox::information(this, "result", resultEmpty, QMessageBox::Ok);
}

void Window::requestFailed( QString id, QString error, QString httpResponse )
{
    QString err = id;
    err = err.append(" - ");
    err = err.append(error);
    err = err.append(" - ");
    err = err.append(httpResponse);
    QMessageBox::information(this, "result", err, QMessageBox::Ok);
}

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    Window window;
    window.show();

    return app.exec();
}
