可以在vim/plugged/prepare-code/snippet/snippet.c里修改初始化的c文件模板



# day1

## git使用

### git存储的原理

首先进行压缩，对于没有发生修改的版本只用虚拟的一个指针指向自己表示新的版本，只有发生修改的版本才会再存放一个新的版本，存储了所有有差异的版本，将其压缩

### git存储系统的组成部分

工作目录/工作树	当前文件夹

缓存区	待提交的内容

仓库		历史的版本

![image-20200313161003267](D:\TyporaPic\复习笔记Linux\image-20200313161003267.png)

### 配置姓名和邮箱

```
git config --global user.name xxx

git config --global user.email xxxg
```

### 创建本地仓库

git init =>	.git	存放仓库信息

### 从远端克隆一个仓库

```
git clone+链接
```

### 常用提交命令

```cpp
git pull origin master	//保持同步,从远端仓库拉取内容；没有的直接从 gitee上拷贝下来，有的，如果 gitee 上新增的直接合并增加到本地，有修改的则不会拉取

git add --all	//提交到缓存区，在工作目录（工作树）上执行完操作后，要把更新后的内容提交到缓存区(stage/index)中，即保存修改的操作，但是还没有提交，因为仍然在本地上
    
git commit -m "提交信息"	//从缓存区提交到本地仓库，将add保存的内容放在本地的仓库中，保存为一个版本，即可以在历史记录中找到它，其他版本可以跳转到这个版本
    
git push origin master	//保持同步push从本地将修改推送过去，把在本地仓库中的内容推送到 gitee 上，如果多个仓库同时推送，push的时候就会进行合并，进入一个文本编辑器，负责写合并信息
    
git reset --hard origin/master	//硬重置本地master的所有内容并使它和线上的origin/master完全相同
```

### 查看工作状态

git status

无修改，

有修改，未stage

有修改，未commit

### 忽略文件

在add的时候就不会把不想提交的提交了

vim .gitignore		通配符规则

### 比较文件差异

git diff 

### 查看提交信息

git log

```
commit：版本号-校验和	指向分支的指针->当前分支
Author：用户	邮箱
Date：	日期
		commit信息
```

git log --stat 显示每次修改的概况

git log -p 显示每次改动的具体内容

git reset	回负缓存区的内容，将某个缓存的内容退回到工作树

### fetch和pull

git fetch

git pull

fetch只会拉取没有的文件，相同的文件名不同的文件内容的不会更新

pull，先fetch再merge

### 分支管理

git remote 显示远端是什么分支

git remote -v 显示URL

git branch  xxx	创建了新的分支

git checkout xxx	切换到分支

git merge 	分支合并

git branch -d/D	删除分支(强制删除)



## Linux 常用命令

### 用户配置

超级用户的开头是`#`

普通用户的开头是`$`

#### 给root配置密码		

`sudo passwd root`

#### 切换用户

`su xxx`	直接su的话是切换到root

可以用`cat /etc/passwd`查看当前系统下有哪些用户

`exit`退出到上一个用户	类似栈，用户在栈中的时候无法被删除

#### 添加用户

`sudo useradd -m xxx -s /bin/bash`

`-m`这样才能在`/home`下添加一个xxx的目录，否则只有读权限没有写权限

`-s /bin/bash` 以何种脚本解析

配置完账户还要配置密码	`passwd xxx`	,这样才能使用这个账户

默认添加一个新用户就会把这个成员分给同名组

#### 删除用户

`sudo userdel xxx`

`sudo userdel -r xxx`	连带/home目录下的一起删除

### 显示系统下的挂载信息

`mount`



### 显示所有文件(包括隐藏文件)

`ls -a` 	文件以`.`开头，就是隐藏文件

### 显示文件的详细信息

`ls -l`			添加`-h`参数可以让文件大小按k、M显示

```cpp
drwxr-xr-x 2 zhou zhou 4096 Feb 24 01:29 Desktop

d开头为目录文件，`-`开头为普通文件	
rwx读 写 执行 权限，三组对应用户、组、其他组的用户
2:	硬链接数
zhou 用户名
zhou 组名
4096 文件大小
Feb 24 01:29 修改时间
Desktop 文件名
```

### 查看设备文件

`cd /dev`	进入设备目录		使用`ls -l`查看

b开头的是块设备文件，一次读取一块

c开头的是字符设备文件，一次读取一个字节

### 目录相关命令

#### 目录的结构

Linux是树形结构，可以用`tree`命令查看，Windows是一个森林，每个盘是一棵树

目录本身也是一个文件，存放的是该目录下存放的文件名和文件的地址(inode)，默认目录大小为4kB

每对文件进行一次操作，同时也会对目录进行修改，因此在目录下对文件的操作的可行与否取决于**当前用户是否对这个目录有写权限**

删除文件的本质操作即为 把文件断开和目录的连接

#### 显示工作目录

`pwd`

#### 改变工作目录

`cd xxx`

`cd /`	根目录

`cd .`当前目录

`cd ..`父目录

`cd ~`	回到用户自己的根目录(全局来看是`/usr/xxx/`下)

`cd -`	回到上一个目录，只能在两个目录间来回切换，本质是两个环境变量`PWD`和`OLDPWD`互相赋值

#### 创建目录

`mkdir xxx`

#### 删除目录

`rmdir xxx`	只能删除空目录

`rm xxx -rf`	全部删除且不确认

# day2

## Linux常用命令

### 拷贝文件

`cp xxx1 xxx2`

`cp -i`	拷贝前会确认是否要覆盖，默认直接覆盖

`-f`强制覆盖

`-r`拷贝目录时使用，循环拷贝

### 移动文件

`mv`

常用来重命名文件

移动文件本质是修改内部记录的路径位置和对应的目录文件中的信息，不发生信息的拷贝，因此比拷贝文件快的多

`mv -i`	移动前会确认是否要覆盖，默认直接覆盖

`-f`	强制覆盖不提示

### 控制台快捷键

`ctrl+A`光标移到行首

`ctrl+E`光标回到行尾

### 删除文件

`rm`

`-r`	删除空目录

`rm -i `	删除前会确认是否要覆盖，默认直接覆盖

`-f`	强制删除不提示

### 查看命令帮助

`man xxx`	查看xxx命令的相关用法

按f和b向前/后移动，q退出

`/xx`查找内容为xx的位置

### 改变文件权限

增加或删除文件和当前目录的写权限有关

文件是否可执行和当前文件的执行权限有关

`chmod`

#### 文字设定法

u-user	g-group	o-other	a-all

`chmod o+w dir1`	给其他用户增加dir1文件的写权限

`chmod o-w dir1`	取消其他用户对dir1文件的写权限

`chmod o=r dir1`	修改其他用户对dir1文件的权限为仅有读权限

#### 数字设定法

八进制数表示rwx的权限，r为4，w为2，x为1

`chmod 777 dir1`	设定所有人都有dir1的所有权限

`chmod 775 dir1`	只有其他用户对dir1没有写权限

编写的bash脚本需要用`chmod +x xxx` 赋予脚本可执行权限后才能`./xxx`执行脚本

### 文件查找

find	起始目录	查找条件	操作

`find . -name "stdio.h"`	在当前目录查找名字为stdio.h的文件

文件名支持通配符`* ? []`

```
`*`表示0或任意多个字符

`?`表示某个字符(占1个字符)

`[]`表示字符的变化范围
```

支持逻辑与或非

```
`-a`	and，且				
`-o`	or，或				
`!`		not，非
```

特定内容查找

```
-gid	组id
-uid	用户id

-user	用户名
-group	组名

-empty	空文件

-perm	权限

-size	block大小

-type	类型	ls -l	里的类型，普通文件是f
```

根据时间查找：

```
-{a|c|m}+{min|time}	+	{-|+| }n

a	访问
c	文件状态被修改
m	文件内容被修改

min	分钟
time	天

n	举例现在的时间等于n
-n	距离现在的时间小于n
+n	距离现在的时间大于n
```



`find . -name "*.cc" -a -type f`	在当前目录查找名字为*.cc且文件类型是普通文件的文件

`find . -name "*.cc" -a -name "b[a-z]?*.cc"`在当前目录查找*.cc且首字符为b，第二个字符范围为a-z，至少有第三个字符的.cc文件

`find . ! -name "*.cc"`在当前目录查找不为*.cc的文件

`find . -user xxx`在当前目录下查找xxx用户创建的文件

`find . -empty`查找空文件

`find . -perm 664`查找权限为664的文件

`find . -size 1`查找1个block(1block=512B)大小的文件

`find . -size 1c`查找1个字节大小的文件

`find . -mmin -n`	查找n分钟以内文件内容被修改的所有文件	+n表示n分钟以前，n表示正好第n分钟，-n表示n分钟以内

`find . -name "*.cc" -exec ls -l {} \;`	查找所有*.cc的文件并同时执行`ls -l`的操作	注意结尾的分号

`find . -name "*.cc"|xargs ls -l`	查找所有*.cc的文件并分别执行`ls -l`

### 查看磁盘使用情况

`df -h`	查看磁盘情况

`du -h`	显示当前路径下的每个目录使用的磁盘空间

`du -h --max-depth=1`	统计当前路径下的所有一级目录使用的磁盘空间

### 查看文件内容

`cat xxx`		把获取的内容绑定到相应的输出流(比如标准输出(命令行))中

```
`-b`	对非空行编号	优先级高于`-n`

`-E`	每行结束显示一个`$`	用来检查代码是否有无法显示的字符

`-n`	对所有行编号
```

如果cat不加参数，则读入的数据会放入标准输入缓冲区中，按下ctrl+d(相当于文件终止符EOF)表示结束(ctrl+c	表示发送一个终止信号),结束之后会把输入缓冲区的内容输出到输出流中



`head -n 3 main.c`	显示main.c的前3行

`tail -n 3 main.c`	显示main.c的后3行

`more xxx`		`less xxx`		查看文件

### 重定向

每次会打开三个文件描述符0(标准输入)	1(标准输出)	2(错误输出)

`<`	重定向输入		`>` 或`1>`重定向输出		`2>`重定向错误输出

`&>`正常输出和错误输出一起重定向

echo	把相应的内容输出到相应的输出流中，默认带一个换行(默认为标准输出)

`echo abc >file`	把"abc"重定向输出到file中(会覆盖)

`echo abc >>file`把"abc"重定向追加到file中(文件末尾，不会覆盖)

`echo -n >file`产生一个空文件file(且不带换行符)

`./main >file 2>errorfile`将程序的输出结果重定向到file文件中，程序的错误输出结果重定向到errorfile文件中

`cat >newfile <oldfile`把oldfile中的内容输出到newfile中

### 对文件内容进行排序

`sort xxx>yyy`把xxx排序的结果输出到yyy		xxx文件本身没有变化

`sort xxx|uniq >yyy`删除重复行输出	uniq只能删除相邻行的，因此要先排序

`sort xxx|uniq -c`显示每个行出现几次

`sort xxx|uniq -d`仅显示重复行

### 统计文件信息

`wc file`

`ls |wc -l`	统计目录下文件数

`find . -name "*"|wc -l`统计当前目录及子目录下文件总数(还会包括一个当前目录的`.`，因此计算结果需要-1)

### 创建新文件

`touch file`创建一个新的空文件，如果touch一个已存在的文件，则文件内容不会变，只是最后修改时间会变

# day3

## Linux常用命令

### 汉字编码转换

`iconv -f gb2312 -t utf-8 oldfile>newfile`将oldfile的编码从gbk转换为utf-8格式并重定向输出到newfile中

### 搜索文件内容

在文件中查找某一行，常和find | xargs	配合使用

grep	[ 选项]	[查找模式 ]	[单个文件名 ]

```
-F	按字面值查找

-c	显示匹配行的数量

-n	添加行号

-E	拓展正则

-i	 不区分大小写
```

通常默认带-nE

#### 正则表达式

c++11有标准库regex提供对正则表达式的支持	正则表示字符集合的连接情况

A = {a,b,c,d}		B = {1,2}

AB	称为连接，即为a1,b2,c1,d1,a2,b2,c2,d2	笛卡儿积

普通字符：单个字符就是一个集合	a	{a}

通配符：集合	·	{a-z,A-Z,0-9,其他符号}

##### 特殊符号

```
·	=>	{字符的全集}	匹配单个字

[ ]	=>	{范围内字符}	匹配范围内的单个字符

{ }	=>	{子正则表达式}	把子正则表达式的结果看作一个集合
```

^A	=>	A集合的元素在开头的位置

A$	=>	A集合的元素在末尾的位置

用来锚定起始和结尾

如`^i j$`	的模板下	"nijk"不匹配		"inkj"匹配

"\<A"			匹配以A集合的元素开头的单词(即A前面有空白(包括空格、tab的空白等))

" A\>"			匹配以A集合的元素结尾的单词(即A后面有空白(包括空格、tab的空白等))

如`grep "\<name.*e\>"`匹配namespace

```
A?	匹配A集合至多出现一次的情况

A*	匹配A集合出现了任意次数(0-多)的情况

A+	匹配A集合至少出现一次的情况

A{n}	匹配A集合恰好出现n次的情况

A{n,m}	匹配A集合出现了n-m次的情况

A{n,}		匹配A集合至少出现n次的情况

A{,m}		匹配A集合至多出现m次的情况
```

如"bk	bok	book	boook"

在"b?k"的模板下会匹配所有单词，但是只有bk是同时匹配了b和k，其他都认为字符b出现了0次

在"b*k"的模板下和上面的结果相同

如果是"b. *k"则表示.出现了0到多次，会匹配所有单词

在"b.+k"的模板下不会匹配bk

在"b+k"的模板下只会匹配bk

在"bo{1,3}k"的模板下会匹配bok、book、boook

如果匹配的模板中有上述的特殊字符，要么使用-F，要么用"\字符"转义

`grep ^int main.c`查找main.c文件中开头为int的行

`grep ";"$ main.c` 查找main.c文件中以;结尾的行	由于;是脚本分割指令，所以要用";"或者\;转义

`find . -name "*.cc"|xargs grep -n "main()"`	查看哪个文件包含main函数

### 压缩解压缩

tar	参数	目标文件	原文件

```
c	创建新的档案文件

r	把要存档的文件追加到档案文件的末尾

x	从档案文件中释放文件

f	使用档案文件或设备

v	在归档的过程中显示处理的文件

z	用gzip来压缩/解压缩文件，后缀名为.gz
```

`tar czvf file.tar.gz file*`压缩

`tar xzf file.tar`解压缩

### 远程拷贝文件

`scp local_file remote_username@remote_ip:remote_folder `	发送文件

`scp remote_username@remote_ip:remote_file local_folder`	拷贝文件

先用ifconfig查看RX和TX收发包是否有变化，或者ping来看能否ping通

`ctrl+r`搜索以前使用的命令

`ssh test@192.168.2.100`	连接到192.168.2.100的test用户

`scp sendfile test@192.168.2.100:~` 将sendfile发送到192.168.2.100的test用户的~目录下

`scp test@192.168.2.100:~/sendfile ./recvdir`将192.168.2.100的test用户的~目录下的sendfile文件拷贝到本机的./recvdir目录下

### 掩码

`umask xxx`

创建权限时默认会和掩码运算，会把创建的权限中的掩码位为1的位忽略为0，如掩码为002表示other用户没有写权限，以此类推(类似子网掩码)

rw_	rw_	rw_		原权限666

110	110	110		原权限666

000	000	010		掩码002

110	110	100		结果664

rw_	rw_	 r_ _		结果664

# day4

## Linux常用命令

### 配置无密钥登录

每个用户的密钥都存放在~/.ssh/下

`ssh-keygen`	生成钥匙，过程可全部按enter跳过

会生成`id_rsa`(私钥，用来解密)、`id_rsa.pub`(公钥)

公钥可以有很多份，在登录时会用私钥和公钥进行匹配

把公钥放到服务器端的`~/.ssh/authorized_keys`，注意使用>>追加

### 查看路由

route -n

### 批量替换文件内容

`sed`	管道查找替换程序

`sed -i "s/printf/puts/g" *.c`	将所有.c文件的printf改成puts，-i参数表示将改变的结果协会去

`find . -name "*.c"|xargs sed -i "s/puts/printf/g"	`将当前目录和子目录下所有.c的puts换为printf		可以在命令行使用vim命令处理文件

## vim 使用

### vimplus的关闭

在~目录下把软链接的.vimrc改个名字如back_.vimrc，再把原先的vimrc改成.vimrc

### 切换状态

使用

i(从光标之前插入文本)

I(光标所在行的起始位置开始插入，shift+i)

a(从光标之后新增文本)

A(光标所在行的末尾位置开始新增，shift+a)

可以从命令状态进入编辑状态，左下角会显示INSERT

在编辑状态下按ESC会回到命令状态

### vim常用的命令操作

#### 删除与修改

```
x	删除光标处的字符

dd	删除光标所在的整行

[n]dd	删除光标及以下n-1行，共n行

d$	删除到行尾

d^	删除到行首

dw	删除一个单词

d[n]w	删除n个单词

yy	复制光标所在行

[n]yy	复制光标及以下n-1行，共n行

p	将复制后的文本粘贴到光标位置

u	撤销上一步的操作		ctrl+r	反撤销

如果先dd再p则粘贴的是删除的一行
```

#### 光标移动

```
^		移动到行首

$		移动到行尾

ctrl+b		向上翻一页

ctrl+f		向下翻一页

gg			光标定位到文档头

G			光标定位到文档尾

H			光标定位到当前页的页首

L			光标定位到当前页的页尾

w			每次向后一个单词

b			每次向前一个单词

[n]+		向后移动n行

[n]-		向前移动n行

[n]G		直接移动到n行			或者:n
```

#### 查找与替换

支持正则表达式

```
/str	查找str

n	查看下一个匹配字符串（tab）

N	查看上一个匹配字符串

:s/xxx/yyy/i			把光标所在行的第一个xxx换成yyy，忽略大小写

:n,ms/xxx/yyy/		把第n行到第m行的xxx换为yyy，每行只替换第一个

:n,ms/xxx/yyy/g		把第n行到第m行的xxx换为yyy，全部替换(global)

:%s/xxx/yyy/g			把整篇文档的xxx都换成yyy

:%s/^ //				把以空格开头的行去掉一个空格，//为空

:%s/\ <set\ >/SET/g		使用正则表达式，只替换set，而不会替换setxxx等

ctrl+v选中要注释的行，然后I输入//，即可批量注释
```

#### 结束编辑

```
:q		保存退出

:q!		不保存退出

:w		保存

:wq		保存退出

:x		保存退出，和wq一样

:X		加密(x大写)
```

#### 十六进制查看

```
:%!xxd			查看十六进制，vim自动在末尾添加了换行\n(0a)

:%!xxd -r		回归正常
```

#### 块操作

```
v	可视化块选择状态，选中后可以对块进行d(删除)、y(复制)、x(剪切)操作

ctrl+v	竖向选择模式，然后按ctrl+i从多行开头，用hjkl选择需要选择的行，然后I进入编辑模式输入//可以一次注释多行(未成功)
```

#### 窗口切换

```
:new xxx		打开新窗口，横向分割，vnew是纵向的

ctrl w	切换窗口

:vsp xxx	同vnew

ctrl+p 切换标签
```

#### 代码自动对齐

```
gg=G		第一行对齐到最后一行

5gg=G		从第五行开始对齐
```

## Linux下文件编译与调试

gcc	编译器

gdb	调试器

Makefile	工程管理器

过程：预编译(.c->.i)-编译(.i->.s)-汇编(.s->.o)-链接

### 预编译

文本替换

gcc -E test.c -o test.i

### 编译

生成汇编文件

gcc -S test.i -o test.s

### 汇编

将指令和二进制位一一对应

生成二进制文件

as test.s -o test.o

`nm test.o`可以查看程序使用的函数，T为定位了的函数，U为未定位到的函数

### 链接

在* .o 文件处理的时候如果遇到了函数调用(其他文件的函数)，就需要调用其他文件(* .o),可能需要不断的在多个.o文件中跳转

将二进制文件与其他二进制文件组装在一起的过程就成为链接

生成可执行文件

gcc test.o -o test

### 一步到位版

gcc -c test.c -o test.o 		生成test.o

gcc test.c -o test	直接生成可执行文件

### 相关参数

```
-I 目录名：指定头文件的起始路径

-D 宏：开启宏开关 #define 宏 

-Wall：打印所有警告，Linux下的程序要求保证程序不会弹警告
```

#### 调试开关

在程序中加入宏，便于调试

```c
#ifdef DEBUG
	printf("end\n");
#endif
```

正常情况下不会执行DEBUG宏开关中间的语句，如果编译时加上了`-D DEBUG`，则会打开开关，执行其中的语句

### gcc编译优化

-O[n]		编译优化选项

代码优化后可能会对调试造成以外的影响，n的数值越大，程序的风险越大

-O	和-g不能一起使用

### gdb程序调试

gcc -g main.c -o main	gdb 可执行程序

```
l	查看源代码

b 	打断点

r	运行

c	运行到下个断点

n	单步	跳过函数

s	单步	进入函数

tb	临时断点

info b		查看断点信息

delete 断点号		删除断点

ignore [b] n		忽略断点b n次

finish		跳出函数

p a			打印

x /nfu &arr			打印内存n为字节数，f为显示进制类型，u表示每次显示多少字节，如	x /20xb

bt			查看调用堆栈

set/show args xxx	设置/查看命令行参数xxx
```

#### 程序崩溃情况下的调试

```
通过查看core文件，即程序崩溃时的现场，相当于黑匣子

gcc -g crash.c

ulimit -a	查看

ulimit -c unlimited			不限制core文件的大小

gcc -g crash.c

./a.out	崩溃会产生core文件

gdb a.out core	返回现场

主要用bt查看调用堆栈

echo $?	显示上一个进程的返回值，常用于判断程序是否执行成功
```

## 静态库和动态库

操作系统中有两种库，静态库和动态库，当程序编译完成后，在链接阶段如果有函数调用的部分就需要依赖其他的二进制文件，除了.o文件以外就需要用到库

### 相关参数

```
-static 	静态编译(只使用静态库)

-shall	  动态编译(优先使用同名动态库，如果找不到动态库才会去链接静态库)	也可以用于生成动态库文件	默认使用-shall

-l[name]	链接到某个库
```



### 动态库

动态库可以同时被多个进程共享，多个程序共享同一个动态库可以节省磁盘空间

libname.so	在程序编译时不会链接到目标代码中，而是在程序运行时才被载入

ldd filename	查看文件都依赖哪些**动态库**，在什么位置

#### 制作动态库

vim add.c

```c
//不依赖任何其他库，不需要任何头文件
int add(int x,int y){
    return x+y;
}
//因为只提供接口，不能有main函数作为程序入口
```

-fPIC		生成使用相对地址的位置无关的目标代码，即把原先的绝对地址改为以某个地址为基址的偏移地址(相对地址)

-shared	生成动态库文件，进行动态编译，尽可能的链接动态库，只有没有动态库的情况下才会使用同名的静态库，libadd.so 的名字其实是add

`gcc -fPIC -Wall -c add.c`	生成add.o

`gcc -shared add.o -o libadd.so`	生成动态库

`sudo cp libadd.so /usr/lib`把编写好的动态库放入lib目录下

#### 使用动态库

其他程序使用该动态库的函数时需要先声明该函数

```c
int add(int,int);
//...
```

在编译时要加上`-ladd`选项，显式链接libadd.so动态库

nm test.o 查看可以发现add函数此时是U，代表在编译时还没有载入

ldd 可执行文件	可以查看该程序依赖的动态库

如果删除了动态库，则程序无法正常运行

#### 动态库的原理

main函数里只填写了预留的使用的动态库的函数的入口地址，只有在执行的时候才把相关函数加载到进程的内存空间的代码段中

#### 使用软链接修改动态库的依赖

动态库需要频繁升级，因此可以使用软链接的方式使得不用每次程序升级都要修改动态库的依赖

##### 制作一个软链接

mv libadd.so libadd.so.1	如果提升了动态库的版本

ln -s libadd.so.1 libadd.so	让libadd.so 指向 libadd.so.1

将软链接libadd.so放入/usr/lib下

libadd.so软链接中存放的就是libadd.so.1的路径。ls -lh查看文件前缀是l

以后每次新版本的动态库更新后都重新做一个软链接libadd.so指向新的动态库即可

### 静态库

libname.a	如果在编译某个程序时链接静态库，则链接器会搜索静态库并直接拷贝到该程序的可执行二进制文件到当前文件中

#### 制作静态库

首先生成二进制文件gcc add.c -c	=>add.o

ar crsv libadd.a add.o	对add.o进行归档，生成libadd.a

将静态库libadd.a 拷贝到/usr/lib下

#### 使用静态库

gcc -o main main.c -ladd	链接静态库libadd.a

#### 静态库的原理

在程序编译时就把静态库的函数拷贝一份到可执行程序中，因此编译成功后就不再依赖静态库了

### 动态库和静态库的区别

动态库在执行时才会被调用，链接时只提供了函数的入口地址，因此配置麻烦，但是容易升级

静态库在链接时就被拷贝到了可执行文件中，在执行时就不再需要静态库的存在了，因此易于部署，对环境的依赖较低，但是需要占据更多的空间，并且难以升级

因此，如果是静态库的函数发生了改变，就需要重新链接生成，而如果是动态库的函数发生了改变，则只需要替换动态库，不需要重新链接生成可执行文件



## Makefile 工程管理器

从目标文件出发，递归的查找依赖文件，根据不同的**规则**依次执行

makefile就是把这些规则，从上到下写出来，最终获得的结果都是可执行文件，可执行文件依赖于未链接的二进制文件.o，而.o文件又依赖于.c源文件和.h头文件

格式如下：

```
目标:依赖			(多个依赖以空格隔开)
[tab]命令1
[tab]命令2
```

如：

```makefile
main:main.o func.o
	gcc main.o func.o -o main
main.o:main.c		# 规则一
	gcc -c main.c -o main.o
func.o:func.c		# 规则二
	gcc -c func.c -o func.o
```

### 伪目标.PHONY

伪目标不是目标文件也不是中间依赖文件

仅仅是利用规则，来执行一些命令，如清理产生的中间文件等

伪目标可能有0~多个中间依赖目标，而伪目标的规则是些可能不生成文件的命令

```makefile
main:main.o func.o
.PHONY:clean rebuild
clean:
	rm -rf main.o func.o main
	
rebuild:clean main			# 先执行依赖一的clean清除再执行依赖二的main生成
```

### 写一个比较通用的makefile文件

上述的Makefile 文件都依赖于具体的文件名，如果有很多个文件，一个一个编写就很麻烦，因此就需要编写一个比较通用的Makefile文件

#### 变量

自定义变量、预定义变量、自动变量

变量的定义：

:=(简单变量展开)	和	=	递归变量展开(不常用)

##### 预定义变量：

CC:=gcc			#以何种方式编译
CFLAGS:=-g -Wall -l[库名]		# 编译的选项

##### 自动变量

$@		在规则的命令部分生效，代表当前规则下的目标

$^		在规则的命令部分生效，代表当前规则下的依赖

```makefile
CC:=gcc
CFLAGS:=-g -Wall
OUT:=main
OBJS:=main.o func.o
$(OUT):$(OBJS)
	$(CC) $^ -o $@
main.o:main.c
	$(CC) -c $^ -o $@
func.o:func.c
	$(CC) -c $^ -o $@
```

#### 模式匹配

把一个句子切成若干单词

单词+空格+单词	main.o func.o

用%.o	匹配上所有的.o文件，此时的%就等价于main	func	



```makefile
CC:=gcc
CFLAGS:=-g -Wall
OUT:=main
OBJS:=main.o func.o
$(OUT):$(OBJS)
	$(CC) $^ -o $@
%.o:%.c		# 模式匹配
	$(CC) -c $^ -o $@
```

#### 内置函数

$(函数名 参数)

wildcard 搜索当前目录下的文件名

```makefile
$(wildcard 通配符表达式)	#在makefile文件所在的目录进行文件的查找/筛选，构造成一个以空格隔开的字符串
$(wildcard *.c)		#把当前目录下的所有.c文件都筛选出来
```

patsubst 字符串替换函数pattern substitute

SRCS:%.c=%.o		把SRCS里的所有.c都替换为.o	SRCS是待处理文本

```makefile
$(patsubst pattern,replacement,text)	#匹配模板，替换，待处理文本(字符串)	text->pattern->replacement
$(text:pattern=replacement)	#等价写法
$(patsubst %.c,%.o,func.c main.c)	#把字符串"func.c main.c"按照pattern"%.c"匹配后切分成func.c和main.c，最后变为替换的"%.o"即main.o 和func.o
```

```makefile
CC:=gcc
CFLAGS:=-g -Wall
OUT:=main
SRCS:=$(wildcard src/*.c)
OBJS:=$(patsubst %.c,%.o,$(SRCS))
$(OUT):$(OBJS)
	$(CC) $^ -o $@
%.o:%.c		# 模式匹配
	$(CC) -c $^ -o $@
```

#### %和*

*从文件系统匹配

%对字符串中的单个单词匹配

### 同时编译出多个可执行二进制

$<	当前规则的第一个依赖文件

%.o: %.c		任何目标文件的依赖文件是与目标文件同名的并且扩展名为.c的文件

for循环会自动把字符串按空格切分

```makefile
@for i in $(TARGETS);do gcc -o $$(i) $$(i).c;done
```

另一种方式

```makefile
SRCS:=$(wildcard *.c)
ELFS:=$(SRCS:%.c=%)
CC:=gcc
all:${ELFS}

%:%.c #类似循环
	${CC} $< -o $@
.PHONY:clean
clean:
	rm -rf $(ELFS)
```

如果不确定某个变量的值，可以使用

```
print:
	echo ${xxx}
```

输入make print	查看xxx变量的值

# day6

## Linux 输入输出与文件

文件分为普通文件，目录文件，链接文件和设备文件

主要是前三项和管道

### 文件的打开与关闭



```c
#include <stdio.h> //头文件包含
FILE *fopen(const char *path,const char *mode); //文件名 模式
int fclose(FILE *stream);
```

fopen 以mode的方式打开或创建文件，创建的文件的访问权限将以0666 和当前的umask结合来确定

![image-20200806164407830](D:\TyporaPic\复习笔记Linux\image-20200806164407830.png)

![image-20200806164422348](D:\TyporaPic\复习笔记Linux\image-20200806164422348.png)

以ab和ab+打开的文件，读取的时候光标还是在开头，而执行写操作的时候光标会优先偏移到文件尾，写之后再读取光标就是在文件尾了

#### fopen的a模式

第一次读的时候还是正常从头开始读，但是第一次写时会把ptr指针直接移到文件末尾，而不是读到的位置，可以防止写坏数据

### 读写文件

```cpp
#include <stdio.h>
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
size_t fwrite(void *ptr, size_t size, size_t nmemb, FILE *stream);
```

fread 从文件流 stream 中读取 nmemb 个元素，写到 ptr 指向的内存中，每个元素的大小为 size 个字节。

fwrite 从 ptr 指向的内存中读取 nmemb 个元素，写到文件流 stream 中，每个元素 size 个字节。

所有的文件读写函数都从文件的当前读写点开始读写，读写完以后，当前读写点自动往后移动size*nmemb 个字节。

整块 copy，速度较快，但是是二进制操作

#### 格式化读写

fprintf 将格式化后的字符串写入到文件流 stream 中

sprintf 将格式化后的字符串写入到字符串 str 中

```c
#include <stdio.h>
int printf(const char *format, ...); //相当于
fprintf(stdout,format,…);
int scanf(const char *format, …);
int fprintf(FILE *stream, const char *format, ...); 重点
int fscanf(FILE *stream, const char *format, …);
int sprintf(char *str, const char *format, ...); // eg: 
sprintf(buf,”the string is;%s”,str); 重点
int sscanf(char *str, const char *format, …); 重点

```

#### 单个字符读写

getchar 和 putchar 从标准输入输出流中读写数据，其他函数从文件流 stream中读写数据。

```c
#include <stdio.h>
int fgetc(FILE *stream);
int fputc(int c, FILE *stream);
int getc(FILE *stream); ➔ 等同于 fgetc(FILE* stream)
int putc(int c, FILE *stream); ➔ 等同于 fputc(int c, FILE* stream)
int getchar(void); ➔ 等同于 fgetc(stdin);
int putchar(int c); ➔ 等同于 fputc(int c, stdout);
```

#### 字符串读写

fgets 和 fputs 从文件流 stream 中读写一行数据;

puts 和 gets 从标准输入输出流中读写一行数据。

fgets 可以指定目标缓冲区的大小，所以相对于 gets 安全，但是 fgets 调用时，如果文件中当前行的字符个数大于 size，则下一次 fgets 调用时，将继续读取该行剩下的字符,fgets 读取一行字符时，保留行尾的换行符。

fputs 不会在行尾自动添加换行符，但是 puts 会在标准输出流中自动添加一换行符。

```c
char *fgets(char *s, int size, FILE *stream);
int fputs(const char *s, FILE *stream);
int puts(const char *s); ➔ 等同于 fputs(const char *s,stdout);
char *gets(char *s); ➔ 等同于 fgets(const char *s, int size, 
stdin);
```

```c
int main(int args,char *argv){
    ARGS_CHECK(args,2);
    FILE *fp;
    fp=fopen(argv[1],"rb+");//打开文件
    ERROR_CHECK(fp,NULL,"fopen");
    char buf[128]={0};
    fread(buf,sizeof(char),5,fp);//只读5个字符
    const char *p="how are you";
    fwrite(p,sizeof(char),strlen(p),fp);
    fclose(fp);
    return 0;
}
```

### 文件定位

文件定位指读取或设置文件当前读写点，所有的通过文件指针读写数据的函数，都是从文件的当前读写点读写数据的。

```c
#include <stdio.h>
int feof(FILE * stream); //通常的用法为 while(!feof(fp))
int fseek(FILE *stream, long offset, int whence);//设置当前读写点到偏移whence 长度为 offset 处
long ftell(FILE *stream); //用来获得文件流当前的读写位置
void rewind(FILE *stream); //把文件流的读写位置移至文件开头➔fseek(fp, 0, SEEK_SET);


int ret;
ret=ftell(fp);//返回距离文件头的长度
printf("ptr pos =%d\n",ret);
```

feof 判断是否到达文件末尾的下一个（注意到达文件末尾之后还会做一次）

fseek 设置当前读写点到偏移 whence 长度为 offset 处，whence 可以是：

```
SEEK_SET (文件开头 →0)
SEEK_CUR (文件当前位置 →1)
SEEK_END (文件末尾 →2)
```

ftell 获取当前的读写点，只会为非负值

rewind 将文件当前读写点移动到文件头

## 目录操作

### 改变目录或文件的访问权限

```c
#include<sys/stat.h>

int chmod(const char *path,mode_t mode);	//mode形如：0777,0表示八进制	path参数指定的文件被修改为具有mode参数给出的访问权限


int ret;
ret=chmod(argv[1],0777);
ERROR_CHECK(ret,-1,"chmod");
```

成功返回0，失败返回-1

### 获取、改变当前目录

```c
#include<unistd.h>

char *getcwd(char *pwd,size_t size);//获取当前目录，返回值是在在堆空间中申请的，防止预设的字符数组长度不够

int chdir(const char *path);//切换目录,相当于cd命令


int ret;
ret=chdir("/tmp");
ERROR_CHECK(ret,-1,"chdir");
printf("current path=%s\n",getcwd(NULL,0));
```

这里改变的只是子进程(当前执行的程序)的工作路径，父进程的工作路径不会变

父进程bash shell $ ./a.out	->	新开一个子进程处理 ./a.out

# day7

## 目录操作

### 目录的存储原理

存储在磁盘中，目录中实际上存放的是文件信息结构体连成的链表

每个结构体dirent：

```
ino_t d_ino				唯一的磁盘块编号(地址)
off_t d_off				从当前结点到下个结点的偏移量，相当于next指针，用于维护链表
unsigned short d_reclen		本结构体的长度
unsigned char d_type		文件的类型(0-15)
char d_name[256]			文件的名字
```

opendir 返回的是整个链表(DIR类型，即目录流，打开的目录)，因为目录的内部不一定是连续的，因此要使用readdir依次读取每个dirent结点

DIR类型有一个专门的指针用于定位下一次要读取哪个结点

因为是流，所以一般情况下是从前向后移动的

### 创建和删除目录

创建好的目录仍然受掩码umask的影响，就算是0777结果也还是775

```c
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
int mkdir(const char *pathname, mode_t mode); //创建目录,mode 是目录权限
int rmdir(const char *pathname); //删除目录

int ret;
ret=mkdir(argc[1],0777);
ERROR_CHECK(ret,-1,"mkdir");
ret=rmdir(argc[1]);//只能删除空目录
ERROR_CHECK(ret,-1,"rmdir");
```

echo $PATH	查看环境变量

export PATH=$PATH:/home/xxx/yyy/可执行文件名		修改环境变量,只对当前窗口生效，下次执行就不再生效了，如果要永久有效就要修改.bashrc

也可以都放在/usr/bin/下

### 获取目录信息

opendir()用来打开参数 name 指定的目录，并返回 DIR*形态的目录流，和文件操作函数 open()类似，接下来对目录的读取和搜索都要使用此返回值。函数失败则返回 NULL；

readdir()函数用来读取目录的信息，并返回一个dirent结构体指针，该指针保存了目录的相关信息。有错误发生或者读取到目录文件尾则返回 NULL

```c
#include <sys/types.h>
#include <dirent.h>
DIR *opendir(const char *name); //打开一个目录
struct dirent *readdir(DIR *dir); //读取目录的一项信息，并返回该项信息的结构体指针，每次自动偏移到下一个进入点，最后返回NULL
int closedir(DIR *dir); //关闭目录文件


DIR *dir;
dir=opendir(argv[1]);
ERROR_CHECK(dir,NULL,"opendir");
struct dirent *p;
p=readdir(dir);
while((p=readdir(dir))){
	printf("ino=%ld len=%d type=%d filename=%s\n",p->d_ino,p->d_reclen,p->d_type,p->d_name);
}
closedir(dir);
```

type=4	代表目录

type=8	代表文件

目录的长度默认为24字节，文件的长度默认为32字节，冗余设置，使得删除后可以再继续利用这片空间

ls -ial	可以查看文件的inode

#### inode

inode的值唯一对应磁盘上的一份数据

对应inode的映射磁盘块，分配给别人

硬链接	2为引用计数   即磁盘上有2个文件的文件名指向磁盘上的这份数据

目录的硬链接数-2就是目录下的子目录数量，一个是他自己的 ，还有一个是目录本身

ln xxx yyy	构建硬链接

