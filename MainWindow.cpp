#include "MainWindow.hpp"

#include "examples/MyComplexButton.hpp"
#include "examples/MyVerticalButton.hpp"
#include "examples/HIconButton.hpp"

#include <QVBoxLayout>

#include <QStyle> // for getting default icons

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget* proxy = new QWidget(this);
    {
        QVBoxLayout* lay = new QVBoxLayout;
        {
            auto* btn_1 = new HIconButton(this);
            auto* btn_2 = new MyVerticalButton(this);
            auto* btn_3 = new MyComplexButton(this);

            btn_1->setIcon( this->style()->standardIcon(QStyle::StandardPixmap::SP_MediaPlay)  );
            btn_2->setIcon( this->style()->standardIcon(QStyle::StandardPixmap::SP_MediaPause) );

            lay->addWidget( btn_1 );
            lay->addWidget( btn_2 );
            lay->addWidget( btn_3 );
        }
        proxy->setLayout( lay );
    }

    this->setCentralWidget(proxy);
}

MainWindow::~MainWindow()
{ }

