/*check build error*/
#include "botan.h"

namespace  {

class _BOTAN_INIT{
    Botan::LibraryInitializer $m$;
public:
    _BOTAN_INIT(){
    }
};

static char _data[8+sizeof(_BOTAN_INIT)];
static _BOTAN_INIT * _unused_=::new(_data) _BOTAN_INIT;

}/*namespace*/

/*just to remove warning*/
_BOTAN_INIT * ___get_Botan_LibraryInitializer(){
    return _unused_;
}

/***

    QFile file(u8R"(D:\x\m\bd3\baidu3\cplusplus_basic\botan\botan.h)");
    QFile outPut(u8R"(D:\x\m\bd3\baidu3\cplusplus_basic\botan\botan.1.h)");
    if(outPut.open( QIODevice::WriteOnly  ))
        if(file.open( QIODevice::ReadOnly |QIODevice::Text )){

            QTextStream textStream(&file);
            bool varIsClassMutiLine=false;
            QString varClassNameMutiLine;
            while(textStream.atEnd() == false){
                QString line = textStream.readLine();
                QVector<QStringRef> items = line.splitRef(
                            QChar(' ') ,QString::SkipEmptyParts );

                if(varIsClassMutiLine
                        &&(false==items.isEmpty())
                        &&(items.last().trimmed().endsWith(QChar('{')))){
                    varIsClassMutiLine=false;
                    line=line+
                            QLatin1String("\n    CPLUSPLUS_OBJECT(",22)+
                            std::move(varClassNameMutiLine)+
                            QLatin1String(")\nprivate:\n",11);
                    outPut.write( line.toUtf8() );
                }
                else if( (false==items.isEmpty())
                         &&(false==varIsClassMutiLine)
                         &&(items[0].trimmed()==QLatin1String("class",5))
                         &&(items.last().trimmed().endsWith(QChar('{'))) ){
                    varIsClassMutiLine=false;
                    for( const QStringRef & var: qAsConst(items) ){
                        auto && varI = var.trimmed();
                        if( varI ==  QLatin1String("class",5) ){ continue; }
                        if( varI == QLatin1String("BOTAN_DLL",9) ){ continue; }
                        //qDebug() << varI <<" !!! "<<line;
                        line=line+
                                QLatin1String("\n    CPLUSPLUS_OBJECT(",22)+
                                varI+
                                QLatin1String(")\nprivate:\n",11);
                        outPut.write( line.toUtf8() );
                        break;
                    }
                }
                else if( (items.size()>2 )
                         &&(false==varIsClassMutiLine)
                         &&(items[0].trimmed()==QLatin1String("class",5))
                         &&(items[1].trimmed()==QLatin1String("BOTAN_DLL",9))){
                    varIsClassMutiLine=true;
                    varClassNameMutiLine=items[2].trimmed().toString();
                    goto raw_write_line;
                }
                else{
raw_write_line:
                    outPut.write( line.toUtf8() );
                    outPut.write("\n",1);
                }

            }

        }

***/