ln -s yyy link	构建软链接

构建硬链接就相当于构建了多个入口进入同一份数据，即使删除了其中一个硬链接，其他链接仍可以进入，而软链接不行

#### struct dirent 包含的成员

```c
struct dirent
{
    ino_t d_ino; /* inode number（此目录进入点的 inode,磁盘上唯一对应一份数据，类型是long int） */
    off_t d_off; /* offset to the next dirent（目录开头到进入点的位移 */
    unsigned short d_reclen; /* length of this record（目录名的长度） */
    unsigned char d_type; /* type of file（所指的文件类型0-15） */
    char d_name[256]; /* filename（文件名） */
};
```

#### 读取目录信息的步骤

```
用 opendir 函数打开目录；

使用 readdir 函数迭代读取目录的内容，如果已经读取到目录末尾，又想重新开始读，则可以使用 rewinddir 函数将文件指针重新定位到目录文件的起始位置；

用 closedir 函数关闭目录
```

#### 目录的深度优先遍历

递归操作

```c
int printDir(char *path,int width){//width为打印时距离屏幕左侧的宽度
    DIR *dir=operdir(path);//1、打开目录
    ERROR_CHECK(dir,NULL,"operndir");
    char buf[1024]={0};
    struct dirent *p;
    p=readdir(dir);//2、循环读取目录
    while((p=readdir(dir))){
        //2.1 .和..不能继续递归
        if(strcmp(p->d_name,".")==0||strcmp(p->d_name,"..")==0){
            continue;
        }
        //2.2 打印信息，%*s打印width个空格
        printf("%*s%s\n",width,"",p->d_name);
        sprintf(buf,"%s%s%s",path,"/",p->d_name);//2.3 拼接当前路径，形参的路径必须是相对于当前执行进程的路径，因此要用buf拼接
        if(p->d_type==4){//2.4 如果当前文件是目录，则递归调用
            printDir(buf,width+4);
        }
        printf("ino=%ld len=%d type=%d filename=%s\n",p->d_ino,p->d_reclen,p->d_type,p->d_name);
    }
    closedir(dir);//3、关闭目录
    return 0;
}
```

### 目录的偏移

seekdir()函数用来设置目录流目前的读取位置，再调用 readdir()函数时，便可以从此新位置开始读取。参数 offset 代表距离目录文件开头的偏移量。

telldir()函数用来返回目录流当前的读取位置。

```c
#include <sys/types.h>
#include <dirent.h>
void rewinddir(DIR *dir); //重新定位到目录文件的头部
void seekdir(DIR *dir,off_t offset);//用来设置目录流目前的读取位置
off_t telldir(DIR *dir); //返回目录流当前的读取位置
```

```c
void test(char *str){
	DIR *dir=opendir(str);//1、打开目录
    ERROR_CHECK(dir,NULL,"opendir");
    struct dirent *p=readdir(dir);//2、循环读取目录
    off_t pos;
    while((p=readdir(dir))){
        if(strcmp(p->d_name,"a.out")){
            pos=telldir(dir);//定位到a.out处
        }
    }
    seekdir(dir,pos);//把目录流的读取位置重新定位到a.out处
    //rewinddir(dir);//重新设定目录流的读取位置到文件开头
    printf("ino=%ld len=%d type=%d filename=%s\n",p->d_ino,p->d_reclen,p->d_type,p->d_name);
    closedir(dir);//3、关闭目录
}
```

## 基于文件描述符的文件操作

### 文件描述符

内存中有一个区域是内核映射的区域

内核为每个进程维护了一个已打开文件的记录表，文件描述符代表该表的一项，其中该表的0，1，2位分别为标准输入、标准输出、标准错误输出，因此其他文件的文件描述符从3开始

通过文件描述符和一组基于文件描述符的文件操作函数，可以对文件进行读、写、创建、删除等操作

常用基于文件描述符的函数有 **open（打开）**、creat（创建）、**close（关闭）、read（读取）、write（写入）**、ftruncate（改变文件大小）、lseek（定位）、fsync（同步）、fstat（获取文件状态）、fchmod（权限）、flock（加锁）、fcntl（控制文件属性）、dup（复制）、dup2、**select** 和 ioctl。

superblock 超级块

dirent<->inode->文件内容		这三种属于在磁盘中存储的信息，而文件描述符是在内存中的文件对象，动态的对打开的文件的描述，每次读完以后能知道去哪里加载下一块到内存中

### 打开、创建和关闭文件



```c
#include <sys/types.h> //头文件
#include <sys/stat.h>
#include <fcntl.h>
int open(const char *pathname, int flags); //文件名 打开方式
int open(const char *pathname, int flags, mode_t mode);//文件名 打开方式 权限
int creat(const char *pathname, mode_t mode); //文件名 权限 //现在已经不常用了
creat 函数等价➔open(pathname,O_CREAT|O_TRUNC|O_WRONLY,mode);
int close(int fd);//fd 表示文件描述词,是先前由 open 或 creat 创建文件时的返回值。

int fd=open(filename,O_RDWR);
ERROR_CHECK(fd,-1,"open");
int fd=open(filename,O_RDWR|O_CREATE,0666);
```

flags的可选参数有：(某一位为真，可以按位异或复合使用)

```c
O_RDONLY		只读
O_WRONLY		只写
O_RDWR			读写(常用)
O_CREAT			若文件不存在，则创建文件
O_EXCL			仅和O_CREAT连用，如果文件已存在，则会强制open失败，常用于防止自动生成日志时按时间顺序生成，但是生成的日志超过规定大小又生成了一份同名的日志。
O_TRUNC			如果文件已存在，则直接清空
O_APPEND		以追加形式打开文件(ab+模式打开文件)
O_NONBLOCK		非阻塞方式打开，无论那有无数据读取或等待，都会立即返回进程
O_NODELAY		非阻塞方式打开
O_SYNC			同步打开文件，只有数据被真正写入物理设备后才返回
```

LINUX 中基于文件描述符的 open 函数，对于一个不存在的文件，不能通过 O_WRONLY 的方式打开，必须加上 O_CREAT 选项。

mode参数常直接写数字表示法的权限，如0755、0664等

文件使用完毕后，应该调用 close 关闭它，一旦调用 close，则该进程对文件所加的锁全都被释放，并且使文件的打开引用计数减 1，只有文件的打开引用计数变为 0 以后，文件才会被真正的关闭。

### 读写文件

对于 read 和 write 函数，出错返回-1，读取完了之后，返回 0， 其他情况返回当前次读写成功的字符的个数。

```c
#include <unistd.h>
ssize_t read(int fd, void *buf, size_t count);//文件描述符 缓冲区 长度
ssize_t write(int fd, const void *buf, size_t count);

int fd=open(filename,O_RDWR);
ERROR_CHECK(fd,-1,"open");
char buf[1024]={0};
int ret=read(fd,buf,strlen(buf));//返回读取的字节数
char *str="helloworld";
ret=write(fd,str,strlen(str));//返回写入的字节数
```

read不会自动加\0

### 改变文件大小

本质就是填0

```c
#include <unistd.h>
int ftruncate(int fd, off_t length);

int fd=open(filename,O_RDWR);
int ret=ftruncate(fd,50);//将fd指定的文件大小改为50字节
ERROR_CHECK(ret,-1,"ftruncate");
```

函数 ftruncate 会将参数 fd 指定的文件大小改为参数 length 指定的大小。参数 fd 为已打开的文件描述词，而且必须是以写入模式打开的文件。如果原来的文件大小比参数 length 大，则超过的部分会被删去。

返回值 执行成功则返回 0，失败返回-1。

必须要给文件写权限才能使用

先变小后变回去，原先的数据还可以读出来

常配合mmap使用，因为要完美映射就需要先用ftruncate扩大文件



# day 8

## 基于文件描述符的文件操作

### 文件定位

```c
#include <sys/types.h>
#include <unistd.h>
off_t lseek(int fd, off_t offset, int whence);//fd 文件描述词
/*
SEEK_SET		文件头
SEEK_CUR		当前指针
SEEK_END		文件尾
*/

int ret=lseek(fd,5,SEEK_SET);//从起始位置向后偏移5字节
```

lseek相当于fseek和ftell的组合成功返回非负，失败返回-1

对于fseek，成功返回0，失败返回-1

利用该函数可以实现文件空洞（对一个新建的空文件，可以定位到偏移文件开头 1024 个字节的地方，在写入一个字符，则相当于给该文件分配了 1025 个字节的空间，形成文件空洞）通常用于多进程间通信的时候的共享内存。

```c
int ret=lseek(fd,1024,SEEK_SET);//从起始位置向后偏移1024个字节,中间用0填充1024个字节
char *buf="helloworld";
write(fd,buf,strlen(buf));//在1025字节的位置开始填充buf字符串
```

### mmap

申请的是堆空间，把磁盘的信息映射到堆空间中

不需要读写就可以改变文件内容

磁盘内存映射，充分发挥内存和磁盘间交换数据(DMA，direct memory access)直接内存存取，不经过CPU的中断，直接把某块磁盘的内容放到某块内存中

DMA的效果：直接从磁盘读取数据到内存

读写磁盘其实还要经过磁盘缓冲区



多进程的情况下，把所有进程的地址空间(虚拟内存)全部放入内存是不可能的(每个都有4g大，多个进程的话太大了)，因此每次只把当时正需要使用的地址空间(虚拟内存的一部分)放入内存，把不需要的内容(剩余部分)放到磁盘里，此时就需要把内存和磁盘进行映射，因为下次可能还要用这些。

由于磁盘的读取速度很慢，而每次传输量又很大，为了加快效率和保护磁盘，就需要对虚拟内存进行分页，每次传输一页的内容，内存和磁盘的映射也是以页为基本单位的。

多进程可以使用映射来通信





#### 映射

文件一旦被映射后，调用mmap()的进程对返回地址的访问是对某一内存区域的访问，暂时脱离了磁盘上文件的影响。所有对mmap()返回地址空间的操作只在内存中有意义，只有在调用了munmap()后或者msync()时，才把内存中的相应内容写回磁盘文件，所写内容仍然不能超过文件的大小。

```c
#include<sys/mman.h>
void *mmap(void *addr,size_t length,int prot,int flags,int fd,off_t offset);	
```

成功返回起始地址，失败返回-1

void *addr映射到内存中的起始地址

size_t length 文件大小(stat获取)，实际上按照块即4k的整数倍加载进内存

prot权限(PROT_EXEC\READ\WRITE\NONE)权限要大于等于open的权限

flag权限MAP_SHARED  共享的、MAP_PRIVATE  私有的、MAP_ANONYMOUS 匿名映射 (将内存映射到虚拟地址。fd和offset设置成0)

fd	使用的普通文件进行映射的文件描述符，可以设置为

off_t offset		如果只想映射一部分，不能直接lseek，而要用offset这个参数，必须是4k的整数倍，sysconf(_SC_PAGE_SIZE);即页大小



如果映射的文件内容是"helloworld"，虽然mmap时指定了5字节，但是其实读入了4k(一个物理页的大小)，因此打印还是可以看到helloworld的而不是hello

#### 解除映射

```c
size_t munmap(void *addr,size_t length);
```

addr	接触映射的起始地址

length	解除的大小

可以多次解除映射，如多个线程同时读取一个文件，如果都用read会效率较低，因此可以用共享(MAP_SHARED)的方式读取到内存中，各线程从内存中分批读取，如果只想用后面部分的数据，则可以用munmap解除前面的映射，length的大小也要是4k的整数倍

```c
void test(char *filename){
    int fd=open(filename,O_RDWR);
    void *p=mmap(NULL,10,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    char *str=(char *)p;
    str[1]='A';//在内存中修改，还没有同步到磁盘的文件
    munmap(p,10);//此时才会把内容写回磁盘，不能超过文件大小
    close(fd);
}
```

如果映射了一个空文件，会报Bus error 总线异常，因为原先文件大小为0，解除映射时DMA找不到写入的block的位置，也就无法写入how

### 获取文件状态

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
int stat(const char *pathname, struct stat *buf); //获取文件状态
int fstat(int fd,struct stat *buf);		//文件描述符，stat结构体指针
```

结构体 stat 的定义为：

```c
struct stat {
    dev_t st_dev; /*如果是设备，返回设备表述符，否则为 0*/
    ino_t st_ino; /* i 节点号inode，把stat和inode关联起来 */
    mode_t st_mode; /* 文件类型 底9位*/
    nlink_t st_nlink; /* 链接数 */
    uid_t st_uid; /* 属主 ID */
    gid_t st_gid; /* 组 ID */
    dev_t st_rdev; /* 设备类型*/
    off_t st_size; /* 文件大小，字节表示 */
    blksize_t st_blksize; /* 块大小*/
    blkcnt_t st_blocks; /* 块数 */
    time_t st_atime; /* 最后访问时间，存储的是秒数，因为只占4个字节节省空间，可以通过ctime转换*/
    time_t st_mtime; /* 最后修改时间*/
    time_t st_ctime; /* 最后权限修改时间 */
};
```

对于mode_t st_mode，可以用下面的宏进行判断

```c
S_ISLNK(mode) 				判断是否是符号链接
S_ISREG(mode) 				判断是否是普通文件
S_ISDIR(mode) 				判断是否是目录
S_ISCHR(mode) 				判断是否是字符型设备
S_ISBLK(mode) 				判断是否是块设备
S_ISFIFO(mode) 				判断是否是命名管道
S_ISSOCK(mode) 				判断是否是套接字

如
if(S_ISDIR(st.st_mode)){
	//...
}
```

```c
void test(char *file){
    struct stat buf;
    int ret=stat(file,&buf);
    ERROR_CHECK(ret,-1,"stat");
    printf("%x %ld %d %d %ld %s ",buf.st_mode,buf.st_nlink,buf.st_uid,buf.st_gid,buf.st_size,ctime(&buf.st_mtime));//模仿ls -l输出效果
}
```

输出不同格式的时间

```c
time_t tt=buf.st_atime;
struct tm *pT = gmtime(&tt);
printf("%4d-%02d-%02d %02d:%02d:%02d\n", (1900+pT->tm_year), (1+pT->tm_mon), pT->tm_mday, (8+pT->tm_hour), pT->tm_min, pT->tm_sec);
```

#### 为什么不能把文件的信息直接放在 dirent结构中，而是要再用stat结构呢

文件对象除了内核缓冲区以外还有一个文件指针，指向inode，inode存放了磁盘信息，从磁盘读取存放的内核内存

使用stat访问的就是文件对象的指向inode的指针，再通过这个指针访问inode

dirent是DIR的链表的一个结点，本质还是目录的一项索引，主要是用来从目录找到文件的，因此**目录应当尽可能的小而精**，索引和内容分开存储，文件的主要内容还是放在inode中

### 文件描述符和文件指针

磁盘里的数据为文件，程序都是加载到内存中运行，正在运行的程序称为进程，每个进程都有一个地址空间，每个地址空间的值都是地址值，即虚拟内存(逻辑上的)，不是真正的物理内存

地址空间从上到下分为内核区(OS)、栈、共享库(运行时的动态库)、堆、数据段、代码段、文本段等

操作系统会把需要用的数据信息从磁盘中拷贝到一个硬件设备上，即数据缓冲区，该缓冲区有三个指针，base、end和ptr

该数据缓冲区又会被抽象为一个文件对象，散布在内核中，由于地址不易操作，因此还会额外维护一个数组(文件描述符表)用于存放这些文件对象的地址，数组的下标(索引)就是文件描述符

使用文件描述符时需要从用户态转为内核态，如果频繁I/O会导致大量时间花费在切换状态上：

用户态(安全，cpu主要运行)	-"陷入"(消耗时间)>	内核态(功能比较多)

为了节省时间，第一次使用某个文件描述符时，就在用户态找一片空间(用户态缓冲区)，把用到的文件描述符指向的对象从内核态拷贝到用户态中，以后再使用这个文件描述符就直接用用户态的拷贝了，这样就可以减少"陷入的次数"

标准库的FILE *fp(即文件指针)就是指向用户态缓冲区的文件的，而内核中的fd(文件描述符)属于unix系统编程

#### 文件指针->文件描述符

```c
int fileno(FILE *stream);

FILE *fp;
fp=fopen(argv[1],"rb+");
ERROR_CHECK(fp,NULL,"fopen");
int fd=fileno(fp);
printf("fd=%d\n",fd);
char buf[128]={0};
read(fd,buf,sizeof(buf));
fclose(fp);
```

#### 文件描述符->文件指针

```c
FILE *fdopen(int fd,const char *mode);

int fd=open(argv[1],O_RDWR);
ERROR_CHECK(fd,-1,"open");
FILE *fp=fdopen(fd,"rb+");
ERROR_CHECK(fp,NULL,"fdopen");
char buf[128]={0};
//close(fd);//如果在使用fp前关闭了fd，则无法进行读写操作了Bad file descriptor文件描述符异常,如果先关闭fp，则不会影响fd的使用
char *p = fgets(buf,sizeof(buf),fp);
ERROR_CHECK(p,NULL,"fgets");
printf("buf=%s\n",buf);
fclose(fp);
```

#### fopen和open的区别

open：内核中的文件描述符指向了一个文件对象，指向了一个文件缓冲区，内核是kalloc和kfree申请和释放空间

fopen：额外在用户态空间(栈、堆)开辟了一个缓冲区，缓冲区内容就是内核的那个指向的缓冲区，因为read和write的系统调用的耗时比较长，因此为了降低系统调用的次数才额外开辟了缓冲区，本质操作就是先对用户态空间的缓冲区进行读写，因此如果每次只用read读取1个字节是非常低效率的，读取4k字节才会比较高效，降低系统调用的使用次数

### 文件描述符的复制

系 统 调 用 函 数 dup 和 dup2 可 以 实 现 文 件 描 述 符 的 复 制 ， 经 常 用 来 重 定 向 进 程 的stdin(0),stdout(1),stderr(2)。

#### dup

管理内核中的文件对象要用到文件描述符表，dup就是对这个数组的元素进行替换，让最小可用文件描述符，管理和oldfd同样的文件对象

dup 返回新的文件描述符（没有使用的文件描述符的最小编号）。这个新的描述符是旧文件描述符的拷贝。这意味着两个描述符共享同一个数据结构。

在程序开始执行时，就已经有0(标准输入stdin)、1(标准输出stdout)、2(标准错误输出stderr)被放入数组，使用dup就会找当前文件描述符表的下标最小的未被使用的空间，把这个元素也指向dup的参数(oldfd)指向的文件对象，如int fd=dup(1);此时fd值为3，但是本质是和1一样控制标准输出

如果有一个文件描述符使用lseek进行了偏移，则两个文件描述符会一起偏移，因为偏移的是文件对象的pstr指针，而两个描述符共享同一个指针，并不是各自拷贝一份pstr

```c
#include <unistd.h> 
int dup(int oldfd);
```

```c
int fd=open(filename,O_RDWR);
int fd1=fd;//文件描述符的赋值
close(fd);
char *buf="hello";
write(fd1,buf,strlen(buf));//error，两个文件描述符变量的值相同，指向同一个打开的文件，但是内核的文件打开引用计数还是为 1，所以 close(fd)或者 close(fd1)都会导致文件立即关闭掉。
close(fd1);//无意义
```

```c
int fd=open(filename,O_RDWR);
int fd1=dup(fd);//内核的引用计数+1=2
close(fd);//引用计数-1=1
char *buf="hello";
write(fd1,buf,strlen(buf));
close(fd1);//引用计数-1=0，文件真正被关闭
```

##### 重定向文件描述符

由于dup会自动选择值最小的未被使用的文件描述符作为新的复制

而printf等价于fprintf(stdout,......)即write(1,......)，本质调用了write接口，借助这个特性可以将0、1、2号文件描述符作重定向操作

```c
void test(char *savefile){
    int fd,fd1;
    fd=open(savefile,O_RDWR);
    printf("\n");//刷新输出缓冲区，原因是文件是全缓冲的，而屏幕本身是不缓冲
    close(1);
    fd1=dup(fd);//fd1的文件描述符为1标准输出
    printf("fd1=%d\n",fd1);//输出到了savefile中而不是控制台
    close(fd);//这里如果先关闭的是fd1，则不会有下面的打印了，因为被重定向的fd1被关闭，而原本的fd文件描述符还是3，不会接收到printf的内容
    printf("fd1=%d\n",fd1);
    close(fd1);
}
```

#### dup2

dup2 允许调用者用一个有效描述符(oldfd)和目标描述符(newfd)，函数成功返回时，目标描述符将变成旧描述符的复制品，此时两个文件描述符现在都指向同一个文件，并且是函数第一个参数（也就是oldfd）指向的文件。

```c
#include <unistd.h> 
int dup2(int oldfd,int newfd);
```

如果成功 dup2 的返回值于fdnew 相同,否则为-1

dup2也是进行描述符的复制，只不过采用此种复制，新的描述符由用户用参数 fdnew 显示指定，而不是象 dup 一样由内核帮你选定（内核选定的是随机的）。对于 dup2，如 果 fdnew 已经指向一个已经打开的文件，内核会**首先关闭掉 fdnew 所指向的原来的文件**。此时再针对于 fdnew 文件描述符操作的文件，则采用的是 fdold 的文件描述符。

```c
void test(char *filename){
	int fd,fd1;
    fd=open(filename,O_RDWR);
    printf("1\n");
    dup2(1,100);//将标准输出拷贝到其他未用过的文件描述符上
    fd1=dup2(fd,1);//先关闭1原本的指向，再复制一份fd指向的给1，最后赋值给fd1，此时fd1=1，fd=3
    printf("fd=%d,fd1=%d\n",fd,fd1);
    dup2(100,1);//重新拷贝回来
    printf("2\n");
}
```

## 实现聊天对话

使用两条管道

### 有名管道(FIFO)

先进先出	半双工

mkfifo	xxx.fifo	也是一种文件

不能同时写读，每次至多一个进程写或读，不能多个进程同时用一个管道写和读

空不可读，满不可写

只写不读：填满管道，写阻塞	

只读不写：读空管道，读阻塞

阻塞：等待I/O，如scanf、printf、read、write等

### 写事件

写端不停的写，而读端不读，最终会把管道写满

ps -elf |grep write	会发现写端在管道写满后进入了sleep态，此时如果直接ctrl+c断开读端，写端也会结束，但是echo $?是异常的，因为在while(1)崩溃了，收到了13号信号才结束

### 防范死锁

保证两个程序第一次打开的管道必须是同一个管道，并且一个程序对管道读，另一个管道必须对该管道写

### 流程

```c
//chat1
while(1){
    读取标准输入
    写入管道fdw，发送给对端
    读取管道fdr
    打印显示
}

//chat2
while(1){
    读取管道fdr
    打印显示
    读取标准输入
    写入管道fdw，发送给对端
}
```

```c
void chat1(char *fifo1,char *fifo2){
    int fdr=open(fifo1,O_RDONLY);
    int fdw=open(fifo2,O_WRONLY);
    printf("I am chat1 fdr=%d,fdw=%d\n",fdr,fdw);
    char buf[128]={0};
    while(1){
        memset(buf,0,sizeof(buf));
        read(STDIN_FILENO,buf,sizeof(buf));//读取标准输入
        write(fdw,buf,strlen(buf));//将内容写入管道
        
        memset(buf,0,sizeof(buf));
        read(fdr,buf,sizeof(buf));//从另一条管道读取对端写入的内容
        printf("%s\n",buf);
    }
}

void chat2(char *fifo1,char *fifo2){
    int fdw=open(fifo1,O_RDONLY);//和chat1的读写端对调
    int fdr=open(fifo2,O_WRONLY);
    printf("I am chat2 fdr=%d,fdw=%d\n",fdr,fdw);
    char buf[128]={0};
    while(1){
        memset(buf,0,sizeof(buf));
        read(fdr,buf,sizeof(buf));//读取对端写入的内容
        printf("%s\n",buf);
        
        memset(buf,0,sizeof(buf));
        read(STDIN_FILENO,buf,sizeof(buf));//读取标准输入
        write(fdw,buf,strlen(buf));//将内容写入管道
        
        
    }
}
```

上述程序只能两端每次互相发一句接受一句，如果想不受拘束任意发n句话，就需要IO多路转接模型

## IO多路转接模型

多个进程同时阻塞时原先是按顺序解锁阻塞的，用多路复用可以达成"谁能不阻塞了就先走"的效果，不必按照原先的顺序依次等待解锁

### select函数

```c
#include <sys/select.h>
#include <sys/time.h>
int select(int maxfd, fd_set *readset,fd_set *writeset, fd_set *exceptionset, struct timeval * timeout);
```

返回就绪描述字的数目，超时返回0，错误返回-1

int maxfd 		最大的文件描述符（其值应该为最大的文件描述符字+1）

fd_set *readset 		内核读操作的描述符字集合，存放可以执行读操作的描述符

fd_set *writeset		内核写操作的描述符字集合，存放可以执行写操作的描述符

fd_set *exceptionset	内核异常操作的描述符字集合

 fd_set 集合的相关操作如下：

```c
void FD_ZERO(fd_set * fdset); /* 将所有 fd 清零 */
void FD_SET(int fd, fd_set * fdset); /* 增加一个 fd */
void FD_CLR(int fd, fd_set * fdset); /* 删除一个 fd */
int FD_ISSET(int fd, fd_set * fdset); /* 判断一个 fd 是否有设置 */
```

struct timeval *timeout：等待描述符就绪需要多少时间。NULL 代表永远等下去，一个固定值代表等待固定时间，0 代表根本不等待，检查描述字之后立即返回;到达时间还没就绪就会超时返回0

```c
struct timeval
{
	long tv_sec; 		/* second */ //秒
	long tv_usec;		 /* microsecond */ //微秒
};
```

#### 循环内具体流程

```c
1、初始化等待集合(清零)

2、添加要监听的文件

3、由原先的多个进程read的阻塞转为由select来阻塞

4、分配到合理的read函数
```

#### select超时机制

struct timeval *timeout 是传入传出参数，传入的值在函数执行后会归零





```c
int main(int args,char *argv[]){
    ARGS_CHECK(args,3);
    int fdw=open(argv[1],O_WRONLY);
    int fdr=open(argv[2],O_RDONLY);
    fd_set rdset;
    int ret,res;
    char buf[128]={0};
    struct timeval timeout;
    while(1){
        //存入监听的文件描述符
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(fdr,&rdset);
        //超时机制
        bzero(&timeout,sizeof(timeout));
        timeout.tv_sec=3;//每次循环都要清零重新赋值3秒
        //为了不从0遍历到1023的文件描述符，select传参就需要传已使用的最大文件描述符+1的值
        ret=select(fdr+1,&rdset,NULL,NULL,&timeout);//rdset是传入传出参数，执行完select后内部只剩下就绪的文件描述符了，timeout也是，使用完会变为0，但是保险起见仍需要自己手动清0
        ERROR_CHECK(ret,-1,"select");
        if(ret>0){//没超时
            if(FD_ISSET(STDIN_FILENO,&rdset)){
                memset(buf,0,sizeof(buf));
                res=read(STDIN_FILENO,buf,sizeof(buf));
                if(res==0){//主动断开
                    break;
                }
                write(fdw,buf,strlen(buf)-1);
            }
            if(FD_ISSET(fdr,&rdset)){
                memset(buf,0,sizeof(buf));
                ////管道的一端关闭有两种情况，一种是ctrl+c强制关闭，另一种是close(fd)
                //如果写端关闭，读端会返回0，状态会被标识为可读，read会一直读空的buf，puts就会一直打印换行了，因此要对read的返回值做判断，如果为0就退出while循环
                res=read(fdr,buf,sizeof(buf));
                if(res==0){//对方断开
                    break;
                }
                puts(buf);
            }
        }else{
            printf("timeout\n");
        }
    }
    close(fdw);
    close(fdr);
    return 0;
}
```

# day10

## 进程

程序是静态的，它是一些保存在磁盘上的指令的有序集合

而进程是一个动态的概念，它是一个运行着的程序，包含了进程的动态创建、调度和消亡的过程，是 Linux 的基本调度单位。

从系统的角度，通过进程控制块（PCB，process control block）(task struct)来描述进程的变化。进程控制块包含了进程的描述信息、控制信息以及资源信息，它是进程的一个静态描述。内核会不断的对它的各种值进行修改

内核使用进程来控制对 CPU (时间片)和其他系统资源(内存、端口等)的访问，并且使用进程来决定在 CPU 上运行哪个程序，运行多久以及采用什么特性运行它(调度器调度)。

内核的调度器负责在所有的进程间分配 CPU 执行时间，称为**时间片**(time slice)，它轮流在每个进程分得的时间片用完后从进程那里抢回控制权。



单核的cpu仍然可以运行多个应用程序，就是基于时间片轮转

如1个调度周期为1us，每个时间片为1ns，此时有n个进程待运行，调度器就会把时间片根据优先级进行时间片轮转，每个进程依次执行一个时间片直至调度周期结束，由于调度周期远小于50hz，每个进程都拿到了时间片，对人来说看起来就像是都在运行

在周期的开始，调度器要拿回cpu的控制权



cpu有一个就绪队列，即能拿到时间片的进程，从头到尾依次运行，分配给进程的时间片用完了该进程就会回到尾部

还有一个睡眠队列，如果进程是要等待，就会被移到睡眠队列，从睡眠队列移回就绪队列需要到下一个调度周期才能被分配时间片

### 进程标识

标识号(pid)是os用来区分进程的，pid从创建就已经有了，且不能被改变

进程除了自身的id外，还有其父进程的ppid

每个进程都是由其父进程创建而来的，所有进程都有一个祖先进程init进程，init进程是被写死 在主板上的bootloader程序启动的，它会把init程序拷贝到内存的固定地址(0x80)上，cpu中的esp寄存器存放的pc指针就会指向这个地址，init 进程负责引导系统、启动守护（后台）进程并且运行必要的程序。

init原先是0号pid，为了保持pid是正值减少判断才把自己置为1号

可以使用getpid()和getppid()获取自己的pid和父进程的ppid

ps -elf|grep xxxx	可以查看到进程号为xxxx的进程信息，父进程其实是-bash解析器

### 进程的用户id和组id(进程的运行身份)

用于进行进程的权限控制

缺省情况下，哪个登录用户运行程序，该程序进程就具有该用户的身份。

使用当前登录用户运行的程序在运行过程中就有了当前用户的身份

#### 真实用户和真实用户组

哪个用户运行的这个程序，真实用户和用户组就是该用户的

```c
getuid();	//获取真实用户
getgid();	//获取真实用户组
```

#### 有效用户和有效用户组

主要用于检验该进程在执行时所获得的访问文件权限，默认情况和真实用户和用户组一致代表真实用户对该文件的访问权限，可以通过修改使得访问权限比真实用户所拥有的权限更大，从而使得真实用户可以对本来不被允许访问的文件进行操作

```c
geteuid();	//获取有效用户	effect
getegid();	//获取有效用户组
```

如果一个文件只有某个特定用户可写，那么其他用户启动写该文件的可执行程序时就会报错，因为内核检查能否进行读写是**检查有效id**的，而此时有效id并不是该特定用户，因此就没有权限了

此时需要chmod u+s modify_file	这时modify_file就会变成红色的，s就是权限提升，设置了该属性后，用户运行该文件时，该进程的有效用户身份就不再是运行该文件的用户，而是该文件的创建者即那个特定用户。

```c
//setuid()	//改变真实id，有效也会跟着改，因为缺省是和uid一致的
//seteuid()	//只改变有效id
```



#### 修改用户对文件的权限

s	提升权限到和文件创建者一致

t	在该目录下有写权限，但是不能写其他用户创建的文件

`chmod u+s file`	提升当前用户对file文件的权限到和file文件的创建者一致

#### 权限降级

可以用setuid()来更改真实用户id，但是只能用root改，常用于root启动进程后修改权限防止其他进程写文件

如果/etc/passwd里的用户有/nologin，则表示它不能用于远程登录(比如mysql)，但是它仍然可以启动进程，因为ps显示的是有效用户id(此时是root)，这些进程是由root启动，然后root用seteuid()降低到mysql进程本身的权限，这样就保证了安全性，虽然是root启动，但是之后就是mysql了，只能操作属于mysql的文件，不能对磁盘上的其他用户进行随意执行读写了

### 进程的状态

R		执行			依据：两次采样之间是不是有时间片消耗

S		等待(阻塞、睡眠，内核可中断)			scanf	getchar	select	read

T		暂停

Z		僵尸

D		内核不可中断状态

执行态：该进程正在运行，即进程正在占用 CPU。 ps和top采样是在两次采样间隔内观察该进程有没有使用时间片，使用了就是R

就绪态：进程已经具备执行的一切条件，正在等待分配 CPU 的处理时间片。

等待态：进程不能使用 CPU，若等待事件发生（等待的资源分配到）则可将其唤醒。处于等待态的进程一定是在内核态睡眠，因为数据结构定义在内核态，只有在内核态才能改变结构体的值，因此一定是系统调用改变的状态

```
就绪->运行			获取cpu
运行->就绪			让出cpu(让出时间片)
运行->阻塞			请求资源
阻塞->就绪			获得资源
```

![image-20200309095159727](D:\TyporaPic\复习笔记Linux\image-20200309095159727.png)



### Linux下的进程结构

内核、栈、堆、bss(未初始化的数据段)、数据段、代码段

从用户态到内核态只有中断和系统调用2种，主要使用系统调用，访问的地址空间是内核态的就需要切换到内核态

### Linux下的进程管理

#### top命令动态显式内存占用

users		当前有多少用户登录了

load average		负载

第一排	运行负载、运行时间

第二排	进程状态

第三排	us	用户	sy	系统		id	空转

第四排第五排	内存，和free的类似

之下	进程状态，和ps类似，NI表示改变了多少权限值，PR表示当前的权限值

#### who命令查看当前登录的用户

ps -elf |grep userid

查看想要踢出的用户的进程号

然后kill -9 pid	就可以杀掉这个进程

#### ps命令查看系统进程列表

S		状态

UID	有效用户id

pid

ppid

pri	优先级，值越大，优先级越低

ni	改变优先级

time	累计运行时间

[]的是内核线程

```
ps -aux		查看cpu和内存占用率
```

#### free命令查看物理内存剩余

#### renice改变进程的优先级

Linux系统的优先级范围为0-140，用ps显示的范围为-40-99

默认进程优先级为80

+为降低，-为提升

renice -n +19 -p pid	把pid的优先级降低19从80到99			

top和ps显示的权限看起来不一样，但是实际是一样的

如果要提升权限，需要root，因为资源的分配需要

#### pkill xxx	匹配名字杀进程

#### kill -[number] pid	向进程发送信号

#### crontab		处理定时任务

其实是写在了/etc/crontab中

#### 热插拔(不关机的情况下更换磁盘)

mount /dev/sda2 /home/xxx/disk2	-t rw		挂载磁盘

umount	卸载磁盘，解除挂载

之后就可以更换磁盘然后mount即可

#### jobs	被ctrl+z暂停的进程

#### bg	将挂起的进程加载到后台运行

`bg n`		n为jobs中该进程的编号

#### fg	将挂起的进程加载到前台运行

`fg n`		n为jobs中该进程的编号

./xxx &	后台运行xxx可执行程序，这个xxx也可以用fg加载回前台(切换进程组)

### 进程的创建

system()	fork()	exec*()	popen()

#### fork

```c
pid_t fork(void);
```

执行一次返回两个值，父进程的返回值是子进程的pid，子进程返回的是0，若出错则返回-1

通过fork创建出子进程后，原有进程和子进程都从函数 fork 返回，各自继续往下运行，但是原进程的 fork 返回值与子进程的 fork 返回值不同

在原进程中，fork 返回子进程的 pid，而在子进程中，fork 返回 0

如果 fork 返回负值，表示创建子进程失败。



内核区分为两个部分，独有区(每个进程独有的)和共享区(所有进程共享的)

用户态分为栈、共享库映射区(动态库)、堆、未初始数据段(.bss)、数据段(.data)、代码段(.text)

![image-20200309095712905](D:\TyporaPic\复习笔记Linux\image-20200309095712905.png)

fork即复制了一份上述内容作为创建的子进程的内容，子进程的用户态保持和父进程一致，内核态的共享区保持一致，而独有区则是自己独有的



内核一般会先调度子进程，因为很多情况下子进程是要马上执行exec，会清空栈、堆这些和父进程共享的空间，加载新的代码段，这就避免了“写时复制”拷贝共享页面的机会。如果父进程先调度很可能写共享页面，会产生“写时复制”的无用功。

```c
pid_t pid;
pid=fork();
if(!pid){
    printf("子进程pid = %d , ppid = %d\n",getpid(),getppid());
}else{
    printf("父进程  pid=%d mychildpid=%d",getpid(),pid);
    sleep(1);//父进程只会等待子进程，对于子进程的子进程是不会等待的，bash的子进程是fork，而fork创建的是fork的子进程,如果没有sleep导致父进程先结束运行了的话，父进程创建的子进程就会被初始进程接管成为孤儿进程
}
```

##### 子进程的资源使用

使用 fork 函数得到的子进程是父进程的一个复制品

子进程从父进程继承了(memcpy来的)进程的地址空间(4g)，包括进程上下文(set jump \ long jump)、进程堆栈、内存信息、打开的文件描述符、信号控制设定、进程优先级(bash是80所以很多进程都是80)、进程组号、当前工作目录、根目录、资源限制、控制终端(xshell的窗口)

而子进程所独有的只有它的进程号、资源使用和计时器等



如果一个函数有上下部分清晰的行为差别，就可以称为上半部和下半部

对于父进程，在fork的上半段就已经memcpy、填好了pid，下半部分返回的就是子进程的pid

对于子进程，下半部分返回的就是0

##### 写时复制

由于进程执行读写操作都是在各自的进程地址空间(虚拟内存)中进行，如果两个进程的数据都相同，可以用1份物理内存映射2份虚拟内存，但是如果进行了写修改，就会把物理内存中的这段数据进行拷贝，即写时复制

fork子进程完全复制父进程的栈空间，也复制了页表，但没有复制物理页面，所以这时虚拟地址相同，物理地址也相同，但是会把父子共享的页面标记为“只读”（类似mmap的private的方式）

直到其中任何一个进程要对共享的页面“写操作”，这时内核会复制一个物理页面给这个进程使用，同时修改页表。而把原来的只读页面标记为“可写”，留给另外一个进程使用。

```c
char *pMalloc=(char *)malloc(20);
strcpy(pMalloc,"hello");
if(!fork()){
    printf("child :%s,%p\n",pMalloc,pMalloc);//hello
}else{
    pMalloc[0]='H';
    printf("parent :%s,%p\n",pMalloc,pMalloc);//Hello
}
```

此时父进程的H变成了大写的，子进程的h是小写的，而且指向的虚拟地址相同(实际的物理内存不同)

```c
printf("hello");//注意这里没有刷新缓冲区
fork();
printf("world\n");
//操作结果，两个进程都会打印helloworld
```

 如上述的代码，由于printf等价于fprintf(stdout,...)，即使用了stdout宏，展开为FILE *类型，即指向用户态的文件缓冲区中，因此如果没有换行刷新缓冲区，则"hello"就会和FILE结构体一起被fork复制到子进程中

如果是文件对象(read、write等)，则是存放在内核的共享区中，但是文件描述符(fd)是在各自的内核的独有区中，因此在产生子进程的时候是使用的dup让子进程独有区的文件描述符仍指向同一个文件对象，具体而言是共享了读写偏移量。

![image-20200309100717140](D:\TyporaPic\复习笔记Linux\image-20200309100717140.png)

```c
int fd=open(filenmae,O_RDWR);//内容为helloworlds
if(!fork()){
    char buf[10]={0};
    read(fd,buf,5);
    printf("child buf=%s\n",buf);//hello
}else{
    char buf[10]={0};
    read(fd,buf,5);
    printf("parent buf=%s\n",buf);//world
}
```

如果改成是在各自的进程体内部再open同一个文件，就是两个文件对象了，但是这样并不高效，而应当各自在进程体内使用mmap映射，因为磁盘的转速是恒定的



#### exec函数簇

```c
int execl(const char *path,const char *argv0,char *argv1...)
int execv(const char *path,char *const argv[])
```

以NULL结束参数列表，失败返回-1，成功无返回值

不会创建新进程，而是进行覆盖，从exec往下的代码都不会被执行了

```c
int main(int argc,char *argv[]){
   	sleep(10);//从ps看会发现进程名在execl前后会变
  execl("./print","processName","123","456",NULL);//从processName开始为新进程的argv[0]
    printf("you cannot see me\n");
    return 0;
}
/*
int main(int argc,char *argv[]){
   	sleep(10);//从ps看会发现进程名在execl前后会变
    char *const args[]={"processName","123","456",NULL};
  	execv("./print",args);
    printf("you cannot see me\n");
    return 0;
}
*/
//print.c
/*
int main(int argc,char *argv[]){
    int i;
    for(i=0;i<argc;i++){
        puts(argv[i]);
    }
    printf(" i am print process\n");
    while(1);//为了能在ps看到下面的processName
    return 0;
}
*/
```

运行exec.c就会发现一开始是execl，之后就变成processName 123 456了

#### system

system()和popen()都是动态库，是由fork和exec封装的

c语言嵌套其他语言本质是启动了一个新的进程，启动进程耗费时间过多

```c
int main(int argc,char *argv[]){
    system("sleep 30");
    return 0;
}
```

ps -elf 观察发现./a.out进程启动了sh -c sleep 30 进程和sleep 30 进程

### 进程的控制

#### 孤儿进程

父进程在子进程运行结束前就结束了，此时init进程会接管该子进程

#### 僵尸进程

子进程结束，但是父进程在忙碌，没有为其进行资源回收(task struct结构体 即pcb)，子进程就变成了僵尸

因此，对于子进程就要使用接口进行回收：

```c
#include <sys/types.h>			//sys是目录
 #include <sys/wait.h>

 pid_t wait(int *status);//成功返回结束的子进程的id，失败返回-1
 pid_t waitpid(pid_t pid, int *status, int options);/*
 pid表示等待的进程组，小于-1	等待这个值的绝对值的进程组的进程
 					-1		等价于wait
 					0		只等和自己属于一个进程组的进程
 					大于0		等待这个进程组的进程
 */
