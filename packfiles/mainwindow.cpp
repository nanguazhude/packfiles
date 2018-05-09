#include "mainwindow.hpp"
#include <QtWidgets>

#if defined(GUI_PACK_FILES)
class CWidget : public QWidget {
    QLineEdit * memDirWidget ;
    QPushButton * memChangeDirButton ;
    QPushButton * memDoButton ;
    MainWindow * super ;
public:
    CWidget( MainWindow * arg){
        super = arg ;
        QHBoxLayout * varLayout = new QHBoxLayout;
        this->setLayout( varLayout );

        memDirWidget = new QLineEdit ;
        memChangeDirButton = new QPushButton ;
        memDoButton = new QPushButton ;

        varLayout->addWidget( memDirWidget );
        varLayout->addWidget( memChangeDirButton );
        varLayout->addWidget( memDoButton );

        memChangeDirButton->setText( "dir" );
        memDoButton->setText( "do" );

        connect( memChangeDirButton,
                 &QPushButton::pressed,
                 this,
                 [this](){
            const auto varDirName = memDirWidget->text() ;
            const auto varNewDirName = QFileDialog::getExistingDirectory(nullptr,"Select Dir");
            if( varNewDirName == varDirName ){ return ; }
            memDirWidget->setText( varNewDirName ) ;
        });

        connect( memDoButton ,
                 &QPushButton::pressed,
                 this,
                 [this](){
            const auto varDirName = memDirWidget->text() ;
            super->dirChanged( varDirName );
        });

    }
} ;
#endif

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent){
#if defined(GUI_PACK_FILES)
    this->setCentralWidget(new CWidget{this});
    this->setMinimumHeight(64);
    this->setMinimumWidth(500);
    this->resize( 64,64 );
#endif
}

MainWindow::~MainWindow(){

}
