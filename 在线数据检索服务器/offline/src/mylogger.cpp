#include "mylogger.hpp"
#include <iostream>

using namespace log4cpp;

Mylogger *Mylogger::_pInstance=nullptr;

Mylogger *Mylogger::getInstance(){
    if(nullptr==_pInstance){
        _pInstance=new Mylogger();

    }
    return _pInstance;
}

void Mylogger::destory(){
    if(_pInstance){
        delete _pInstance;
        _pInstance=nullptr;

    }
}

Mylogger::Mylogger():
    _mycat(log4cpp::Category::getRoot()){

        PatternLayout *pPatternLayout1=new PatternLayout();
        pPatternLayout1->setConversionPattern("%d %c [%p] %m%n");
        PatternLayout *pPatternLayout2=new PatternLayout();
        pPatternLayout2->setConversionPattern("%d %c [%p] %m%n");

        OstreamAppender *pOstreamAppender=new OstreamAppender("OstreamAppender",&std::cout);
        pOstreamAppender->setLayout(pPatternLayout1);
        FileAppender *pFileAppender=new FileAppender("FileAppender","../log/offline.log");
        pFileAppender->setLayout(pPatternLayout2);

        _mycat.addAppender(pOstreamAppender);
        _mycat.addAppender(pFileAppender);

        _mycat.setPriority(Priority::DEBUG);
    }

Mylogger::~Mylogger(){
    log4cpp::Category::shutdown();

}   