```

```c
pid_t pid;
pid=fork();
if(pid==0){
	printf("child pid=%d\n",getpid());
}else{
    wait(NULL);//NULL表示无差别回收即哪个子进程先结束就先回收哪个，一次wait只能回收1个进程
    printf("parent pid = %d,child pid = %d\n",getpid(),pid);
}
```

执行完后echo $?返回的是父进程的返回值0，bash只能拿到父进程的返回值，子进程的1拿不到



status分两部分，3个字节用来存放是正常退出还是崩溃了，剩下的1个字节存放返回值(0-255)

`WIFEXITED`按位与宏，和0x7f按位与，判断是否正常返回，可以通过预处理看.i文件确定是个宏

`WEXITSTATUS`	和0xff00按位与，按位与宏	获取子进程的返回值

```c
if(!fork()){
    printf("child pid=%d\n",getpid());
    char *p=NULL;
    *p='A';//崩溃
}else{
    int status;
    wait(&status);
    if(WIFEXITED(status)){
        printf("exit code=%d\n",WEXITSTATUS(status));
    }else{
        printf("child process crashed\n");
    }
}
```

```c
pid_t pid;
pid=fork();
if(!pid){
    printf("child pid=%d\n",getpid());
    char *p=NULL;
    *p='A';//崩溃
}else{
    pid_t childpid;
    int status;
    childpid=waitpid(pid,&status,0);
    printf("i am parent, child pid=%d\n",childPid);
    if(WIFEXITED(status)){
        printf("exit code=%d\n",WEXITSTATUS(status));
    }else{
        printf("child crash\n");
    }
}
```

waitpid的第三个参数option可以为`WNOHANG`，表示不会等待子进程执行完，这种情况下waitpid返回值为0

```c
pid_t pid;
pid=fork();
if(!pid){
    printf("child pid=%d\n",getpid());
    sleep(10);
    return 1;
}else{
    pid_t childpid;
    int status;
    childpid=waitpid(pid,&status,0);//没等到会返回0
    if(childpid>0){
        printf("i am parent, child pid=%d\n",childPid);
        if(WIFEXITED(status)){
            printf("exit code=%d\n",WEXITSTATUS(status));
        }else{
            printf("child crash\n");
        }
    }else{
        printf("未等待到结束的子进程\n");
    }
    return 0;
}
```

### 进程的终止

进程的终止并不会释放已占用的资源，通常会由该进程的父进程进行资源回收(wait waitpid)，如果不回收就会变成僵尸进程

1、main函数的自然返回

2、调用exit函数(如果是调用很深的栈不方便用return)

3、调用_exit函数	封装的系统调用，尽量不用

-----------------------下面的是异步的----------------------

4、调用abort函数	发送信号	6号信号	kill -l查看信号，前31个

5、接收到能导致进程终止的信号`ctrl+c`	SIGINT	2号信号	`ctrl+\ `SIGQUIT	3号信号

#### exit	和_exit

_exit比exit少了一步清理I/O缓冲即刷新标准输出的操作

```c
void print1(){
    printf("i am print");//这里没加\n刷新标准输出
    exit(5);//这里帮忙清理了
}

void print2(){
    printf("i am print");//这里没加\n刷新标准输出
    _exit(5);//这里就没刷新缓冲区，无法打印上一句的i am print了
}

void print3(){
    abort();//执行就会有core dumped,echo $?返回值为134，恰好为6号信号的返回值
}
```

# day12

## 守护进程

护进程要脱离终端后台运行，直到整个系统关闭时才退出。

### 守护进程的特性

1、后台运行

2、与其运行前的环境隔离开来，。这些环境包括未关闭的文件描述符、控制终端、会话和进程组、工作目录已经文件创建掩码等。通常是从父进程继承下来的

### 编程规则

#### 创建子进程，父进程退出(成为孤儿进程)

#### 在子进程中创建新会话setsid()

```
进程组：是一个或多个进程的集合。进程组有进程组 ID 来唯一标识。除了进程号(PID)之外，进程组 ID（GID）也是一个进程的必备属性。每个进程都有一个组长进程，其组长进程的进程号等于进程组 ID。且该进程组 ID 不会因为组长进程的退出而受影响。

会话周期：会话期是一个或多个进程组的集合。通常，一个会话开始于用户登录，终止于用户退出，在此期间该用户运行的所有进程都属于这个会话期。

控制终端：由于在 linux 中，每一个系统与用户进行交流的界面称为终端，每一个从此终端开始运行的进程都会依赖这个控制终端。

操作系统一旦启动，就会有一个init进程，init进程fork出一个新的子进程，子进程exec(不一定是execl)了login，登录完成(Xshell开启一个窗口)之后就会开启一个会话，会话中就会有一个shell命令行(bash)，每当执行一条命令，就会fork出一个子进程，子进程调用exec执行命令

一个用户登录，开启一个会话(setsid()函数创建新会话)
一个会话最多可用一个控制终端连接
一个会话里有若干进程组，最多有一个前台(统一接收终端信号)
```

![image-20200309104931928](D:\TyporaPic\复习笔记Linux\image-20200309104931928.png)

由于在调用 fork 函数的时候，子进程全盘拷贝了父进程的会话期、进程组、控制终端等，虽然父进程退出了，但会话期、进程组、控制终端并没有改变，因此，还不是真正意义上的独立开来，需要使用系统函数 `setsid()`创建新的会话组

调用 setsid 函数有下面 3 个作用：让进程摆脱原会话的控制，让进程摆脱原进程组的控制，让进程摆脱原控制终端的控制

##### 获取进程组id getpgid()

```c
pid_t getpgid(pid_t pid);	//pid为想要获取进程组id的进程的id	
```

pid=0表示pid是当前进程的pid

进程组组长的pid就是进程组id

```c
if(!fork()){
	printf("i am child pid=%d,ppid=%d,pgid=%d\n",getpid(),getppid(),getpgid(0));//获取当前进程的进程组id，pid填0
	return 0;
}else{
	printf("i am parent pid=%d,ppid=%d,pgid=%d\n",getpid(),getppid(),get pgid(0));//获取当前进程的进程组id，pid填0
    wait(NULL);
    return 0;
}
```

打印发现父进程就是这两个进程的进程组id，即进程组组长

```c
if(!fork()){
	printf("i am child pid=%d,ppid=%d,pgid=%d\n",getpid(),getppid(),getpgid(0));//获取当前进程的进程组id，pid填0
    while(1);//子进程不会结束，父进程也就会一直wait
	return 0;
}else{
	printf("i am parent pid=%d,ppid=%d,pgid=%d\n",getpid(),getppid(),get pgid(0));//获取当前进程的进程组id，pid填0
    wait(NULL);
    return 0;
}
```

此时按ctrl+c	结束会两个都结束，因为信号是发给**进程组**的

##### 设置进程组id setpgid()

```c
int setpgid(pid_t pid,pid_t pgid);//把pid原先的pgid设置为pgid
```

pid=0表示pid是当前进程的pid

pgid=0表示自己成立一个新的进程组，即自己作为新的进程组组长

```c
if(!fork()){
	printf("i am child pid=%d,ppid=%d,pgid=%d\n",getpid(),getppid(),getpgid(0));
    int ret=setpgid(0,0);//这样子进程就自己创建了新的进程组，不会被bash的ctrl+c终止了
    while(1);
	return 0;
}else{
	printf("i am parent pid=%d,ppid=%d,pgid=%d\n",getpid(),getppid(),get pgid(0));
    wait(NULL);
    return 0;
}
```

此时会发现子进程的pgid就会变成自己了

而bash为了不和运行的进程是同一个进程组，在启动进程的时候就会使用setpgid让运行的进程自己作为一个新的进程组

要退出子进程可以`kill -2 pid`

##### 获取会话组id getsid()

```c
pid_t getsid(pid_t pid);
```

和getpgid()类似，会话组的组长的pid就是会话组的id

会发现父子进程的sid都为bash的pid

##### 设置会话组id setsid()

```c
pid_t setsid(void);
```

不能加入其他会话组，只能新建会话组，作为新的会话组的组长

#### 改变当前路径为根目录

Linux可以删除正在启动的程序

pwd显示的是当前依赖的路径，不能被umount卸载掉，因此为了能对某些文件进行操作，就需要把路径切换到根目录

使用 fork 函数创建的子进程继承了父进程的当前工作目录。由于在进程运行中，当前目录所在的文件是不能卸载的，这对以后的使用会造成很多的不便。

```c
chidr("/");
```

#### 重设文件权限掩码

```c
umask(0);
```

#### 关闭不需要使用的文件描述符

新进程会从父进程那里继承一些已经打开了的文件。这些被打开的文件可能永远不会被守护进程读写，而它们一直消耗系统资源。

另外守护进程已经与所属的终端失去联系，那么从终端输入的字符不可能到达守护进程，守护进程中常规方法（如 printf）输出的字符也不可能在终端上显示。

所以通常关闭从 0 到 MAXFILE 的所有文件描述符。

```c
for(int i=0;i<MAXFILE;++i){
    close(i);
}
```

#### 添加守护进程要执行的任务

### 一个例子

```c
void Daemon(){
    if(!fork()){
        setsid();//建立新会话组
        chdir("/");//改变工作路径
        umask(0);//重设子网掩码
        for(int i=0;i<MAXFILE;++i){
            close(i);//关闭文件描述符
        }
        //守护进程需要执行的任务...
        
    }else{
        exit(0);//父进程退出，使得子进程成为孤儿进程
    }
}

int main(){
    Daemon();
    while(1);
    return 0;
}
```

## 格林尼治时间

```c
time_t 	秒数
ctime	字符串时间
gmtime	格林尼治时间
    
int main(){
    time_t now;
    time(&now);
    struct tm *p;
    p=gmtime(&now);
    printf("%04d-%02d-%02d %02d:%02d:%02d %d %d\n",p->tm_year+1900,p->tm_month+1,p->tm_day,p->tm_hour+8,p->tm_min,p->tm_sec,p->tm_wday,p->tm_yday);
    
    return 0;
}
```

## 管道

sudo apt install manpages -posix

标准流管道

无名管道

命名管道

### 标准流管道

```c
FILE *popen(const char *command,const char *open_mode);
int pclose(FILE* fp);
```

可以用来重定向某个进程的标准输入和标准输出到另一个进程

open_mode 有"r"和"w"两种

popen会在它和它拉起的新进程之间有一个新的无名管道

如果是r模式，则会把新进程的标准输出重定向到管道中，即原进程从新进程读

```c
//print.c=>print
int main(){
	printf("i am print\n");
}

int main(){
    FILE *fp=popen("./print","r+");
    char buf[128]={0};
    fread(buf,1,sizeof(buf),fp);
    puts(buf);//i am print
    pclose(fp);
}
```

如果是w模式，则会把新进程的标准输入重定向到管道中，和oj的思想一致(oj的测试用例都是单独的文件)，即原进程向新进程写

```c
//add.c=>add
int main(){
    int i,j;
    scanf("%d %d",&i,&j);
}

int main(){
    FILE *fp=popen("./add","w+");
    char *buf="3 4";
    fwrite(buf,1,strlen(buf)-1,fp);
    pclose(fp);
}
```

### 无名管道

```
1、只能在亲缘关系进程间通信(fork创建的关系)

2、半双工(固定的读端和固定的写端)

3、是特殊的文件，可以用read、write，在内存中创建
```

```c
int pipe(int fds[2]);
```

管道在程序中用一对文件描述符表示，其中一个文件描述符有可读属性，一个有可写的属性，fds[0]是可读，fds[1]是可写

管道是存在于内核中的，在使用fork创建子进程后，管道进行的是dup，而文件描述符的数组会被copy给子进程和父进程，相当于两个进程同时操作了内核中的一个文件对象(管道)，因此可以分别关闭两个进程的读/写端，实现了借助管道两个进程互相通信

父子进程同时拥有无名管道的读端和写端，因此只能同时有一个进程写，此时该进程的读端会关闭

```c
int main(){
    int fds[2];
    pipe(fds);//读端fds[0]	写端fds[1]
    if(!fork()){
        close(fds[1]);//关闭写端，因为子进程要读
        char buf[128]={0};
        read(fds[0],buf,sizeof(buf));
        puts(buf);
        exit(0);
    }else{
        close(fds[0]);//关闭读端，因为父进程要写
        char *buf="helloworld";
        write(fds[1],buf,strlen(buf));
        wait(NULL);//等待子进程读完
        exit(0);
    }
}
```

### 命名管道

使用mkfifo创建管道，在文件系统创建，但是还是在内存中传递信息

通信的进程间不需要亲缘关系，均使用open()打开管道

使用完成后使用unlink解除连接

```c
#include<sys/types.h>
#include<sys/stat.h>
int mkfifo(char *pathname,mode_t mode);
int unlink(const char *pathname);//解除连接
```

```c
int main(){
    int fd;
    unlink("fifo");
    mkfifo("fifo",0777);//仍然收到umask掩码的影响
    if(!fork()){
        fd=open("fifo",O_RDONLY);
        char buf[128]={0};
        read(fd,buf,sizeof(buf));
        puts(buf);
        close(fd);
        exit(0);
    }else{
        char *buf="helloworld";
        fd=open("fifo",O_WRONLY);
        write(fd,buf,sizeof(buf));
        wait(NULL);
        close(fd);
        exit(0);
    }
}
```



## 共享内存

进程间通信最快的方式

System V

ipcs可以查看已定义的共享内存

nattch		连接的进程数

使用shmget在物理内存的某一块创建共享内存区，各进程使用shmat（attach）连接，使用shmdt	(detach)断开连接，最后一个使用的进程使用完毕后使用shmctl关闭共享内存

### 原理及实现

进程的虚拟地址空间分为内核虚拟地址空间和用户态虚拟地址空间

```c
char buf[1000];	//在栈空间分配空间
char *buf=(char *)malloc(1000); //堆空间
```

文件描述符存放于内核区的进程独占区，指向内核共享区的文件对象

```
磁盘(网络设备、未分配物理内存等)	-拷贝>	
文件缓冲区(文件对象)				-拷贝>	
用户态缓冲区buf
```

![image-20200313144232211](D:\TyporaPic\复习笔记Linux\image-20200313144232211.png)

用户态的文件缓冲区(堆空间)直接和物理内存映射(shm)

用户态的文件缓冲区(堆空间)借助DMA设备直接和磁盘的文件映射(mmap)

比起read，少了一步将数据从内核转移到用户态的拷贝



进程间需要共享的数据被放在该共享内存区域中，所有需要访问该共享区域的进程都要把该共享区域映射到本进程的地址空间中去。

这样一个使用共享内存的进程可以将信息写入该空间，而另一个使用共享内存的进程读操取刚才写入的信息，从而实现进程间的通信。

共享内存允许一个或多个进程通过同时出现在它们的虚拟地址空间的内存进行通信，而这块虚拟内存的页面被每个共享进程的页表条目所引用，同时并不需要在所有进程的虚拟内存都有相同的地址(即不需要每个进程的地址空间分配同样的起始地址)。

进程对象对于共享内存的访问通过 key（键）来控制，同时通过 key 进行访问权限的检查。

```c
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
key_t ftok(const char *pathname, int proj_id);//生成k，一般都直接指定
int shmget(key_t key, int size, int shmflg);//创建或打开共享内存
void *shmat(int shmid, const void *shmaddr, int shmflg);//把堆空间和创建的共享内存建立联系
int shmdt(const void *shmaddr);//将共享内存段与进程空间分离，解除联系
int shmctl(int shmid, int cmd, struct shmid_ds *buf);//控制操作，多为删除共享内存段(标记删除)
```

#### ftok()	不常用

```c
key_t ftok(const char *pathname, int proj_id);
```

参数 pathname 为一个全路径文件名，并且该文件必须可访问。

参数 proj_id 通常传入一非 0 字符

通过 pathname 和 proj_id 组合可以创建唯一的 key

如果调用成功，返回一关键字，否则返回-1

vim ftok.c

```c
int main(int argc,char *argv[]){
    ARGS_CHECK(argc,2);
    key_t key;
    key=ftok(argv[1],1);
    printf("key=%d\n",key);
    return 0;
}
```

#### shmget()

```c
int shmget(key_t key, int size, int shmflg);
```

用于创建或打开一共享内存段，该内存段由函数的第一个参数唯一创建。

函数成功，则返回一个唯一的共享内存标识号shmid（相当于进程号，唯一的标识着共享内存），失败返回-1。

参数 key 是一个与共享内存段相关联关键字，如果事先已经存在一个与指定关键字关联的共享内存段，则直接返回该内存段的标识，表示打开，如果不存在，则创建一个新的共享内存段。key 的值既可以用 ftok 函数产生，也可以是 IPC_PRIVATE（用于创建一个只属于创建进程的共享内存，主要用于父子通信）,表示总是创建新的共享内存段；

参数 size 指定共享内存段的大小，以字节为单位，最好为4k的整数倍，可以充分利用页机制

参数 shmflg 是一掩码合成值，可以是访问权限值与(IPC_CREAT 或 IPC_EXCL)的合成。IPC_CREAT 表示如果不存在该内存段，则创建它。IPC_EXCL 表示如果该内存段存在，则函数返回失败结果(-1)。如果调用成功，返回内存段标识，否则返回-1

**创建的共享内存不会因为进程的结束而消失**

vim shmget.c

```c
int main(int argc,char *argv[]){
    int shmid;
    shmid=shmget(1000,1<<20,IPC_CREAT|0600);//1M		0600表示只有自己可读可写
    ERROR_CHECK(shmid,-1,"shmget");
    return 0;
}
```

#### shmat()

```c
void *shmat(int shmid, const void *shmaddr, int shmflg);
```

将共享内存段映射到进程空间的某一地址。

参数 shmid 是共享内存段的标识 通常应该是 shmget 的成功返回值

参数 shmaddr 指定的是共享内存连接到当前进程中的地址位置。通常是 NULL，表示让系统来选择共享内存出现的地址。

参数 shmflg 是一组位标识，通常为 0 即可。

如果调用成功，返回映射后的进程空间的首地址，否则返回(char *)-1。

vim shmat.c

```c
int main(int argc,char *argv[]){
    int shmid;
    shmid=shmget(1000,1<<20,IPC_CREAT|0600);//1M		0600表示只有自己可读可写
    ERROR_CHECK(shmid,-1,"shmget");
    char *p;
    p=(char *)shmat(shmid,NULL,0);
    ERROR_CHECK(p,(char *)-1,"shmat");
    strcpy(p,"hello");
    //while(1);//观察nattch
    return 0;
}
```

这里的链接会随着进程的结束而关闭，因为是连接到进程自己的虚拟内存空间的，即nattch在进程运行时和结束的是不一样的

vim shmat_r.c

```c
int main(int argc,char *argv[]){
    int shmid;
    shmid=shmget(1000,1<<20,IPC_CREAT|0600);//1M		0600表示只有自己可读可写
    ERROR_CHECK(shmid,-1,"shmget");
    char *p;
    p=(char *)shmat(shmid,NULL,0);
    ERROR_CHECK(p,(char *)-1,"shmat");
    puts(p);//可以获取到hello
    return 0;
}
```

会发现能读到hello，因为本质是对物理内存进行了修改



#### shmdt()

```c
int shmdt(const void *shmaddr);
```

用于将共享内存段与进程空间分离，只能解除一次，不能像munmap一样多次解除映射

参数 shmaddr 通常为 shmat 的成功返回值。

函数成功返回 0，失败时返回-1.

**注意，将共享内存分离并没删除它，只是使得该共享内存对当前进程不在可用。**

#### shmctl()

```c
int shmctl(int shmid, int cmd, struct shmid_ds *buf);
```

是共享内存的控制函数，可以用来删除共享内存段。

参数 shmid 是共享内存段标识 通常应该是 shmget 的成功返回值

参数 cmd 是对共享内存段的操作方式，可选为 IPC_STAT,IPC_SET,IPC_RMID。通常为 IPC_RMID，表示删除共享内存段。

参数 buf 是表示共享内存段的信息结构体数据，通常为 NULL。

 有进程连接，执行返回 0，**标记删除**成功，但是最后一个进程解除连接后，共享内存真正被删除。

#### 标记删除

在有其他进程对共享内存进行读写时，是不能删除该段共享内存的，只是status会变成dest(destory)，key值也变成0x00了，因为删除是标记删除，并不是真正的删除了，而shmctl只要标记成功了，就会返回成功，key值变为0就不能再被shget获取到这段共享内存了，即不允许新的进程连接到共享内存，等待正在读写的进程解除连接后，最后一个连接进程就会把这段共享内存删除掉了。

#### IPC_STAT

IPC_STAT可以获取文件信息，其中`shm_segsz`表示共享内存的大小，不能被修改；`shm_nattch`代表链接数，长整型，但是现在都是分布式，不会创建很多进程

只能改变uid、gid、mode

```c
int main(){
    int shmid=shmget(1000,1<<20,IPC_CREAT|0600);
    struct shmid_ds buf;
    shmctl(shmid,IPC_STAT,&buf);
    printf("uid=%d,mode=%o,size=%ld,nattch=%ld,\n",buf.shm_perm.uid,buf.shm_perm.mode,buf.shm_segsz,buf.shm_nattch);
    buf.shm_perm.mode=0666;//修改权限为0666
    shmctl(shmid,IPC_SET,&buf);//写回
}
```



### 为什么要用共享内存

使用管道进程多个进程间的相互通信，需要大量的管道，占用大量的空间

### 两个进程的共享内存

交换数据的成本较低

两个进程A、B各自的虚拟内存(4g)会使用物理内存的一块区域作为共享内存(4k的整数倍，利用页机制)，然后把这段共享内存映射到各自进程的堆空间(p1,p2)

因为映射的是同一块物理内存，所以A进程对p1的写操作对于B进程也可见，并且p2的相同位置也会被写入相同的信息

但是要注意的就是同时对共享内存的写操作可能会导致意外的结果

#### 借助共享内存各自加1kw

```c
int main(){
    int shmid=shmget(1000,1<<20,IPC_CREAT|0600);//创建共享内存
    int *p=(int *)shmat(shmid,NULL,0);//连接共享内存
    if(!fork()){
        for(int i=0;i<10000000;++i){
            ++p[0];
        }
        exit(0);
    }else{
        for(int i=0;i<10000000;++i){
            ++p[0];
        }
        wait(NULL);
        shmdt(p);
        shmctl(shmid,IPC_RMID,NULL);
        exit(0);
    }
    
}
```

执行的结果每次都不一定相同，因为是并发

并行：各操作各的

并发：多个进程同时对某一个资源进行操作

数据在做加法时，通过一级缓存二级缓存最后放入cpu的加法器中，但是在准备写回内存的时候时间片恰好用完，此时另一个进程进行+1操作，但是拿到的数并不是前一个进程+1后的结果，(如果用同一个寄存器操作则进行压栈操作，类似long jump，再次使用会进行恢复现场)，因此会导致一个进程覆盖另一个进程，核数更多的时候并发更大，得到的结果会更小

### 大页创建共享内存

如果页内偏移量超过了4k，就要新创建一个页，此时把页的大小改为2M，即可解决，这个页称为大页，常用在共享内存中 

在shmget的shmflg中要加上SHM_HUGETLB和SHM_HUGE_2MB(这个 要自己define一下)

```c
#define SHM_HUGE_2MB	(1<<21)
int main(int main,char *argv[]){
    int shmid;
  shmid=shmget(1000,1<<21,IPC_CREAT|0600|SHM_HUGETLB|SHM_HUGE_2MB);
    ERROR_CHECK(shmid,-1,"shmget");
   	return 0;
}
```

运行会报错，因为没有开启大页开关，在root下运行

echo 20 > /proc/sys/vm/nr_hugepages 	

因为相当于是现在要把原先的4k一个页重新化成20个2M的页，需要root先分好，其他用户才能使用这些页，sudo不行的原因可能和这个命令会判断当前用户的id，sudo只是提升了权限，本质还是当前的用户在操作这个中断而不是root用户

/etc/rc.local		写到这里可以保证每次开机都是大页

在下/proc/sys/vm/nr_hugepages 	查看允许存在多少大页，默认为0

#### 查看大页使用情况

cat /proc/meminfo		查看内存信息

### mmap实现共享内存

将进程的虚拟内存和磁盘进行映射，堆空间

多个进程映射同一块磁盘，牵一发而动全身

`MAP_SHARED`

`MAP_PRIVATE`	的话就是私有的映射了，其他进程就无法访问这个映射，因此即使是对同一个文件进行映射也是两块不同的物理内存

```c
int main(int args,char *argv[]){
    int fd=open(argv[1],O_RDWR);
    ftruncate(fd,1<<20);
    char *p=(char *)mmap(NULL,1<<20,PORT_READ|PORT_WRITE,MAP_SHARED,fd,0);
    if(!fork()){
        printf("%s\n",p);
    }else{
        strcpy(p,"hello");
        wait(NULL);
        exit(0);
    }
}
```

#### 强制把文件从内存写回磁盘

```c
int msync(void *addr,size_t length,int flags);
```

flags：

MS_SYNC	只有真正写回磁盘了才会返回，写回之前进程会一直在睡眠，在DMA写完后给cpu发中断，此时进程才会醒来

MS_ASYNC	立刻返回

#### mmap和shm的区别

mmap需要一个实际存在的且大小不为0的文件

如果要存储共享的信息，就要用mmap；如果进程运行结束后不再需要共享的信息就可以用shm

#### 使用mmap实现大页共享内存

因为mmap的实现需要借助磁盘上的文件系统，需要和本地的磁盘进行连接，所以需要修改文件系统

在大页形式的目录下新建文件，用这个文件进行mmap，此时mmap的都是大页形式存储的文件，即每个都是规定好的大小

```
echo 20 > /proc/sys/vm/nr_hugepages 	一共新分配20个大页
mkdir huge	新建一个目录专门存放大页文件
pwd后获取huge目录的位置dir
sudo mount none dir/huge -t hugetlbfs		挂载成大页类型的目录
mount	可以查看是否挂载成功
cat /proc/meminfo	查看大页的相关信息
```

```c
#define MAP_HUGE_2MB 1<<21
//要把文件系统挂载为大页形式的文件系统
int main(int argc,char *argv[]){
    ARGS_CHECK(argc,2);
    int fd=open(argv[1],O_RDWR|O_CREAT,0666);
    ERROR_CHECK(fd,-1,"open");
    int ret;
    char *p=(char *)mmap(NULL,MAP_HUGE_2MB,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    ERROR_CHECK(p,(char *)-1,"mmap");
    strcpy(p,"hello");
    sleep(20);//查看映射的是否为大页
    ret=munmap(p,MAP_HUGE_2MB);
    ERROR_CHECK(ret,-1,"munmap");
    close(fd);
    return 0;
}
```

`./mmap_hugepage huge/test`			在成为了大页系统的huge目录下创建一个大页文件test，用来实现mmap的大页机制

# day13

## 信号量

信号量是一种原语，即原子操作

`ipcs -s semid` 删除信号量

### 竞争条件

多个进程同时争夺同一个系统资源

### 原子操作

cpu不可被切换的最小操作

进程切换是cpu维持系统执行效率的重要方法

1、每个进程都先用原子操作给某个内存进行加锁，执行完对该内存的使用后再**解锁**		即初始状态下是解锁状态

2、加锁后给有需要的进程配一把钥匙，每个进程用钥匙开门执行完后再重新**加锁**			即初始状态下是加锁状态(多用于线程状态下)

### 信号量与计数器

信号量为正代表无锁，信号量为0代表有锁

-1操作(p)是加锁，+1操作(v)是解锁

信号量的初值就代表着资源数(最多可以有多少进程同时对该资源进行使用)

p操作：如果资源大于0就-1，否则会等待直到资源数大于0

v操作：如果资源小于上限就+1，否则会等待直到资源被使用，小于上限

### 具体实现

```c
#include <sys/sem.h> 
#include <sys/ipc.h> 
#include <sys/types.h> 

int semget(key_t key,int nsems,int flag); 
int semop(int semid,struct sembuf *sops,size_t num_sops); 
int semctl(int semid, int semnum, int cmd, …);
```

#### semget

```c
int semget(key_t key,int nsems,int flag); 
```

函数 semget 创建一个信号量集或访问一个已存在的信号量集。返回值：成功时，返回 一个称为信号量标识符的整数，semop 和 semctl 会使用它；出错时，返回-1. 

参数 key 是唯一标识一个信号量的关键字，如果为IPC_PRIVATE(值为 0，创建一 个只有创建者进程才可以访问的信号量，通常用于父子进程之间；非 0 值的 key(可以通 过 ftok 函数获得)表示创建一个可以被多个进程共享的信号量； 

参数 nsems 指定需要使用的信号量数目。如果是创建新集合，则必须制定 nsems。 如果引用一个现存的集合，则将 nsems 指定为 0. 

参数 flag 是一组标志，其作用与 open 函数的各种标志很相似。它低端的九个位是该信号量的权限，其作用相当于文件的访问权限。此外，它们还可以与键值 IPC_CREAT 按位或操作，以创建一个新的信号量。即使在设置了 IPC_CREAT 标志后给出的是一个 现有的信号量的键字，也并不是一个错误。我们也可以通过 IPC_CREAT 和 IPC_EXCL 标志的联合使用确保自己将创建出一个新的独一无二的信号量来，如果该信号量已经存在，就会返回一个错误。

#### semop

```c
int semop(int semid,struct sembuf *sops,size_t num_sops); 
```

这个函数是原子操作，不会被其他进程打断，它要先关闭中断和抢占，因此非常耗时，如果已经被加锁，就会sleep直到解锁

函数 semop 用于改变信号量对象中各个信号量的状态。返回值：成功时，返回 0；失败时，返回-1. 

参数 semid 是由 semget 返回的信号量标识符。 

参数 sops 是指向一个结构体数组的指针。每个数组元素至少包含以下几 个成员：

```c
struct sembuf{ 
    short sem_num; //操作信号量在信号量集合中的编号，第一个信号量的编号是0。 
    short sem_op; //sem_op成员的值是信号量在一次操作中需要改变的 数值。通常只会用到两个值，一个是-1，也就是p操作，它等待信号量变为可用；一个 是+1，也就是v操作，它发送信号通知信号量现在可用。 
    short sem_flg; //通常设为：SEM_UNDO，程序结束，信号量为 semop 调用前的值。
}; 
```

参数 num_sops为 sops 指向的 sembuf 结构体数组的大小，即即将要操作的信号量的个数

```c
p操作：是原子操作，即不可分割的操作，此时无法进行进程间切换
if(sem>0){
	sem--;
}else{
	等待，重新调用(返回if判断)
}

v操作：
if(sem<MAX){
	sem++;
}else{
	等待，重新调用(返回if判断)
}
```

#### semctl

```c
int semctl(int semid, int semnum, int cmd, …);
```

函数 semctl 用来直接控制信号量信息。函数返回值：成功时，返回 0；失败时，返回-1. 

参数 semid 是由 semget 返回的信号量标识符。 

参数 semnum 为集合中信号量的编号，当要用到成组的信号量时，从 0 开始。一般取值为 0，表示这是第一个也是唯一的一个信号量。 

参数 cmd 为执行的操作。通常为：IPC_RMID（立即删除信号集，唤醒所有被阻 塞的进程）、GETVAL（根据 semun 返回信号量的值，从 0 开始，第一个信号量编号 为 0）、SETVAL（根据 semun 设定信号的值，从 0 开始，第一个信号量编号为 0）、 GETALL（获取所有信号量的值，第二个参数为 0，将所有信号的值存入 semun.array 中）、SETALL（将所有 semun.array 的值设定到信号集中，第二个参数为 0）等。 

参数…是一个 union semun（共用体是所有成员公用一块内存,需要由程序员自己定义），它至少包含以下几个成员： 		

```c
union semun{ 
int val; /* Value for SETVAL */ 
struct semid_ds *buf; /* Buffer for IPC_STAT, IPC_SET */ 
unsigned short *array; /* Array for GETALL, SETALL */ 
}; 
```

通常情况仅使用 val，给 val 赋值为 1 

```c
int main(){
	int semArrid=semget(1000,1,IPC_CREAT|0600);
    int ret=semctl(serArrid,0,SETVAL,1);
    ret=semctl(semArrid,0,GETVAL);
    printf("get sem val=%d\n",ret);
    ret=semctl(semArrid,0,IPC_RMID);
}
```

如果创建的时候不给0600权限，在运行时就会报错，ipcs查看perms发现没有权限，此时如果用rmid删除会提示没有权限，因为信号量集合一旦被创建，权限就已经被确定是0000了，此时用上面的代码的0600权限就无法使用了

##### 一个信号量集合创建多个信号量

一个信号量是保护一段共享内存的

获取的信号量个数一定要小于信号量的总数

要用`unsigned short`类型的数组设定每个信号量的值

semctl只知道传入的arr的起始地址，因为semctl是系统调用，在系统内核能知道信号量的属性里的信号量个数是多少，因此就可以知道偏移几次，至于偏移量则是short规定好的，因此不能用int，因为int偏移量是short的两倍

```c
int main(){
    int semArrid=semget(1000,2,IPC_CREAT|0600);
    unsigned short arr[2]={5,10};//设置两个信号量初始值为5和10
    int ret=semctl(semArrid,0,SETVAL,arr);
    memset(arr,0,sizeof(arr));
    semctl(semArrid,0,GETVAL,arr);
    printf("arr[0]=%d,arr[1]=%d\n",arr[0],arr[1]);
}
```

##### IPC_STAT & IPC_SET 

获取信号量状态，与共享内存类似

```c
int main(){
    int semArrid=semget(1000,1,IPC_CREAT|0600);
    struct semid_ds buf;
    int ret=semctl(semArrid,0,IPC_STAT,&buf);
    printf("uid=%d,mode=%o,nsems=%ld\n",buf.sem_perm.uid,buf.sem_perm.mode,buf.sem_nsems);
    buf.sem_perm.mode=0666;//ipcs可以看到权限更改
    rem=semctl(semArrid,0,IPC_SET,&buf);
}
```



### 实现生产者消费者问题

生产者	消费者

需要设定初始资源空位数量

对于生产者，空位>0 代表解锁，可以生产+1商品，-1空位

对于消费者，商品数>0代表解锁，可以消费-1商品，+1空位

因此就需要p1v1对空格进行加解锁，p2v2对商品进行加解锁

```c
生产者：
p1				//有没有空格，有的话空格-1
	生产()
v2				//商品数+1
	
消费者：
p2				//有没有商品，有的话商品-1
	消费()
v1				//空格数+1
```

space空间		初始化为10		代表空的位置		0号信号量的值

product产品	初始化为0			代表产品个数		1号信号量的值

```c
int main(){
    int semArrid=semget(1000,2,IPC_CREAT|0600);
    unsigned short arr[2]={10,0};//0号信号量代表空位，1号信号量代表产品数
    int ret=semctl(semArrid,0,SETVAL,arr);
    struct sembuf sopp,sopv;
    if(!fork()){//子进程为消费者
        while(1){
            sopv.sem_num=0;//第一个信号量，即空位
            sopv.sem_op=1;//v操作
            sopv.sem_flag=SEM_UNDO;
            sopp.sem_num=1;//第二个信号量，即产品数
            sopp.sem_op=-1;//p操作
            sopp.sem_flag=SEM_UNDO;
            //先-1产品数，再+1空位
            printf("I am customer ,space num=%d product num=%d\n",semctl(semArrId,0,GETVAL),semctl(semArrId,1,GETVAL));
            semop(semArrid,&sopp,1);
            semop(semArrid,&sopv,1);
            printf("I am customer ,after custom,space num=%d product num=%d\n",semctl(semArrId,0,GETVAL),semctl(semArrId,1,GETVAL));
            sleep(2);
        }
    }else{
        while(1){
            sopv.sem_num=0;//第一个信号量，即空位
            sopv.sem_op=-1;//p操作
            sopv.sem_flag=SEM_UNDO;
            sopp.sem_num=1;//第二个信号量，即产品数
            sopp.sem_op=1;//v操作
            sopp.sem_flag=SEM_UNDO;
            //先-1空位，再+1产品数
            printf("I am producer ,space num=%d product num=%d\n",semctl(semArrId,0,GETVAL),semctl(semArrId,1,GETVAL));
            semop(semArrid,&sopp,1);
            semop(semArrid,&sopv,1);
            printf("I am producer ,after produce,space num=%d product num=%d\n",semctl(semArrId,0,GETVAL),semctl(semArrId,1,GETVAL));
            sleep(2);
        }
    }
}
```

如果只有一个信号量加解锁，如果消费的比生产的快，消费的进程会不停的进行无用的加解锁，相对于计数信号量要占用更多的cpu时间片

同时计数信号量的效率更高，因为有多个信号量，多个进程可以同时进入各自的生产\消费，而单个信号量不能并行

### SEM_UNDO

如果在运行时用kill杀掉父进程，会发现空变多了(变成了子进程消费的次数)

在加解锁之间的代码如果执行崩溃了，就不会自动解锁了，因此引入了标识位SEM_UNDO，在加锁后如果崩溃了，系统就会回退到第一次加锁前的状态，防止进程死锁，其他进程无法解锁，加的次数要回减至0，减的次数要回加

此时子进程就是孤儿进程了，由于产品为0，子进程就会进入睡眠态，显示为semtim

### 读写锁

读写速度不匹配导致出错，因此有读锁和写锁

读锁	可以加无数次，每个进程读的时候都要加一把读锁，当存在写锁的时候要加读锁就会睡眠等待

写锁	要求读锁的数目为零，否则会睡眠等待

用的比较少，通常是映射到内存中用内存锁

#### 通常采用读者优先法

```
对于reader，只有当有writer正在写时需要等待，其他时候都可以直接读
对于writer，只有当没有其他reader和writer时可写，其他时候都要等待
```

```c
//设置两把锁，一把锁(mutex)控制读者数量(rc)这个临界资源，另一把锁(w)控制正在写这个临界资源
//读者数量初始为0，两把锁初始设为1，表示解锁状态
读者：
    p(mutex);
    ++rc;
    if(rc==1){//开始有读者了，因此在读操作之前要看有没有写者正在写
        p(w);//如果已经有人写，则需要等待
    }
    v(mutex);

	read();//执行读操作

	p(mutex);
	--rc;//读操作结束，读者-1
	if(rc==0){
        v(w);//读者数为0，表示没人读，才能写
    }
	v(mutex);

写者：
    p(w);
	write();
	v(w);
```



### 使用信号量解决进程间的同步和互斥

#### 同步

不同进程，执行操作的时候，要满足合适的时序，即进程的操作的执行要按一定的顺序(时间发生的先后顺序)

pv往往不在一起	mutex 初始化为0

![image-20200313111846711](D:\TyporaPic\复习笔记Linux\image-20200313111846711.png)

#### 互斥

多个进程同时操作某个资源的时候由于进程执行的先后顺序随机可能会导致不同的结果(寄存器的内容还没有写回就再次被调用导致被覆盖了)，因此当某个进程正在操作资源时，其他进程就不能操作这个资源了，只能阻塞等待资源被操作完毕

pv往往连在一起	mutex 互相排斥，初始化为1

tips：互斥区应当尽可能的小，防止等待时间过长

![image-20200313111410354](D:\TyporaPic\复习笔记Linux\image-20200313111410354.png)

### 死锁

互相等待对方对临界资源的释放

```c
死锁成立的四个条件：
    1、互斥使用
    2、占有且等待
    3、不可抢占
    4、循环等待		//设法去除
```

如何解决死锁：找到循环等待链，设法使进程间有同步关系，把等待链断开

# day14

## 消息队列

存放在内存中，不会随进程的消亡而结束，可以用`ipcs`查看

消息可以看作是一个一个的报文数据包，每次读写都是以包为单位，包与包之间按照队列的形式互相连接，写端写在队列尾，读端从队列头读

![image-20200313095121371](D:\TyporaPic\复习笔记Linux\image-20200313095121371.png)

### 消息队列和管道的区别

对于管道，write和read的次数可以不匹配，只要缓冲区够大，可以一次读取其他进程多次写的数据

但是消息队列则是按照次数，send1次只能receive1次，每个包是独立的，比如多个用户同时写，一个用户读，容易消息分离，就需要消息队列

### 具体实现

```c
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
int msgget(key_t key, int msgflg);
int msgsnd(int msqid, struct msgbuf *msgp, size_t msgsz, int msgflg);
ssize_t msgrcv(int msqid, struct msgbuf *msgp, size_t msgsz, long msgtyp, int 
msgflg);
int msgctl(int msqid, int cmd, struct msqid_ds *buf);
```

#### msgget

```c
int msgget(key_t key, int msgflg);
```

函数 msgget 创建和访问一个消息队列。该函数成功则返回一个唯一的消息队列标识符（类似于进程 ID 一样），失败则返回-1.

参数 key 是唯一标识一个消息队列的关键字，如果为IPC_PRIVATE(值为 0)，用创建一个只有创建者进程才可以访问的消息队列，可以用于父子间通信；非 0 值的 key(可以通过 ftok 函数获得)表示创建一个可以被多个进程共享的消息队列；

参数 msgflg 指明队列的访问权限和创建标志，创建标志的可选值为 IPC_CREAT和 IPC_EXCL 如果单独指定 IPC_CREAT,msgget 要么返回新创建的消息队列 id,要么返回具有相同 key 值的消息队列 id；如果 IPC_EXCL 和 IPC_CREAT 同时指明，则要么创建新的消息队列，要么当队列存在时，调用失败并返回-1。

#### msgsnd 和 msgrcv

```c
int msgsnd(int msqid, struct msgbuf *msgp, size_t msgsz, int msgflg);
ssize_t msgrcv(int msqid, struct msgbuf *msgp, size_t msgsz, long msgtyp, int msgflg);
```

参数 msgid 指明消息队列的 ID; 通常是 msgget 函数成功的返回值。

参数 msgp 是包的地址即定义的消息结构体，它的长度必须小于系统规定的上限，必须以一个长整型成员变量开始，接收函数将用这个成员变量来确定消息的类型。必须重写这个结构体，其中第一个参数不能改，其他自定义。如下：

```c
struct msgbuf {
    long mtype; /* type of message *///必须为正数，包的类型
    char mtext[1]; /* message text *///自己定义长度，包存储的数据
 };
//字段 mtype 是用户自己指定的消息类型（必须是正整数），该结构体第 2个成员仅仅是一种说明性的结构，实际上用户可以使用任何类型的数据，就是消息内容；
//参数 msgsz 是消息体的大小，每个消息体最大不要超过 4K;
```

参数 msgflg 可以为 0（通常为 0）或 IPC_NOWAIT，如果设置 IPC_NOWAIT,则msgsnd 和 msgrcv 都不会阻塞，此时如果队列满并调用 msgsnd 或队列空时调用 msgrcv将直接返回错误；

参数 msgtyp 有 3 种选项：

```
msgtyp == 0	 接收队列中的第 1 个消息（通常为 0）
msgtyp > 0	 接收队列中的第 1 个类型等于 msgtyp 的消息
msgtyp < 0 	接收其类型小于或等于 msgtyp 绝对值的第 1 个最低类型消息
```

#### msgctl

```c
int msgctl(int msqid, int cmd, struct msqid_ds *buf);
```

消息队列的控制函数，常用来删除消息队列。

参数 msqid 是由 msgget 返回的消息队列标识符。

参数 cmd 通常为 IPC_RMID 表示删除消息队列。

参数 buf 通常为 NULL 即可。

### 消息队列的创建

```c
int main(){
    int msgid=msgget(1000,IPC_CREAT|0600);
}
```

使用ipcs查看创建的消息队列，messages是消息的个数，used-bytes是消息的大小

### 消息队列的发送和接收

/proc/sys/kernel	可以设置消息队列的相关参数

```c
typedef struct msgbuf{//必须重写该结构体
    long mtype;
    char mtext[64];//人为规定最大存64字节数据
}MSG_t;
int main(){
    int msgid=msgget(1000,IPC_CREAT|0600);
    struct msgbuf msgInfo;
    msgInfo.mtype=100;//自己指定的消息类型,用于固定接收和发送方
    strcpy(msgInfo.mtext,"hello");
    int ret=msgsnd=(msgid,&msgInfo,strlen(msgInfo.mtext),0);
}
```

上面发送到hello会保存在内存的消息队列中，等待接收,每次执行都会发现ipcs都有变化

```c
typedef struct msgbuf{//必须重写该结构体
    long mtype;
    char mtext[64];//人为规定最大存64字节数据
}MSG_t;
int main(){
    int msgid=msgget(1000,IPC_CREAT|0600);
    struct msgbuf msgInfo;
    int ret=msgrcv=(msgid,&msgInfo,sizeof(msgInfo.mtext),100,0);//和上面发送端的mtype=100对应
    printf("%d:%s\n",msgInfo.mtype,msgInfo._mtext);
}
```

接收消息队列的消息不依赖于发送消息的进程的状态

消息队列只能按次接，如果一次发送的是"helloworld"，而接收只接受一次"hello"，则接受完"hello"的同时剩下的world就会消失了

#### 不等待读

msgsnd 和 msgrcv 都不会阻塞，此时如果队列满并调用 msgsnd 或队列空时调用 msgrcv将返回错误

```c
int ret=msgsnd=(msgid,&msgInfo,strlen(msgInfo.mtext),IPC_NOWAIT);

int ret=msgrcv=(msgid,&msgInfo,sizeof(msgInfo.mtext),100,IPC_NOWAIT);
```

### 消息队列的删除

ipcrm -q msqid	命令行下删除

删除时立即删除，不像共享内存是标记删除,删除时其他在等待接收的进程都会立刻结束

```c
int main(){
    int msgid=msgget(1000,IPC_CREAT|0600);
    int ret=msgctl(msgid,IPC_RMID,NULL);
}
```

### 消息队列目前的使用

集群：

比如同时有大量消息需要发送，中央处理机器就需要先告知其他机器(已经提前得知了其他机器的繁忙程度)要发送的信息，此时就需要用消息队列实现异步，即要告诉其他机器需要把这条消息发送给其他用户(不需要等这台机器返回已完成任务的信息再找下一台机器发送)，至于发送完了要回告中央处理机器则也需要用消息队列回告，中央处理机器通过type就可以确定是哪台机器完成了任务





## 信号

信号是进程在运行过程中，有自身产生或由进程外部发过来的消息(事件)，信号是硬件中断的软件模拟(软中断)(软件中断：在正常执行进程的过程中途插入执行信号(signal handler))

中断管理器会区分中断的优先级，同一时刻只会把优先级最高的发送给cpu，每个中断都有个编号，每个编号都对应一段代码(中断例程)，执行完这段代码后cpu才会返回原先的状态

每个信号都有独特的意义，本质就是个数字，填在接收进程的pcb结构体的struct sigpending结构体中

信号想传递的是某种行为，而不是某个数据

信号的传递的时机是**随机**的，可能在函数执行前、执行中、执行后

![image-20200313145501413](D:\TyporaPic\复习笔记Linux\image-20200313145501413.png)

### 使用流程

```
定义信号集合	->	设置信号的阻塞情况	->	signal/sigaction设计信号处理函数	->	sigpending测试信号
```

### 信号的响应时机

1、当进程在睡眠，在发送信号的时候就把该睡眠进程移到就绪队列，信号处理流程开启

2、当进程在运行，当shedule(调度器)每一轮调度周期重新分时间片，在进程开始执行之前，esp寄存器会检查是否有信号(sigpending结构体)，没有信号才会恢复原有的上下文

3、当进程在运行，执行到系统调用时，就会检查进程上是否有信号

进程通过陷入门陷入内核态，要用系统调用编号拿到每个系统调用的实际所在内核的入口地址，有一个查找的过程

### 未决期与阻塞

某处产生信号发送给操作系统，随后操作系统把该信号传递给相应的进程，这段 接收-传递 空挡称为**未决**期(pending)

而接收的进程从接收到信号到开始处理这个信号这段时间称为**阻塞**

<img src="D:\TyporaPic\复习笔记Linux\image-20200313151240152.png" alt="image-20200313151240152" style="zoom:50%;" />

使用一个结构体记录所有信号的信息，其中

<img src="D:\TyporaPic\复习笔记Linux\image-20200313151539959.png" alt="image-20200313151539959" style="zoom: 50%;" />

位为1表示这一位代表的信号接收到会直接进入阻塞

处于阻塞集合的信号，内核产生以后，不能传递，解除阻塞以后，可以传递

阻塞集合解除阻塞后，当前未决集合内部的信号，会传递一次(就是多次发送至多响应一次的原因)

### 可靠信号与不可靠信号

可靠信号指的是接收方能够知道该信号发送了几次，发送几次就处理几次；信号值位于SIGRTMIN(34)和SIGRTMAX(64)之间的信号都是可靠信号

不可靠信号只会处理最后一次，会造成信号的丢失

### 信号的产生

信号的生成来自内核，让内核生成信号来自如下：

用户：用户能够通过输入 CTRL+c、Ctrl+\，或者是终端驱动程序分配给信号控制字符的其他任何键来请求内核产生信号； 

内核：当进程执行出错时，内核会给进程发送一个信号，例如非法段存取(11号信号的内存访问违规)、浮点数溢出等； 

进程：一个进程可以通过系统调用 `kill`函数给另一个进程发送信号，一个进程可以通过信号和另外 一个进程进行通信。

### 同步信号与异步信号

同步(synchronous signals)：A进程执行发送请求->等待->接受反馈		此时B进程必须等待A进程接受反馈后才能继续发送自己的请求，若干事件的执行有前后依赖性，如除 0、当前进程代码运行错误等导致的信号

异步(asynchronous signals)：A进程等待请求的反馈的时候B进程仍可以发送请求而不是只能等待A进程接受完反馈，即若干事件的执行没有前后依赖性，如像用户击键这样的进程外部事件产生的信号

但是对于cpu来说，由于是时间片轮转，因此在cpu看来所有的并行本质都是串行(即不同进程的信号传递先后不一定)

**信号的执行先后和所在进程执行的先后没有关系**

### 各系统信号的含义

term		终止

ign			忽略

core		终止并产生core

stop		进程的T状态，暂停

cont		继续

所有的信号都有唤醒功能

4号信号	硬编码		把一个数据当作一条指令执行，代码段的数据才有可执行权限，栈堆都没有可执行权限，最多可读可写

8号信号	类似try-catch

11号信号		非法内存

13号信号		管道的读端关闭链接

14号信号		sleep用的，移动到睡眠队列

SIGUSR1 2	操作系统保留的信号，用来自己编写，为了让进程能有序合理的退出

SIGCHLD	唤醒父进程，子进程需要资源回收

### 信号的处理方式

**接收默认处理**：接收默认处理的进程通常会导致进程本身消亡。例如连接到终端的进程，用户 按下 CTRL+c，将导致内核向进程发送一个 SIGINT 的信号，进程如果不对该信号做特殊的处理，系统将采用默认的方式处理该信号，即终止进程的执行； signal(SIGINT,SIG_DFL)； 

**忽略信号**：进程可以通过代码，显式地忽略某个信号的处理，例如：signal(SIGINT,SIG_IGN); 但是某些信号是不能被忽略的,例如 9 号信号； 

**捕捉信号并处理**：进程可以事先注册信号处理函数，当接收到信号时，由信号处理函数自动捕捉并且处理信号

### signal信号处理机制

信号的传递是在两条指令之间

![image-20200312100500356](D:\TyporaPic\复习笔记Linux\image-20200312100500356.png)



```c
#include <signal.h> 
typedef void (*sighandler_t)(int); //函数指针 
sighandler_t signal(int signum, sighandler_t handler);		//描述一个行为就需要函数指针，要放函数名，返回值为void，入参为int，即信号处理函数
```

signal 的第 1 个参数 signum 表示要捕捉的信号，第 2 个参数是个函数指针，表示要对该信号进行捕捉的函数，该参数也可以是 SIG_DFL(表示交由系统缺省处理，相当于白注册了,常用于复位)或 SIG_IGN(表示忽略掉 该信号而不做任何处理)。

signal 如果调用成功，返回值是函数指针(handler)，指向接收信号时正在执行的函数，即以前该信号的处理函数的地址，否则返回 SIG_ERR。 

sighandler_t 是信号捕捉函数，由 signal 函数注册，注册以后，在整个进程运行过程中均有效，并且 对不同的信号可以注册同一个信号捕捉函数。该函数只有一个整型参数，表示信号值。 

```c
void sigFunc(int signum){//内核使用的函数
    printf("%d is coming\n",signum);
}
int main(){
    if(signal(SIGINT,sigFunc)==SIG_ERR){//SIGINT即2号信号，可以ctrl+c触发
        perror("singal");
        return -1;
    }
    while(1);
    return 0;
}
```

设定了2号信号的行为后，每次按ctrl+c就会打印"2 is coming"

此时只能用`ctrl+\` 3号信号等其他未捕捉的信号关闭进程

```c
int main(){
    if(signal(SIGINT,SIG_IGN)==SIG_ERR){//SIGINT即2号信号，可以ctrl+c触发,但是SIG_IGN会把2号信号设为忽略
        perror("singal");
        return -1;
    }
    sleep(10);
    signal(SIGINT,SIG_DFL);//10秒后改回默认
    while(1);
    return 0;
}
```

这样的话用ctrl+c就没有反应了，在sleep之后再按ctrl+c就可以正常结束了，但是在sleep的时候传入其他信号就会有反应

### 在进行信号处理流程时如果又接受到了新传递的信号

```
1、相同信号：至多执行一次(信号的阻塞和未决各用一个位图存储，置位生效/0失效
阻塞1->0	->	未决1->0	->	执行handler
由于是位图，因此如果一个信号在阻塞态的过程中又传来多个同样的信号，在重新置位回1之前都只会执行一次)

2、不同信号：执行完新的信号处理流程后再回到原有的信号处理流程		
	转移 执行 回归
```

不同的信号有不同的优先级，在没有设置的情况下，同一个信号不会打断自己信号正在进行的信号处理流程，而优先级更高的信号就会打断原信号的处理流程

```c
void sigFunc(int signum){//内核使用的函数
    printf("before sleep %d is coming\n",signum);
    sleep(3);
    printf("after sleep %d is coming\n",signum);
}

int main(int argc,char *argv[]){
    if(signal(SIGINT,sigFunc)==SIG_ERR){//设定ctrl+c的信号行为
        perror("signal");
        return -1;
    }
    signal(SIGQUIT,sigFunc);//多个信号可以用一个信号处理函数
    while(1);
    return 0;
}
```



### sigaction信号处理机制

#### 信号处理情况分析

1、注册一个信号处理函数，并且处理完毕一个信号之后，是否需要重新注册，才能够捕捉下一个信号；（不需要） 

但是如果只想该函数生效一次，signal就不太适合(可以用SIG_DFL)

2、 如果信号处理函数正在处理信号，并且还没有处理完毕时，又发生了一个同类型的信号，这时该怎么处理；（挨着执行），**后续相同信号忽略（至多再执行一次）。** 

sigaction可以被相同信号打断

3、 如果信号处理函数正在处理信号，并且还没有处理完毕时，又发生了一个不同类型的信号，这 时该怎么处理；**（跳转去执行另一个信号，之后再执行剩下的没有处理完的信号）** 

sigaction	可以不被其他信号打断

4、 如果程序阻塞在一个系统调用(如 read(...))时，发生了一个信号，这时是让系统调用返回错误再接着进入信号处理函数，还是先跳转到信号处理函数，等信号处理完毕后，系统调用再返回。（后者）

#### sigaction注册

```c
#include <signal.h> 
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact); 
```

参数 signum 为需要捕捉的信号 

参数 act 是一个结构体，里面包含信号处理函数地址、处理方式等信息 

参数 oldact 是一个传出参数，sigaction 函数调用成功后，oldact 里面包含以前对 signum 的处理方式 的信息，通常为 NULL 

如果函数调用成功，将返回 0，否则返回-1 



结构体 struct sigaction(注意名称与函数 sigaction 相同)的原型为： 

```c
struct sigaction { 
    void (*sa_handler)(int); //老类型的信号处理函数指针 一般不使用
    void (*sa_sigaction)(int, siginfo_t *, void *);//新类型的信号处理函数指针 
    sigset_t sa_mask; //将要被阻塞的信号集合 
    int sa_flags; //信号处理方式掩码 (  SA_SIGINFO ) 
    void (*sa_restorer)(void); //保留，不要使用 
}; 
```

该结构体的各字段含义及使用方式： 

1、字段 sa_handler 是一个函数指针，用于指向原型为 void handler(int)的信号处理函数地址， 即老类型的信号处理函数（如果用这个再将 sa_flags = 0,就等同于 signal()函数） 

2、字段 sa_sigaction 也是一个函数指针，用于指向原型为： 

```c
void handler(int iSignNum, siginfo_t *pSignInfo, void *pReserved);
```

的信号处理函数，即新类型的信号处理函数 该函数的三个参数含义为： 

```
iSignNum：传入的信号的编号
pSignInfo：与该信号相关的一些信息，它是个结构体 
pReserved：保留，现没用，通常为 NULL 
```

字段 sa_handler 和 sa_sigaction 只应该有一个生效，如果想采用老的信号处理机制，就应该让 sa_handler 指向正确的信号处理函数，并且让字段 sa_flags 为 **0**；否则应该让 sa_sigaction 指向正确 的信号处理函数，并且让字段 sa_flags 包含 `SA_SIGINFO` 选项 

3、字段 sa_mask 是一个包含信号集合的结构体，该结构体内的信号表示在进行信号处理时，将要被阻塞的信号。也被称为临时阻塞集合，这个集合内的信号在其他信号的信号处理流程内是失效状态的。

针对 sigset_t 结构体，有一组专门的函数对它进行处理，它们是： 

```c
#include <signal.h> 
int sigemptyset(sigset_t *set); //清空信号集合 set 相当于memset
int sigfillset(sigset_t *set); //将所有信号填充进 set 中 
int sigaddset(sigset_t *set, int signum); //往 set 中添加信号 signum 
int sigdelset(sigset_t *set, int signum); //从 set 中移除信号 signum 
int sigismember(const sigset_t *set, int signum); //判断 signum 是否包含在 set 中(是:返回 1,否:0） 
int sigpending(sigset_t set); //将被阻塞的信号集合由参数set指针返回(挂起信号)
```

其中，对于函数 sigismember 而言，如果 signum 在 set 集中，则返回 1；不在，则返回 0；出错时返 回-1.其他的函数都是成功返回 0，失败返回-1.

4、字段 sa_flags 是一组掩码的合成值，指示信号处理时所应该采取的一些行为，各掩码的含义为

```
SA_RESETHAND	
处理完毕要捕捉的信号后，将自动撤消信号处理函数的注册， 即必须再重新注册信号处理函数，才能继续处理接下来产生的信号。该选项不符合一般的信号处理流程，现已经被废弃。

