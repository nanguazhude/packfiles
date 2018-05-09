#include "qtbasic.hpp"
#include "mainwindow.hpp"
#include <QApplication>
#include <map>
#include <vector>
#include <memory>
#include <QRegularExpression>
#include <QtCore>

extern bool move_file(const QString & argS,const QString & argT);

const QRegularExpression staticR =[](){
    QRegularExpression varAns{u8R"([0-9][0-9.]*[0-9])"_qs};
    return std::move(varAns);
}();

inline void doWork( const QString & argDirName ){

    std::map< QString, std::shared_ptr< std::vector< QFileInfo> > > staticData;

    {
        QDirIterator varI{ argDirName,QDir::NoDotAndDotDot|QDir::Files};
        while ( varI.hasNext() ) {
            varI.next();
            const QFileInfo varInfo = varI.fileInfo();
            const QString varFileName = varInfo.fileName() ;
            const QString varFileIndex = staticR.match(varFileName).captured(0);
            if(varFileIndex.isEmpty()){continue;}
            auto varPos = staticData.find(varFileIndex);
            if(varPos == staticData.end()){
                staticData[varFileIndex]=std::make_shared<std::vector<QFileInfo>>();
                varPos = staticData.find(varFileIndex);
            }
            varPos->second->push_back( varInfo  ) ;
        }
    }

    const QDir varDir{ argDirName } ;
    for(const auto & varI : staticData ){
        const QString & varFileIndex = varI.first ;
        const std::vector< QFileInfo> & varFiles = *(varI.second);

        const QString & varT = argDirName+"/"_q1s +varFileIndex;
        varDir.mkpath( varT );

        for( const QFileInfo & varJ : varFiles ){
            move_file( varJ.absoluteFilePath() , varT+"/"_q1s+varJ.fileName() );
        }

    }

}


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

#if defined(GUI_PACK_FILES)
    MainWindow window;
    window.connect(&window,&MainWindow::dirChanged,
                   &window,
                   [](const QString arg){ doWork( arg ); },
                   Qt::QueuedConnection);
    window.show();
#else
    doWork( u8R"(E:\图片\E71001)"_qs );
    doWork( u8R"(E:\图片\E82001)"_qs );
    doWork( u8R"(E:\图片\半成)"_qs );
    doWork( u8R"(E:\图片\刹车鼓)"_qs );
    doWork( u8R"(E:\图片\华汽)"_qs );
    doWork( u8R"(E:\图片\金麒麟)"_qs );
    doWork( u8R"(E:\图片\隆通大盘)"_qs );
    doWork( u8R"(E:\图片\鲁达a单片作废)"_qs );
    doWork( u8R"(E:\图片\赛路CDR图纸)"_qs );
    doWork( u8R"(E:\图片\三力)"_qs );
    doWork( u8R"(E:\图片\三力单片半成)"_qs );
    doWork( u8R"(E:\图片\外调)"_qs );
    doWork( u8R"(E:\图片\新建文件夹)"_qs );
    MainWindow window;
    window.show();
#endif

    return app.exec();
}

/*
 *
*/

