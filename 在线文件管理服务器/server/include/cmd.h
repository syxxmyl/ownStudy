#ifndef __CMD_H__
#define __CMD_H__

#include "head.h"

int cmdCd(int,char *);

int cmdLs(int);

int cmdPuts(int);

int cmdGets(int);

int cmdRemove(int);

int cmdPwd(int);

int cmdMkdir(int);

/*删除目录*/
int remove_dir(char*);


#endif
