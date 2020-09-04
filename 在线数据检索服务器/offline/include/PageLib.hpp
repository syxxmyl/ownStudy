#ifndef _PAGELIB_H_
#define _PAGELIB_H_

#include <string>
#include <vector>


namespace zyh
{

class Configuration;
class DirScanner;

class PageLib
{
public:
	PageLib(Configuration & conf,
			DirScanner & dirScanner);

	void create();
	void store();

private:
	Configuration &          _conf;
	DirScanner &             _dirScanner;
	std::vector<std::string> _vecPages;
};

}//end of namespace zyh

#endif