SA_NODEFER	
在处理信号时，如果又发生了其它的信号，则立即进入其它信号的处理，等其它信号处理完毕后，再继续处理当前的信号，即递规地处理。（不常用）不断重入，次数不丢失

SA_RESTART	
如果在发生信号时，程序正阻塞在某个系统调用，例如调用 read()函数，则在处理完毕信号后，接着从阻塞的系统返回。如果不指定该参数，中断处理完毕之后，read 函数读取失败。

SA_SIGINFO		
指示结构体的信号处理函数指针是哪个有效，如果 sa_flags包含该掩码，则sa_sigaction指针有效，否则是sa_handler指针有效（常用） 
```

#### SA_FLAGS的参数举例

##### SA_RESETHAND

```c
void sigFunc(int sigNum,siginfo_t *p,void *p1){
    printf("%d is coming\n",sigNum);
}
int main(){
    struct sigaction act;
    bzero(&act,sizeof(act));
    act.sa_sigaction=sigFunc;
    act.sa_flags=SA_SIGINFO|SA_RESETHAND;
    int ret=sigaction(SIGINT,&act,NULL);//act是传入参数
    while(1);
    return 0;
}
```

只能响应一次ctrl+c

##### SA_NODEFER

```c
void sigFunc(int sigNum,siginfo_t *p,void *p1){
	printf("before sleep,%d is coming\n",sigNum);
    sleep(3);
    printf("after sleep,%d is coming\n",sigNum);
}
int main(){
    struct sigaction act;
    bzero(&act,sizeof(act));
    act.sa_flags=SA_SIGINFO|SA_NODEFER;
    act.sa_sigaction=sigFunc;
    int ret=sigaction(SIGINT,&act,NULL);
    ret=sigaction(SIGQUIT,&act,NULL);
    while(1);
    return 0;
}
```

如果不加SA_NODEFER，此时连续发2号信号是无法打断的，必须要等待2号信号执行完

如果加了SA_NODEFER,再按ctrl+c就会立刻唤醒进程，sleep本身是设置了alarm的时间

信号处理函数类似函数压栈，连续ctrl+c压栈后会逐次弹出，但是在内核中还是按位存了1

2号信号和3号信号都互相打断，停止打断3秒后一次弹出所有的sleep

##### SA_RESTART

```c
void sigFunc(int sigNum,siginfo_t *p,void *p1){
    printf("%d is coming\n",sigNum);
}
int main(){
    struct sigaction act;
    bzero(&act,sizeof(act));
    act.sa_sigaction=sigFunc;
    act.sa_flags=SA_SIGINFO|SA_RESTART;
    int ret=sigaction(SIGINT,&act,NULL);//act是传入参数
    char buf[128]={0};
    ret=read(STDIN,buf,sizeof(buf));
    printf("ret=%d,buf=%s\n",ret,buf);
    return 0;
}
```

如果不用SA_RESTART，就会让read返回失败，ret的值为-1了

#### SA_MASK的使用举例

sa_mask就是临时阻塞集合，这个集合内的信号在其他信号的信号处理流程内是失效状态的

##### sigaddset()

下面演示在2号信号处理流程中传入3号信号，借助SA_MASK实现3号信号阻塞直到2号信号处理完才处理3号信号的过程

```c
void sigFunc(int sigNum,siginfo_t *p,void *p1){
	printf("before sleep,%d is coming\n",sigNum);
    sleep(3);
    printf("after sleep,%d is coming\n",sigNum);
}
int main(){
    struct sigaction act;
    bzero(&act,sizeof(act));
    act.sa_flags=SA_SIGINFO;
    act.sa_sigaction=sigFunc;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask,SIG_QUIT);//在2号信号的信号处理流程中阻塞3号信号
    int ret=sigaction(SIGINT,&act,NULL);
    while(1);
}
```

先发2号信号ctrl+c，再发3号信号ctrl+\会发现2号仍然会睡3秒，睡完会立刻进入3号信号的睡3秒

##### sigfillset()

9(杀死信号)和16(进程暂停)不能被sigfillset填入，即这两个信号是不允许被阻塞的

##### sigpending()

`sigpending`是系统调用，`sa_mask`的其他的函数都是位操作

将(被阻塞的)挂起的信号拿出来，比如上面的3号信号，主要用于在进程退出时检查是否还有没有处理的信号

必须有被阻塞的信号才能被sigpending拿出来

```c
void sigFunc(int sigNum,siginfo_t *p,void *p1){
    printf("before sleep %d is coming\n",sigNum);
    //在2号信号处理流程中发3号信号才能被侦测到3号信号挂起
    sleep(3);
    sigset_t pending;//从内核的pcb结构体拿出进程尚未处理的信号(被阻塞的即挂起的)   
    sigpending(&pending);//传地址只有8个字节，更高效
    if(sigismember(&pending,SIGQUIT)){
        printf("SIGQUIT is pending\n");
    }else{
        printf("SIGQUIT is not pending\n");
    }
    printf("after sleep %d is coming\n",sigNum);
}
int main(){
    struct sigaction act;
    bzero(&act,sizeof(act));
    act.sa_flags=SA_SIGINFO;
    act.sigacton=sigFunc;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask,SIGQUIT);//在2号信号的信号处理流程中阻塞3号信号
    int ret=sigaction(SIGINT,&act,NULL);
}
```

此时先发2号信号，再发3号信号，就会显示3号信号在挂起，稍后就会执行3号信号的信号处理流程，并且3号信号可以侦测3号信号自己

但是同种信号至多再执行一次：当前信号执行过程中至多再捕捉一次相同信号，以后除非执行完当前信号的信号处理流程，否则不会继续捕捉同种信号

#### 信号处理函数的参数

如果要传递参数给信号处理函数，就直接用全局变量

第三个参数`void *p1 `就是在用户态保存内核的上下文信息，从而在执行完信号处理函数后能回到原来的位置

```c
void sigFunc(int sigNum,siginfo_t *p,void *p1){
    printf("%d is coming,send pid=%d send uid=%d\n",signum,p->si_pid,p->si_uid);
}
```

自己的终端发2号信号会显示都是0



### sigprocmask

全程阻塞函数，被sigprocmask设置为阻塞的信号都处于未决态，可以被sigpending捕获到

常用于：

```
sigprocmask阻塞信号
加锁
关键代码
解锁
sigprocmask解除阻塞
```

```c
int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
```

参数 how 的值为如下 3 者之一： 

```
SIG_BLOCK ,将参数 2 的信号集合添加到进程原有的阻塞信号集合中 +=	
SIG_UNBLOCK ,从进程原有的阻塞信号集合移除参数 2 中包含的信号 	-=	
SIG_SETMASK，重新设置进程的阻塞信号集为参数 2 的信号集	=
```

参数 set 为阻塞信号集 ，注意是const的，因此是传入参数

参数 oldset 是传出参数，存放进程原有的信号集，通常为 NULL，如果想知道以前阻塞了哪些可以定义结构体把他取出来查看

```c
int main(){
    sigset_t procmask;
    sigemptyset(&procmask);
    sigaddset(&procmask,SIGINT);
    int ret=sigprocmask(SIG_BLOCK,&procmask,NULL);//阻塞2号信号
    sigset_t pending;
    sigemptyset(&pending);
    sigpending(&pending);
    sleep(3);//模拟关键代码
    if(sigismember(&pending,SIGINT)){
        printf("SIGINT is pending\n");
    }
    ret=sigprocmask(SIG_UNBLOCK,&procmask,NULL);//解除对2号信号的阻塞
    while(1);//此时可以用ctrl+c打断
}
```

### 信号的阻塞和忽略

```c
signal(SIGINT,SIG_IGN);//忽略信号
sigprocmask(SIG_BLOCK,&procmask);//阻塞信号
sleep(3);//模拟关键代码
sigprocmask(SIG_UNBLOCK,&procmask);//解除阻塞
signal(SIGINT,SIG_DFL);//回到默认处理方式
```

如果在信号被忽略的过程内发出了该信号，该信号是不会被处理的。因为发出信号时由于是忽略，位图上的1会改成0

信号的**设定**是异步的，本质是内核的数据结构发生了变化，因此`sig_ign`和`sigprocmask`谁写在前谁写在后没有影响

但是信号的处理方式上，阻塞的优先级要高于忽略，因此如果某个信号即被设置了忽略，又被设置了阻塞，最终接收到该信号会被识别为阻塞

通常情况下只有解除了信号的阻塞，才会继续执行信号的处理动作，但是如果阻塞和忽略同时出现，在程序结束运行前没有解除忽略的话，被阻塞的信号在阻塞结束后也不会执行处理动作，因为忽略被置位了，无法执行处理函数

### 永久等待函数

比如read读pipe，此时可能在阻塞，如果此时传递了一个信号给该进程：

```
1、停止read(放弃数据)
2、执行信号处理流程(handler)
3、重启read
```

signal支持上述流程，而sigaction 默认read失败，read会return -1，必须要将`sa_flags`的`SA_RESTART`置位

### 可重入函数与不可重入函数

#### 可重入函数

在func函数中要执行信号处理函数，而信号处理函数又调用了func

如果上述的重复使用对func的执行结果没有影响(因为信号的传递有随机性，不能确定是在func函数执行哪条语句开始执行信号处理函数，而不管在那条语句处转而执行信号处理函数，最后得到的结果都相同，就称为无影响)

read和write是可重入函数

#### 不可重入函数

使用静态、全局、文件对象、使用堆空间、传递某些数据的指针

而printf是不可重入函数，因此调试时尽量不要用printf

# day15

## Linux内存机制

### 计算机系统结构

#### 硬件

##### cpu		抽象出进程来管理cpu

```
控制器、运算器		  运行代码的地方
寄存器				指令存放的地方
高速缓存			cache
```

##### 主存储器	抽象出虚拟内存

内存

##### IO设备	抽象出文件系统

磁盘、键盘等

#### 软件

##### 系统软件

开发应用软件或支持应用软件的运行

如os、编译器、数据库等

##### 应用软件

### 虚拟内存和内存之间的关系

#### 虚拟内存	(va虚拟地址)

进程的地址空间(若干地址，按字节编址)

32位： 0~2^32 -1		4GB内存

64位： 0~2^64 -1		

实际上内存并没有分配那么多空间

#### 内存	(pa物理地址)

按页把内存分隔开，可以把内存看作一个数组元素是页的数组

按字节编址，每个字节都有一个地址

#### 映射

虚拟内存需要在内存上找到一块空间存放进程的数据

### 虚拟内存的使用

进程执行时(cpu)使用的都是进程的虚拟地址(va)，因此就需要一个硬件设备(MMU存储器管理单元，地址翻译)将va转换成pa

### 虚拟内存的存储

将虚拟内存存储在**磁盘**中，但是由于磁盘的读写速度很慢，因此就也要将虚拟内存也分页

虚拟内存的页有三种状态：

未分配：磁盘中还没有被使用的页，比如进程刚创建时，虚拟内存的很多部分都没有被使用

缓存：这一页的数据正在被使用，需要被拷贝到内存中，数据的处理全部都再内存中处理完再写回磁盘，提高执行速度，本质是空间换时间

未缓存：已经被使用过的现在不在内存中的数据所在的页

### 页表

为了能关联起虚拟内存使用的磁盘和内存，需要在内存中构建一个该虚拟内存的索引表(页表)，表中记录了虚拟内存的页的状态、在磁盘中的页号(也就是虚拟内存的页号)、在内存中的页号

#### 页表的特征

数组，数组下标是虚拟页号，数组存了结构体，结构体成员包含虚拟页状态、物理页号

#### 一个页表有多大？

数组的项数：进程有多少个虚拟内存页

对于32位系统，每一页4k字节，一共有2^(10+10)页，即页表一共占用了内存中的2^20*4(4是因为地址是4个字节32位的)即4MB的大小

如果是64位系统，很明显就无法放在内存中了，因此就需要把页表分层，即用页表查页表

### 最简单的地址翻译

通过页表把需要转换的虚拟页对应的把物理页号放在cpu的寄存器(PTBR页表基址寄存器)中

一页4k，按字节编址，除了找到页号，还要找到他在这一页的位置(偏移)

对于虚拟地址：虚拟页号+偏移

通过虚拟页号+PTBR寄存器的物理页号找到内存中的页

通过虚拟地址的偏移找到内存中页的偏移位置

而页表是存放在内存中的，每次进行地址翻译都需要查找内存，而高速缓存的速度更快

由于高速缓存的大小不足以放入整个页表，因此就可以把已经查询过的页表的某个数组成员放入高速缓存，(因此编写程序尽量写在同一页中，减少内存查询页表次数)

因此就引入了基于局部性原理的TLB(翻译后备缓冲)即快表

在TLB中，把虚拟页号分为标记和索引(地址的后几位，因为虚拟页一般连续分配如0xaaaa1234,0xaaaa1235之类的)，对于进程运行时需要查询的索引，如果在TLB中的标记相同，就直接把TLB中存储的物理页号拿出来，不需要查内存的页表了

![image-20200311114310971](D:\TyporaPic\复习笔记Linux\image-20200311114310971.png)

### 虚拟地址空间和物理地址空间的转化--页目录机制(32位系统下)

```
不同进程相同的虚拟地址，可以映射不同的物理地址：通过写时复制即可

不同进程相同的虚拟地址，可以映射相同的物理地址：比如共享内存(先连接再fork)

