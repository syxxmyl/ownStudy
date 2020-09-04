#pragma once

#include <log4cpp/Category.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Priority.hh>


class Mylogger{
public:

    static Mylogger *getInstance();

    static void destory();


    template <class ...Args>
        void warn(Args... args){
            _mycat.warn(args...);
        }

    template <class ...Args>
        void error(Args... args){
            _mycat.error(args...);
        }

    template <class ...Args>
        void info(Args... args){
            _mycat.info(args...);
        }

    template <class ...Args>
        void debug(Args... args){
            _mycat.debug(args...);
        }

private:
    Mylogger();
    ~Mylogger();

    static Mylogger *_pInstance;
    log4cpp::Category &_mycat;
};
