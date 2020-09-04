#include "Configuration.hpp"
#include "PageLib.hpp"
#include "DirScanner.hpp"
#include "RssReader.hpp"
#include "GlobalDefine.hpp"
#include "mylogger.hpp"

#include <iostream>
#include <fstream>

namespace zyh
{
PageLib::PageLib(Configuration & conf,
				 DirScanner & dirScanner)
	: _conf(conf),
	  _dirScanner(dirScanner)
{}


void PageLib::create()
{
	std::vector<std::string> & vecFiles = _dirScanner.files();//xml文件
	RssReader reader(vecFiles);
	reader.loadFeedFiles();//读取每个xml文件,并处理保存到vector中
	reader.makePages(_vecPages);//将处理完的结果转换为需要的格式保存到另一个vector中
}

//存储到ripepage.lib和offset.lib中
void PageLib::store()
{
	//从map中读取存放的ripepage.lib的路径
    
	std::map<std::string, std::string> & confMap = _conf.getConfigMap();
	std::string pageLibPath = confMap[RIPEPAGELIB_KEY];
	std::string offsetLibPath = confMap[OFFSETLIB_KEY];

    Mylogger *logger=Mylogger::getInstance();

	std::ofstream ofsPage(pageLibPath.c_str());
	std::ofstream ofsOffset(offsetLibPath.c_str());
	if(!(ofsPage.good() && ofsOffset.good()))
	{
        logger->error("读取ripepage.lib和offset.lib文件路径出错");
		std::cout << "ofstream open error!" << std::endl;
		return;
	}

	for(size_t idx = 0; idx != _vecPages.size(); ++idx)
	{
		int id = idx + 1;
		int length = _vecPages[idx].size();
		std::ofstream::pos_type offset = ofsPage.tellp();
		ofsPage << _vecPages[idx];

		ofsOffset << id << '\t' << offset << '\t' << length << '\n';
	}

	ofsPage.close();
	ofsOffset.close();
}

}//end of namespace zyh