不同进程不同的虚拟地址，可以映射相同的物理地址：mmap
```

每个进程都有起始页目录地址PGD(Page Global Directory)，mm_struct就是将虚拟地址转换成物理地址

前10位页目录偏移，中间10位页表偏移，后12位页内偏移

PGD指向一个页(4k)，页内有1024个指针(4B)，每个的初始化都是0

根据前十位1fe(十进制是510)PGD偏移到页目录的第510的位置，如果这里映射的物理地址是0，就会发生缺页异常，就会用内核的申请物理地址，申请一个新的页表，这个页又可以存1024个指针，将这个新创建的页表的起始地址填到页目录的510的位置，

再根据中间十位89(十进制137)偏移到新创的页表的137位，如果还是0就再申请一个页，用来存放真正的物理地址，

根据最后12位确定存放在页的哪里

```
7f 88 9d 91
0111 1111 10   00 1000 1001   1101 1001 0001
```

![image-20200309121030761](D:\TyporaPic\复习笔记Linux\image-20200309121030761.png)

进程在执行时一定会先用到物理内存，比如代码段

多个进程的页表页可以指向同一个物理地址

每次申请一个虚拟地址，就会在mm_struct的vma新增一个链表结点，这个结点包括起始地址startAddr和大小size

如果页内偏移量超过了4k，就要新创建一个页



# day16

## 用程序发送信号

### kill信号发送函数

```c
#include <sys/types.h> 
#include <signal.h> 
int kill(pid_t pid, int sig);
```

参数 pid 为将要接受信号的进程的 pid，可以通过 getpid()函数获得来给自身发送信号，还可以发送 信号给指定的进程，此时 pid 有如下描述： 

```
pid > 0 将信号发给 ID 为 pid 的进程 
pid = 0 将信号发送给与发送进程属于同一个进程组的所有进程(包括发送进程本身) 
pid < 0 将信号发送给**进程组** ID 等于 pid 绝对值的所有进程(进程需要对此进程组有发送信号的权限即两个uid相同) 
pid = -1 将信号发送给该进程有权限发送的系统里的所有进程(如果是root就会进行注销，因为底层有其他程序保护，即只是关闭所有进程再重新启动) 
```

参数 sig 为要发送的信号  如果成功，返回 0，否则为-1

#### 对于fork的进程，必须要发送给进程组(负号)才能保证父子进程都收到

## 计时器

所有信号都具有唤醒功能

alarm 是不可重入函数

### 睡眠函数

```c
#include <unistd.h> 
unsigned int sleep(unsigned int seconds); 
void usleep(unsigned long usec); 
```

函数 sleep 让进程睡眠 seconds 秒，函数 usleep 让进程睡眠 usec 微秒。 

sleep 睡眠函数内部是用信号机制进行处理的，用到的函数有： 

```c
#include <unistd.h> 
unsigned int alarm(unsigned int seconds); 
//告知自身进程，要进程在 seconds 秒后自动产生一个 SIGALRM 的信号 
int pause(void); //将自身进程挂起，直到有信号发生时才从 pause 返回
```

#### 用alarm实现sleep

kill -l 可以查看各个信号

```c
void sigFunc(int sigNum){
    printf("i am awake\n");
}
int main(){
    int ret=signal(SIGALARM,sigFunc);
    alarm(3);//设定睡眠时间，进程还会继续执行
    pause();//直接把进程移到阻塞队列,直到程序收到信号才会解除阻塞
    return 0;
}
```

sleep和alarm最好只同时使用其中一个，否则会导致提前唤醒

```c
alarm(3);
sleep(10);
```

上面程序的执行结果为沉睡3秒，因为alarm在3秒过后会发送SIGALARM信号，唤醒进程解除阻塞

### 时钟处理与三种计时器

Linux 为每个进程维护 3 个计时器，分别是真实计时器、虚拟计时器和实用计时器。 

```
真实计时器计算的是程序运行的实际时间；	---直接 

虚拟计时器计算的是程序运行在用户态时所消耗的时间(可认为是实际时间减掉(系统调用和程序睡眠所消耗)的时间)；		---需要了解内核 

实用计时器计算的是程序处于用户态和处于内核态所消耗的时间之和。记录的是消耗的时间片之和						---常用
```

例如：有一程序运行，在用户态运行了 5 秒，在内核态运行了 6 秒，还睡眠了 7 秒，则真实计算器计算的结果是 18 秒，虚拟计时器计算的是 5 秒，实用计时器计算的是 11 秒。 

用指定的初始间隔和重复间隔时间为进程设定好一个计时器后，该计时器就会定时地向进程发送时钟信号。3 个计时器发送的时钟信号分别为`SIGALRM`,`SIGVTALRM `和 `SIGPROF`。 

#### 用到的函数与数据结构

```c
#include <sys/time.h> 
int getitimer(int which, struct itimerval *value); //获取计时器的设置 
int setitimer(int which, const struct itimerval *value, struct itimerval *ovalue); //设置计时器 
```

参数 which 指定哪个计时器，可选项为 ITIMER_REAL(真实计时器)、ITIMER_VIRTUAL(虚拟 计时器、ITIMER_PROF(实用计时器)) 

参数 value 为一结构体的**传出参数**，用于传出该计时器的初始间隔时间和重复间隔时间 

参数 ovalue 为一结构体传出参数，用于传出以前的计时器时间设置。 

返回值：如果成功，返回 0，否则-1 

```c
struct itimerval { 
struct timeval it_interval; /* next value */ //重复间隔 
struct timeval it_value; /* current value */ //初始间隔 
}; 
```

**性能测试就是对信号进行采样，每隔一定秒数采样一次进行比较**

#### 真实计时器

使用的是`SIGALARM`信号，因此如果是在真实计时器下让进程阻塞，不要用sleep，因为真实计时器返回的是SIGALRM信号，会提前唤醒，可以用read阻塞读

```c
void sigFunc(int signum){
    time_t now;
    time(&now);//获取距离19700101的秒数
    printf("%s\n",ctime(&now));//ctime自己也会再打一个\n
}
int main(){
    signal(SIGALRM,sigFunc);
    struct itimerval t;
    bzero(t,sizeof(t));
    t.it_value.tv_sec=2;	//初始间隔2秒
    t.it_interval.tv_sec=3;	//重复间隔3秒
    int ret;
    sigFunc(0);		//可以不用再写一次，因为这个函数不仅仅是内核能调用，本进程也可以调用
    ret=setitimer(ITIMER_REAL,&t,NULL);
    ERROR_CHECK(ret,-1,"setitimer");
    char buf[128]={0};
    read(STDIN_FILENO,buf,sizeof(buf));
    printf("buf=%s\n",buf);
    while(1);
    return 0;
}
```

在输入字符串前每3秒打印一次，而top查看运行态进程无法找到该进程，该进程现在在睡眠态，同时，输入字符串不会打断3秒一次的计时，需要ctrl+c断开

#### 实用计时器

使用的是SIGPROF信号

如果程序没有消耗时间片则不会计时，即睡眠态不会计时

```c
void sigFunc(int signum){
    time_t now;
    time(&now);//获取距离19700101的秒数
    printf("%s\n",ctime(&now));//ctime自己也会再打一个\n
}
int main(){
    signal(SIGPROF,sigFunc);
    struct itimerval t;
    bzero(t,sizeof(t));
    t.it_value.tv_sec=2;	//初始间隔2秒
    t.it_interval.tv_sec=3;	//重复间隔3秒
    int ret;
    sigFunc(0);		//可以不用再写一次，因为这个函数不仅仅是内核能调用，本进程也可以调用,也可以用kill(0,SIGPROF);但是是系统调用不够高效
    ret=setitimer(ITIMER_PROF,&t,NULL);
    ERROR_CHECK(ret,-1,"setitimer");
    char buf[128]={0};
    read(STDIN_FILENO,buf,sizeof(buf));
    printf("buf=%s\n",buf);
    while(1);
    return 0;
}
```

上述程序就无法每隔3秒计时一次，因为程序阻塞在了read处处于睡眠态，没有消耗时间片，就不会被计算时间

如果用了sleep

```c
void sigFunc(int signum){
    time_t now;
    time(&now);//获取距离19700101的秒数
    printf("%s\n",ctime(&now));//ctime自己也会再打一个\n
}
int main(){
    signal(SIGPROF,sigFunc);
    struct itimerval t;
    bzero(t,sizeof(t));
    t.it_value.tv_sec=3;	//初始间隔3秒
    t.it_interval.tv_sec=4;	//重复间隔4秒
    int ret;
    sigFunc(0);		
    ret=setitimer(ITIMER_PROF,&t,NULL);
    ERROR_CHECK(ret,-1,"setitimer");
    char buf[128]={0};
    read(STDIN_FILENO,buf,sizeof(buf));
    printf("buf=%s\n",buf);
    sleep(5);//3+5=8
    while(1);
    return 0;
}
```

则执行程序后，8秒后第一次打印，因为初始间隔是3秒，sleep是5秒，8秒的时候时间片消耗满了3秒就会打印了

如果是单核的情况，CPU不可能只为这一个进程分配时间片，因此实际的打印时间可能会比预计的时间要久，因为实用计时器统计的是本进程使用的时间片

#### 虚拟计时器

使用的是SIGVTALRM信号

相当于在实用计时器-内核态消耗的时间，但在内核中其实时间很短，因此不怎么区分的开虚拟和实用

```c
long times=0;
void sigFunc(int signum){
    time_t now;
    time(&now);//获取距离19700101的秒数
    printf("%s\n times=%ld\n",ctime(&now),times);//ctime自己也会再打一个\n
}
int main(){
    signal(SIGVTALRM,sigFunc);
    struct itimerval t;
    bzero(t,sizeof(t));
    t.it_value.tv_sec=1;	//初始间隔
    t.it_interval.tv_sec=1;	//重复间隔
    int ret;
    sigFunc(0);		//可以不用再写一次，因为这个函数不仅仅是内核能调用，本进程也可以调用,也可以用kill(0,SIGPROF);但是是系统调用不够高效
    ret=setitimer(ITIMER_VIRTUAL,&t,NULL);
    ERROR_CHECK(ret,-1,"setitimer");
    sleep(3);
    double d,f;
    while(1){
        f=1234568.26;//为了防止立即数直接生成好，每次都进行赋值操作再相乘
        d=892.126*f;
        times++;
    }
    return 0;
}
```

# day19

## 线程

线程是进程的基本调度单元，每个进程都有一个main线程，优先级和调度策略是分配给线程的

线程必须依附于进程，不能独立存在，线程会与同进程中的其他线程共享进程空间｛堆 代码 数据 文件描述符 信号等｝，只拥有自己的栈空间

程序的执行本质就是函数的压栈弹栈，如果想要并行执行，就需要给新启动的子线程就需要给一个新的函数入口地址，即可和main线程同时入栈

线程执行开销小，占用的 CPU 少，线程之间的切换快，线程启动时不需要构造整个task struct 结构体，只需要创建线程独有的成员，但不利于资源的管理和保护，类似一个篮子的鸡蛋，一个线程崩溃，整个进程都会崩溃

### 线程和进程的区别

进程是程序执行的一个实例，进程的目的担当操作系统中资源分配的基本单位

线程是进程中的一个执行流，更加接近于执行体的概念，是cpu调度的基本单位，线程和同属于一个进程的其他线程共享进程所拥有的全部资源

进程---资源分配的最小单位，线程---程序执行的最小单位

### 使用的线程库

nptl线程库

使用时在编译时需要加 -lpthread 参数	，因为是动态库，Makefile文件加在$(CC)那一行即可

man pthread_create 会发现-pthread参数也可以

线程库的接口不再使用perror，因为这些接口没有改变errnum，成功返回0，失败返回错误编号

### 获取线程id

```c
pthread_t pthread_self(void);//获取线程id
```

### 线程的创建

创建线程其实就是确定调用该线程函数的入口点

nptl线程库创建的是一对一(一个用户级线程对应一个核心级线程)

```c
#include <pthread.h>
int pthread_create(pthread_t* thread, pthread_attr_t * attr, void *(*start_routine)(void *), void * arg);//线程的创建
```

参数 thread 是传出参数，保存新线程的标识id；

参数 attr 是一个结构体指针，结构中的元素分别指定新线程的运行属性,attr 可以用 pthread_attr_init 等函数设置各成员的值，但通常传入为 NULL 即可；表示是普通的线程

参数 start_routine 是一个函数指针，指向新线程的入口点函数，线程入口点函数带有一个 void *的参数由 pthread_create 的第 4 个参数传入；

参数 arg 用于传递给第 3 个参数指向的入口点函数的参数，可以为 NULL，表示不传递。(c++封装多传递类指针this)

#### 线程的属性

在创建线程的第二个参数中指明线程具有的相关属性

##### PTHREAD_CREATE_DETACHED 

`__detachstate `表示新线程是否与进程中其他线程脱离同步，如果置位则新线程不能用` pthread_join()`来同步，且在退出时自行释放所占用的资源。

缺省为 `PTHREAD_CREATE_JOINABLE `状态即可以被其他线程回收

这个属性也可以在线程创建并运行以后用 `pthread_detach()`来设置，而一旦设置为`PTHREAD_CREATE_DETACHED `状态(即由系统回收，不需要其他线程join来回收)（不论是创建时设置还是运行时设置）则不能再恢复到`PTHREAD_CREATE_JOINABLE`状态。

```c
pthread_t pthid;
pthread_attr_t attr;
pthread_attr_init(&attr);
pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
pthread_create(&pthid,&attr,threadFunc,NULL);//设置子线程为detach状态，即无法被主线程join

//pthread_detach(pthid);//或在创建完成后用detach函数设置，或者在子线程用pthread_self()拿到线程id自己设置

pthread_join(pthid,NULL);//子线程处于detach状态不会被join了，因此ret会异常，直接运行到下面的代码
```

detach只是设置了一个分离状态，线程内的其他代码还是会继续执行完的

detach 之后子线程的返回值就没用了，因为其他线程join不到了，也就拿不到返回值了

##### 设置调度策略

__schedpolicy，表示新线程的调度策略

进程间的调度其实是对线程的调度，进程主要用来分配资源，真正使用资源的还是各个线程

主要有：

```
SCHED_OTHER	（正常、非实时）
SCHED_RR	（实时、轮转法）
SCHED_FIFO	（实时、先入先出）
```

缺省为 SCHED_OTHER

##### 设置线程的运行优先级

 __schedparam

一个sched_param 结构，目前仅有一个 sched_priority 整型变量表示线程的运行优先级。这个参数仅当调度策略为实时（即 SCHED_RR 或 SCHED_FIFO）时才有效，并可以在运行时通过pthread_setschedparam()函数来改变，缺省为 0。

##### 设置线程优先级的有效范围

__scope，表示线程间竞争 CPU 的范围，也就是说线程优先级的有效范围。

PTHREAD_SCOPE_SYSTEM 和 PTHREAD_SCOPE_PROCESS

前者表示与系统中所有线程一起竞争 CPU 时间

后者表示仅与同进程中的线程竞争 CPU

目前 Linux 仅实现了PTHREAD_SCOPE_SYSTEM 一值。

### 线程的退出

```c
void pthread_exit(void *retval);//线程的退出
```

函数 pthread_exit 表示线程的退出。其参数可以被其它线程用 pthread_join 函数捕获。常用于判断线程的执行状态，如成功返回0，不同的错误返回不同的结果

主线程执行结束会释放所有该进程使用的资源，即主线程结束，子线程自动消亡，而标准输入标准输出也都会关闭

#### exit和pthread_exit

exit函数是针对进程而言的，因此使用exit函数会结束整个进程，因此`exit()`函数只能在主线程使用。

phtread_exit则是子线程退出时而使用的，并且可以返回一些参数给主线程

对于进程，只能父进程wait子进程，而对于线程，除了不能join主线程，其他线程间可以互相join的

### 线程的等待退出join

线程从入口点函数自然返回，或者主动调用 pthread_exit()函数，都可以让线程正常终止，函数返回值可以被其它线程用 pthread_join 函数获取

```c
#include <pthread.h>
int pthread_join(pthread_t thid, void **thread_return);
```

该函数是一个阻塞函数，一直等到参数 thid 指定的线程返回；与多进程中的 wait 或 waitpid 类似。

thread_return 是一个传出参数，接收线程函数的返回值。如果线程通过调用 pthread_exit()终止，则pthread_exit()中的参数相当于自然返回值，照样可以被其它线程用 pthread_join 获取到，如果线程是被其他线程取消的，返回值为-1

thid 传递 0 值时，join 返回 ESRCH 错误

```c
void *threadFunc(void *p){
    p=malloc(20);
    bzero(p,strlen(p));
    strcpy((char *)p,"hello");
    pthread_exit(p);
}
void test(){
    pthread_t pthid;
    int ret=pthread_create(&pthid,NULL,threadFunc,NULL);
    char *pstr;
    pthread_join(pthid,(void **)&pstr);//*&pRet=p;	二级指针必须要强转，因为void**可以偏移，每次偏移一个void*指针，而void*不能偏移
    printf("pstr=%s\n",pstr);
}
```

线程一般用于逻辑处理，上述的子线程开辟空间工作用的比较少，工作常用返回值返回子线程处理的是否从正确的分支返回

### 线程间数据的传递

借助`pthread_create`的第四个参数传递

任何类型的指针转换成`void *`类型都不需要强转

堆空间的数据直接传递指针即可

对于栈空间上的数据，由于线程同属于一个进程，虽然栈对每个线程是私有的，但是同一个进程内的线程对整个进程地址空间的读写权限是相同的，因此也只需要传递指针

```c
void *threadFunc(void *p){
    printf("value=%d\n",*(int *)p);
}
void test(){
    pthread_t pthid1,pthid2;
    int f=4;
    int ret=pthread_create(&pthid1,NULL,threadFunc,&f);
    f=5;
    ret=pthread_create(&pthid2,NULL,threadFunc,&f);
    pthread_join(pthid1,NULL);
    pthread_join(pthid2,NULL);
}
```

由于线程执行的并发性，子线程和main线程同时执行，而子线程执行printf打印之前,main线程就已经执行到了val=2，因此两个线程都会打印值为5，而不是一个4一个5

但是如果使用long类型传递参数，在64位系统下，long类型和指针的内存大小都为8字节，因此可以直接把long类型的变量的值作为指针存放的地址值，这样在传递的时候传递的就是变量的值而不是变量的地址，也就不会随主线程值的变化而变化了

```c
void *pthreadFunc(void *p){
    printf("value=%ld\n",(long)p);
}
void test(){
    pthread_t pthid1,pthid2;
    long f=4;
    int ret=pthread_create(&pthid1,NULL,threadFunc,(void *)f);//不加类型转换会有warning
    f=5;
    pthread_create(&pthid2,NULL,threadFunc,f);
    pthread_join(pthid1,NULL);
    pthread_join(pthid2,NULL);
}
//第二个线程执行的比第一个块，因为第二个分配的时间片还没有用完就已经输出了，然后才轮到第一个子线程继续执行printf
```

同时要注意如果子线程内部要对传递的数据进行修改，一定要用指针类型的接参数，否则不会生效的

```c
void *threadFunc(void *p){
    int *val=(int *)p;//注意这里传递的是指针而不是值
    //int val=*(int *)p;//错误
    for(int i=0;i!=100;++i){
        *val+=1;
    }
}
```

### 线程的取消cancel

因为信号的处理对于同一个进程的线程，是共享的

通过向其他线程发送cancel信号可以取消该线程，但是不要用子线程对主线程发送

发送取消信号后，子线程要运行到**取消点**才会检查是否有取消信号，随后进行取消操作。

线程在while(1)的时候无法取消，因为没有取消点，必须在代码块中加取消点

增加 man 信息 ，apt install manpages-posix-dev

线程的终止其实并不是一个很好的方式，因为本质是一个线程强行杀另一个线程，不符合设计

```c
int pthread_cancel(pthread_t thread);
```

线程被cancel要做资源清理

cancel的线程id填错了会返回失败，其他情况都会成功，但是子线程是否被cancel成功与返回值无关，因为子线程要运行到取消点才可以进行cancel，是异步的

```c
void *threadFunc(void *p){
    //printf("i am child\n");//printf调用了系统调用write，是取消点
    while(1);//没有取消点
}
void test(){
    pthread_t pthid;
    int ret=pthread_create(&pthid,NULL,threadFunc,NULL);
    pthread_cancel(pthid);
    long ret;
    pthread_join(pthid,(void **)&ret); //如果一个子线程被cancel，pthread_join拿到的线程的返回值是-1
    printf("ret=%ld\n",ret);
}
```

使用`ps -elf |grep xxx` 只能看到进程，如果要看到线程就要`ps -elLf |grep xxx`	加个`-L`参数

此时在`/proc/xxx/task`就会发现有两个文件，即线程控制表

在ps里有futex_的就是主线程，因为此时子线程在while(1)

man futex	用户态快速锁，监控用户态

### 线程终止清理函数

每个线程都有自己的清理函数栈

如果子线程申请了堆空间，cancel后就无法free了，因此需要资源清理函数，线程一旦被cancel，就会去执行清理函数

一旦线程被清理，就会到线程清理函数处，如果不为空，就弹出该函数，进行清理

```c
void pthread_cleanup_push(void (*routine) (void *), void *arg);
void pthread_cleanup_pop(int execute);
```

execute如果为真，即弹出一个处理函数并执行，如果为0则弹出一个处理函数但是不执行

清理函数必须成对出现，因为清理函数其实是个宏，push和pop分别是宏的各一半部分(注意大括号{ })

```c
#define pthread_cleanup_push(routine,arg) \
 { 
struct _pthread_cleanup_buffer _buffer; \
_pthread_cleanup_push (&_buffer, (routine), (arg)); 

#define pthread_cleanup_pop(execute) \
_pthread_cleanup_pop (&_buffer, (execute)); 
}
```

```c
void cleanup(void *p){
    free(p);
    printf("free success\n");
}
void *threadFunc(void *p){//线程函数，这个函数执行完毕，该线程就结束了
    p=malloc(20);
    pthread_cleanup_push(cleanup,p);
    sleep(1);//是取消点，确保不会在主线程执行到cancel之前就运行结束
    printf("cannot see these words\n");//执行到取消点就会转去调用清理函数了，随后子线程就已经没了
    pthread_cleanup_pop(1);//为了保证不会编译报错，因为push和pop是一对宏
    return NULL;//return不会触发清理函数，因为不是nptl库函数
}
void test(){
    pthread_t pthid;
    pthread_create(&pthid,NULL,threadFunc,NULL);
    pthread_cancel(pthid);
    pthread_join(pthid,NULL);
}
```

#### 清理函数会被得到执行的3种情况

push只是把清理函数压栈了，真正得到执行是在以下情况：

1、线程被取消pthread_cancel()	注意取消点的判定

2、线程通过pthread_exit()退出

3、pthread_cleanup_pop(1)	即把栈对象的标志位置为1	如果这句之前都没有取消点或者退出函数，则到这里会执行清理函数，如果是这种情况触发的清理函数，在清理函数执行完毕之后线程还会继续执行下去直到被主线程`pthread_cancel`、子线程自身`pthread_exit`或执行到函数体末尾

#### 清理函数不会被执行的情况

1、pthread_cleanup_pop(0)	此时把push进去的栈对象的标志位flag改为了0，pop出的时候就不会执行了

2、return;	return是c语言库的，不是nptl库中的，没有做响应的处理

#### 清理函数的执行顺序

和栈的原理一样，先入栈的后执行

#### 需要在线程执行体做资源清理时

如果在子线程的执行过程中需要对资源进行释放，推荐使用清理函数，在资源定义的地方`pthread_cleanup_push`压栈，在不需要使用资源之后的位置调用`pthread_cleanup_pop`使用之前压入栈的清理函数将资源清理



## 线程的互斥

### 线程的互斥mutex

man futex	整个nptl线程库都用的这个接口

互斥，又称为间接制约关系，是指系统中的某些共享资源，一次只允许一个线程访问。当某一个线程正在访问临界资源时，其他线程必须等待。需要使用互斥锁

#### 创建和销毁互斥锁mutex

##### 静态方式：

POSIX 定义了一个宏 PTHREAD_MUTEX_INITIALIZER 来静态初始化互斥锁，方法如下：

```c
 pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 
```

在 Linux Threads 实现中，pthread_mutex_t 是一个结构，而 PTHREAD_MUTEX_INITIALIZER 则是一个宏常量。

##### 动态方式：

动态方式是采用 pthread_mutex_init()函数来初始化互斥锁，API 定义如下：

```c
#include <pthread.h>
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *mutexattr)
```

 其中 mutexattr 用于指定互斥锁属性，如果为 NULL 则使用缺省属性。通常为 NULL 

pthread_mutex_destroy()用于注销一个互斥锁，API 定义如下：

```c
int pthread_mutex_destroy(pthread_mutex_t *mutex);
```

销毁一个互斥锁即意味着释放它所占用的资源，且要求锁当前处于开放状态。由于在 Linux 中，互斥锁并不占用任何资源，因此 Linux Threads 中的 pthread_mutex_destroy()除了检查锁状态以外（锁定状态则返回 EBUSY）没有其他动作。

传递的时锁的地址，要确保使用的是同一把锁

同一个线程不能连续对同一把锁加锁两次，因为第二次加锁发现锁处于上锁状态就会阻塞住

#### 锁的常用操作

```c
int pthread_mutex_lock(pthread_mutex_t *mutex);//加锁
int pthread_mutex_unlock(pthread_mutex_t *mutex);//解锁
int pthread_mutex_trylock(pthread_mutex_t *mutex);//测试加锁
```

pthread_mutex_lock：

加锁，不论哪种类型的锁，都不可能被两个不同的线程同时得到，而必须等待解锁。

对于普通锁类型，解锁者可以是同进程内任何线程；而检错锁则必须由加锁者解锁才有效，否则返回 EPERM；

对于嵌套锁，文档和实现要求必须由加锁者解锁，但实验结果表明并没有这种限制，这个不同目前还没有得到解释。

在同一进程中的线程，如果加锁后没有解锁，则任何其他线程都无法再获得锁。



pthread_mutex_unlock：

根据不同的锁类型，实现不同的行为：

对于快速锁，pthread_mutex_unlock 解除锁定；

对于递规锁，pthread_mutex_unlock 使锁上的引用计数减 1；

对于检错锁，如果锁是当前线程锁定的，则解除锁定，否则什么也不做。



pthread_mutex_trylock：

语义与 pthread_mutex_lock()类似，不同的是多次加锁不会阻塞，在锁已经被占据时会返回 EBUSY而不是挂起等待。

#### 使用互斥锁保证同时相加的稳定性

```c
typedef struct {
    int val;
    pthread_mutex_t mutex;
}Data_t;
void *threadFunc(void *p){
    Data_t *pdata=(Data *)p;
    for(int i=0;i!=100000;++i){
        pthread_mutex_lock(&p->mutex);
        ++p->val;
        pthread_mutex_unlock(&p->mutex);
    }
    pthread_exit(NULL);
}
void test(){
    pthread_t pthid;
    Data_t data;
    bzero(&data,sizeof(Data_t));
    data.val=0;
    pthread_mutex_init(&data.mutex,NULL);
    struct timeval start,end;
    gettimeofday(&start,NULL);
    pthread_create(&pthid,NULL,threadFunc,&data);
    for(int i=0;i!=100000;++i){
        pthread_mutex_lock(&data.mutex);
        ++data.val;
        pthread_mutex_unlock(&data.mutex);
    }
    pthread_join(pthid,NULL);//等待子线程结束，期间处于睡眠态，即回收子线程的实体
    gettimeofday(&end,NULL);
    //pthread_self()获取当前线程id，这里获取的是nptl分配的pid(本进程唯一)，而不是操作系统内核的pid即ps显示的(操作系统全局唯一)
    printf("i am main thread %d，val=%d, use time =%ld\n",pthread_self(),threadInfo.val,(end.tv_sec-start.tv_sec)*1000000 +end.tv_usec-start.tv_usec);//秒数不够精确，因此输出结果为微秒，10^-6秒
}
```

### 使用锁要注意的问题

#### 如果主线程加锁，子线程解锁，是否可以解锁

可以解锁，加锁和解锁都是对锁的状态进行修改即读写，只要拿到的权限是可读写就可以，但是一般不会这样用，因为锁的目的就是互斥使用

#### cancel以后如何清理锁资源

使用线程清理函数`pthread_cleanup_push/pop`

把unlock放到清理函数中

```c
void cleanup(void *p){
    pthread_mutex_unlock((pthread_mutex_t *)p);
    printf("unlock success\n");
}
void *threadFunc(void *p){
    Data_t *pdata=(Data_t *)p;
    pthread_mutex_lock(&pdata->mutex);//一个线程会阻塞在这里，直到另一个线程解锁，该线程才会继续执行到取消点进行解锁
    pthread_cleanup_push(cleanup,&p->mutex);//用户态的锁，因此必须传递对应的地址
    sleep(2);//取消点
    pthread_cleanup_pop(1);//这样和lock配对的是pop了而不是unlock，可以避免加锁一次解锁两次
    printf("you cannot see these\n");//在sleep的时候被cancel了
    pthread_exit(NULL);
}
void test(){
    pthread_t pthid1,pthid2;
    Data_t data;
    bzero(&data,sizeof(data));
    pthread_mutex_init(&data.mutex,NULL);
    pthread_create(&pthid1,NULL,threadFunc,&data);
    pthread_create(&pthid2,NULL,threadFunc,&data);
    sleep(1);
    pthread_cancel(pthid1);
    pthread_cancel(pthid2);
    pthread_join(pthid1);
    pthread_join(pthid2);
}
```

第一个线程的解锁是要等待1秒的，但是第二个线程的解锁是紧跟着第一个线程的解锁，这是因为在主线程的sleep(1)的时候两个cancel信号都发出了，第二个线程当时阻塞在lock处，获得锁运行到sleep触发了取消点，也就跟着解锁了

### 互斥锁属性设置

互斥锁的属性在**创建**锁的时候指定，不同的锁类型在试图对一个已经被锁定的互斥锁加锁时表现不同也就是是否阻塞等待。

#### PTHREAD_PROCESS_SHARED

进程间共享同一把锁

#### PTHREAD_MUTEX_TIMED_NP

这是缺省值（直接写 NULL 就是表示这个缺省值），也就是普通锁(或快速锁)。当一个线程加锁以后，其余请求锁的线程将形成一个阻塞等待队列，并在解锁后按优先级获得锁。这种锁策略保证了资源分配的公平性

#### PTHREAD_MUTEX_RECURSIVE

嵌套锁，允许同一个线程对同一个锁成功获得多次，并通过多次 unlock 解锁。如果是不同线程请求，则在加锁线程解锁时重新竞争。

初始化一个嵌套锁：

```c
int main(){
    pthread_mutex_t mutex;
    pthread_mutexattr_t mattr;
    int ret=pthread_mutexattr_init(&mattr);
    THREAD_ERROR_CHECK(ret,"pthread_mutexattr_init");
    pthread_mutexattr_settype(&mattr,PTHREAD_MUTEX_RECURSIVE);//允许一个线程对一把锁连续加锁
    pthread_mutex_init(&mutex,&mattr);
    pthread_mutex_lock(&mutex);
    ret=pthread_mutex_lock(&mutex);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_lock");
    printf("you can see me\n");
    return 0;
}
```

#### PTHREAD_MUTEX_ERRORCHECK

检错锁，如果同一个线程请求同一个锁，则返回 EDEADLK，否则与 PTHREAD_MUTEX_TIMED 类型(默认)动作相同。这样就保证当不允许多次加锁时不会出现最简单情况下的死锁。如果锁的类型是快速锁，一个线程加锁之后，又加锁，则此时就是死锁。

只能用来检测同一个线程加锁两次同一个锁

```c
int main(){
    pthread_mutex_t mutex;
    pthread_mutexattr_t mattr;
    int ret=pthread_mutexattr_init(&mattr);
    THREAD_ERROR_CHECK(ret,"pthread_mutexattr_init");
    pthread_mutexattr_settype(&mattr,PTHREAD_MUTEX_ERRORCHECK);//第二次加锁就会报错了
    pthread_mutex_init(&mutex,&mattr);
    pthread_mutex_lock(&mutex);
    ret=pthread_mutex_lock(&mutex);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_lock");
    printf("you cannot see me\n");
    return 0;
}
```

### 进程间使用互斥锁访问临界资源

通过共享内存使用同一把锁，要使用`PTHREAD_PROCESS_SHARED`设置为进程间共享

```c
typedef struct{
    int val;
    pthread_mutex_t mutex;
}Data_t;
void test(){
    int shmid=shmget(1000,4096,IPC_CREAT|0600);
    Data_t *pdata=(Data_t *)shmat(shmid,NULL,0);
    pdata->val=0;
    pthread_mutexattr_t mattr;
    pthread_mutexattr_init(&mattr);
    pthread_mutexattr_setshared(&mattr,PTHREAD_PROCESS_SHARED);//设置为进程间共享
    pthread_mutex_init(&pdata->mutex，&mattr);
    struct timeval start,end;
    gettimeofday(&start,NULL);
    if(!fork()){
        for(int i=0;i!=100000;++i){
            pthread_mutex_lock(&pdata->mutex);
            pdata->val++;
            pthread_mutex_unlock(&pdata->mutex);
        }
    }else{
        for(int i=0;i!=100000;++i){
            pthread_mutex_lock(&pdata->mutex);
            pdata->val++;
            pthread_mutex_unlock(&pdata->mutex);
        }
        wait(NULL);
        gettimeofday(&end,NULL);
        printf("result=%d,use time=%ld\n",p->val,(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec);
    }
}
```

### 线程的优先级反转

按照常理，高优先级的分配时间片多，低优先级的分配到时间片少

假设任务1，任务2，任务3；他们的优先级顺序分别为1 > 2 > 3。有一个稀缺资源S，S由一个信号量控制为互斥访问。

```c
1. 任务3正在执行，并申请到了资源S；
2. 任务1抢占了任务3的执行，任务3挂起，任务1执行；
3. 任务1申请资源S，发现被占用，所以挂起，任务3恢复执行；
4. 任务2抢占了任务3的执行，任务3挂起，任务2执行；
5. 任务2执行完毕，任务3恢复；
6. 任务3释放资源S，任务1抢占资源S，任务1执行，任务3挂起；
7. 任务1执行完毕，任务3执行。
```

以上可以看出，任务2虽然比任务1优先级低，但是比任务1优先执行。也就是说任务1的优先级被降低到了任务3的级别，这就是所谓的优先级反转

#### 解决方法

如果想让任务1比任务2先执行，有两种方法：

任务3先释放资源，让任务1使用	(X，临界资源没有操作完就释放会出错)

让任务2不能抢占任务3的执行	(✔)

```
1、优先级天花板。当任务3使用资源S时，就把任务3的优先级提升到能访问资源S的最高优先级，执行完成释放资源之后，把优先级再改回来；这样的方法，简单易行，解决了多个高优先级任务抢占资源S的问题。但是带来了一些缺点，就是不一定每次都有高优先级任务抢占资源S，每次都提升优先级是对CPU资源的一种浪费。

2、优先级继承。当任务3使用资源S时，任务1抢占执行权，申请资源S，比较资源1和资源3的优先级，假如任务1优先级高，才提升任务3，提升到和任务1相同的优先级，当任务3释放资源后，将优先级再调整回来。相对于优先级天花板方法，相当于延后执行，克服了任务1的缺点，自己本身的特点是，逻辑复杂，需要操作系统支持相同优先级。在ucos中不容易实现。

3、两者结合的方案：当任务3使用资源S时，任务1抢占执行权，申请资源S，比较资源1和资源3的优先级，假如任务1优先级高，才提升任务3，提升到能访问资源S的最高优先级，当任务3释放资源后，将优先级再调整回来。
```

## 线程的同步

同步，又称为直接制约关系，是指多个线程为了合作完成某一个任务，必须按照规定的某种先后顺序来运行

### 条件变量

条件变量是利用线程间共享的全局变量进行同步的一种机制，主要包括两个动作：一个线程等待条件变量的条件成立而挂起；另一个线程使条件成立（给出条件成立信号）

为了防止竞争，条件变量的使用总是和一个互斥锁结合在一起。

### 条件变量的创建和注销

条件变量和互斥锁一样，都有静态、动态两种创建方式：

静态方式使 PTHREAD_COND_INITIALIZER 常量，如下：

```c
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
```

动态方式调用 pthread_cond_init()函数，API 定义如下：

```c
int pthread_cond_init(pthread_cond_t *cond, pthread_condattr_t *cond_attr);
```

尽管 POSIX 标准中为条件变量定义了属性，但在 Linux Threads 中没有实现，因此 cond_attr 值通常为 NULL，且被忽略。



注销一个条件变量需要调用 pthread_cond_destroy()，只有在没有线程在该条件变量上等待的时候能注销这个条件变量，否则返回 EBUSY。因为 Linux 实现的条件变量没有分配什么资源，所以注销动作只包括检查是否有等待线程。API 定义如下：

```c
int pthread_cond_destroy(pthread_cond_t *cond);
```

###  条件变量等待和激发

#### 等待函数

```c
int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);//无条件等待
int pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex, const struct timespec *abstime);//计时等待
```

线程解开 mutex 指向的锁并被条件变量 cond 阻塞。其中计时等待方式表示经历 abstime 段时间后，即使条件变量不满足，阻塞也被解除。

无论哪种等待方式，都必须和一个互斥锁配合，以防止多个线程同时请求的竞争条件

##### timewait超时等待

超过一段时间就不再等待,其他和wait相同

```
绝对时间 abstime
time(NULL)+3 这样填入才可以是等待3秒
```

```c
void cleanup(void *p){
    pthread_mutex_unlock((pthread_mutex_t *)p);
}
void *threadFunc(void *p){
    struct timespec t;
    t.tv_sec=3;//无效，会立刻超时
    //t.tv_sec=time(NULL)+3;//真正的等3秒
    t.tv_tv_nsec=0;
    pData pdata=(pData)p;
    pthread_mutex_lock(&p->mutex);
    pthread_cleanup_push(cleanup,&p->mutex);
    pthread_cond_timewait(&p->cond,&p->mutex,&t);//等待条件变量成立，此时子进程在睡眠，如果在规定的时间内没有条件变量的唤醒，就会超时返回
    pthread_cleanup_pop(1);
    pthread_exit(0);
}
```

timedwait超时了的情况下返回值是110，正常唤醒也是和wait一样的0

#### wait函数分为上下两个部分

```c
上半部：
    1、排队在对应的cond
    2、解锁	//多个线程就可以同时进入wait了
    3、睡觉

下半部：
    1、醒来
    2、加锁	//否则执行wait前后锁的状态可能不一致
    3、返回
