#include "Configuration.hpp"
#include "GlobalDefine.hpp"
#include "mylogger.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

namespace zyh
{

Configuration::Configuration(const std::string & filepath)
	: filepath_(filepath)
{
	readConfiguration();
}

void Configuration::readConfiguration()
{
	std::ifstream ifs(filepath_.c_str());
    Mylogger *logger=Mylogger::getInstance();
	if(ifs.good())
	{
		std::string line;
		while(getline(ifs, line))
		{
			std::istringstream iss(line);
			std::string key;
			std::string value;
			iss >> key >> value;
			configMap_[key] = value;
		}
		std::cout << "read configuration is over!" << std::endl;
        logger->info("读取配置文件成功");
	}
	else
	{
		std::cout << "ifstream open error" << std::endl;
        logger->error("读取配置文件失败");
	}
}

std::map<std::string, std::string> & Configuration::getConfigMap()
{
	return configMap_;
}

std::set<std::string> & Configuration::getStopWordList()
{
	if(stopWordList_.size() > 0)
		return stopWordList_;

    Mylogger *logger=Mylogger::getInstance();
	std::string stopWordFilePath = configMap_[STOP_WORD_KEY];
	std::ifstream ifs(stopWordFilePath.c_str());
	if(!ifs)
	{
		std::cout << "StopWord ifstream open error!" << std::endl;
        logger->error("获取停词库出错");
	}
	
	std::string word;
	while(getline(ifs, word))
	{
		stopWordList_.insert(word);
	}

// for debug	
#if 0
	for(auto &str : stopWordList_)
	{
		std::cout << str << "\t" << str.size() << std::endl;
	}
	std::cout << std::endl;
#endif

	return stopWordList_;
}

}// end of namespace zyh
