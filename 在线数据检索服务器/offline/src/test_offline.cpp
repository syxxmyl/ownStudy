#include "GlobalDefine.hpp"
#include "Configuration.hpp"
#include "DirScanner.hpp"
#include "PageLib.hpp"
#include "WordSegmentation.hpp"
#include "WebPage.hpp"
#include "PageLibPreprocessor.hpp"
#include "mylogger.hpp"

#include <stdio.h>
#include <time.h>

int main(void)
{
    Mylogger *logger=Mylogger::getInstance();
    logger->info("程序启动...");
	zyh::Configuration conf("../conf/my.conf");
	conf.debug();

	zyh::DirScanner dirScanner(conf);
	dirScanner();
	dirScanner.debug();

	zyh::PageLib pagelib(conf, dirScanner);

	time_t t1 = time(NULL);
	pagelib.create();
	pagelib.store();
	time_t t2 = time(NULL);
	printf("raw lib create and store time: %ld min\n", (t2 - t1));

	zyh::PageLibPreprocessor libPreprocessor(conf);
	libPreprocessor.doProcess();

	return 0;
}