```

mutex互斥锁必须是普通锁（PTHREAD_MUTEX_TIMED_NP），且在调用 pthread_cond_wait()前必须由本线程加锁，而在更新条件等待队列以前，mutex 保持锁定状态，并在线程挂起进入等待前解锁。

在条件满足从而离开 pthread_cond_wait()之前，mutex 将被重新加锁，以与进入pthread_cond_wait()前的加锁动作对应。（也就是说在做 pthread_cond_wait 之前，往往要用pthread_mutex_lock 进行加锁，而调用 pthread_cond_wait 函数会将锁解开，然后将线程挂起阻塞。直到条件被 pthread_cond_signal 激发，再将锁状态恢复为锁定状态，最后再用 pthread_mutex_unlock 进行解锁）。

##### 等待函数都是线程取消点

也就是说如果pthread_cond_wait()被取消，则退出阻塞，然后将锁状态恢复，则此时 mutex 是保持锁定状态的，而当前线程已经被取消掉，那么解锁的操作就会得不到执行，此时锁得不到释放，就会造成死锁，因而需要定义线程清理函数来为其解锁。

```c
void cleanup(void *p){
    pthread_mutex_unlock((pthread_mutex_t *)p);
    printf("unlock success\n");
}
typedef struct{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}Data_t;
void *threadFunc(void *p){
    Data_t *pdata=(Data_t *)p;
    pthread_mutex_lock(&pdata->mutex);
    pthread_cleanup(&pdata->mutex);
    pthread_cond_wait(&pdata->cond,&pdata->mutex);//wait是cancel点
    pthread_cleanup_pop(1);//用pop代替unlock
    pthread_exit(MULL);
}
void test(){
    Data_t data;
    pthread_mutex_init(&data->mutex,NULL);
    pthread_cond_init(&data->cond,NULL);
    pthread_t pthid[2];
    for(int i=0;i!=2;++i){
        pthread_create(pthid+i,NULL,threadFunc,&data);
    }
    sleep(1);
    for(int i=0;i!=2;++i){
        pthread_cancel(pthid[i]);
    }
    for(int i=0;i!=2;++i){
        pthread_join(pthid[i],NULL);
    }
}
```

#### 激发函数

激发是瞬发的，类似脉冲，因此需要其他线程先等待好才能唤醒

```c
pthread_cond_signal(pthread_cond_t *);//激活一个等待该条件的线程，存在多个等待线程时按入队顺序激活其中一个,先等待的先唤醒
pthread_cond_broadcast(pthread_cond_t *);//激活所有等待线程
```

### 线程安全

线程安全：如果一个函数可以同时被多个线程调用，并且和预期结果一致的，即为线程安全函数

可重入函数：避免使用全局变量和静态全局变量

可重入函数是线程安全函数的真子集



# day22

## 协议

协议即通信双方必须遵循的规矩，由iso规定，rpc文档详细解释

协议分两种：

```
私有协议(各个公司自己根据业务需求定制化开发的协议)
公有协议(大家都要遵守和支持的协议)
```

传输层以下的私有协议都不被路由器之类的支持，因此只能自己内部用

## osi模型和tcp/ip模型

### osi模型

应用层、表示层、会话层		传输层		网络层、数据链路层、物理层

(物联网舒适会用)

### tcp/ip模型



TCP协议是进程间的通信，因为进程拥有计算机分配的资源

通信时需要知道通信双方的地址和是哪个进程负责通信，即ip地址和端口号，这样就唯一确定了通信的进程，ip用来定位主机，port区别应用(进程)，每个进程都进程绑定了唯一的ip+port

### TCP和osi模型的对应关系

TCP的应用层对应osi的应用层、表示层、会话层

TCP的传输层对应osi的传输层

TCP的数据链路层层对应osi的数据链路层层

TCP的网络接口层对应osi的数据链路层、物理层



### tcp/ip协议族

#### 应用层

负责应用程序的网络访问，这里通过端口号来识别各个不同的进程。

```
http 超文本传输协议
ftp 文件传输协议
telnet 远程登录
ssh 安全外壳协议
smtp 简单邮件发送
pop3 收邮件
```

各大公司通常也会在应用层自己开发一套协议用于自己的产品的信息传输，传输效率更高，也更安全

#### 传输层

负责端对端之间的通信会话连接和建立。传输协议的选择根据数据传输方式而定。

```
tcp 传输控制协议	面向连接(内核中维护的一种状态ESTABLISHED，并不是真的连接了，只是一种判断的依据)的协议，能保证传输安全可靠，速度较udp要慢(有3次握手)

udp 用户数据包协议	非面向连接	速度快	不可靠(不保证接收)
```

#### 网络层

负责将数据帧封装成 IP 数据报，并运行必要的路由算法。

```
ip 网际互连协议				和tcp协议一起作为协议族最重要的协议
icmp 网络控制消息协议		   ping命令
igmp 网络组管理协议			组播、广播
```

#### 网际接口层

负责将二进制流转换为数据帧，并进行数据帧的发送和接收。要注意的是数据帧是独立的网络信息传输单元。

```
arp 地址转换协议				ip地址->mac地址的转换
rarp 反向地址转换协议			mac地址->ip地址的转换
mpls 多协议标签交换
```

#### 数据的封装与解封

```
对于发送方：
    应用层：将信息加入应用层头部封装成数据传递给传输层
    传输层：将应用层传递来的数据加入传输层头部(主要是端口号)封装成 段 传递给网络层
    网络层：将传输层传递来的段加入网络层头部(主要是ip)封装成 包 传递给网络接口层
    网络接口层：将网络层传递的包加入网络接口层头部封装成 帧 传递给接收方的网络接口层

对于接收方：
	从下到上每层根据接收到的包依次拆解属于自己层的头部(根据头部包含的信息进行不同的操作)，再将包剩下的部分发送给上一层
```

网络层负责点到点的传输(发送方到路由器1，路由器1到路由器2……路由器n到接收方，点指主机或路由器)

传输层负责端到端的传输(发送方到接收方，源地址到目的地址，端指主机和目的主机)

## tcp协议

TCP提供全双工和可靠交付的服务，采用序列号、确认重传、滑动窗口等机制确保端到端之间的可靠数据传输

### 特点

面向连接、确认重传、流量控制、可靠交付的传输层协议

可靠传输的定义：接收端能够按照正确的顺序接收到正确的内容

可靠传输的实现：TCP的可靠性是通过顺序编号(seq)和确认(ACK/ack)来实现的。TCP在开始传送一个报文时，为准备重传而首先将该报文插入到发送队列中，同时启动时钟。其后，如果收到了接收端对报文的ACK信息，就将该报文从队列中删去。如果在时钟规定的时间内，ACK未返回，那么就从发送队列中再次发送这个报文

一次完整的TCP通信过程：建立连接(三次握手)、数据传输、断开连接(四次挥手)

### 序列号

TCP 要为所发送的每一个报文段加上序列号，保证每一个报文段能被接收方接收，并只被正确的接收一次。

### 确认重传

接收端在正确收到报文段之后向发送端回送一个确认（ACK）信息。

发送方将每个已发送的报文段备份在自己的缓冲区里，而且在收到相应的确认之前是不会丢弃所保存的报文段的。

发送发在每一个报文段发送完毕的同时启动一个定时器，加入定时器的定时期满而关于报文段的确认信息还没有达到，则发送方认为该报文段已经丢失并主动重发。为了避免由于网络延时引起迟到的确认和重复的确认，TCP 规定在确认信息中捎带一个报文段的序号，使接收方能正确的将报文段与确认联系起来。

### 滑动窗口

采用可变长的滑动窗口协议进行流量控制，以防止由于发送端与接收端之间的不匹配而引起的数据丢失。

采用可变长的滑动窗口，使得发送端与接收端可根据自己的 CPU 和数据缓存资源对数据发送和接收能力来进行动态调整，从而灵活性更强，也更合理。

### TCP报文头部格式

![image-20200319150521849](D:\TyporaPic\复习笔记Linux\image-20200319150521849.png)

```
源端口、目的端口：16 位长。

顺序号seq：32 位长。标识发送的数据报的顺序，确保有序接收

确认号ack：32 位长。希望收到的下一个数据报的序列号。

TCP 头长：4 位长。表明 TCP 头中包含多少个 32 位字。

URG：紧急指针（urgent pointer）有效，紧急指针指出在本报文段中的紧急数据的最后一个字节的序号

ACK：ACK 位置 1 表明确认号是合法的。如果 ACK 为 0，那么数据报不包含确认信息，确认字段被省略

PSH：表示是带有 PUSH 标志的数据。接收方因此请求数据报一到便可送往应用程序而不必等到缓冲区装满时才发送。当 PSH=1 时，则报文段会被尽快地交付给目的方，不会对这样的报文段使用缓存策略

RST：用于复位由于主机崩溃或其他原因而出现的错误的连接。还可以用于拒绝非法的数据报或拒绝连接请求。当 RST 为 1 时，表明 TCP 连接中出现了严重的差错，必须释放连接，然后再重新建立连接。

SYN：用于建立连接。当 SYN=1 时，表示发起一个连接请求。

FIN：用于释放连接。当 FIN=1 时，表明此报文段的发送端的数据已发送完成，并要求释放连接。

窗口大小：16 位长。窗口大小字段表示在确认了字节之后还可以发送多少个字节。此字段用来进行流量控制。单位为字节数，这个值是本机期望一次接收的字节数。

校验和：16 位长。是为了确保高可靠性而设置的。它校验头部、数据和伪 TCP 头部之和。

可选项：0 个或多个 32 位字。包括最大 TCP 载荷，窗口比例、选择重复数据报等选项。
```

### 建立连接的三次握手

![image-20200319152144514](D:\TyporaPic\复习笔记Linux\image-20200319152144514.png)

```
TCP 的标准规定，SYN 置 1 的报文段要消耗掉一个序号。

请求方发起第一次握手，发送SYN=1，seq=x
接收方收到请求后，发送SYN=1，ACK=1，seq=y，ack=x+1
请求方收到后，发送ACK=1，seq=x+1，ack=y+1

1、源主机 A 的 TCP 向主机 B 发送连接请求报文段，其首部中的 SYN（同步）标志位应置为 1，表示想跟目标主机 B 建立连接，进行通信，并发送一个同步序列号 X（例：SEQ=100）进行同步，表明在后面传送数据时的第一个数据字节的序号为 X+1（即 101）。

2、目标主机 B 的 TCP 收到连接请求报文段后，如同意，则发回确认。再确认报中应将 ACK 位和SYN 位置为 1.确认号为 X+1，同时也为自己选择一个序号 Y。 

3、源主机 A 的 TCP 收到目标主机 B 的确认后要想目标主机 B 给出确认。其 ACK 置为 1，确认号为 Y+1，而自己的序号为 X+1。
```

运行客户进程的源主机 A 的 TCP 通知上层应用进程，连接已经建立。当源主机 A 向目标主机 B 发送第一个数据报文段时，其序号仍为 X+1，因为前一个确认报文段并不消耗序号。

当运行服务进程的目标主机 B 的 TCP 收到源主机 A 的确认后，也通知其上层应用进程，连接已经建立。至此建立了一个全双工的连接。

#### 保证可靠性

前两次握手成功后(两次SYN)，双方就已经确认了对方的序列号，这样双方都知道什么样的序列号是合法的，什么样的是不合法的。server端接收到不合法的就丢弃，接收到合法的就认为连接是成功建立的，注意不论接收到的信息是否合法，都会发送给请求方确认

#### 为什么需要三次握手

理解1：三次握手的目的是为了防止已失效的连接请求报文段突然又传送到了服务端，因而产生错误(为什么不是两次握手)

```
假设不采用三次握手即采用两次握手的话，那么只要server发出确认，server就认为是建立连接了；
但是如果第二次握手连接丢失了，那么client端不会认为连接建立，因此不会理睬server的确认，也不会向server发送数据；
但server却认为新的传输连接已经建立，并一直等待client发来数据；
这样server的很多资源就白白浪费掉了。采用三次握手的方法就可以防止上述现象的发生
```

理解2：请求方发送同步信号，接收方收到后需要确认，TCP确认收到的包(为什么不是四次握手)

第二次握手同时完成了服务器端响应客户端连接建立请求和客户端向服务器端发送连接建立请求两件事，合并发送可以减少连接建立的时延和资源损耗

#### 三次握手的包丢包了会有哪些情况

核心：对端的超时重传机制重传上一个包，促使本端重新发包

##### 第一个包，即请求方A发送给接收方B的SYN中途被丢，没有到达B		

A会周期性的超时重传，直到收到B的确认(第二次握手)

##### 第二个包，即B发给A的SYN+ACK中途被丢，没有到达A		

A没有收到第一个包的ACK，会重传第一个包；B也会周期性的超时重传，直到收到A的确认(第三次握手)

##### 第三个包，即A发给B的ACK中途被丢，没有到达B

1、假定此时双方都没有数据发送，B会周期性超时重传，直到收到A的确认，收到之后B的TCP连接也为Established状态，双向可以发包

2、假定此时A有数据发送，B收到A的Data+ACK，自然会切换为Established状态，并接收A的Data，因为此时A发送的seq就是第二次握手时B发送的ack即x+1，A发送给B的第三次握手的seq=x+1，A下一次发给B的正常数据的seq也是x+1

3、假定此时B有数据发送，数据发送不了，会一直周期性超时重传SYN+ACK，直到收到A的确认才可以发送数据

### 释放连接的四次挥手

由于 TCP 连接是全双工的，因此每个方向都必须单独进行关闭。这原则是当一方完成它的数据发送任务后就能发送一个 FIN 来终止这个方向的连接。

收到一个 FIN 只意味着不再接收到此方向的数据，仍能发送数据。首先进行关闭的一方将执行主动关闭，而另一方执行被动关闭。

在TIME_WAIT状态时两端的端口不能使用，要等到2MSL的时间结束才可继续使用，当连接处于2MSL等待阶段时任何迟到的报文段都要被丢弃

2MSL Maximum Segment Lifetime 英文的缩写，中文可译为最大报文段生存时间， 在Linux的/proc/sys/net/ipv4/tcp_fin_timeout可以看到

![image-20200319165231522](D:\TyporaPic\复习笔记Linux\image-20200319165231522.png)

```
请求方发起关闭连接请求，发送FIN=1，seq=u
接收方收到请求后先进行应答，即只发送ACK=1，seq=v，ack=u+1
接收方处理完毕所有数据的发送后再发送结束报文FIN，FIN=1，ACK=1，seq=w，ack=u+1			w是因为这期间可能发送了其他报文，因此序列号不一定会是v+1
请求方收到后，发送ACK=1，seq=u+1，ack=w+1


1、 TCP 客户端发送一个 FIN，用来关闭客户到服务器的数据传送。 

2、服务器收到这个 FIN，它发回一个 ACK，确认序号为收到的序号加 1。和 SYN 一样，一个FIN 将占用一个序号。

3、服务器关闭客户端的连接，发送一个 FIN+ACK给客户端。

4、客户端发回 ACK 报文确认，并将确认序号设置为收到序号加 1
```

#### 为什么建立连接只需要三次握手？断开连接需要四次挥手？

因为TCP是全双工模式，接收到FIN时只是意味对端将没有数据再发来，但是还是本端可以继续发送数据过去。

当Server端收到Client端的SYN连接请求报文后，可以直接发送SYN+ACK报文。其中ACK报文是用来应答的，SYN报文是用来同步的；但是关闭连接时，当Server端收到FIN报文时，很可能并不会立即关闭SOCKET，所以只能先回复一个ACK报文，告诉Client端，"你发的FIN报文我收到了"。只有等到Server端所有的报文都处理完了，Server端才会发送FIN报文，因此需要四步握手。

#### 为什么TIME_WAIT状态需要经过2MSL才能返回CLOSED状态？

##### 1、保证TCP协议的全双工连接能够可靠关闭

如果Client直接CLOSED了，那么由于IP协议的不可靠性或者是其它网络原因，导致Server没有收到Client最后回复的ACK。那么Server就会在超时之后继续发送FIN，此时由于Client已经CLOSED了，就找不到与重发的FIN对应的连接，最后Server就会收到RST而不是ACK，Server就会以为是连接错误把问题报告给高层。这样的情况虽然不会造成数据丢失，但是却导致TCP协议不符合可靠连接的要求。所以，Client不是直接进入CLOSED，而是要保持TIME_WAIT，当再次收到FIN的时候，能够保证对方收到ACK，最后正确的关闭连接。

##### 2、保证这段连接的重复数据段从网络中消失

虽然按道理，四个报文都发送完毕，我们可以直接进入CLOSE状态了，但是我们必须假设网络是不可靠的，有可能最后一个ACK丢失。所以TIME_WAIT状态就是用来重发可能丢失的ACK报文。在Client发送出最后的ACK回复，但该ACK可能丢失。Server如果没有收到ACK，将不断重复发送FIN片段。所以Client不能立即关闭，它必须确认Server接收到了该ACK。Client会在发送出ACK之后进入到TIME_WAIT状态。Client会设置一个计时器，等待2MSL的时间。如果在该时间内再次收到FIN，那么Client会重发ACK并再次等待2MSL。MSL指一个片段在网络中最大的存活时间，2MSL就是一个发送和一个回复所需的最大时间。如果直到2MSL，Client都没有再次收到FIN，那么Client推断ACK已经被成功接收，则结束TCP连接。

A发给B的第四次回收丢了，B发送第三次挥手之后的超时重传的计时器的时间加上数据包在网络中的传输时间一定小于2MSL的，所以能够保证第四次挥手的包丢了，仍然有足够的时间超时重传。

## 网络编程

netstat -an|grep tcp	可查看状态

### 网络编程的相关概念

#### 套接口

是操作系统内核中的一个数据结构，是网络进程的ID

主要包含源地址，源端口，目的地址，目的端口

一个端口号一次只能分配给一个进程，即在一台计算机中，端口号和进程之间是一一对应的关系

#### 端口号的概念

TCP/IP协议中的端口号为0~65535，其中0~1023 都是一些固定使用的端口，如http的80，ssh的22，telnet的23，ftp的21等

用户自己定义的通常要大于1024

#### ip地址的表示

用户在表达时常用点分十进制表示，而在网络中传输的其实是一个整型值，socket编程中常用的也是一个二进制值，因此需要进行数值转换

### socket的概念

Linux 中的网络编程是通过 socket 接口来进行的。socket 是一种特殊的 I/O 接口，它也是一种文件描述符。它是一种常用的进程之间通信机制，通过它不仅能实现本地机器上的进程之间的通信，而且通过网络能够在不同机器上的进程之间进行通信。

每一个 socket 都用一个半相关描述{协议、本地地址、本地端口}来表示；一个完整的套接字则用一个相关描述{协议、本地地址、本地端口、远程地址、远程端口}来表示。socket 也有一个类似于打开文件的函数调用，该函数返回一个整型的 socket 描述符，随后的连接建立、数据传输等操作都是通过 socket来实现的；

### socket类型

```
（1）流式 socket（SOCK_STREAM） →用于 TCP 通信
流式套接字提供可靠的、面向连接的通信流；它使用 TCP 协议，从而保证了数据传输的正确性和顺序性。 

（2）数据报 socket（SOCK_DGRAM） →用于 UDP 通信
数据报套接字定义了一种无连接的服务，数据通过相互独立的报文进行传输，是无序的，并且不保证是可靠、无差错的。它使用数据报协议 UDP。 

（3）原始 socket（SOCK_RAW） →用于新的网络协议实现的测试等
原始套接字允许对底层协议如 IP 或 ICMP 进行直接访问，它功能强大但使用较为不便，主要用于自己开发的协议。
```

### socket数据结构



```c
#include <netinet/in.h>
struct sockaddr_in {
    short int sin_family; /*地址族*/
    unsigned short int sin_port; /*端口号*/
    struct in_addr sin_addr; /*IP 地址*/
    unsigned char sin_zero[8]; /*填充 0 以保持与 struct sockaddr 同样大小,其实是4个*/
};
```

### 一些可能会用到的转换函数

#### 网络字节序和主机字节序

大端模式，是指数据的高字节保存在内存的低地址中，而数据的低字节保存在内存的高地址中，这样的存储模式有点儿类似于把数据当作字符串顺序处理：地址由小向大增加，而数据从高位往低位放；这和我们的阅读习惯一致。

小端模式，是指数据的高字节保存在内存的高地址中，而数据的低字节保存在内存的低地址中，这种存储模式将地址的高低和数据位权有效地结合起来，高地址部分权值高，低地址部分权值低。

```
网络字节序	大端			 低地址存高位字节
主机字节序	小端(通常)		低地址存低位字节
```

对于内存地址表示，从左到右地址从低到高

对于数据字节表示，从左到右字节从高到低

##### 如何判断主机字节序是大端还是小端

```c
short s=0x1234;
//大端存储 12 34
//小端存储 34 12	每个字节低位在前，高位在后

if(*(char *)&s == 0x12){//解引用是一个字节
	//大端
}else{
	//小端
}
```

##### 转换函数

端口号一定要转为网络字节序

注意会造成截断，htons截断只保留最低位2个字节

```c
#include<netinet/in.h>
//主机字节序转网络字节序
uint16_t htons(unint16_t host16bit);	//host to net short
uint32_t htonl(unint32_t host32bit);//几乎不用

//网络字节序转主机字节序
uint16_t ntohs(unint16_t net16bit);		//net ti host short
uint32_t ntohl(unint32_t net32bit);//几乎不用
```

端口号通常会从配置文件中读取，因此常如下使用：

```
char port[4]="1234";
htons(atoi(port));
```

#### ip地址转化

通常用户在表达地址时采用的是点分十进制表示的数值（或者是为冒号分开的十进制 Ipv6 地址），而在通常使用的 socket 编程中使用的则是 32 位的网络字节序(4字节整型数)的二进制值，这就需要将这两个数值进行转换。

```c
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int inet_aton(const char *straddr, struct in_addr *addrptr);//将点分十进制数的 IP 地址转换成为网络字节序的 32 位二进制数值。参数 addrptr：传出参数，保存网络字节序的 32 位二进制数值。
char *inet_ntoa(struct in_addr inaddr);//将网络字节序的 32 位二进制数值转换为点分十进制的 IP 地址。
in_addr_t inet_addr(const char *straddr);// in_addr_t 就是 unsigned int ,代表 s_addr，功能和inet_aton相同
```

比如ip地址192.168.5.21转换成二进制就是15 05 a8 c0	在内核中就是直接大端存储，直接转成对应字符串

#### 域名和ip地址的转换

需要联网

不是线程安全的函数

IPV6是16字节

```c
#include <netdb.h>
struct hostent* gethostbyname(const char* hostname);//用于将域名或主机名转换为 IP 地址。
struct hostent* gethostbyaddr(const char* addr, size_t len, int family);//用于将 IP 地址转换为域名或主机名。
```

```c
struct hostent
{
char *h_name; /*正式主机名*/
char **h_aliases; /*主机别名，指针数组的起始地址*/
int h_addrtype; /*主机 IP 地址类型 IPv4 为 AF_INET*/
int h_length; /*主机 IP 地址字节长度，对于 IPv4 是 4 字节，即 32 位*/
char **h_addr_list; /*主机的 IP 地址列表这个是指向了网络字节序，需要用ipv6的转接的函数转换成主机字节序*/
}
#define h_addr h_addr_list[0] /*保存的是 ip 地址*/
```

### socket编程

服务端：socket---bind---listen---while(1){---accept---recv---send---close---}---close

客户端：socket-------------------------------connect---send---recv-----------------close

<img src="D:\TyporaPic\复习笔记Linux\image-20200320151026608.png" alt="image-20200320151026608" style="zoom:40%;" />

#### socket函数

 socket 函数：生成一个套接口描述符。

原型：

```c
int socket(int domain,int type,int protocol);
```

参数：

```
domain→{ AF_INET：Ipv4 网络协议 AF_INET6：IPv6 网络协议}

type→｛tcp：SOCK_STREAM udp：SOCK_DGRAM}

protocol→指定 socket 所使用的传输协议编号。通常为0. 
```

返回值：成功则返回套接口描述符，失败返回-1。

```c
int sfd=socket(AF_INET,SOCK_STREAM,0);//第一次打开就是3，类似文件描述符
```

#### bind函数

 bind 函数：用来绑定一个端口号和 IP 地址，使套接口与指定的端口号和 IP 地址相关联。

原型：

```c
int bind(int sockfd,struct sockaddr * my_addr,socklen_t addrlen);
```

参数：

```
sockfd→为前面 socket 的返回值。

my_addr→为结构体指针变量

