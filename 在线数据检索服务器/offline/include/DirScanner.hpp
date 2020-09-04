#ifndef _DIRSCAN_H_
#define _DIRSCAN_H_

#include <string>
#include <vector>


namespace zyh
{

const int kFileNo = 10000;

class Configuration;

class DirScanner
{
public:
	DirScanner(Configuration & conf);

	void operator()();

	std::vector<std::string> & files();

	void debug();
private:
	void traverse(const std::string & dirName);

private:
	Configuration & conf_;
	std::vector<std::string> vecFiles_;
};

} // end of namespace zyh
#endif