addrlen→sockaddr 的结构体长度。通常是计算 sizeof(struct sockaddr);
```

返回值：成功则返回 0，失败返回-1

对于不同的 socket domain 定义了一个通用的数据结构,当使用的是AF_INET(即ipv4)时， socketaddr 结构定义便为

```c
struct sockaddr_in{ //常用的结构体
    unsigned short int sin_family; //即为 sa_family ➔AF_INET
    uint16_t sin_port; //为使用的 port 编号
    struct in_addr sin_addr; //为 IP 地址
    unsigned char sin_zero[8]; //未使用
};
```

```c
struct sockaddr_in my_addr; //定义结构体变量
memset(&my_addr, 0, sizeof(struct sockaddr)); //将结构体清空
//或 bzero(&my_addr, sizeof(struct sockaddr));
my_addr.sin_family = AF_INET; //Ipv4
my_addr.sin_port = htons(8888); //htons()用来将主机字节序转换成网络字节序,如果参数填0会自动选一个未占用端口
my_addr.sin_addr.s_addr = inet_addr("192.168.0.101");
//将IP地址字符串转换成网络所使用的二进制数字，如果参数为 INADDR_ANY，这表示自动填充本机 IP 地址。
bind(sfd, (struct sockaddr*)&my_str, sizeof(struct socketaddr);//向前兼容
```

#### listen函数

 listen 函数：使服务器的这个端口和 IP 处于监听状态，等待网络中某一客户机的连接请求。如果客户端有连接请求，端口就会接受这个连接。

backlog参数是已连接(三次握手成功)的最大数 man listen 可以查看，backlog是队列大小，队列存放已完成三次握手的连接，从Linux2.2开始发生的改变,accept函数从这个队列中取走已完成握手的连接

内核中开启了syncookies，防止通过三次握手的方式进行网络攻击

原型：

```c
int listen(int sockfd,int backlog);
```

参数：

```
sockfd→为前面 socket 的返回值.即 sfd

backlog→指定同时能处理的最大连接要求，通常为 10 或者 5。最大值可设至 128
```

返回值：成功则返回 0，失败返回-1

```c
listen(sfd,10);
```

#### accept函数

和客户端的connect进行三次握手

 accept 函数：接受远程计算机的连接请求，建立起与客户机之间的通信连接。

服务器处于监听状态时，如果某时刻获得客户机的连接请求，此时并不是立即处理这个请求，而是将这个请求放在等待队列中，当系统空闲时再处理客户机的连接请求。

当 accept 函数接受一个连接时，会返回一个新的 socket 标识符，以后的数据传输和读取就要通过这个新的 socket 编号来处理，原来参数中的 socket 也可以继续使用，继续监听其它客户机的连接请求。

accept是一个系统调用，只是没把客户信息从内核拿出来

原型：

```c
int accept(int s,struct sockaddr * addr,socklen_t* addrlen);
```

参数：

```
s→为前面 socket 的返回值.即 sfd

addr→为结构体指针变量，和 bind 的结构体是同种类型的，系统会把远程主机的信息（远程主机的地址和端口号信息）保存到这个指针所指的结构体中。

addrlen→表示结构体的长度，为整型指针，是value-result传入传出参数
```

返回值：成功则返回新的 socket 处理代码 new_fd，失败返回-1

```c
struct sockaddr_int clientaddr;
bzero(&clientaddr,sizeof(clientaddr));
int clientlen=sizeof(clientaddr);
int clientfd=accept(socketfd,&clientaddr,&clientlen);
```

#### recv函数

ecv 函数：用新的套接字来接收远端主机传来的数据，并把数据存到由参数 buf 指向的内存空间

原型：

```c
int recv(int sockfd,void *buf,int len,unsigned int flags);
```

参数：

```
sockfd→为前面 accept 的返回值.即 new_fd，也就是新的套接字。

buf→表示缓冲区

len→表示缓冲区的长度

flags→通常为 0
```

返回值：成功则返回实际接收到的字符数，可能会少于你所指定的接收长度。失败返回-1

```c
char buf[128]={0};//规定了长度的可以用sizeof
int ret=recv(clientfd,buf,sizeof(buf),0);
```

#### send函数

 send 函数：用新的套接字发送数据给指定的远端主机

send 成功不代表对方已经成功接收到了！！！send是把数据从用户态buf拷贝到发送缓冲区，并不代表发送到网络，缓冲区数据的发送时机是由底层的网卡决定的，不是我们能控制的

原型：

```c
int send(int s,const void * msg,int len,unsigned int flags);
```

参数：

```
s→为前面 accept 的返回值.即 new_fd

msg→一般为常量字符串

len→表示长度

flags→通常为 0
```

返回值：成功则返回实际传送出去的字符数，可能会少于你所指定的发送长度。失败返回-1

```c
int ret=send(clientfd,buf,strlen(buf),0);
```

#### close函数

close 函数：当使用完文件后若已不再需要则可使用 close()关闭该文件，并且 close()会让数据写回磁盘，并释放该文件所占用的资源

原型：

```c
int close(int fd);
```

参数：

```
fd→为前面的 sfd,new_fd
```

返回值：若文件顺利关闭则返回 0，发生错误时返回-1

```
close(clientfd);
close(socketfd);
```

#### connect函数

connect 函数：用来请求连接远程服务器，将参数 sockfd 的 socket 连至参数 serv_addr 指定的服务器IP 和端口号上去。

原型：

```c
int connect (int sockfd,struct sockaddr * serv_addr,int addrlen);
```

参数：

```
sockfd→为前面 socket 的返回值，即 sfd

serv_addr→为结构体指针变量，存储着远程服务器的 IP 与端口号信息。

addrlen→表示结构体变量的长度
```

返回值：成功则返回 0，失败返回-1

```c
struct sockaddr_in addr;
bzero(&addr,sizeof(addr));
addr.sin_family=AF_INET;
addr.sin_port=htons(9000);//服务器端的端口号
addr.sin_addr.s_addr=inet_addr("192.168.0.101");//服务器的ip
int ret=connect(socketfd,(struct sockaddr *)&addr,sizeof(addr));
```

#### 一个例子

```c
void server(){
    int socketfd=socket(AF_INET,SOCK_STREAM,0);
    
    struct sockaddr_in addr;
    bzero(&addr,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_port=htons(0);
    addr.sin_addr.s_addr=inet_addr(INADDR_ANY);
    int ret=bind(socketfd,(struct sockaddr *)&addr,sizeof(addr));
    
    listen(socketfd,10);//激活,10表示缓冲区大小为10，在同一时间内最多有10个客户端连接即并发，需要经过测试，这里可以先填个10
    
    struct sockaddr_in client;
    bzero(&client,sizeof(client));
    int clientlen=sizeof(client);
    int clientfd=accept(socketfd,&client,&clientlen);
    
    printf("client ip=%s,client port=%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
    char buf[128]={0};
    recv(clientfd,buf,sizeof(buf),0);
    send(clientfd,"hello",5,0);
    //while(1);//使用netstat -an|grep tcp 观察establish状态
    close(newFd);
    close(socketFd);
}

void client(){
    int socketfd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in addr;
    bzero(&addr,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_port=htons(0);//connect 后本地会随即开启一个端口，通常大于10000，因此自己写的端口最好不要大于10000
    addr.sin_addr.s_addr=inet_addr("192.168.0.101");
    int ret=connect(socketfd,(struct sockaddr *)&addr,sizeof(addr));
    send(socketfd,"helloworld",10,0);
    char buf[128]={0};
    recv(socketfd,buf,sizeof(buf),0);
    puts(buf);
    while(1);
    close(socketfd);
}
```

### 客户端断开连接，服务器端不断开，且客户端可以再次连接

传入传出参数的经典解决方案

```c
void tcpInit(int *sfd,char *port,char *ip){
    int socketfd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in addr;
    bzero(&addr,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_port=htons(atoi(port));
    addr.sin_addr.s_addr=inet_addr(ip);
    int ret=bind(socketfd,(struct sockaddr*)&addr,sizeof(addr));
    listen(socketfd,10);
    *sfd=socketfd;
}
int main(int argc,char *argv[]){
    ARGS_CHECK(argc,3);
    int socketfd=0;
    tcpInit(&socketfd,argv[2],argv[1]);
    fd_set rdset;
    fd_set moniterset;
    FD_ZERO(&moniterset);
    FD_SET(STDIN_FILENO,&moniterset);
    FD_SET(socketfd,&moniterset);
    char buf[128]={0};
    int newFd;
    while(1){
        memset(&rdset,&moniterset,sizeof(fd_set));
        ret=select(14,&rdset,NULL,NULL,NULL);
        if(ret>0){
            if(FD_ISSET(socketfd,&rdset)){
                newFd=accept(socketfd,NULL,NULL);//如果有多个用户，则需要取他们的ip和port
                FD_SET(newFd,&moniterset);
            }
            if(FD_ISSET(STDIN_FILENO,&rdset)){
                bzero(&buf,sizeof(buf));
                ret=read(STDIN_FILENO,buf,sizeof(buf));
                if(ret==0){//服务器端断开连接
                    break;
                }
                send(newFd,buf,strlen(buf)-1,0);
            }
            if(FD_ISSET(newFd,&rdset)){
                bzero(&buf,sizeof(buf));
                ret=recv(newFd,buf,sizeof(buf),0);
                if(ret==0){//客户端断开连接
                    FD_CLR(newFd,&moniterset);
                    close(newFd);
                }else{
                    puts(buf);
                }
            }
        }
    }
    close(socketfd);
    return 0;
}

void client(char *ip,char *port){
    int socketfd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in addr;
    bzero(&addr,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_port=htons(atoi(port));
    addr.sin_addr.s_addr=inet_addr(ip);
    int ret=connect(socketfd,(struct sockaddr *)&addr,sizeof(addr));
    char buf[128]={0};
    fd_set rdset;
    while(1){
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(socketfd,&rdset);
        ret=select(socketfd+1,&rdset,NULL,NULL,NULL);
        if(ret>0){
            if(FD_ISSET(STDIN_FILENO,&rdset)){
                bzero(&buf,sizeof(buf));
                int ret=read(STDIN_FILENO,buf,sizeof(buf));
                if(ret==0){
                    break;
                }
                send(socketfd,buf,strlen(buf)-1,0);
            }
            if(FD_ISSET(socketfd,&rdset)){
                bzero(&buf,sizeof(buf));
                int ret=recv(socketfd,buf,sizeof(buf),0);
                if(ret==0){
                    break;
                }
                puts(buf);
            }
        }
    }
    close(socketfd);
}
```

### 发送方发送的信息长度远大于接收方接受字符串的长度的情况

tcp会循环读取直到全部读取完，udp只会读取接受字符串长度的数据，剩下的全部舍弃

### 设置套接口选项setsockopt

一定要在bind之前

```c
#include <sys/types.h>
#include <sys/socket.h>
int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
```

#### SO_REUSEADDR

即服务器主动断开连接处于TIME_WAIT状态时仍然可以使用之前断开的端口作为监听端口

同时也允许在同一个端口上启动同一个服务器的多个实例，只要每个实例捆绑的本地ip地址是不同的

```c
int reuse=1;//置位,表示true
ret=setsockopt(socketFd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
```

#### SO_REUSEPORT

支持多个进程或者线程(套接字)绑定到同一端口，但是彼此拥有独立的socket文件描述符

```c
int reuse=1;//置位,表示true
ret=setsockopt(socketFd,SOL_SOCKET,SO_REUSEPORT,&reuse,sizeof(int));
```

#### SO_RCVLOWAT

改变接收缓冲区下限，可以减少epoll_wait的触发次数，缓冲区的数据只有达到下限值才会触发一次epoll_wait，常用于视频接收

注意是设置给newFd的，而不是socketfd

```c
int revLowAtValue=20;//累计传递20个字节后，服务器端才会一次性接收显示在一行
ret=setsockopt(newFd,SOL_SOCKET,SO_RCVLOWAT,&revLowAtValue,sizeof(int));
```



# day25

## DDos攻击

### SYN Flooding

采用三次握手的机制进行攻击

Server 接收到 SYN 连接请求。 内部维护一个队列（我们暂称之半连接队列，半连接并不准确）， 发送 ack 及 syn 给 Client 端，等待 Client 端的 ack 应答，接收到则完成三次握手建立连接。 如果接收不到 ack 应答，则根据延时重传规则继续发送 ack 及 syn 给客户端。

利用上述特点。我们构造网络包，源地址随机构建，意味着当 Server 接到 SYN 包时，应答 ack 和syn 时不会得到回应。在这种情况下， Server 端，内核就会维持一个很大的队列来管理这些半连接。 当半连接足够多的时候，就会导致新来的正常连接请求得不到响应， 也就是所谓的 DOS 攻击。

被攻击时可以top命令查看内核占用率

### 攻击防护手段

tcp_max_syn_backlog： 增加半连接队列长度，默认128

tcp_synack_retries: 		减少syn+ack 的重传次数，默认5

tcp_syncookies : 				syn cookie(更有效)，默认1

root下在/proc/sys/net/ipv4/xxx中修改

建议直接买云服务(

## epoll 多路复用

epoll 是在 2.6 内核中提出的，是之前的 select 和 poll 的增强版本。相对于 select 和 poll 来说，epoll更加灵活，没有描述符限制。

epoll 使用一个文件描述符管理多个描述符，将用户关系的文件描述符的事件存放到内核的一个事件表中，这样在用户空间和内核空间的 copy 只需一次。同时 epoll 的性能更好，因此在工作中首选 epoll。

### 接口使用

```c
#include <sys/epoll.h> 
int epoll_create(int size); 
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event); 
int epoll_wait(int epfd, struct epoll_event * events, int maxevents, int timeout);
```

#### int epoll_create(int size);

 创建一个 epoll 的句柄，本身也占用一个文件描述符的位置，size 用来告诉内核这个监听的数目一共有多大，可以直接填1(只要不是0就行)。需要注意的是，当创建好 epoll 句柄后，它就是会占用一个fd 值，在 linux 下如果查看/proc/进程 id/fd/，是能够看到这个 fd 的，所以在使用完 epoll 后，必须调用 close()关闭，否则可能导致 fd 被耗尽。

在内核中用红黑树维护注册

#### int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);

 epoll 的事件注册函数，先注册要监听的事件类型，再执行监听

第一个参数是 epoll_create()的返回值

第二个参数表示动作，用三个宏来表示：

```
EPOLL_CTL_ADD：注册新的 fd 到 epfd 中；
EPOLL_CTL_MOD：修改已经注册的 fd 的监听事件；
EPOLL_CTL_DEL：从 epfd 中删除一个 fd；
```

第三个参数是需要监听的 fd

第四个参数是告诉内核需要监听什么事，是传入参数，struct epoll_event 结构如下：

```c
struct epoll_event {
	__uint32_t events;/* Epoll events */
	epoll_data_t data;/* User data variable，是个联合体 ，主要用他的fd字段存放要监听的文件描述符*/ 
};
```

events 事件类型以下几个比较常用：

```
EPOLLIN ：表示对应的文件描述符可以读（包括对端 SOCKET 正常关闭）；
EPOLLOUT：表示对应的文件描述符可以写；
EPOLLET： 将 EPOLL 设为边缘触发(Edge Triggered)模式，这是相对于水平触发(Level Triggered)来说的。
EPOLLONESHOT：只监听一次事件，当监听完这次事件之后，如果还需要继续监听这个 socket 的话，需要再次把这个 socket 加入到 EPOLL 队列里
```

#### int epoll_wait(int epfd, struct epoll_event \* events, int maxevents, int timeout);

等待事件的产生，类似于 select()调用。

参数 events 用来从内核得到事件的集合，是传出参数，一次注册永久生效，返回的时候只会返回链表中可读的描述符，而不像select单纯是memcpy全拷贝了

```c
struct epoll_event evs[number];//number为监控文件描述符的总量，因为可能同时接收到请求
```

maxevents 告知内核这个 events 有多大，这个 maxevents 的值不能大于创建 epoll_create()时的 size

参数 timeout 是超时时间（毫秒，0 会立即返回，-1永久阻塞至有请求到来）

该函数返回需要处理的事件数目，如返回 0 表示已超时。

```c
int main(){
    int socketfd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in addr;
    bzero(&addr,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_port=htons(atoi("8000"));
    addr.sin_addr.s_addr=inet_addr(INADDR_ANY);
    bind(socketfd,(struct sockaddr *)&addr,sizeof(addr));
    listen(socketfd,10);
    
    struct epoll_event event,evs[3];//event用于事件注册，evs用于存放wait中就绪的文件描述符
    int epollfd=epoll_create(1);
    event.events=EPOLLIN;
    event.data.fd=STDIN_FILENO;
    epoll_ctl(epollfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
    event.data.fd=socketfd;//传入参数，因此可以直接重用
    epoll_ctl(epollfd,EPOLL_CTL_ADD,socketfd,&event);
    int readyCount,ret,i,newFd;
    char buf[128]={0};
    
    while(1){
        readyCount=epoll_wait(epollfd,evs,3,-1);//3个要监听的文件描述符(stdin,socketfd,newfd)，无限等待
        for(i=0;i!=readyCount;++i){//每次readyCount可能都不一样
            if(evs[i].events==EPOLLIN&&evs[i].data.fd==socketfd){//新连接&&可读
                newFd=accept(socketfd,NULL,NULL);//通常会用结构体接对端的ip地址和端口号并保存
                event.data.fd=newFd;
                epoll_ctl(epollfd,EPOLL_CTL_ADD,newFd,&event);
            }
            if(evs[i].events==EPOLLIN&&evs[i].data.fd==STDIN_FILENO){//标准输入&&可读
                bzero(buf,sizeof(buf));
                ret=read(STDIN_FILENO,buf,sizeof(buf));
                if(ret==0){//服务器端退出
                    goto end;
                }
                send(newFd,buf,strlen(buf)-1,0);
            }
            if(evs[i].events==EPOLLIN&&evs[i].data.fd==newFd){//客户端连接请求&&可读
                bzero(buf,sizeof(buf));
                ret=read(newFd,buf,sizeof(buf));
                if(ret==0){//对端断开连接
                    event.data.fd=newFd;
                    epoll_ctl(epollfd,EPOLL_CTL_DEL,newFd,&event);//将断开连接的文件描述符移出监听队列
                    close(newFd);//关闭
                    break;//退出for循环
                }
                puts(buf);
            }
        }//end for
    }//end while
end:
    close(epollfd);
    close(socketfd);
}
```



### 水平触发和边缘触发

epoll 对文件描述符的操作有两种模式：LT（level trigger）水平触发和 ET（edge trigger）边缘触发。LT 模式是默认模式

####  LT (level trigger，水平触发)模式

当 epoll_wait 检测到描述符事件发生并将此事件通知应用程序，应用程序可以不立即处理该事件。下次调用 epoll_wait 时，会再次响应应用程序并通知此事件。

缓冲区只要有数据，就会触发，即缓冲区里有数据就认为描述符就绪，缓冲区数据被读完，则变回未触发状态

![image-20200323163210290](D:\TyporaPic\复习笔记Linux\image-20200323163210290.png)

####  ET (edge trigger，边缘触发)模式

当 epoll_wait检测到描述符事件发生并将此事件通知应用程序，应用程序必须立即处理该事件。如果不处理，下次调用 epoll_wait 时，不会再次响应应用程序并通知此事件。

对方发送一次，则相应的只会触发一次而不是一直处于触发状态，数据缓冲区有上升沿(数据缓冲区内容增加)就会触发，可以降低epoll_wait的触发次数，因此效率要比 LT 模式高。epoll工作在ET模式的时候，必须使用非阻塞套接口，以避免由于一个文件句柄的阻塞读/阻塞写操作把处理多个文件描述符的任务饿死。

![image-20200323163343925](D:\TyporaPic\复习笔记Linux\image-20200323163343925.png)



比如接收的字符数组长度为10，发送方一次发送了20个字节，如果是水平触发，则会将20个字节一次分两行打印出来，而如果是边缘触发，则只会打印10个字节，剩余的10个字节仍然在接收缓冲区中，需要等到下一次对方发送了数据，才会把上一次剩下的的10个字节读下来

```c
struct epoll_event event;
event.events=EPOLLIN|EPOLLET;//设置为监听读事件，边缘触发
```

常配合非阻塞减少epoll_wait的触发次数

### 阻塞和非阻塞

#### 阻塞的情况

```c
int main(){
    cha buf[128]={0};
    int ret;
    sleep(5);//验证缓冲区是被提前搬运进来的
    ret=read(0,buf,sizeof(buf));
    printf("ret=%d,buf=%s\n",ret,buf);
    return 0;
}
```

内核会把网卡中的数据搬运到内核协议栈中，即使此时进程在sleep，缓冲区也已经有数据等待read了，因此如果什么都不输入，会阻塞在read

#### 非阻塞的情况

```c
int setNonBlock(int fd){
    int status;//文件的状态
    status=fcntl(fd,F_GETFL);//获取文件描述符在内核的状态
    status=status|O_NONBLOCK;//添加非阻塞属性
    fcntl(fd,F_SETFL,status);//重新设置回内核
    return 0;
}

int main(){
    setNonBlock(0);
    cha buf[128]={0};
    int ret;
    sleep(5);//验证缓冲区是被提前搬运进来的
    ret=read(0,buf,sizeof(buf));
    printf("ret=%d,errno=%d,buf=%s\n",ret,errno,buf);
    return 0;
}
```

这样的话即使什么都不输入，5秒后也会自动结束，返回ret=-1

可以用于检测哪些用户已经不再发送数据了，可以for循环遍历所有文件描述符

错误码errno为11

#### 边缘触发情况下的非阻塞编程

在边缘触发的情况下，如果一次性发送很大的数据，而接收的数组又很小的话，就无法一次recv读空数据了，因此需要将客户端连接的文件描述符设置为非阻塞的

```c
event.events=EPOLLIN|EPOLLET;//设置为边缘触发
//...
newFd=accept(socketfd,NULL,NULL);
setNonBlock(newFd);//将newFd设置为非阻塞的
```

#### send的阻塞和非阻塞的情况

客户端一直发送数据，但是服务器端不接收数据

如果是阻塞的：在缓冲区满之前，send会返回第三个参数的值，在发送缓冲区被填满后，客户端的send函数会阻塞，直到客户端的发送缓冲区有空位存放这次send的数据

如果是非阻塞的：在把发送缓冲区填满的那次会返回实际发往缓冲区的字节数，再下一次会直接返回-1，不会阻塞等待缓冲区有空位

非阻塞的好处：比如同时给多个客户端发送数据，如果一个客户端的网络波动较大，发送缓冲区填满了，就会造成程序阻塞，会影响其他客户端的数据发送，而采用非阻塞编程就不会出现这种问题

#### recv的阻塞和非阻塞的情况

把recv的第四个参数改为`MSG_DONTWAIT`，单次生效的非阻塞

# day26

## select、poll和epoll对比

https://www.cnblogs.com/aspirant/p/9166944.html

### select原理概述

#### 调用select时，会发生以下事情：

使用copy_from_user从用户空间拷贝fd_set到内核空间

注册回调函数__pollwait

遍历所有fd，调用其对应的poll方法(_pollwait)，主要工作就是把current（当前进程）挂到设备的等待队列中。在设备收到一条消息（网络设备）或填写完文件数据（磁盘设备）后，会唤醒设备等待队列上睡眠的进程，这时current便被唤醒了。

poll方法返回时会返回一个描述读写操作是否就绪的mask掩码，其中的各个位指示当前的不同的就绪状态（全0为没有任何事件触发），根据mask可对fd_set赋值；

如果遍历完所有的fd，还没有返回一个可读写的mask掩码，则会调用schedule_timeout使调用select的进程（也就是current）进入睡眠。当设备驱动发生自身资源可读写后，会唤醒其等待队列上睡眠的进程。如果超过一定的超时时间（schedule_timeout指定），还是没人唤醒，则调用select的进程会重新被唤醒获得CPU，进而重新遍历fd，判断有没有就绪的fd。

把fd_set从内核空间拷贝到用户空间。

### select的缺点

内核/用户空间内存拷贝问题：每次调用select，都需要把fd_set集合从用户态拷贝到内核态，并且每次要把当前进程挂在描述符的等待队列上，开销大。

最大并发数限制：使用32个整数的32位，即32*32=1024来标识fd(32位系统，64位系统每个整数64位)，虽然可修改，但是有以下的瓶颈

效率低：select只知道有IO事件发生，但是不知道是哪个流，需要自己不断轮询所有fd集合，直到设备就绪，期间内核可能要睡眠和唤醒多次交替，集合越大速度越慢(O(N))；

### poll原理

poll的实现和select非常相似，只是描述fd集合的方式不同，poll使用pollfd结构而不是select的fd_set结构，其他的都差不多,管理多个描述符也是进行轮询，根据描述符的状态进行处理，**但是poll没有最大文件描述符数量的限制**。

poll和select同样存在一个缺点就是，包含大量文件描述符的数组被整体复制于用户态和内核的地址空间之间，而不论这些文件描述符是否就绪，它的开销随着文件描述符数量的增加而线性增大。

### epoll的原理

#### epoll_create 

内核帮我们在epoll文件系统里建了个file结点；

在内核cache里建了个红黑树用于存储以后epoll_ctl传来的socket；

建立一个list链表，用于存储准备就绪的事件。

#### epoll_ctl

把需要监听的描述符挂在红黑树上，后面修改和删除的时候先到红黑树上查找。

给内核中断处理程序注册一个该文件描述符的回调函数，把当前进程挂载等待队列上，描述符就绪的时候，执行回调函数，回调函数把描述符放到就绪链表上

即	文件描述符就绪->调用回调函数->把文件描述符挂到就绪链表上等待epoll_wait探查到

#### epoll_wait

检查就绪链表，没有数据就sleep，等到timeout时间到后即使链表没数据也返回。

如果不为空，epoll_wait醒来，把就绪的描述符拷贝到evs结构体数组里，同时返回就绪描述符的数量

通常情况下即使我们要监控百万计的描述符，大多一次也只返回很少量的准备就绪描述符而已，所以，epoll_wait仅需要从内核态copy少量的描述符到用户态而已。

#### 小结

内核中一棵红黑树，一张准备就绪描述符链表，少量的内核cache，解决了大并发下的socket处理问题。

执行epoll_create时，创建了红黑树和就绪链表； 

执行epoll_ctl时，如果增加socket描述符，则检查在红黑树中是否存在，存在立即返回，不存在则添加到树干上，然后向内核注册回调函数，用于当中断事件来临时向准备就绪链表中插入数据; 

执行epoll_wait时立刻返回准备就绪链表里的数据即可。



### epoll的提升

select 监控描述符有限 1024,而epoll本身没有最大并发连接的限制，仅受系统中进程能打开的最大文件数目限制，具体数目可以cat /proc/sys/fs/file-max察看

每次注册新的事件到epoll句柄中时（在epoll_ctl中指定EPOLL_CTL_ADD），会把所有的fd拷贝进内核，而不是在epoll_wait的时候重复拷贝。epoll保证了每个fd在整个过程中只会拷贝一次。

epoll 内核采用红黑树和就绪链表，当设备就绪，唤醒等待队列上的等待者时，就会调用回调函数，而这个回调函数会把就绪的fd加入一个就绪链表，epoll_wait的工作实际上就是在这个就绪链表中查看有没有就绪的fd，如果不为空，则只把发生的事件复制到用户态

## 短连接和长连接

短连接	http1.0		connect	send1次	recv1次	close	无状态编程，不需要知道客户端什么状态

长连接	http1.1		有状态编程，服务器能同步客户端的状态(客户端都做了什么事)	



## epoll_wait超时机制

超时返回0.成功返回就绪描述符数目，出错返回-1

```c
void test(){
    time_t pastTime,nowTime;//记录用户上一次操作的时间和当前操作的时间
    pastTime=nowTime=time(NULL);
    while(1){
        readyCount=epoll_wait(epollfd,evs,2,1000);//超时1秒返回
        for(int i=0;i!=readyCount;++i){
            //...
            pastTime=time(NULL);//最近一次操作计时
        }
        if(readyCount==0){//超时返回
            nowTime=time(NULL);
            if(nowTime-pastTime>=5){//超时5秒断开客户端
                close(newFd);
                break;
            }
        }
    }
}
```

可以设置一个结构体存放多个用户的文件描述符和计时器

### 针对多个用户处理超时问题的轮盘法

设计一个轮盘(数组)，容量就是超时上限，元素全部是单链表，每过一秒，就更新数组的元素，将单链表上的连接全部结束

每当有一个新连接到来，就把他放在数组的第1个元素的链表上，每次进行读写操作都修改他在数组的位置

更好的设计：在存放用户连接信息的结构体加入Pos数据成员代表他在数组的哪里，而不是真的插入到数组里(即抽象一个数组)，初始为0，每次读写操作时修改值

## send和recv的第四个flag参数

通常不需要特殊处理可以直接填0，但是也可以用以下宏作为特殊用途

### MSG_PEEK

已经读完的数据不会删除，仍然保存在缓冲区中

用于任务转发时仍保持原本的数据、提前分析数据

### MSG_DONTWAIT

单次recv非阻塞

比如一般recv都会阻塞直到对端发送数据过来，但是在recv的时候添加这个参数就不会阻塞了，如果运行到这里没有数据接收会直接返回-1



## 五种IO模型

同步阻塞

同步非阻塞

多路复用

信号驱动

异步

### 同步和异步

同步和异步关注的是消息通信机制，即程序中的协作关系(自己获取/其他线程通知)

同步：执行一个操作之后，进程触发IO操作并等待(也就是我们说的阻塞)或者轮询的去查看IO操作(也就是我们说的非阻塞)是否完成，等待结果，然后才继续执行后续的操作。

异步：执行一个操作后，可以去执行其他的操作，然后等待通知再回来执行刚才没执行完的操作。

真正的异步IO需要CPU的深度参与。换句话说，只有用户线程在操作IO的时候根本不去考虑IO的执行全部都交给CPU去完成，而自己只等待一个完成信号的时候，才是真正的异步IO。所以，拉一个子线程去轮询、去死循环，或者使用select、poll、epoll，都不是异步。

### 阻塞和非阻塞

阻塞与非阻塞这一对词关注的是用户态进程/线程(程序)的状态、其要访问的数据是否就绪，进程/线程是否需要等待，即单个进程/线程的执行状态

阻塞：进程给CPU传达一个任务之后，一直等待CPU处理完成，然后才执行后面的操作。

非阻塞：进程给CPU传达任务后，继续处理后续的操作，隔断时间再来询问之前的操作是否完成。这样的过程其实也叫轮询。

## 进程池

### 解决文件描述符的传递

父子进程文件描述符是相互独立的

#### 第一步：初始化socketpair管道描述符

```c
int fds[2];
socketpair(AF_LOCAL,SOCK_STREAM,0,fds);//全双工管道
```

#### 第二步：父进程sendmsg发送描述符

由内核进行操作，并不是内核->用户态A->用户态B->内核，而是内核间在操作系统层面上的映射

```c
ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags);
```

```c
int sendFd(int pipeFd,int fd){//pipeFd为上一步初始化的管道一端，fd表示要传递的描述符
    struct msghdr msg;
    bzero(&msg,sizeof(msg));
    /*这里目前随便写，以后要用来实现退出机制*/
    struct iovec iov[2];
    char buf1[10]="hello";
    iov[0].iov_base=buf1;
    iov[0].iov_len=5;
    char buf2[10]="world";
    iov[1].iov_base=buf2;
    iov[1].iov_len=5;
    /*					*/
    msg.msg_iov=iov;
    msg.msg_iovlen=2;
    
    struct cmsghdr *cmsg;
    int cmsgLen=CMSG_LEN(sizeof(int)*1);//传1个文件描述符所要的空间大小
    cmsg=(struct cmsghdr *)calloc(1,cmsgLen);
    cmsg->cmsg_len=cmsgLen;
    cmsg->cmsg_level=SOL_SOCKET;
    cmsg->cmsg_type=SCM_RIGHTS;
    
    *(int *) CMSG_DATA(cmsg)=fd;//把要传递的描述符告诉内核
    
    msg.msg_control=cmsg;
    msg.msg_controllen=cmsgLen;
    
    int ret=sendmsg(pipeFd,&msg,0);//第三个参数填0即可
    ERROR_CHECK(ret,-1,"sendmsg");
    return 0;
}
```

#### 第三步：子进程recvmsg接收描述符

```c
int recvFd(int pipeFd,int *fd){
    struct msghdr msg;
    bzero(&msg,sizeof(msg));
    /*这里目前随便写，以后要用来实现退出机制*/
    struct iovec iov[2];
    char buf1[10]="hello";
    iov[0].iov_base=buf1;
    iov[0].iov_len=5;
    char buf2[10]="world";
    iov[1].iov_base=buf2;
    iov[1].iov_len=5;
    /*					*/
    msg.msg_iov=iov;
    msg.msg_iovlen=2;
    
    struct cmsghdr *cmsg;
    int cmsgLen=CMSG_LEN(sizeof(int)*1);//传1个文件描述符所要的空间大小
    cmsg=(struct cmsghdr)calloc(1,cmsgLen);
    cmsg->cmsg_len=cmsgLen;
    cmsg->cmsg_level=SOL_SOCKET;
    cmsg->cmsg_type=SCM_RIGHTS;
    
    msg.msg_control=cmsg;
    msg.msg_controllen=cmsgLen;
    
    int ret=recvmsg(pipeFd,&msg,0);
    ERROR_CHECK(ret,-1,"recvmsg");
    
    *fd=*(int *) CMSG_DATA(cmsg);
    return 0;
}
```

#### 使用举例

```c
int main(){
    int fds[2];//类似tcp的两端
    int ret;
    ret=socketpair(AF_LOCAL,SOCK_STREAM,0,fds);//全双工管道
    ERROR_CHECK(ret,-1,"socketpair");
    if(!fork()){
        close(fds[1]);
        int fd;
        recvFd(fds[0],&fd);
        printf("i am child,fd=%d\n",fd);
        char buf[128]={0};
        read(fd,buf,sizeof(buf));
        printf("i am child,buf=%s\n",buf);
    }else{
        close(fds[0]);
        int fd=open("file",O_RDWR);
        printf("i am parent,fd=%d\n",fd);
        sendFd(fds[1],fd);
        wait(NULL);
    }
    return 0;
}
```

### 进程池的目的

多核情况下top查看的占用率时，满负载为核数*100%

进程池有利于充分利用多核优势

### 进程池工作流程

同步编程

每当新客户端请求，就找一个空闲进程执行任务

子进程执行任务结束后通知父进程

### 父进程管理子进程所使用的数据结构

保存子进程信息：子进程ID，管道，进程状态

```c
typedef struct{
     pid_t pid;//子进程的 pid
     int pipefd;//管道的一端,socketpair管道
     short busy;//代表子进程是否忙碌，0 代表非忙碌，1 代表忙碌
}process_data_t;
```

当父进程处在epoll_wait状态时，为了能让父进程在等待状态知道哪一个子进程已经执行完成需要标记为非忙碌，就可以用epoll监控每一个子进程的管道fd，如果监控到fd有写，即可认为该子进程空闲

### 进程池代码编写流程

#### 第一步：

make_child 函数初始化子进程

循环创建子进程，并初始化父进程的子进程管理结构体数组 parr，通过 socket_pair 将 socket描述符一端放入数组，子进程数目传参

```c
int makeChild(process_data_t *p,int processNum){
    int fds[2];
    int i;
    pid_t pid;
    int ret;
    for(i=0;i!=processNum;++i){
        ret=socketpair(AF_INET,SOCK_STREAM,0,fds);
        pid=fork();
        if(pid==0){//子进程
            close(fds[0]);
            childHandle(fds[1]);
        }else{//父进程
            close(fds[1]);
            p[i].pid=pid;
            p[i].pipefd=fds[0];
            p[i].busy=0;
        }
    }
}
```

#### 第二步

子进程流程，目前让子进程死循环，接收任务，给客户端发文件，然后通知父进程完成任务，退出机制暂时先不考虑

```c
While(1){
    Recv_fd 等待父进程发送任务
    Hand_request 发送文件数据
    Write 向父进程发送完成任务
}
```

```c
int childHandle(int pipefd){
    int newFd;
    char finishFlag;
    while(1){
        recvFd(pipefd,&newFd);//父进程没有发送任务时子进程会阻塞在这里，发送过来的是描述客户端的文件描述符
        //...发送文件
        write(pipefd,&finishFlag,1);//通知父进程完成任务
    }
}
```



#### 第三步：

父进程 epoll 监控 fd_listen 描述符。

父进程 epoll 监控 parr 结构体数组的 socket 描述符，结构体数组中的描述符是每一个子进程的管道对端，通过监控这个，当子进程通过 write 向我们写通知时，我们就知道子进程非忙碌了。

```c
int tcpInit(char *ip,char *port,int *fd){
    int socketfd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in addr;
    bzero(&addr,sizeof(addr));
    addr.sin_port=htons(atoi(port));
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr(ip);
    int reuse=1;
    int ret=setsockopt(socketfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
    ret=bind(socketfd,(struct sockaddr *)&addr,sizeof(addr));
    ERROR_CHECK(ret,-1,"bind");
    listen(socketfd,10);
    *fd=socketfd;
    return 0;
}

int epollInAdd(int epollfd,int fd){
    struct epoll_event event;
    event.flag=EPOLLIN;
    event.data.fd=fd;
    int ret=epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    return 0;
}

int main(int argc,char *argv[]){
    ARGS_CHECK(argc,4);
    int processNum=atoi(argv[3]);//进程数
    process_data_t *pdata=(process_data_t *)calloc(processNum,sizeof(process_data_t));
    makeChild(pdata,processNum);
    
    int socketfd;
    tcp_init(argv[1],argv[2],&socketfd);//ip port fd
    
    int epollfd=epoll_create(1);
    struct epoll_event evs[processNum+1];
    epollInAdd(epollfd,socketfd);
    for(int i=0;i!=processNum;++i){
        epollInAdd(epollfd,pdata[i].pipefd);
    }
}
```



#### 第四步：

while 1 启动 epoll_wait，等待是否有客户端连接

有客户端连接后，accept 获得描述符，循环找到非忙碌的子进程，并发送给子进程，标记对应子进程忙碌。

当子进程完成任务后，父进程一旦监控 socket 描述符可读，代表子进程非忙碌，然后标记子进程非忙碌。

```c
int main(int argc,char *argv[]){
    ARGS_CHECK(argc,4);
    int processNum=atoi(argv[3]);//进程数
    process_data_t *pdata=(process_data_t *)calloc(processNum,sizeof(process_data_t));
    makeChild(pdata,processNum);
    
    int socketfd;
    tcp_init(argv[1],argv[2],&socketfd);//ip port fd
    
    int epollfd=epoll_create(1);
    struct epoll_event evs[processNum+1];
    epollInAdd(epollfd,socketfd);
    for(int i=0;i!=processNum;++i){
        epollInAdd(epollfd,pdata[i].pipefd);
    }
    int readyCount,newFd,j;
    char noBusyFlag;
    while(1){
        readyCount=epoll_wait(epollfd,evs,processNum+1,-1);
        for(int i=0;i!=readyCount;++i){
            if(evs[i].data.fd==socketfd){
                newFd=accept(socketfd,NULL,NULL);
                //查询空闲子进程
                for(j=0;j<processNum;++j){
                    if(pdata[j].busy==0){
                        sendFd(pdata[j].pipefd,newFd);
                        pdata[j].busy=1;
                        break;
                    }
                }
                close(newFd);//sendFd就相当于跨进程的dup，一个进程可以拥有多个端口，一个端口也可以被多个进程使用，此时端口的引用计数为2，子进程关闭描述符的时候并不会发送FIN结束标识，因为父进程此时还占用该端口，所以在吧文件描述符发送给客户端后要把父进程的关闭
            }
            
            for(j=0;j!=processNum;++j){
                if(evs[i].data.fd=pdata[j].pipiefd){//子进程任务已完成
                    read(pdata[j].pipefd,noBusyFlag,1);
                    pdata[j].busy=0;
                    break;
                }
            }
        }//for
    }//while
    close(epollfd);
    close(socketfd);
}
```

```c
int childHandle(int pipefd){
    int newfd;
    char finishflag;
    while(1){
        recvFd(pipefd,&newfd);
        tranfile(newFd);
        close(newFd);
        write(pipefd,&finishflag,1);
    }
}
```



### 文件传输

1、发送文件名给客户端

2、传输文件内容

3、发送结束标志		不一定是strlen，因为tcp封装成了字符串，以后其他的私有协议设计不一定是字符串

#### 要注意的问题

##### TCP 粘包问题

可以理解为发送速度快，接受速度慢，无法区分边界

```
问题描述:发送方多次send的数据停留在接收方的接收缓冲区里，导致多次send的数据不能清晰的分辨出来，造成混乱。

举例：
	我们希望的流程是：发送("hello"),接收("hello"),发送("world"),接收("world");
	实际的流程可能是：发送("hello"),发送("wo"),接收("hellowo"),接收("rld");

解决方法：
	小火车：增加控制信息，火车头记录发送字节数，火车车厢装真正要发的数据。
	接收方接收的时候，先接火车头，按照火车头记载的长度精确去接后面的数据。这样就不会把多次发送的数据接到一起，造成混淆

```

##### 发送速度慢，接受速度快问题

常出现在发送大文件时

```
问题描述：接收方想接41000个字节，但是发送方发送速度慢，接收方的接收缓冲区中只有300个字节，recv读了300个字节之后，就会返回。

举例
	发送方：本来每次要发4个字节火车头+1000个字节火车内容，但是第一次只发了4个字节+300个字节，第二次发了700个字节，第三次发4个字节火车头+1000字节内容。
	接收方：本来每次要接4个字节火车头+1000个字节火车内容，但是发送方发的慢，第一次到缓冲区取数据的时候，缓冲区只有4个字节头部和300个字节内容，此时虽然没有接完1004个字节，但是缓冲区中有数据，recv也会返回，返回值为104，下一次再接的时候还是先接火车头的4个字节，但是此时缓冲区中可能只有第二次发过来的700个字节内容，因此会把这700个字节里的前4个字节当做火车头来接。这就导致数据错乱。

解决方法：recvCycle(int fd,void *buf, int recvLen)
	定义一个函数，只有真正从缓冲区读了recvLen个字节的数据后，才返回，代替recv，这样就能够保证接到足够的数据。
	或者使用recv的flag的MSG_WAITALL(接收到size大小的字节数后才返回)，但是较大的文件仍然会失败(400M的文件)
```

##### 断开

服务器给客户端发送文件，如果发送过程中，客户端断开，服务器仍在发送文件，第一次send会返回-1，第二次send时调用send的子进程会收到SIGPIPE信号，子进程收到信号终止之后，父子进程间的管道会变成就绪状态，父进程的epoll会一直唤醒。为了避免子进程收到信号终止，每次send判断send的返回值是否为-1，如果是-1，就停止发送，直接返回。

#### 协议设计

```c
typedef struct{
    int dataLen;//当前发送的buf的内容长度
    char buf[1000];//火车车厢，不超过64k即可
}train_t;
```

#### 示例

```c
void sigFunc(int signum){
    printf("%d is coming\n",signum);
}

int tranfile(int newFd){
    signal(SIG_PIPE,sigFunc);//防止send出错返回的13号信号让整个程序挂掉
	train_t train;
    train.dataLen=strlen(FILENAME);
    strcpy(&train.buf,FILENAME);
    send(newFd,&train,train.datalen+4,0);
    int filefd=open(FILENAME,O_RDWR);
    int ret;
    while(train.datalen=read(filefd,train.buf,sizeof(train.buf))){
        ret=send(newFd,&train,train.datalen+4,0);
        if(ret==-1){//客户端提前断开
            return -1;
        }
    }
    send(newFd,&train,4,0);//文件结束标志，train发送过去的那一部分正好是最后一次read返回的0
    return 0;
}
```

```c
int recvCycle(int fd,void *buf,int recvLen){//void *无类型
    char *p=(char *)buf;//表明接收的都是字符
    int total=0;
    while(total<recvLen){
        ret=recv(fd,p,recvLen,0);
        total+=ret;
    }
    return 0;
}

int main(int argc,char *argv[]){
    ARGS_CHECK(argc,3);
    int socketfd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in addr;
    bzero(&addr,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_port=htons(atoi(argv[2]));
    addr.sin_addr.s_addr=inet_addr(argv[1]);
    connect(socketfd,(struct sockaddr *)&addr,sizeof(addr));
    char buf[1000]={0};
    int datalen;
    recvCycle(socketfd,&datalen,4);//文件名大小
    recvCycle(socketfd,buf,datalen);//文件名
    int filefd=open(buf,O_CREAT|O_RDWR,0600);
    while(1){
        recvCycle(socketfd,&datalen,4);
        if(datalen>0){
            recvCycle(socketfd,buf,datalen);
            write(filefd,buf,datalen);//电影或音乐有大量的0，因此不能用strlen
        }else{
            break;//发送完毕
        }
    }
    close(filefd);
    close(socketfd);
}
```

#### 服务器端先发送文件大小，再传输文件内容

可以用作断点重连、传输进度条显示等

```c
void sigFunc(int signum){
    printf("%d is coming\n",signum);
}

int tranFile(int newFd){
    signal(SIG_PIPE,sigFunc);
    int filefd=open(FILENAME,O_RDWR);
    train_t train;
    bzero(&train,sizeof(train));
    train.datalen=sizeof(FILENAME);
    strcpy(train.buf,FILENAME);
    send(newFd,&train,train.datalen+4,0);//第一次仍然是发送文件名
    struct stat file;
    fstat(filefd,&file);
    train.datalen=sizeof(file.st_size);
    memcpy(train.buf,&file.st_size,train.datalen);
    send(newFd,&train,train.datalen+4,0);//第二次发送文件大小
    int ret;
    while(train.datalen=read(filefd,train.buf,sizeof(trian.buf))){
        ret=send(newFd,&train,train.datalen+4,0);
        if(ret==-1){
            return -1;
        }
    }
    send(newFd,&train,4,0);//文件结束标志，train发送过去的那一部分正好是最后一次read返回的0
}
```

```c
int main(int argc,char *argv[]){
    ARGS_CHECK(argc,3);
    int socketfd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in addr;
    bzero(&addr,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_port=htons(atoi(argv[2]));
    addr.sin_addr.s_addr=inet_addr(argv[1]);
    connect(socketfd,(struct sockaddr *)&addr,sizeof(addr));
    
    char buf[1000]={0};
    int datalen;
    recvCycle(socketfd,&datalen,4);//文件名大小
    recvCycle(socketfd,buf,datalen);//文件名
    int filefd=open(buf,O_CREAT|O_RDWR,0600);
    
    off_t receiveSize=0,fileSize=0;
    recvCycle(socketfd,&datalen,4);//文件长度大小
    recvCycle(socketfd,&fileSize,datalen);//文件长度
    
    time_t lastTime,nowTime;
    struct timeval start,end;
    lastTime=nowTime=time(NULL);
    gettimeofday(&start,NULL);
    while(receiveSize<fileSize){
        recvCycle(socketfd,&datalen,4);
        if(datalen>0){
            recvCycle(socketfd,buf,datalen);
            write(filefd,buf,datalen);
            receiveSize+=datalen;
            time(&nowTime);
            
            if(nowTime-lastTime>=1){//每隔1秒刷新一次进度条
				printf("%5.2f%s\r",(float)receiveSize/fileSize*100,"%");
                fflush(stdout);
                lastTime=nowTime;
            }
        }else{
            printf("100.00%%\n");
            break;
        }
    }
    gettimeofday(&end,NULL);
    printf("use time=%ld\n",(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec);
    close(filefd);
    close(socketfd);
}
```

### 提升效率 零拷贝

零拷贝是指没有从内核态拷贝到用户态。更加现实的情况是，系统的性能瓶颈往往是网络IO

read+send的缺点：先从内核缓冲区读到用户态缓冲区，又从用户态缓冲区拷贝到socket缓冲区，多次拷贝，效率低。

mmap方式：将内核缓冲区与用户共享，这样能减少内核缓冲区到用户缓冲区的之间的复制。只能提升服务器端的速度

sendfile：
	sendfile在内核里把数据从一个描述符缓冲区拷贝到另一个描述符缓冲区，不需要经历，从内核拷贝到用户空间的过程，因此效率更高。
	sendfile的一个限制是只能用于发送端。

splice：
	splice可以从两个文件描述符之间拷贝数据而不用经过用户地址空间

#### mmap

```c
int tranFile(int newFd){
    signal(SIG_PIPE,sigFunc);
    train_t train;
    int filefd=open(FILENAME,O_RDWR);
    train.datalen=sizeof(FILENAME);
    strcpy(train.buf,FILENAME);
    send(newFd,&train,train.datalen+4,0);//发送文件名
    struct stat file;
    fstat(filefd,&file);
    train.datalen=sizeof(file.st_size);
    memcpy(train.buf,&file.st_size,train.datalen);
    send(newFd,&train,train.datalen+4,0);//发送文件大小
    char *pMap=(char *)mmap(NULL,file.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,filefd,0);
    send(newFd,pMap,file.st_size,0);//直接开大火车一次全部发送过去
    send(newFd,&train,4,0);//结束标志
}
```

```c
//客户端
void receiveFile(int socketFd){
    int datalen;
    off_t fileSize;
    char buf[1000]={0};
    recvCycle(socketFd,&datalen,4,0);
    recvCycle(socketFd,buf,datalen,0);//文件名
    recvCycle(socketFd,&datalen,4,0);
    recvCycle(socketFd,&fileSize,datalen,0);//文件长度
    int filefd=open(buf,O_RDWR|O_CREAT,0666);
    ftruncate(filefd,fileSize);//先建立相同大小的文件
    char *pMap=(char *)mmap(NULL,fileSize,PORT_READ|PORT_WRITE,MAP_SHARED,filefd,0);
    recvCycle(socketfd,pMap,fileSize,0);
    munmap(pMap,fileSize);
}
```

#### sendfile

内存充足的情况下可以使用mmap，内存不足的情况下使用sendfile，因为sendfile没有开辟额外的内存空间

sendfile不能传输大于2g的文件

零拷贝是指没有从内核态拷贝到用户态

```c
#include<sys/sendfile.h>
ssize_t sendfile(int out_fd,int in_fd,off_t *offset,size_t count);//成功返回传输的字节数，in必须是文件描述符(从哪里读)，而out只要是描述符即可(发送到哪里的缓冲区)
```

```c
int sendFile(int newFd){
    sendfile(newFd,fileFd,0,file.st_size);
}
```

#### splice

从socket描述符到文件描述符

搬运时需要借助一条管道pipe

```c
#define _GNU_SOURCE	//宏开关，加在头文件前面
#include<fcntl.h>

ssize_t splice(int fd_in,loff_t *off_in,int fd_out,loff_t *off_out,size_t len,unsigned int flags);//fd_out要是pipe的，不能直接是文件
//返回值是写入管道的字节数或者是从管道读出的字节数
```

```c
void receiveFile(int socketFd){
    int datalen;
    off_t fileSize;
    char buf[1000]={0};
    recvCycle(socketFd,&datalen,4,0);
    recvCycle(socketFd,buf,datalen,0);//文件名
    recvCycle(socketFd,&datalen,4,0);
    recvCycle(socketFd,&fileSize,datalen,0);//文件长度
    int filefd=open(buf,O_RDWR|O_CREAT,0666);
    
    int fds[2],ret;
    pipe(fds);
    off_t receiveSize=0;
    while(receiveSize<fileSize){
        ret=splice(socketfd,NULL,fds[1],NULL,32767,SPLICE_F_MOVE|SPLICE_F_MORE);//从socketfd搬运到fds[1]，每次搬运32767字节.ret表示实际搬运的字节数
        splice(fds[0],NULL,filefd,NULL,ret,SPLICE_F_MOVE|SPLICE_F_MORE);//从管道搬运到内核
        receiveSize+=ret;
    }
}
```

### 进程池的退出

只考虑服务器端的

```
1、父进程收到信号，直接杀掉子进程，回收每一个子进程
2、父进程收到信号，通知子进程退出，子进程退出

子进程如果在进行重要业务，则可以用sigprocmask暂时屏蔽信号
```

#### 第一种情况

```
全局变量的一对管道，一端交给epoll监听，另一端交给信号处理函数
main函数	创建信号处理函数，写管道，在epoll中监听管道的读端

```

```c
int exitFds[2];
void sigFunc(int sigNum){
    write(exitFds[1],&sigNum,1);//写一下管道，在进程池的epoll监听另一端
}
int main(){
    //...
    //记得先创建完子进程再创建管道，防止管道被子进程继承拷贝了
    pipe(exitFds);
    signal(SIGUSR1,sigFunc);//10号信号
    epollInAdd(epollfd,exitFds[0]);//添加对退出管道的监听
    //...
    if(evs[i].data.fd==exitFds[0]){//退出机制
        for(j=0;j!=processNum;++j){
            kill(pData[j].pid,SIGUSR1);//SIGUSR1如果没有信号处理的话默认是13号信号,子进程没有设置信号处理函数，会直接被杀掉
        }
        for(j=0;j!=processNum;++j){//先全部通知，再统一wait，节省时间
            wait(NULL);
        }
        exit(0);//服务器退出
    }
}
```



#### 第二种情况

在传递描述符的时候要加一个退出标志，平时保持0，退出时发送1

```
修改send_fd	额外传递一个退出信号
修改main		额外监听一个接收退出信号的管道，收到退出会用sendFd发送给每个子进程
修改child		接收时判断recvFd的最后一个参数是否为1，为1则退出
```

```c
int sendFd(int pipeFd,int fd,char childExitFlag)//多了一个参数
{
    struct msghdr msg;
    bzero(&msg,sizeof(msg));
    struct iovec iov[2];
    iov[0].iov_base=&childExitFlag;//不退出的是0
    iov[0].iov_len=1;//这里是1个字节
    char buf2[10]="world";
    iov[1].iov_base=buf2;
    iov[1].iov_len=5;
    msg.msg_iov=iov;
    msg.msg_iovlen=2;
    struct cmsghdr *cmsg;
    int cmsgLen=CMSG_LEN(sizeof(int));
    cmsg=(struct cmsghdr *)calloc(1,cmsgLen);
    cmsg->cmsg_len=cmsgLen;
    cmsg->cmsg_level=SOL_SOCKET;
    cmsg->cmsg_type=SCM_RIGHTS;
    *(int *)CMSG_DATA(cmsg)=fd;//要把传递的描述符告诉内核
    msg.msg_control=cmsg;
    msg.msg_controllen=cmsgLen;
    int ret;
    ret=sendmsg(pipeFd,&msg,0);
    ERROR_CHECK(ret,-1,"sendmsg");
    return 0;
}
int recvFd(int pipeFd,int *fd,char* childExitFlag)//传入传出参数char *
{
    struct msghdr msg;
    bzero(&msg,sizeof(msg));
    struct iovec iov[2];
    iov[0].iov_base=childExitFlag;//调用recvFd接到sendFd传递来的退出标志
    iov[0].iov_len=1;
    char buf2[10]="world";
    iov[1].iov_base=buf2;
    iov[1].iov_len=5;
    msg.msg_iov=iov;
    msg.msg_iovlen=2;
    struct cmsghdr *cmsg;
    int cmsgLen=CMSG_LEN(sizeof(int));
    cmsg=(struct cmsghdr *)calloc(1,cmsgLen);
    cmsg->cmsg_len=cmsgLen;
    cmsg->cmsg_level=SOL_SOCKET;
    cmsg->cmsg_type=SCM_RIGHTS;
    msg.msg_control=cmsg;
    msg.msg_controllen=cmsgLen;
    int ret;
    ret=recvmsg(pipeFd,&msg,0);
    ERROR_CHECK(ret,-1,"recvmsg");
    *fd=*(int*)CMSG_DATA(cmsg);
    return 0;
}
```

```c
int exitFds[2];
void sigFunc(int sigNum){
    write(exitFds[1],&sigNum,1);//写一下管道，在进程池的epoll监听另一端
}
int main(){
    //...
    //记得先创建完子进程再创建管道，防止管道被子进程继承拷贝了
    pipe(exitFds);
    signal(SIGUSR1,sigFunc);//10号信号
    epollInAdd(epollfd,exitFds[0]);//添加对退出管道的监听
    int status;
    pid_t pid;
    //...
    if(evs[i].data.fd==exitFds[0]){//退出机制
        for(j=0;j!=processNum;++j){
            sendFd(pData[j].pipeFd,0,1);//退出发送1，第二个参数无所谓
        }
        for(j=0;j!=processNum;++j){//先全部通知，再统一wait，节省时间
            pid=wait(&status);
            if(WIFEXITED(status)){
                printf("%d exit code is %d\n",pid,WEXITSTATUS(status));
            }
        }
        exit(0);//服务器退出
    }
    
    if(evs[i].data.fd==socketfd){
        newFd=accept(socketfd,NULL,NULL);
        for(j=0;j!=processNum;++j){
            if(pdata[j].busy==0){
                sendFd(pdata[j].pipefd,newFd,0);//平常使用的时候还是置0
                pdata[j].busy=1;
            }
        }
        close(newFd);
    }
}
```

```c
int childHandle(int pipefd){
    int newFd;
    char finishFlag,exitFlag;
    while(1){
        recvFd(pipefd,&newFd,&exitFlag);
        if(exitFlag){//退出
            exit(0);
        }
        tranFile(newFd);
        close(newFd);
        write(pipeFd,&finishFlag,1);
    }
}
```

# day31

## 线程池

主线程连接客户端，收到socket连接后采用任务队列的方式存储newFd，因为同一个进程中的线程共享描述符，子线程启动后从任务队列取出任务进行处理(访问任务队列需要加解锁)，如果任务队列为空，则子线程要去条件变量cond_wait上排队等待，主线程将任务放入队列后要用cond_signal唤醒条件变量中等待的子线程取任务执行

![image-20200330095810618](D:\TyporaPic\复习笔记Linux\image-20200330095810618.png)

### 主要流程

#### 初始化线程池

初始化队列，队列头，队列尾初始化，队列能力初始化（队列长度），队列锁

初始化线程池条件变量

给子线程赋入口函数		如果有很多种业务则可以用函数指针进行管理

为线程池的子线程的线程 ID 申请空间

线程池是否启动标志初始化为 0

#### 启动线程池

循环启动子线程，设置线程池启动标志设置为 1

#### 主线程启动 listen，接收客户端请求

加锁，然后将接收到的 rs_fd 放入到 que 队列中，解锁，pthread_cond_signal 等待在对应条件上的子线程

### 进程池和线程池的对比

#### 进程池

优点：进程间资源相互独立，一个进程崩溃不会影响其他进程

缺点：进程启动速度慢，资源不共享，进程间切换速度慢，进程间通信开销大

#### 线程池

优点：线程间切换开销小，线程共享同一进程的数据，通信方便

缺点：不利于管理，一个线程崩溃会导致整个进程结束

#### 池的概念

先创建好一定数量的资源，统一管理，需要时到池子里拿创建好的资源进行分配

### 线程池的退出

不能直接发信号给线程池，因为所有线程共享信号处理函数，此时谁执行到信号相应时机就会响应谁。

因此可以用以下方法：

用fork创建父子进程，父进程注册信号处理函数，收到信号后，通过写管道通知子进程退出

线程池的启动由子进程进行，epoll监听socketFd和管道的读端，如果管道读端可读，表示要退出了，可以使用pthread_cancel或者是pthread_join两种方式退出

如果用pthread_cancel记得写线程清理函数处理锁资源的释放

如果用pthread_join要先把threadInfo的startFlag标识为0，然后用pthread_cond_broadcast进行一次广播，因为可能子线程在wait处阻塞了，因此就需要一次集体唤醒，在子线程的while循环的开头判断startFlag是否为0，如果为0，子线程就用pthread_exit退出

代码越多，越不稳定，为了防止进程崩溃导致客户端无法再接收服务，就采用上述方法，父进程可以用wait函数监控子进程，如果子进程的返回值为崩溃，就重新把子进程拉起来，事后再去分析子进程的相关日志

```c
while(fork()){
    //这里可以写接收退出的信号处理函数，用来对子进程发送结束信号
	//父进程,接收退出信号，用管道发送给子进程，子进程接收后cancel子线程
    int status;
    wait(&status);//父进程会卡在这里，而不会一直while
    if(WIFEXITED(status)){
        printf("程序正常结束\n");
        exit(0);
    }else{//异常挂掉的
        //重新走到while，再fork一个子进程重启线程池
    }
}
//这以下的就是子进程，即线程池的相关操作以及线程池的退出处理
```

### 子线程不判断queGet的返回值会出现什么问题

由于pthread_cond_wait分为上下两部分，即排队解锁睡觉----唤醒加锁，如果一个子线程在wait等待条件变量(互斥锁为解锁)，当父进程cond_signal唤醒了等待在条件变量的子线程时如果恰好另一个子线程刚传输完毕，就会抢到互斥锁(互斥锁变为加锁)，如果此时任务队列恰好为1，2号线程就会把任务拿走，此时1号任务就会卡在wait的加锁处，等2号线程拿到任务解锁后1号线程才会执行完wait，再去取任务就会拿到空任务

### 线程清理函数不要放在while(1)里

因为pop和push是一对do while宏

# day32

## SQL

### 关系型数据库

关系型数据库把复杂的数据结构归结为简单的二元关系，在存储数据时实际就是采用的一张二维表（和Word和excell里表格几乎一样）。

它通过SQL结构化查询语言来存取、管理关系型数据库的数据。

```sql
show databases;	/*显示存储于物理设备上的的数据库

也可以用Nevicat 图形化界面管理mysql

以下四个库是mysql自带的库*/
information_schema
mysql
performance_schema
sys
```

#### 数据库服务器、数据库和表的关系

```sql
use test;	/使用test数据库*/

show tables;	/显示当前数据库下的所有表*/
```

所谓安装数据库服务器，只是在机器上装了一个数据库管理程序，这个管理程序可以管理多个数据库，一般开发人员会针对每一个应用创建一个数据库。

为保存应用中实体的数据，一般会在数据库创建多个表，以保存程序中实体的数据。

数据库服务器、数据库和表的关系如图所示：

![image-20200331111011906](D:\TyporaPic\复习笔记Linux\image-20200331111011906.png)

对于数据库管理程序来说，我们是客户端

#### 数据在数据库中的存储方式

![image-20200331111550228](D:\TyporaPic\复习笔记Linux\image-20200331111550228.png)



### DDL 数据定义语言

DDL：Data Definition Language

作用：用于描述数据库中要存储的现实世界实体的语言。即创建数据库和表的结构。

常用关键字：

```c
CREATE 		//创建
ALTER 		//修改
DROP		//删除	 
TRUNCATE	//清空
```

#### 创建数据库

sql语言不区分大小写

```sql
CREATE {DATABASE | SCHEMA} [IF NOT EXISTS] db_name
    [create_specification [, create_specification] ...]
 
create_specification:
    [DEFAULT] CHARACTER SET charset_name	/*指定字符集*/

  | [DEFAULT] COLLATE collation_name	/*指定数据库字符集的比较方式

我们不太关心数据库是如何管理的，只是使用数据库管理系统提供的服务，因此上述的那些设定方式不太常用*/
```

如

```sql
create database testbase;	/*创建一个名为testbase的数据库*/
```

#### 查看、删除数据库

```sql
显示数据库语句：
SHOW DATABASES

显示数据库创建语句：即显示创建该数据库时用的ddl以及数据库的创建的各种属性
SHOW CREATE DATABASE db_name
 
数据库删除语句：
DROP DATABASE  [IF EXISTS]  db_name 
```

#### 修改、备份、恢复数据库

```sql
ALTER  DATABASE  [IF NOT EXISTS] db_name    
	[alter_specification [, alter_specification] ...] 
```

#### 创建表

```sql
先写列名，再写类型

CREATE TABLE table_name
(
	field1  datatype,
	field2  datatype,
	field3  datatype
)[character set 字符集 collate 校对规则]
field：指定列名　datatype：指定列类型

/*注意：创建表前，要先使用use db语句使用库。

注意：创建表时，要根据需保存的数据创建相应的列，并根据数据的类型定义相应的列类型。例：user对象
	id        	int                              
	name 		string
	password 	string
	birthday 	date

field列名、域、字段都是同一个意思*/
```

如

```sql
create table person(
	ID int auto_increment, 		/*int 类型，auto_increment表示如果缺省会自增1，只能设定主键*/
    name char(20),		/*字符串类型，长度最大为20字节*/
    
    primary key(ID)			/*设定ID为主键，最后一句不用加逗号*/
    
);

/*主键	类似身份证	在一张表中必须不能为空	不能重复	标识一行数据的唯一性	是索引*/
```

```sql
show create table person;
/*查看创建表的ddl*/
```

#### MySQL 常用数据类型

```sql
数值类型    

BIT(M)位类型。M指定位数，默认值1，范围1-64

BOOL，BOOLEAN 使用0或1表示假或真

TINYINT [UNSIGNED] [ZEROFILL]带符号的范围是-128到127。无符号0到255。

SMALLINT [UNSIGNED] [ZEROFILL] 2的16次方

INT [UNSIGNED] [ZEROFILL] 2的32次方

BIGINT [UNSIGNED] [ZEROFILL] 2的64次方

FLOAT[(M,D)] [UNSIGNED] [ZEROFILL] M指定显示长度，d指定小数位数 （5, 2）

DOUBLE[(M,D)] [UNSIGNED] [ZEROFILL]     表示比float精度更大的小数



文本、二进制类型    

CHAR(size)固定长度字符串（size表示 有多少个字符）空间换时间，效率比varchar更高

VARCHAR(size)   可变长度字符串 （varchar 是可变的） varchar（50）表示最大可以存放的长度是50

BLOB   LONGBLOB 二进制数据

TEXT(clob)    LONGTEXT(longclob)     大文本

//通常做法是把大文件保存在磁盘中，数据库中记录文件路径


时间日期    MySQL独有

DATE/DATETIME/TIMESTAMP
日期类型 DATE (YYYY-MM-DD)
日期时间类型 DATETIME(YYYY-MM-DD HH:MM:SS)
上面两个是字符串类型，如‘2020-3-31 12:00:00’要自己插入

时间戳类型 TIMESTAMP(YYYY-MM-DD HH:MM:SS)

TIME    
```

#### 修改表

```sql
/*追加*/
ALTER TABLE table_name
ADD        (column datatype [DEFAULT expr]
           [, column datatype]...);

/*修改*/
ALTER TABLE table_name
CHANGE     column datatype [DEFAULT expr]
           [, column datatype]...;

/*删除*/
ALTER TABLE table_name
DROP          (column);
```



```sql
alter table person add entryDate timestamp ;/*给person表添加一个timestamp类型的entryDate字段

然后可以用show create table person 查看*/

insert into person (ID,name) values (1,'zhangsan');     /*插入一条数据，字符串类型推荐用单引号*/

select * from person where NAME='zhangsan';/*查找姓名为zhangsan的行*/

alter table person change entryDate entry_date timestamp default current_timestamp on update current_timestamp ;/*把字段entryDate改成entry_date,设置默认值为当前时间,当发生更新时触发*/

insert into person (name) values ('lisi');/*再次插入，主键自增*/

select * from person;/*发现ID自增，entry_date 也有了数据*/

update person set name='zhangsan1' where ID=1;/*把id为1的行的name字段修改为zhangsan1，同时会更新entry_date为最新的时间*/

alter table person add math float;/*给person表增加float类型的math字段*/

alter table person add (
    english float default 60 
    science float default 50 not null
    );/*给person表增加float类型的默认值为60的english字段和float类型默认值为50的非空的science字段*/
    
select * from person;/*此时发现之前的数据的english和science也有了默认值60和50*/

insert into person (name,math,science) values ('wangwu',80,80);/*向person表插入一条数据*/

insert into person (name,math,english) values ('xiaoming',90,80),
('xiaohua',50,50);/*用一条语句向person表插入多项数据*/

alter table person drop (math);/*删除person表中的math字段*/
```

### DML 数据操纵语言



DML:Data Manipulation Language

作用：用于向数据库表中插入、删除、修改数据。

常用关键字：

```sql
INSERT      //插入
UPDATE      //修改
DELETE      //删除
```

#### insert

```sql
INSERT INTO table [(column [, column...])]
VALUES      (value [, value...]);
```

插入的数据应与字段的数据类型相同。

数据的大小应在列的规定范围内，例如：不能将一个长度为80的字符串加入到长度为40的列中。

在values中列出的数据 。

字符和日期型数据应包含在单引号中。

插入空值，不指定或insert into table value(null)

```sql
insert into person (ID,name,english,science) values(10,'xiaowang',50,50);/*之后再用ID的自增就会从11开始了，show table person create 可以看到auto_increment=12*/

select * from person;
```

#### 中文乱码

mysql有六处使用了字符集，分别为：client 、connection、database、results、server 、system。 client是客户端使用的字符集。  connection是连接数据库的字符集设置类型，如果程序没有指明连接数据库使用的字符集类型就按照服务器端默认的字符集设置。        database是数据库服务器中某个库使用的字符集设定，如果建库时没有指明，将使用服务器安装时指定的字符集设置。     results是数据库给客户端返回时使用的字符集设定，如果没有指明，使用服务器默认的字符集。        server是服务器安装时指定的默认字符集设定。        system是数据库系统使用的字符集设定。

```sql
/*注意插入数据时的中文问题：*/
show variables like 'character%';

/*如果插入中文时，要调整编码为GBK*/
        show variables like 'character%';
        
/*修改客户端工具所用的编码*/
        set character_set_client=gbk;
        
/*客户端显示结果的编码*/
        set character_set_results=gbk;
```

#### update

```sql
UPDATE  tbl_name    
    SET col_name1=expr1 [, col_name2=expr2 ...]    
    [WHERE where_definition]    
```

UPDATE语法可以用新值更新原有表行中的各列。

SET子句指示要修改哪些列和要给予哪些值。

WHERE子句指定应更新哪些行。如没有WHERE子句，则更新所有的行。



```sql
update person set science=100 where name='zhangsan';/*如果不加where字句则会修改所有行的science*/

update person set science=80 where english=60;/*将person表中所有english字段值为60的行的science字段的值全部改为80*/
```

#### delete

```sql
delete from  table_name       
    [WHERE where_definition]    
```

如果不使用where子句，将删除表中所有数据。

Delete语句不能删除某一列的值（可使用update）

使用delete语句仅删除记录，不删除表本身。如要删除表，使用drop table语句。

同insert和update一样，从一个表中删除记录将引起其它表的参照完整性问题，在修改数据库数据时，头脑中应该始终不要忘记这个潜在的问题。



```
delete from person where ID=4;/*删除person表中ID字段值为4的那一行*/ 
```

### DQL 数据查询语言

DQL:Data Query Language

作用：查询数据。

常用关键字：

```sql
SELECT
```

#### 基本的select语句

```sql
SELECT [DISTINCT] [* ] |{column1, column2, column3..}
        FROM    table [where ];
/*方括号为可选项*/
```

Select 指定查询哪些列的数据。

column指定列名。

*号代表查询所有列。

From指定查询哪张表。

DISTINCT可选，指显示结果时，是否剔除重复数据

```sql
select ID,name from person;/*只显示person表的各行的ID和name字段的值*/

select distinct english from person;/*查询person表中的english字段有多少种不同数值*/

select * from person where english>80;/*查询person表中english字段大于80的所有行*/
```

#### 使用表达式对查询的列进行运算

```
SELECT *|{column1｜expression, column2｜expression，..}
        FROM    table;

select english+science from  person;/*将person表中的每行的english和science字段的值相加显示*/

```

#### 使用as语句

```
SELECT column as 别名 from 表名;
select english+science as total from  person;/*将person表中的每行的english和science字段的值相加显示为别名total*/

select english as math from person;/*把英语起了个math的别名*/

update person set science=science+10;/*修改所有science的值*/
select english+10 as 'english+10' from person;/*显示的时候把英语+10分*/
```

#### where子句中经常使用的运算符  

```
比较运算符   

    >   <   <=   >=   =    <>   
/*大于、小于、大于(小于)等于、不等于*/

BETWEEN  ...AND...  /*显示在某一区间的值(闭区间)*/

IN(set) /*显示在in列表中的值，例：in(100,200)*/

LIKE ‘张pattern’ /*模糊查询,
在Like语句中，
% 代表零个或多个任意字符，
_ 代表一个字符，
例first_name like ‘_a%’;  aaxxxx  aaxx aa
*/

IS NULL 
/*判断是否为空,因为可以把‘NULL’作为字符串插入到表中，此时会和空项产生误解

mysql中的NULL其实是占用空间的，下面是来自于MYSQL官方的解释

“NULL columns require additional space in the row to record whether their values are NULL. For MyISAM tables, each NULL column takes one bit extra, rounded up to the nearest byte.”
打个比方来说，你有一个杯子，空值代表杯子是真空的，NULL代表杯子中装满了空气，虽然杯子看起来都是空的，但是二者仍然是由区别的。

*/


逻辑运算符   

and /*多个条件同时成立*/

or  多个条件任一成立

not 不成立，例：where not(salary>100);
select * from person where english between 70 and 100;/*查询person表中english字段值为70-100的行*/

select * from person where english in(60,70,80,90);/*显示person表中english字段值为60或70或80或90的行*/

select * from person where name like '&zhang%';/*查询person表中所有名字含义zhang子串的行*/

select * from person where name like '_a_a_';

alter table person add math float;
/*此时math列全为空*/

select * from person where math is NULL;/*查询所有math字段为空的*/
```

#### order by 子句排序

```
SELECT column1, column2. column3..
        FROM    table;
        order by column asc|desc

```

Order by 指定排序的列，排序的列即可是表中的列名，也可以是select 语句后指定的列名。

Asc 升序、Desc 降序

ORDER BY 子句应位于SELECT语句的结尾。

limit 显示前几行   select * from pats limit 0,3;前三行

```
select * from person order by english;/*按照english升序排序person表*/

select * from person order by english desc;/*按照english降序排序person表*/

select * from person order by english desc limit 3;/*只显示前3行的数据*/
```

### 数据完整性

数据完整性是为了保证插入到数据库中的数据是正确的，它防止了用户可能的输入错误。

```
insert into person (name,english) values ('xiaoli','test');/*此时会报错提示english这一列有错误，插入失败*/

show create table person;/*查看表中各字段的规定*/
```

数据完整性主要分为以下三类：

#### 实体完整性

规定表的一行（即每一条记录）在表中是唯一的实体。实体完整性通过表的主键来实现。

#### 域完整性

指数据库表的列（即字段）必须符合某种特定的数据类型或约束。比如NOT NULL。

#### 参照完整性

保证一个表的外键和另一个表的主键对应。表和表之间的关系

```
create table pets(
    petID int,
    petName char(20),
    masterID int,
    primary key(petID),/*主键为petID*/
    foreign key(masterID) references person(ID) /*pets表的masterID字段和person表的ID字段对应*/
);

insert into pets (petID,petName,masterID) values (1,'cat',2);

select * from pets;

select * from person;
/*此时pets表的第一行就和person表的第二行绑定了*/

delete from person where ID=2;/*会失败，因为和pets表绑定了，有外键约束,需要把pets表中的masterID的2改掉*/

update pets set masterID=5;/*这样就可以删除ID为2的了*/

delete from person where ID=2;/*会失败，因为和pets表绑定了，有外键约束,需要把pets表中的masterID的2改掉*/

insert into pets(petID,petName,masterID) values(2,'dog',2);/*错误，无法添加person表中不存在的ID*/
```



#### 数据库主键

主键：表中经常有一个列或列的组合，其值能唯一地标识表中的每一行。这样的一列或多列称为表的主键，通过它可强制表的实体完整性。当创建或更改表时可通过定义 PRIMARY KEY 约束来创建主键。一个表只能有一个 PRIMARY KEY 约束，而且 PRIMARY KEY 约束中的列不能接受空值。由于 PRIMARY KEY 约束确保唯一数据，所以经常用来定义标识列。

作用 : 1）保证实体的完整性;  2）加快数据库的操作速度,主键默认建立索引 3） 在表中添加新记录时，会自动检查新记录的主键值，不允许该值与其他记录的主键值重复。  4) 自动按主键值的顺序显示表中的记录。如果没有定义主键，则按输入记录的顺序显示表中的记录。



### 定义表的约束

#### 定义主键约束

  primary key:不允许为空，不允许重复     (可以区分两条记录的唯一性)

删除主键：alter table tablename drop primary key ;

#### 定义主键自动增长

  auto_increment

#### 定义唯一约束

  unique	允许为空

#### 定义非空约束

  not null

#### 定义外键约束

constraint ordersid_FK foreign key(ordersid) references orders(id)



### 多表设计

避免数据的冗余

#### 一对多

比如个人信息表中的省份需要用省份表的各省份的ID做外键，因为比如比较长的省份比如新疆维吾尔自治区这种巨长的字符串，如果表统计的数据条数很多，占用的空间就会很大，而如果用int型的ID则可以节省很大一笔空间

#### 多对多

比如课程表有课程的ID，学生信息表有学生ID，而选课表有学生ID和所选课程的ID

#### 一对一

比如学生信息表有学生ID，设备表中有设备的ID和作为外键的学生ID



### DQL 数据查询语言

#### 连接查询：

##### 交叉连接（cross join）

不带on子句，返回连接表中所有数据行的笛卡儿积。



连接查询的from子句的连接语法格式为：

```
select * from TABLE1 join_type TABLE2  [on (join_condition)] [where (query_condition)]
```

其中

TABLE1和TABLE2表示参与连接操作的表，TABLE1为左表，TABLE2为右表

on子句设定连接条件

where子句设定查询条件，join_type表示连接类型

```
insert into pets(petID,petName,masterID) values (3,'fish',10);

select * from person cross join pets;/*交叉查询，行数为各自表的的行数的乘积即person表中的每行数据都和pets表的每行数据做一个组合*/

select * from person as p 
cross join pets as t 
on p.ID=t.masterID;/*查询pets表中masterID和person表的ID相同的行,as可省略*/


```

##### 内连接（inner join）

内连接查询操作列出与连接条件匹配的数据行，它使用比较运算符比较被连接列的列值。内连接分三种： 

1、等值连接：在连接条件中使用等于号(=)运算符比较被连接列的列值，其查询结果中列出被连接表中的所有列，包括其中的重复列。 

例，下面使用等值连接列出authors和publishers表中位于同一城市的作者和出版社： 

```
SELECT * FROM authors AS a INNER JOIN publishers AS p ON a.city=p.city 
```

2、不等连接： 在连接条件使用除等于运算符以外的其它比较运算符比较被连接的 列的列值。这些运算符包括>、>=、<=、<、!>、!<和<>。 

3、自然连接：在连接条件中使用等于(=)运算符比较被连接列的列值，但它使用选择列表指出查询结果集合中所包括的列，并删除连接表中的重复列。

返回连接表中符合连接条件及查询条件的数据行。

```
select * from person inner join pets;/*交叉查询，行数为各自表的的行数的乘积即person表中的每行数据都和pets表的每行数据做一个组合*/

select * from person as p 
inner join pets as t 
on p.ID=t.masterID;/*查询pets表中masterID和person表的ID相同的行*/
```

显式内连接：使用inner join关键字，在on子句中设定连接条件

```
SELECT * FROM customer as c 
INNER JOIN orders as o 
ON c.id=o.customer_id; 

SELECT * FROM customer as  c 
INNER JOIN orders as o 
ON c.id=o.customer_id; 
```

隐式内连接：不包含inner join关键字和on关键字，在where子句中设定连接条件

```
SELECT * FROM customer as c,
orders as o 
WHERE c.id=o.customer_id; 
```

##### 外连接

分为左外连接（left outer join）、右外连接（right outer join）。与内连接不同的是，外连接不仅返回连接表中符合连接条件及查询条件的数据行，也返回左表（左外连接时）或右表（右外连接时）中仅符合查询条件但不符合连接条件的数据行。

左外连接就是以左表为主表，首先显示左表的所有信息，再显示和右表相关的信息

1、左外连接

使用left outer join关键字，在on子句中设定连接条件

```
SELECT * FROM customer as c LEFT OUTER JOIN orders as o ON c.id=o.customer_id; 
```

不仅包含符合c.id=o.customer_id连接条件的数据行，还包含左表中的其他数据行 带查询条件的左外连接查询，在where子句中设定查询条件

```
SELECT * FROM customer as c LEFT OUTER JOIN orders as o ON c.id=o.customer_id WHERE o.price>250;
```



```
select * from person left outer join pets on person.ID=pets.masterID;/*会显示cross join的内容外加左表person所有的剩余行，这些行的petID、petName、masterID都为NULL        即查询person表中所有人的信息，并显示每个人是否有宠物*/
```

2、右外连接

使用right outer join关键字，在on子句中设定连接条件

```
SELECT * FROM customer c RIGHT OUTER JOIN orders o ON c.id=o.customer_id; 
```

不仅包含符合c.id=o.customer_id连接条件的数据行，还包含orders右表中的其他数据行 带查询条件的右外连接查询，在where子句中设定查询条件

```
SELECT * FROM customer c RIGHT OUTER JOIN orders o ON c.id=o.customer_id WHERE o.price>250;
```



```
select * from person right outer join pets on person.ID=pets.masterID;/*会显示和cross join一样的内容*/

select * from pets right outer join person on person.ID=pets.masterID;/*以person表为主体，就是和之前的左外连接的掉了个个，即左边显示pet表的相关字段，右边显示person表的相关字段*/
```

#### 子查询

子查询也叫嵌套查询，是指在where子句或from子句中又嵌入select查询语句（一般写在where字句） 练习： 查询“郭靖”的所有订单信息

```
SELECT * FROM orders 
WHERE customer_id=(
    SELECT id FROM customer
    WHERE name LIKE ‘%郭靖%'
);
```



#### 联合查询

联合查询能够合并两条查询语句的查询结果，

去掉其中的重复数据行，

然后返回没有重复数据行的查询结果。联合查询使用union关键字

```
SELECT * FROM orders WHERE price>100 
UNION 
SELECT * FROM orders WHERE customer_id=1;
```

注意：联合查询的各子查询使用的表结构应该相同，同时两个子查询返回的列也应相同。

```
select * from person where ID>3
union
select * from person where science>60;/*
预期结果：查询ID大于3和science字段大于60的行
实际结果：在同一个表中使用时和or效果相同，因为是或的关系所以只要满足其中一个就可以了
select * from person where ID>3 or science>60;
*/
```



#### 报表查询

报表查询对数据行进行分组统计，其语法格式为：

```
 select …  from … [where…] [ group by … [having… ]] [ order by … ]
```

其中group by 子句指定按照哪些字段分组，having子句设定分组查询条件。

在报表查询中可以使用SQL函数.

```
select science from person group by science;/*把分数相同的显示在同一行上，此时每行只有science是相同的，也就不能用select *了*/
```



#### 常用统计函数

##### count

Count(列名)返回某一列，行的总数（有多少条记录）

```
Select count(*)|count(列名) from tablename
        [WHERE where_definition]   
select science,count(*) from person group by science;/*统计每个分数都有多少人*/
```



##### sum

Sum函数返回满足where条件的行的和

注意：sum仅对数值起作用，否则会报错。 注意：对多列求和，“，”号不能少。

```
Select sum(列名)｛,sum(列名)…｝ from tablename
        [WHERE where_definition]  
select science,count(*),sum(english) from person group by science;/*按照science分组，统计每组所有成员的english总和*/
```



##### avg

AVG函数返回满足where条件的一列的平均值

```
Select avg(列名)｛,avg(列名)…｝ from tablename
        [WHERE where_definition]   
select science,count(*),sum(english),avg(english) from person group by science;/*按照science分组，统计每组所有成员的english总和以及每组english的平均值*/
```



##### max/min

Max/min函数返回满足where条件的一列的最大/最小值

```
Select max(列名)　from tablename
        [WHERE where_definition]   
select science,count(*),sum(english),avg(english),max(english),min(english) from person group by science;/*按照science分组，统计每组所有成员的english总和,每组english的平均值,每组内的english的最高和最低*/
```

#### group和having

使用group by 子句对列进行分组

```
SELECT column1, column2. column3.. FROM table
        group by column 
```

使用having 子句过滤

```
SELECT column1, column2. column3..
        FROM    table
        group by column having ...
```

having和where均可实现过滤，但在having可以使用合计函数,having通常跟在group by后，它作用于组。



```
select science,count(*),sum(english),avg(english) from person group by science;/*按照science分组，统计每组所有成员的english总和,每组english的平均值*/

select science,count(*),sum(english),avg(english) from person group by science having avg(english)>60;/*在上面的基础上只显示english平均值大于60的组*/
```

### 数据库的备份与恢复

#### 数据库备份

cmd命令下

```
mysqldump -u root -p test>test.sql
```



#### 数据库恢复

需要先把test库删了

```
drop database test;
```

然后重新创建test数据库并use选择该数据库

```
create database test;
use test;
```

最后在cmd命令下：

```
mysql -u root -p test<test.sql
```

或者：

在mysql >命令行下 执行  `SOURCE 数据库文件`

如果在恢复前又在新的test库中创建了新的和之前备份的库不同名的表，则恢复后仍然会存在

# day33

## MySQL的索引

MySQL官方对索引的定义为：索引（Index）是帮助MySQL高效获取数据的**数据结构**。

索引	给数据库的某一列或某几列建立索引，主键也是一种索引

数据库中的一张表一般最多存储1000w行数据，如果再多的话一般要分表分库

### 索引是什么

索引是一种数据结构

### 索引的作用

帮助MySQL高效获取数据

查询是数据库最主要的功能之一，我们都希望查询的速度尽可能快。

优化：查询算法

只针对select进行优化， 对insert、update、delete没有优化，因为这三项操作后还要额外对索引表进行一次维护，因此索引也不是越多越好



```mysql
select * from person where ID=1;/*给id建立了主键索引，mysql会从索引中查找，否则只能顺序查找从上往下遍历*/
```



### 索引数据结构

查找效率(时间复杂度)

磁盘空间占用

磁盘IO次数

#### 顺序查找

O(n)

```mysql
select * from person;/*不加任何where的时候就是顺序查找*/

select * from person where id=1;/*id是主键索引，就会用索引的方式进行查找，效率更高*/
```



#### 二分查找

O(logn)

要求：

数据有序排放

连续的存储空间(行与行之间也是)



如果用二分查找会产生的问题：

key-value	键值对

如果表的行数很多，就需要很大的连续存储空间用来存储索引的key(int型编号每个4字节)

由于要求有序排放，因此如果要在已排序好的表中插入新数据，就会发生大量的磁盘空间的移动(磁盘IO次数过多)，会耗费大量时间

#### 二叉树查找

O(logn)

由于数据库是按行存储的，即把一整行数据作为一个整体保存在磁盘上，同一行内的数据是连续存储的，但是行与行之间不一定是连续存储的

key-value		key为索引(即数据的值)，value是该数据所在行所在的地址(InnoDb数据库引擎的情况下)

和二分查找相比，二叉树查找不要求连续空间存储数据，因此存储空间要求会更低

如果表的行数很多，则建立的二叉树的深度就很大，在查找key时使用二叉树查找进行的磁盘IO次数就很多(每次对根结点的判断都要读写一次IO，因为是先读value的地址再去该地址找key值进行比较)，磁盘IO次数多的问题还是没有得到解决

#### 哈希

O(1)

hash索引会建立一张hash表，分别存储了各索引的key由hash函数得到的hash值以及对应行存储的地址

hash表类似一个二位数组，表的存储必须是连续的，因此和二分查找的相同，都需要一块连续的存储空间用于存放索引表，因此也面临着磁盘IO次数过多的问题



索引的检索可以一次定位，速度快，效率高于树索引

但是Hash索引本身由于其特殊性也带来了很多限制和弊端

主要有：
哈希索引只支持等值比较查询  包括=，in，不支持范围查询(即如果是select score <60 这种情况会退变为顺序查找)

哈希索引数据并不是按照索引值顺序存储的(按照hash函数得到的hash值排序的)，所以也就无法用于排序  

Hash索引遇到大量Hash值相等的情况(hash冲突)后性能并不一定就会比BTree索引高。

在大多数场景下，都会有范围查询、排序、分组等查询特征，用B+树索引就可以了

#### B树 -多叉平衡搜索树

每一个节点最多有 m 个子节点（m阶，m不小于3）

每一个内部节点最少有 ⌈m/2⌉ 个，最多m-1个元素

如果根节点不是叶子节点，那么它至少有两个子节点(要么只有根节点，要么至少还有2个子节点)

有 k 个子节点的非叶子节点拥有 k − 1 个元素(k<=m，即每个结点自己包含的元素数量为该节点的子节点数目-1)

所有的叶子节点都在同一层

其搜索性能等价于在关键字集合内做一次二分查找，因为每个节点中的关键字和左右子树都是有序的，所以只要比较节点中的关键字，或者沿着指针就能很快地找到指定的关键字，如果查找失败，则会返回叶子节点，即空指针



二叉树一个节点只有一个元素，至多2个孩子，而B树每个节点可以有多个元素(孩子节点数目-1)，多个孩子，大大降低了磁盘IO次数，比如100w行数据，用1001阶B树保存，则每个节点可以保存1000个key，而每个节点可以有1001个子节点，因此1001*1000>100w，因此只需要2层就可以存储完，一次查找所要使用的磁盘IO最多进行2次

对于B树的每个节点内部，都需要有序连续存储key，每个结点有m个指向子节点的指针和m-1个存储的关键字，如果是上面的100w行用1000阶B树存储，也只需要1000*(4+8)=12000个字节，而子节点之间并不需要连续存储，因此大大降低了连续存储空间的消耗

##### B树的插入

所有的插入都从根节点开始。要插入一个新的元素，首先搜索这棵树找到新元素应该被添加到的叶子节点。将新元素插入到这一节点中的步骤如下：

1、如果叶子节点未满，将新元素插入到这一节点，且保持节点中元素有序。

2、否则的话这一节点已经满了，将它平均地分裂成两个节点：

2.1、从叶子节点的元素和新的元素中选择出中位数

2.2、小于这一中位数的元素放入左边节点，大于这一中位数的元素放入右边节点，中位数作为分隔值。

2.3、分隔值（中位数）上提，插入到父节点中，这可能会造成父节点分裂，分裂父节点时可能又会使它的父节点分裂，以此类推。

#### B+树

非叶子节点不存储data，只存储key,即非叶子节点只提供索引

所有的叶子节点存储完整的一份key信息以及key对应的data

每一个父节点都出现在子节点中，是子节点的最大或者最小的元素

B+树的每个节点的叶子节点数和该节点元素key数量一致

每个叶子节点都有一个指针，指向下一个数据，形成一个链表



B+树的查找过程，与B树类似，只不过查找时，如果在非叶子节点上的关键字等于给定值，并不终止，而是继续沿着指针直到叶子节点位置。因此在B+树，不管查找成功与否，每次查找都是走了一条从根到叶子节点的路径。



### 主键索引

主键索引建立的规则是 int优于varchar,一般在建表的时候创建,最好是与表的其他字段不相关的列或者是业务不相关的列.一般会设为 int 而且是 AUTO_INCREMENT自增类型的。

可以通过

```mysql
SHOW INDEX FROM tablename;/*查看索引*/
```

```mysql
show index from person;/*查看person表索引，Key_name索引名称、Index_type索引类型、Column_name列名*/
```

### 普通索引

```mysql
CREATE INDEX 'index_name' ON `table_name`(`field_name`);

ALTER TABLE table_name ADD INDEX index_name(`field_name`)；

```

```mysql
create index english_index on person(english);/*给person表的english字段建立索引*/

alter table person add index english_index2(english);/*可以为同一列重复创建索引，虽然没什么用*/ 
```

### 唯一索引

与普通索引类似,但是不同的是唯一索引要求所有的索引值是唯一的,这一点和主键索引一样.但是他允许有空值，

```MySQL
CREATE UNIQUE INDEX 'index_name' ON `table`(`field`);
```

### 组合索引

一个表中含有多个单列索引不代表是组合索引,通俗一点讲 组合索引是:包含多个字段但是只有索引名称

```mysql
CREATE INDEX 'index_name' ON `table`(`field1`, `field2` ,......);
```

```mysql
create index english_science_index on person(english,science);/*给person表的english和science创建一个组合索引，通过show create table person 和show index from person可以查看*/
```

### 删除索引

```mysql
ALTER TABLE table_name DROP INDEX index_name；
DROP INDEX index_name ON table_name;
```

```mysql
alter table person drop index english_index;/*删除person表的english_index索引*/

drop index english_index on person;
```

