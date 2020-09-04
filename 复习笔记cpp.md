# day1

## 命名空间

```cpp
using namespace std;	//using 编译指令
std::cout;	//作用域限定符
using std::cout;	//using 声明机制
::printf();	//匿名命名空间
```



## const 关键字

```cpp
const *;		//最右为*，可以修改指向，不可以修改指向对象的值
* const;		//最右为常量，不可以修改指向，可以修改指向对象的值
```

### const常量和宏定义的区别

宏定义没有类型检查，字符串替换发生在预处理阶段

const常量在编译器进行类型检查



## new/delete 表达式

### 和malloc/free的区别

malloc/free是函数，new/delete是运算符表达式

new能够自动分配空间大小，malloc需要传参

new申请的空间自动初始化，malloc需要借助bzero或memset

new/delete能对对象进行构造和析构函数的调用



## 引用

引用在声明的时候必须初始化，一旦绑定，不能改绑或解绑

引用的底层实现是指针，在汇编中表现为间接寻址

函数传递参数时使用引用可以减少形参的空间开销

当以引用作为函数的返回值时，注意返回的变量的生命周期一定要大于函数本身



# day2 

## 默认参数

从右向左，默认值设置放在函数声明中，注意函数重载产生的二义性



## inline 内联函数

函数体的代码长度尽可能的短，不要出现for循环或其他复杂控制结构

### inline和宏定义的区别

宏发生在预处理阶段，进行字符串的替换，不能调试，**不能操纵类的私有数据成员**

inline函数在编译时用函数体替换函数调用语句，通过编译器的上下文优化提升效率

### 头文件和实现文件分开的inline函数

```cpp
//add.hpp
#ifndef __ADD_HPP__
#define __ADD_HPP__
inline
int add(int,int);
#include "add.cc"
#endif

//add.cc
inline
int add(int x,int y){
    return x+y;
}
```



## string 字符串

string 其实和stl的容器一样也有迭代器，可以对迭代器进行stl的一系列算法的操作

```cpp
string s1="hello";
string s2="world";
s2.append(s1);	//s2=worldhello	尾部拼接
size_t pos=s2.find("hello");//pos=5	查找子串
string s3=s2.substr(pos,5);//s3=hello	从pos开始截取5个字符
```



## 程序内存的分配方式

从高地址到低地址依次为：内核空间	栈	堆	读写段(全局/静态区)	只读段(文字常量区，程序代码区)

### 栈和堆的比较

栈的空间由编译器管理，无需手动申请和释放，从高地址向低地址生长，由于栈的后入先出特性因此不会有内存空间碎片

堆的空间必须由程序员自己管理，只能动态分配，从低地址向高地址生长，由于动态分配会造成申请空间的不连续，长期运行会产生内存碎片



## 类和对象

### struct 和 class 区别

struct 的成员属性默认为public

class 的成员属性默认为private

### 编码规范

```
自定义头文件
c头文件
c++头文件
```

### 对象的创建--构造函数

最好给定一个有默认值的构造函数

#### 默认构造函数

```cpp
class Point{
public:
    Point(){	//默认构造函数

    }
};
```

#### 初始化表达式

数据成员在初始化表达式中的初始化顺序仅取决于在类中被声明的前后顺序，与表达式中的顺序无关

```cpp
class Point{
public:
    Point(int ix,int iy):_ix(ix),_iy(iy){

    }
private:
	int _ix;
	int _iy;
};
```



# day3

## 类和对象

### 对象的销毁

析构函数

```cpp
class Computer{
public:
	Computer(char *str):
	_str(new char[strlen(str)+1]()){
		strcpy(_str,str);
	}
	
	~Computer(){
		if(_str){
			delete [] _str;
		}
	}
	
private:
	char *_str;
};
```

### 拷贝构造函数

如果自己实现了拷贝构造函数而没有**提供普通构造函数**，则编译的时候会报错(因为默认的构造函数被丢弃了)

注意浅拷贝`shadow copy`和深拷贝`deep copy`：默认的拷贝构造函数是浅拷贝，拷贝前后的对象指向同一个地址，修改一个会连带着另一个被修改；因此往往需要自己重写一个深拷贝的版本

```cpp
class Computer{
public:
	Computer(const Computer &rhs):
	_str(new char[strlen(rhs._str)+1]()),
	_price(rhs._price){
		strcpy(_str,rhs._str);	//深拷贝
	}
private:
	char *_str;
	double _price;
};
```

#### 拷贝构造函数调用时机

1、把一个已经存在的对象赋值给另一个新对象时

2、作为函数参数传递时

3、作为函数返回值返回时

#### 拷贝构造函数为什么参数是const Object &rhs

引用是为了防止实参传入的时候再次发生拷贝，导致循环调用拷贝构造函数

const是为了保证原数据不会被修改，同时也是为了防止传入的实参是右值不能被引用



# day4

## this 指针

每个非静态的成员函数都有，指向当前对象本身，作为默认第一个参数

类的成员函数在编译时就已确定了该函数的入口地址，同一个类的不同对象的数据就是靠各自的this函数加以区分

静态成员函数没有this指针



## 赋值运算符函数

```cpp
class Computer{
public:

	Computer & operator=(const Computer &rhs){
		if(this!=&rhs){//自复制
			delete [] _str;//释放左操作数
			_str=nullptr;
			_str=new char[strlen(rhs._str)+1]();
			strcpy(_str,rhs._str);//深拷贝
			_price=rhs.price;
		}
		return *this;//返回*this
	}

private:
	char *_str;
	double _price;
};
```

## 特殊数据成员的初始化

常量数据成员	只读属性，构造函数初始化列表初始化

引用数据成员	构造函数初始化列表初始化

类对象成员	构造函数初始化列表初始化，否则执行默认初始化

静态数据成员	类外初始化，如果头文件和实现文件分离，则放在实现文件中，防止重定义



## 特殊成员函数

静态成员函数	内部只能使用静态数据成员和其他静态成员函数(因为不含this指针无法确定具体是哪个对象)	可以通过类名+作用域限定符形式直接调用

const 成员函数	只能读取数据成员	只能调用const成员函数，不能调用非const成员函数	



## 对象的组织

### const 对象

const对象只能调用const成员函数，而非const对象均可

### 指向对象的指针

单纯创建一个指针不会调用构造函数Point *p;

指针存储的是对象所占内存空间的首地址

```cpp
类名 * 指针名 [=初始化表达式];
Point *pt1=new Point(1,2);
Point p(3,4);
Point *pt2=&p;
```

### 对象数组

```cpp
类名 数组名[对象个数];
Point pt1[3]={Point(1,2),Point(3,4),Point(5,6)};
```

### 堆对象

注意堆空间的释放	RAII智能指针管理



## 单例模式

构造函数私有化

类中定义一个静态的指向本类型的指针变量

对外暴露静态的`getInstance()`函数获取该静态指针变量

解决析构函数可能出现的double free 问题

```cpp
class Singleton{
public:
	static Singleton * getInstance(){
		if(!_pInstance){
			_pInstance=new Singleton();
		}
		return _pInstance;
	}
	
	static void destory(){
		if(_pInstance){
			delete _pInstance;
            _pInstance=nullptr;
		}
	}
	
private:
	Singleton(){}
	
	~Singleton(){}
	
	static Singleton *_pInstance;
};

Singleton * _pInstance=nullptr;

void test(){
    Singleton *s1=Singleton::getInstance();
    Singleton *s2=Singleton::getInstance();
    //do something
    Singleton::destory();
}
```



# day5

## new 和 delete 表达式

```cpp
//operator new库函数，返回值是void *，指向构造好的对象,调用malloc
void * operator new(size_t); 
void * operator new[](size_t); 
//operator delete库函数，返回值是void，传参是指向待释放的对象的指针，调用free
void operator delete(void *); 
void operator delete[](void *);
```

### new 表达式工作步骤

1、调用operator new函数分配足够大的已初始化的未类型化的空间

2、运行该类型的构造函数初始化对象(基类->派生类)，可能需要先通过初始化列表初始化某些数据成员

3、返回指向新分配并构造好的对象的指针

可以在调用new之前使用std::set_new_handler设置申请空间失败后的回调函数(参数为void，返回值也是void的函数)

### delete 表达式工作步骤

1、调用对象的析构函数(派生类->基类)，回收对象中数据成员申请的资源

2、调用operator delete函数，释放对象占用的内存(释放对象本身)

### 重载

为类重载时必须定义为类的静态函数(默认仍为static函数)

operator new 和 operator delete 必须成对出现，且函数内要做的也是成对的

operator new 重载函数中的size至少为1，即使类中没有任何成员变量(类似申请堆空间时至少要1个字节)

派生类operator new的重载会隐藏基类operator new的重载，此时编译会报错，应当使用using Base::operator new;规避

```cpp
class Derived{
public:
	static void *operator new(size_t sz){
		//派生类重载的operator new
	}
	
	using Base::operator new;//导入基类重载的operator new
};
```

一般类的operator new重载时会隐藏全局operator new的重载，除了提供自己重载的私有版本以外，还应当对所有全局operator new形式提供转换函数

```cpp
//还需要额外提供返回全局的operator new的转换函数
static void *operator new(size_t sz){
	return ::operator new(sz);//返回全局的operator new
}
```

### 要求一个类只能创建栈对象

把operator new 和 operator delete 挪到private 区域(堆对象需要new，而new需要调用operator new，delete同理)，保持析构函数是public的



### 要求一个类只能创建堆对象

把operator new 和 operator delete 挪到public 区域，保持析构函数是private的

这种情况下对象的释放就需要额外指定释放函数的形式才可以了，在释放时除了要释放类的数据成员占用的内存，还要释放类本身的内存

```cpp
class A{
public:
    void destory(){
        delete this;	//不但释放了_str(~A())，还释放了对象本身(operator delete)
    }  
private:
    char *_str;
    
    ~A(){
        if(_str){
            delete []_str;
            _str=nullptr;
        }
    }
};
```

## c++输入输出流

### 输入输出与序列化反序列化

内存->文件	输出

对象->二进制字节流输出	序列化(write)	把内存中的对象转换成字节流存放在文件中

文件->内存	输入

输入二进制字节->对象		反序列化(read)	从文件中读取字节流到内存转换成对象

### c++常用3种流类型

标准io：<iostream>	包括istream标准输入流、ostream标准输出流、iostream标准输入输出流

文件io：<fstream>	包括ifstream文件输入流、ofstream文件输出流、fstream文件输入输出流

字符串io：<sstream>	包括istringstream字符串输入流、ostringstream字符串输出流、stringstream字符串输入输出流

### 流的状态

常用于判断文件流是否通畅

```cpp
//badbit	置位表示流失效，不可恢复
bool bad();	//若badbit被置位，返回true
	
//failbit	置位表示流失效，可恢复
bool fail();	//若failbit或badbit置位，返回true

//eofbit	置位表示到达文件末尾，此时eofbit和failbit都会被置位
bool eof();	//置位返回true

//goodbit	流未发生错误则置位，badbit、failbit、eofbit任一被置位则goodbit不再置位
bool good();	//置位返回true，表示流正常

void clear();	//重置流的状态
```

### 流的通用操作

```cpp
//读取一行数据 
istream & getline(char_type * s, std::streamsize count, char_type delim ='\n');

//读取count个字节的数据 
istream & read(char_type * s, std::streamsize count);

//查看输入流中的下一个字符, 但是并不将该字符从输入流中取走 //不会跳过输入流中的空格、回车符; 在输入流已经结束的情况下，返回 EOF。 
int_type peek(); 

//获取当前流中游标所在的位置 
pos_type tellg();

//偏移游标的位置 
basic_istream & seekg(pos_type pos); basic_istream & seekg(off_type off, std::ios::seekdir dir);

//----以下为输出流操作---- 
//往输出流中写入count个字符 
ostream & write(const char_type * s, std::streamsize count); 

//获取当前流中游标所在的位置 
pos_type tellp();

//刷新缓冲区 
ostream & flush(); 

//偏移游标的位置 
ostream & seekp(pos_type pos); ostream & seekp(off_type off, std::ios_base::seekdir dir);
```

### 缓冲区类型

全缓冲：填满缓存后再执行I/O操作

行缓冲：当输入和输出遇到换行符时在进行I/O操作

无缓冲：不进行缓冲

### 标准IO

```cpp
void printStreamStatus(){
    cout<<"cin.badbit = "<<cin.bad()<<endl;
    cout<<"cin.failbit = "<<cin.fail()<<endl;
    cout<<"cin.eofbit = "<<cin.eof()<<endl;
    cout<<"cin.goodbit = "<<cin.good()<<endl;
}

cin.clear();//重置流的状态
  
cin.ignore(std::numeric_limits<std::std::streamsize>::max(),'\n');//清空输入缓冲区,可以推测max是static类型的,需要头文件limits

while(cin>>number,!cin.eof()){}	//循环输入

cout<<number<<endl;//输出
```

# day6

## c++输入输出流

### 文件IO

```cpp
//文件输入流ifstream
void test1(){
    //默认情况，当文件不存在时，创建失败
   	ifstream ifs("test.txt");
    if(!ifs.good()){
        cerr<<"open file failed"<<endl;
        return;
    }

    vector<string> vec;
    vec.reserve(100);//预先知道大小可以减少扩容的拷贝操作
    string word;
    //getline 一次获取一行
    while(getline(ifs,word)){
		vec.push_back(word);//存入vector
    }
    for(size_t idx=0;idx!=vec.size();++idx){
        cout<<vec[idx]<<endl;//vector支持随机访问
    }
    /*
    for(auto &c:vec){
    	cout<<c<<endl;
    }
    */
    ifs.close();    
}

//文件输出流ofstream
void test2(){
    //默认情况，当文件不存在时，创建失败
   	ifstream ifs("test.txt");
    if(!ifs.good()){
        cerr<<"open file failed"<<endl;
        return;
    }
    
    //对于文件输出流，当文件不存在的时候，会默认先创建一个文件
    //当文件名存在的时候，先清空文件，再写入
    string filename("test2.txt");
    ofstream  ofs(filename);
    if(!ofs){
        cerr<<"ofs open"<<filename<<"error"<<endl;
        ifs.close();
        return;
    }
    string word;
    //对于文件输入流，默认以空格为分隔符
    while(getline(ifs,word)){
        ofs<<word<<endl;
    }
    ifs.close();    
    ofs.close();
}

//文件输入输出流fstream
void test3(){
    fstream fs("test.txt");
    if(!fs.good()){
        cerr<<"open file failed"<<endl;
        return;
    }
    int number=0;
    for(size_t idx=0;idx!=5;++idx){
        cin>>number;	//读取输入的字符
        fs<<number<<" ";		//输入文件
    }
    //tellg(输入流)/tellp(输出流)	获取文件指针位置
    size_t pos = fs.tellg();
    cout<<"now pos = "<<pos<<endl;//10,在文件末尾
    fs.seekg(0);//设置为开头，绝对路径，从头读取
    //fs.seekg(0,std::ios::beg);//相对路径
    //参数可以选择ios_base::beg、ios_base::cur或ios_base::end
    for(size_t idx=0;idx!=5;++idx){
        fs>>number;
        cout<<number<<" ";
    }
    fs.close();
}
```

#### 文件模式

```cpp
in : 输入，文件将允许做读操作；如果文件不存在，打开失败

out : 输出，文件将允许做写操作；如果文件不存在，则直接创建一个

app : 追加，写入将始终发生在文件的末尾

ate : 末尾，写入最初在文件的末尾

trunc : 截断，如果打开的文件存在，其内容将被丢弃，其大小被截断为零

binary : 二进制，读取或写入文件的数据为二进制形式

ifstream ifs("test.txt",std::ios::in|std::ios::ate);

ofstream  ofs(filename，std::ios::out|std::ios::app);
```

复制文件应该用 ios::binary (二进制模式)，原因是使用二进制文件模式时，程序将数据从内存传递给文件，将不会发生任何隐藏的转换，而默认状态下是文本模式，复制的内容可能会发生改变。(针对windows平台，记事本换行的\r\n)

### 字符串IO

```cpp
//字符串输入流istringstream
//ip 192.168.233.2
//port 5000
//pwd /usr/xxx
//读取配置文件
void readConf(const string &filename){
    ifstream ifs(filename);
    if(!ifs){
        cerr<<"ifs open"<<filename<<"error"<<endl;
        return;
    }
    string line;
    while(getline(ifs,line),!ifs.eof()){
        string key,value;
        istringstream iss(line);
        iss>>key>>value;
        cout<<key<<"---->"<<value<<endl;
    }
    ifs.close();
}

//字符串输出流ostringstream
void test(){
    ostringstream oss;
    int value=10;
    oss<<value;
    string str=oss.str();
    cout<<str<<endl;
}

//字符串输入输出流stringstream
void test2(){
    stringstream ss;
    int value=10;
    ss<<"value= "<<value;
    string str=ss.str();
    cout<<str<<endl;
    
    string word;
    int number;
    while(ss>>word>>number,!ss.eof()){
        cout<<word<<number<<endl;
    }
}
```

## 隐式转换

在类的构造函数前加`explicit`关键字可以防止隐式转换，隐式转换关键字只能用于只有一个参数的构造函数，或者构造函数有n个参数，但有n-1个参数提供了默认值的情况

```cpp
class Point{
public:
    explicit
    Point(int ix=0,int iy=0):_ix(ix),_iy(iy){}
private:
    int _ix;
    int _iy;
};

void test(){
    Point pt1(3,4);
    Point pt2=4;//隐式转换Point(4,0)
}
```



## 内存对齐

### 必要性

1、cpu对内存的读取不是连续而是分块读取的，块的大小是2的指数幂1，2，4，...

2、如果读取操作的数据未对齐，则需要两次总线周期来访问内存，性能会降低

3、某些硬件平台只能从规定的相对地址处读取特定类型的数据

### 内存对齐规则

```cpp
#pragma pack(n)		//对齐系数
```

结构体内部数据成员各自对齐：按照对齐系数和自身长度较小的一个进行

结构体自身对齐：按照对齐系数和结构体内最大数据成员的长度较小的一个进行

结构体内部数据成员仍是结构体：结构体数据成员需要从其内部最大元素大小的整数倍地址开始存储(即上一行剩余全部舍弃，从下一行开始存放)



# day7

## log4cpp

设置日志格式Layout

设置日志目的地Appender

设置日志种类Category

回收Category::shutdown()

编译时要在尾部加上 -llog4cpp -lpthread 参数

```cpp
//RollingFileAppender回滚文件,文件写满后会回到开头覆盖写,运行会发现有test.log、test.log.1、test.log.2、test.log.3 4个文件
void test4(){
    
    //设置日志格式
    PatternLayout *pPatternLayout1=new PatternLayout();
    pPatternLayout1->setConversionPattern("%d %c [%p] %m%n");//d日期、c名字、p优先级、m消息、n换行符
    PatternLayout *pPatternLayout2=new PatternLayout();
    pPatternLayout2->setConversionPattern("%d %c [%p] %m%n");
    
    //设置日志的目的地到输出流
    OstreamAppender *pOstreamAppender=new OstreamAppender("OstreamAppender1",&cout);
    pOstreamAppender->setLayout(pPatternLayout1);
    
    //设置日志的目的地到文件，追加回滚
	RollingFileAppender *pRollingFileAppender=new RollingFileAppender("fileAppender1","test.log",5*1024,3);//每个文件大小5M，一共3个备份
	RollingFileAppender->setLayout(pPatternLayout2);
    
    //设置日志的种类
    Category &myCategory=Category::getRoot().getInstance("myCategory");
    myCategory.setAppender(pOstreamAppender);
    myCategory.setAppender(pRollingFileAppender);
    
    //设置日志的优先级
    myCategory.setPriority(Priority::ERROR);
    
    //打印
    for(size_t idx=0;idx!=300;++idx){
        myCategory.emerg("This is a emerg message");
        myCategory.fatal("This is a fatal message");
        myCategory.alert("This is a alert message");
        myCategory.crit("This is a crit message");
        myCategory.error("This is a error message");
        myCategory.warn("This is a warn message");
        myCategory.notice("This is a notice message");
        myCategory.info("This is a info message");
        myCategory.debug("This is a debug message");
    }
    
    //回收
    Category::shutdown();
}
```

# day8 

## 友元

为了在类的外部访问到类内部private权限的成员，需要将其他类设置为当前类或函数设置为类的友元(friend)

```cpp
class 类名{
    friend 函数原型;
    friend class 类名;
};

class A{
    friend class B;//B可以使用A的private成员
};
```

友元是单向的，不具备传递性，不能被继承，不受权限关键字限制

### 友元函数

#### 全局函数

```cpp
#include <math.h>
class Point{
    friend float getDistance(const Point &lhs,const Point &rhs);
private:
    int _ix;
    int _iy;
};
//全局函数作为友元直接访问private的数据成员
float getDistance(const Point &lhs,const Point &rhs){
    return hypot(lhs._ix-rhs._ix,lhs._iy-rhs._iy);
}
```

#### 成员函数

```cpp
class Point;

class Line{
public:
	float getDistance(const Point &lhs,const Point &rhs);
};

class Point{
    friend float Line::getDistance(const Point &lhs,const Point &rhs);
private:
    int _ix;
    int _iy;
};
//A的成员函数需要访问B类的私有数据成员时，可以在B类的内部声明该函数为类B的友元
float Line::getDistance(const Point &lhs,const Point &rhs){
    return hypot(lhs._ix-rhs._ix,lhs._iy-rhs._iy);
}
```

### 友元类

如上成员函数，直接将类Line设为类Point的友元类

```cpp
class Point;

class Line{
public:
	float getDistance(const Point &lhs,const Point &rhs);
};

class Point{
    friend class Line;
private:
    int _ix;
    int _iy;
};
//A的成员函数需要访问B类的私有数据成员时，可以在B类的内部声明该函数为类B的友元
float Line::getDistance(const Point &lhs,const Point &rhs){
    return hypot(lhs._ix-rhs._ix,lhs._iy-rhs._iy);
}
```

## 运算符重载

当我们需要对自定义类型进行一些运算时，就需要对相应的运算符进行重载

运算符重载的实质是函数重载或函数多态

```cpp
返回类型 operator 运算符(参数列表){
    //...
}
```

### 运算符重载的规则

```cpp
为了防止用户对标准类型进行运算符重载， C++ 规定重载的运算符的操作对象必须至少有一个是自定义类型或枚举类型,即不能改变内置类型之间的运算方式

重载运算符之后，其优先级和结合性还是固定不变的。

重载不会改变运算符的用法，原来有几个操作数、操作数在左边还是在右边，这些都不会改变。

重载运算符函数不能有默认参数，否则就改变了运算符操作数的个数。

重载逻辑运算符（ && , || ）后，不再具备短路求值特性。

不能臆造一个并不存在的运算符，如@、$等
```

#### 不能重载的运算符

```cpp
.		.*		?:		::		sizeof
//成员指针运算符	.*
Student student;
int (Student::*p)=Student::func;
student.*p();//调用func

sizeof 是一个运算符，在预处理阶段使用，因此不能被重载为编译时的函数
```

### 运算符重载的形式

#### 普通函数的重载形式

需要借助get成员函数以获取私有数据成员

```cpp
Complex operator+(const Complex &lhs,const Complex &rhs){
    return Complex(lhs.getReal()+rhs.getReal(),lhs.getImag()+rhs.getImag());
}
```

#### 成员函数的重载形式

在类内声明该运算符，在类外借助作用域限定符`::`来定义该运算符，或者借助inline直接在类内定义

使用成员函数重载双目运算符时，无需从参数列表传递左操作数，而是通过隐含的this指针

```cpp
class Complex{
    Complex operator+(const Complex &);
};

Complex Complex::operator+(const Complex &rhs){
    return Complex(_real+rhs._real,_imag+rhs._imag);//类内就不需要get函数了
}
```

#### 友元函数的重载形式

最推荐使用的方式

```cpp
class Complex{
    friend Complex operator+(const Complex &,const Complex &);
};

Complex operator+(const Complex &lhs,const Complex &rhs){
    return Complex(lhs_dreal+rhs._dreal,
                   lhs_dimag+rhs._dreal);
}
```

### 特殊运算符的重载

#### 复合赋值运算符(+= -= *= /=)

由于左操作数对象发生了变化，所以推荐使用成员函数的形式进行重载，注意返回值类型是引用(*this)

```cpp
class Complex{
    Complex &operator+=(const Complex &);
};

Complex &Complex::operator(const Complex &rhs){
    _real+=rhs._real;
    _imag+=rhs._imag;
    return *this;
}
```

#### 自增自减运算符(++ --)

推荐以成员函数的形式重载

前置(++x)和后置(x++)需要进行区分,c++根据参数的个数来区分前置和后置形式，如果参数列表没有参数，则默认是前置，如果需要对后置进行重载，则需要在参数列表里加一个int型的无实际意义的参数表示这是后置

同时，由于局部对象的生存周期问题，不能返回引用，需要拷贝，因此前置效率更高

```cpp
class Complex{
    //++x
    Complex &operator++(){
        ++_real;
        ++_imag;
        return *this;
    }
    
    //x++，返回值仍然是自增前的
    Complex operator++(int){//int表明是后置
        Complex com(*this);
        ++_real;
        ++_imag;
        return com;
    }
};
```

#### 赋值运算符

只能以成员函数的形式进行重载

注意考虑连续赋值的情况(返回的是this的引用)

```cpp
class String{
    String &operator=(const String &rhs){
        if(this!=&rhs){//1、自复制
            delete [] _str;
            _str=new char[strlen(rhs._str)+1]();
            strcpy(_str,rhs._str);
        }
        return *this;
    }
private:
    char *_str;
};
```

#### 函数调用运算符

只能以成员函数的形式进行重载

```cpp
返回类型 operator()(参数列表){
	//...
}
```

一个类如果重载了函数调用运算符，则可以将该类的对象作为一个函数使用，该对象也称为函数对象

```cpp
class FunctionObject{
    int operator()(int x,int y){
        return x+y;
    }
    int operator()(int x,int y,int z){
        return x+y+z;
    }
};
void test(){
    FunctionObject f;
    cout<<f(1,2)<<endl;
    cout<<f(1,2,3)<<endl;
}
```

#### 下标访问运算符

是一个二元运算符

只能以成员函数的形式进行重载

返回值类型是引用，防止返回对象时调用拷贝构造函数降低i笑傲率

`arr[idx]` 本质就是`arr.operator[](idx)`

```cpp
class CharArray{
    char &operator[](int idx){
        if(idx<size()){
            return _data[idx];
        }else{
            static char nullchar='\0';	//static保证多个对象共享一个，减少重复空间
            return nullchar;
        }
    }
};
```

# day9

## 运算符重载

### 特殊运算符的重载

#### 成员访问运算符

成员访问运算符包括箭头访问运算符`->`和解引用运算符`.`

箭头访问运算符只能以成员函数的形式重载，返回值必须是一个指针或者重载了箭头访问运算符的对象

```cpp
class Data{
public:
    int getData(){
        return _data;
    }
private:
    int _data;
};

class SecondLayer{
private:
    Data *operator->(){
        return _pData;
    }
private:
    Data *_pData;
};

void test(){
    SecondLayer sl;
    cout<<sl->getData()<<endl;
    cout<<(*sl).getData()<<endl;
    cout<<sl.operator->().getData()<<endl;
}
```

#### 输入输出流运算符

由于输入输出流运算符要求流作为左操作数，因此不能重载为成员函数(否则会有this指针)，通常会涉及到对类的私有成员的访问，因此常设置为类的友元函数

```cpp
class Point{
    friend ostream &operator<<(ostream &,const Point &);
    friend istream &operator>>(istream &,const Point &);
private:
    int _ix;
    int _iy;
};

ostream &operator<<(ostream &os,const Point &rhs){
    os<<"("<<rhs._ix<<","<<rhs._iy<<")"<<endl;
    return os;
}

istream &operator>>(istream &is,const Point &rhs){
    is>>rhs._ix>>rhs._iy;//需要对输入进行判断，可以改为函数读取
    return is;
}
```

### 对运算符重载采用的形式的建议

所有的一元运算符，建议以成员函数重载

运算符 `= () [] -> ->*` ，必须以成员函数重载

运算符 `+= -= /= *= %= ^= &= != >>= <<=` 建议以成员函数形式重载

其它二元运算符，建议以非成员函数重载



## 类型转换

### 由其他类型向自定义类型转换

由自定义类型的构造函数实现，称为隐式转换

```cpp
class Point{
    Point(int ix=0,int iy=0):_ix(ix),_iy(iy){}
};

void test(){
    Point p=2;//(2,0)
}
```

### 由自定义类型向其他类型转换

借助类型转换函数完成

```cpp
operator 目标类型(){
	//...
}
```

类型转换函数必须是成员函数，参数列表为空，没有返回值，但是函数体内部要用return语句返回一个目标类型的变量(对象)

```cpp
class Point(){
    operator int(){
        return _ix+_iy;
    }
}

void test(){
    Point pt(1,2);
    int i=pt;
}
```



## 类作用域

在类中定义的成员变量和成员函数的作用域是整个类，这些名称只有在类中(包含类的定义部分和类外函数实现部分)是可见的。

一个类可以定义在另一个类的定义中，即所谓的嵌套类或内部类，如果嵌套类的访问权限是public的，则嵌套类的作用域和被嵌套类的作用域相同，只不过必须用被嵌套类+作用域限定符+嵌套类的方式访问嵌套类的类名。如果访问权限是private的，则只能在被嵌套类的内部使用嵌套类的类名创建对象，在类外是不可见的



## 设计模式之PIMPL

PIMPL(Private Implementation 或 Pointer to Implementation)是通过一个私有的成员指针，将指针所指向的类的内部实现数据进行隐藏，也成为"编译防火墙"。

类内部存放一个私有的实现类对象指针，实现类的私有部分是具体的数据

优点如下：

```
提高编译速度

实现信息隐藏

减小编译依赖，可以用最小的代价平滑的升级库文件

接口与实现进行解耦

移动语义友好
```

Line.hpp

```cpp
//隐藏了具体的Point类的实现细节，对外只暴露了LineImpl
class Line{
public:
    Line(int,int,int,int);
    ~Line();
    void printLine() const;
    
    class LineImpl;//类的前向声明
private:
    LineImpl *_pimpl;
};
```

Line.cc

```cpp
class Line::LineImpl{
public:
    LineImpl(int x1,int y1,int x2,int y2):_pt1(x1,y1),_pt2(x2,y2){}
    
    void printLineImpl()const{_pt1.print();cout<<"-->";_pt2.print();}
    
    ~LineImpl(){}
private:
    class Point{
    public:
        Point(int x,int y):_x(x),_y(y){}
        void print() const{cout<<"("<<_x<<","<<_y<<")"<<endl;}
        
    private:
        int _x;
        int _y;
    };
    Point _pt1;
    Point _pt2;
};

Line::Line(int x1,int y1,int x2,int y2):_pImpl(new LineImpl(x1,y1,x2,y2)){}

Line::~Line(){if(_pimpl){delete _pimpl;}}

Line::printLine(){_pimpl->printLineImpl();}
```

# day10

## 内存泄漏检测工具valgrind

```
valgrind --tool=memcheck --leak-check=full ./testProgram
```

## 单例模式的自动释放

### 借助内部类

```cpp
class Singleton{
public:
    static Singleton *getInstance(){
        if(!_pInstance){
            _pInstance=new Singleton();
        }
        return _pInstance;
    }
    static void destory(){
        if(_pInstance){
            delete _pInstance;
        }
    }
private:
    class AutoRelease{
    public:
        AutoRelease(){}
        ~AutoRelease(){
            if(_pInstance){
                delete _pInstance;
            }
        }
    };
    static Singleton *_pInstance;
    static AutoRelease _auto;
};
Singleton * Singleton::_pInstance=nullptr;
AutoRelease Singleton::_auto;
```

### 借助进程结束回调函数

atexit 函数可以注册一个回调函数，当前进程结束后会被调用，每注册一次就会回调一次，但是不是线程安全的。

```cpp
Singleton *getInstance(){
    if(!_pInstance){
        _pInstance=new Singleton();
        atexit(destory);
    }
    return _pInstance;
}
```

饱汉模式：静态变量在初始化时就创建好对象，可以避免多线程的线程不安全问题

```cpp
Singleton * Singleton::_pInstance=getInstance();
```

饿汉模式：具体调用函数的时候才创建对象，存在线程不安全的情况，需要处理好加解锁

```cpp
Singleton * Singleton::_pInstance=nullptr;
```

### 线程安全的回调函数pthread_once

pthread_once基于POSIX标准，因此只能在Linux下编译运行，编译时要加-lpthread参数

```cpp
class Singleton{
public:
    //静态成员函数只能访问静态函数和静态数据成员
    static Singleton *getInstance(){
        pthread_once(&_once,init);
        return _pInstance;
    }
    //静态可以确保多线程安全，由于只会执行一次，因此不需要判断_pInstance是否为nullptr
    static void init(){
		_pInstance=new Singleton();
		atexit(destory);

    }
    static void destory(){
        if(_pInstance){
            delete _pInstance;
        }
    }
private:
    Singleton(){}
    static Singleton *_pInstace;
    static pthread_once_t _once;
};
//这种情况下由于回调函数保证了线程安全，所以可以用饱汉模式设置为nullptr
Singleton *Singleton::_pInstance=nullptr;
pthread_once_t Singleton::_once=PTHREAD_ONCE_INIT;
```

## 标准库中string的底层实现

一共有三种方式，分别是

```
Eager Copy		深拷贝
COW(Copy-On-Write)	写时复制
SSO(Short String Optimization)	短字符串优化
```

每种实现，`std::string`都包含了下面的信息

```
字符串的大小
能容纳的字符数量
字符串内容本身
```

可以用`printf("%p",str);`的方式查看字符串的起始地址

### Eager Copy 深拷贝

如果写时并不修改字符串原本的内容，就会使得效率很低

### COW 写时复制

当两个`std::string`发生复制构造或者赋值时，不会直接复制字符串的内容，而是引用计数加1，`std::string`对象共享字符串内容；当`std::string`对象销毁时，并不直接释放字符串所在的空间，而是先将引用计数减1，直到引用计数为0时，则真正释放字符串内容所在的空间。

对于引用计数，栈上生命周期不够，全局区被所有对象公用不合适，只能放在堆上，且放在数据的前面(因为如果放在后面，每次修改数据都可能造成内存踩踏)

```cpp
class String{
    class CharProxy;//代理模式
    //重载输出流
    friend std::ostream &operator<<(std::ostream &os,const CharProxy &rhs);
    friend std::ostream &operator<<(std::ostream &os,const String &rhs);
public:
    //构造函数,至少要申请1个字节的空间+4个字节存放引用计数，申请完后指针向后偏移4个字节到字符串存放的起始位置
    String():_pstr(new char[5]()+4){initRefcount();}
    
    String(const char *pstr):_pstr(new char[strlen(_pstr)+5]()+4){
        strcpy(_pstr,pstr);
        initRefcount();
    }
    
    //拷贝构造函数
    String(const String &rhs):_pstr(rhs._pstr){
        increaseRefcount();
    }
    
    //赋值运算符函数
    String &operator=(const String &rhs){
        if(this!=&rhs){//1、自复制
            release();//2、释放左操作数
            _pstr=rhs._pstr;//3、浅复制
            increaseRefcount();//4、引用计数+1
        }
        return *this;//5、返回*this
    }
        
    ~String(){
        release();
    }
    
    int getRefcount(){
        return *(int *)(_pstr-4);
    }

    const char *c_str()const{
        return _pstr;
    }
    
    int size(){
        return strlen(_pstr);
    }
    
    //重载下标访问运算符，读写应当有所区分
    CharProxy &operator[](size_t idx){
		return CharProxy(*this,idx);
    }
    
private:
    char *_pstr;
    
    //初始化引用计数为1
    void initRefcount(){
       *(int *)(_pstr-4)=1;//(int *)表示类型是int型指针，直接(int)会强转为整型数
    }
    
    void increaseRefcount(){
        ++*(int *)(_pstr-4);
    }
    
    void decreaseRefcount(){
        --*(int *)(_pstr-4);
    }

    void release(){
        decreaseRefcount();
        if(getRefcount()==0){
            delete [](_pstr-4);//注意还要释放掉前面的引用计数
        }
    }
    
    class CharProxy{
    public:
        CharProxy(String &self,size_t idx):_self(self),_idx(idx){}//引用必须列表初始化
        //写操作	s[idx]=xxx;
        char &operator=(const char ch){
            if(_idx<_self.size()){
                cahr *ptmp=new char[strlen(_self._pstr)+5]()+4;
                strcpy(ptmp,_self._pstr);
                _self.decreaseRefcount();
                _self._pstr=ptmp;
                _self.initRefcount();//初始化新的字符串引用计数
                _self._pstr[_idx]=ch;
            }else{
                static char nullchar='\0';
                return nullchar;
            }
            return _self._self[_idx];
        }
        //读操作	cout<<s[idx];
        /*
        两者选其一
        friend std::ostream &operator<<(std::ostream &os,const CharProxy &rhs);
        
        operator char(){//这个好点
            return _self._pstr[_idx];
        }
        */
        
    private:
        //内部类的情况下如果不是指针或引用，则无法成功创建完String类
        String &_self;
        size_t _idx;
    };
};

std::ostream &operator<<(std::ostream &os,const String &rhs){
    os<<rhs._pstr;
    return os;
}

std::ostream &operator<<(std::ostream &os,const CharProxy &rhs){
    os<<rhs._self._pstr[_idx];//CharProxy对象的_self成员的_pstr成员的下标为_idx的字符
    return os;
}
```

### SSO 短字符串优化

对于较短的字符串，直接执行字符串的拷贝消耗的空间可能会小于指针的拷贝

当字符串的长度小于等于15个字节时直接存放整个字符串

当字符串大于15个字节时存放的就是一个指针，指向堆空间的区域。

这样做的好处是，当字符串较小时，直接拷贝字符串，放在string内部，不用获取堆空间，开销小。

# day11

## 继承

### 继承的定义

当一个派生类继承一个基类时，需要在派生类的类派生列表指出是哪个基类继承来的

默认的继承是private私有继承

```cpp
class 派生类
:public/protected/private 基类{
//...
};
```

派生类的生成过程包括

```
1、吸收基类的成员
2、改造基类的成员
3、添加自己的新成员
```

### 继承的局限性

基类的以下特征是无法被派生类继承的

```
构造函数、析构函数
用户重载的operator new/delete运算符
用户重载的operator=运算符
友元关系
```

### 派生类对基类成员的访问权限

private成员是私有成员，只能在本类的内部访问

public成员是公有成员，任何地方都可以访问

protected成员是保护成员，只能在本类和派生类的内部访问

```
1、不论是何种继承方式，派生类内部都不能访问基类的private成员
2、派生类内部可以访问基类的除了private成员以外的其他成员
3、派生类对象只能访问public继承的基类的public成员
```

如果B公有继承自A，而C私有继承自B，则对C来说是无法在类内访问A的公有成员的，只能访问B的公有成员，而C的对象无法访问A和B的任何公有成员



### 派生类对象的构造

由于派生类不能继承基类的构造函数和析构函数，因此派生类需要重新定义自己的构造函数和析构函数

由于派生类对象通过继承而包含了基类的数据成员，因此创建派生类对象时，在调用派生类的构造函数的过程中会**先调用基类的构造函数完成基类成员的初始化**，再对派生类中新增的数据成员进行初始化

```cpp
派生类名(总参数表):基类构造函数(基类参数表){
	//...
}
```

必须将基类的构造函数放在派生类的构造函数的初始化列表中

派生类的构造函数如果没有显式的调用基类的构造函数，则基类的默认构造函数必须为public的

派生类的构造函数如果要调用基类相应的构造函数，必须显式调用

派生类构造函数的调用顺序为

```
1、完成对象所占整块内存的开辟，由系统在调用构造函数时自动完成
2、调用基类的构造函数完成基类成员的初始化
3、若派生类中含对象成员、const成员或引用成员，则也必须在初始化列表中完成其初始化
4、派生类构造函数的函数体执行
```

### 派生类对象的销毁

派生类析构函数的调用顺序为

```
1、先调用派生类的析构函数
2、在调用派生类中成员对象的析构函数
3、最后调用基类的析构函数
```

# day13

## 继承

### 多基继承(多基派生)

```cpp
class 派生类
:public/private/protected 基类1
,...,public/private/protected 基类N{
	//...
};
```

### 多基继承的派生类对象的构造和销毁

各基类构造函数的执行顺序与其在初始化列表中的顺序无关，而是由定义派生类时指定的基类顺序决定的

多基派生时的构造函数的总参数表需要包含后面各个基类构造函数需要的参数

析构函数的执行顺序与构造函数的执行顺序相反

### 成员名冲突的二义性

如果多个基类中存在同名成员的情况，就会产生二义性

解决方法也很简单，使用作用域限定符指明调用的是哪个基类的成员函数即可

### 菱形继承的二义性问题

采用虚拟继承的方式解决，即在中间派生类中使用virtual关键字继承基类

### 基类与派生类之间的相互转换

派生类的对象(指针、引用)能直接用于基类对象所能应用的场合(向上转型)

基类对象不能直接赋给派生类对象，因为会导致派生类对象的一部分数据成员无法被操作到或造成派生类指针越界的问题(虽然强制转换可以实现向下转型，但是这是不安全的)

关键点在于基类操纵的内存范围要小于派生类

### 派生类对象间的复制控制

由于基类的拷贝构造函数和赋值运算符函数都不能被派生类继承，因此在执行派生类对象间的复制操作时

```
1、如果没有定义派生类的拷贝构造函数或重载派生类的赋值运算符函数，则基类部分执行基类的复制行为，派生类部分执行默认的缺省复制行为

2、如果定义了，则会执行用户定义的复制函数，通常需要用户在定义的派生类复制函数中显式调用基类的复制函数
```

# day14

## 多态

对于同一个消息、同一种调用，在不同的场合、不同的情况下，有不同的执行行为

### 两种多态性

编译时多态(静态多态)：函数重载、运算符重载、模板等，编译器根据传递给函数对参数和函数名决定要使用哪个函数

运行时多态(动态多态、动态联编)：编译器无法在编译时完成联编，而是必须在程序运行时完成选择

### 虚函数的定义

虚函数就是在基类中被声明为virtual，并在一个或多个派生类中被重新定义的成员函数

```cpp
//类内部
class 类名{
	virtual 返回类型 函数名(参数列表){
		//...
	}
};
//类之外
virtual 返回类型 类名::函数名(参数列表){
	//...
}
```

如果一个基类的成员函数被定义为虚函数，那么它在所有的派生类中也是虚函数，派生类如果要对虚函数进行重定义，需要满足下面的条件

```
1、要与基类的虚函数有相同的参数个数
2、要与基类的虚函数有相同的参数类型
3、要与基类的虚函数有相同的返回类型
```

### 虚函数多态性被激活的条件

```
1、基类中定义虚函数
2、派生类重定义(覆盖)该虚函数
3、创建派生类对象
4、基类的指针(引用)要指向(绑定)派生类对象
5、基类的指针(引用)调用虚函数
```

### 虚函数的实现机制

基类定义一个虚函数时，就会在基类对象的存储布局中产生一个虚函数指针，该指针会指向一张虚函数表(虚表)，该虚表存放了基类各虚函数的入口地址

当派生类继承基类时，会把基类的虚函数指针和虚函数表也继承过来，如果派生类重定义(覆盖)了虚函数，就会把原本的虚函数表中该虚函数的入口地址覆盖为新的函数入口地址

### 哪些函数不能被设置为虚函数

```
1、普通函数(非成员函数)		  普通函数在编译时已经绑定，并且没有重写的必要

2、静态成员函数				静态意味着类的所有对象都可以共享，不需要动态绑定

3、内联成员函数				内联函数在编译时就已经展开了，而虚函数是在运行时才动态绑定的

4、构造函数					  构造函数就是为了初始化对象成员，与虚函数"在不了解细节的情况下也能处理事务"的目的不符

5、友元函数					  本质是可以访问类内成员的普通函数，并不是类的成员函数
```

如果是类的成员函数，则可以设置为虚函数，并作为友元函数提供给其他类

```cpp
class Line{
public:
	virtual void distance();
};

class Base{
	friend void Line::distance();
};
```

### 虚函数的访问

#### 指针访问

使用指针访问非虚函数时，编译器根据指针本身的类型决定调用哪个函数

使用指针访问虚函数时，编译器根据指针所指的对象的类型决定要调用哪个函数

#### 引用访问

与指针访问相同

不同点在于引用一经声明后，无论引用变量本身如何改变，其调用的函数都不会再改变了，始终指向其定义的时候的函数，提高了代码的安全性

#### 成员函数中访问

借助this指针体现多态性

#### 对象访问

这种情况下采用的是静态联编，调用哪个类的函数取决于对象名的类型，与多态无关了，只能说明虚函数能被对象访问(因为本质还是类的成员函数)

#### 构造函数和析构函数中访问

采用静态联编，即使是使用`this->虚函数名`的形式，编译器仍会解释为`本类名::虚函数名`即它们调用的虚函数是自己类中定义的函数，如果在自己的类中没有实现，则会调用基类的虚函数而不会调用任何在派生类中重定义的虚函数

注意构造函数体中调用虚函数时派生类的对象还没创建成功，此时调用的是基类的

#### 虚函数的执行不一定体现多态性，但多态性一定是在虚函数的执行中体现的

### 纯虚函数

即在基类中不对虚函数给出具体的实现，而是交由派生类去实现

```cpp
class 类名{
public:
    virtual 返回类型 函数名(参数列表)=0;
};
```

派生类必须实现基类的所有纯虚函数，否则派生类会成为抽象类，不能创建对象

派生类会继承基类重写的纯虚函数以及未重写的纯虚函数

### 抽象类

只要类中含有一个纯虚函数，该类就称为抽象类，抽象类只能作为基类派生新类，不能创建对象。

只有派生类给出了基类中所有纯虚函数的实现，才不再是抽象类

另一种形式的派生类：构造函数定义为protected类型不能创建对象，派生出的类可以创建对象

### 虚析构函数

如果类中定义了虚函数，那么析构函数就应当被定义为虚析构函数，尤其是类内有申请动态内存需要清理和释放的时候，这样的话不用强制转换，基类的指针也可以执行派生类的析构函数了

基类的析构函数设置为虚函数后，派生类的析构函数也自动会变为虚函数

析构函数不能重载，具有唯一性

### 重载、隐藏、覆盖

重载`override`：发生在同一个类中，函数名称相同，但是参数的类型、个数、顺序不同

隐藏`oversee`：发生在父子类中，指某些情况下派生类的函数屏蔽了基类的同名函数，可以用作用域限定符调用被隐藏的基类函数

覆盖`overload`：发生在父子类中，同名虚函数，参数完全相同





# day15

## 多态

### 测试虚表的存在

同一个类不同对象在栈上的地址不同，但是共享同一张虚表，虚表存在于只读段

```cpp
class Base{
public:
    Base():_base(10){}
    virtual void func1(){}
    virtual void func2(){}
    virtual void func3(){}
private:
    double _base;
};
class Derived{
public:
    Derived():Base(),_derived(20){}
    virtual void func1(){}
    virtual void func2(){}
    virtual void func3(){}
private:
    double _derived;
};

void func(){
    cout<<"sizeof(Base)="<<sizeof(Base)<<endl;//8+8
    cout<<"sizeof(Derived)="<<sizeof(Derived)<<endl;//16+8
    Derived derived;
    printf("派生类对象derived的地址：%p\n",&derived);
    printf("派生类对象derived的vfptr地址：%p\n",(long *)&derived);//和derived的地址一样，只不过代表的实际意义是vfptr
    printf("vfptr指向的虚表的地址：%p\n",(long *)*(long *)&derived);//打印的是的位于只读段的虚表的首地址
    printf("vfptr指向的虚表的存放的首个虚函数的入口地址：%p\n",(long *)*(long *)*(long *)&derived);//打印的是第一个虚函数的入口地址
    
    typedef void (*pFunc)();//函数指针，指向返回值为void，参数为空的函数
    pFunc f=NULL;
    f=(pFunc)*((long *)*(long *)&derived);
    f();//func1
    printf("第一个虚函数的入口地址：%p\n",f);
    f=(pFunc)*((long *)*(long *)&derived+1);//+1偏移一个pFunc所占字节大小的位置
    f();//func2
    printf("第二个虚函数的入口地址：%p\n",f);
    
    cout<<"_base = "<<*((double *)&derived+1)<<endl;//基类成员在虚函数指针之后
    cout<<"_derived = "<<*((double *)&derived+2)<<endl;//派生类在基类成员之后
}
```

### 多基派生的二义性

基类指针调用派生类的函数时，对于重写了的虚函数会调用派生类的版本，对于没有重写的虚函数则仍会调用基类的版本，同时，对于基类自己的成员函数，仍采用静态联编，不会调用派生类的同名函数

如果派生类同时继承自多个基类，且恰好基类有重名的虚函数，派生类又没有重写这个虚函数，就会造成二义性的问题。

派生类同时继承自多个基类时，第一个基类的虚函数指针地址和派生类本身的指针地址是相同的，之后的基类的虚函数指针从第一个基类虚函数指针起依次往下

### 虚拟继承

虚拟继承是为了解决多重继承中基类可能被多次继承的命名冲突和冗余数据的问题而出现的

如果在多条继承路径上有一个公共的基类，为了让公共的基类只产生一个实例，就需要在继承路径上将该基类说明为虚基类，这样就不会产生派生类使用基类成员时出现的可能的二义性问题

虚拟继承体现的存在、间接、共享三特征：

```
虚继承体系和虚基类确实存在
当访问虚基类的成员时必须通过某种间接机制(虚基表)来完成
共享性表现在虚基类会在虚继承体系中被共享，而不会出现多份拷贝
```

虚拟继承是指在类之间的继承定义中包含了virtual关键字的继承关系

虚基类是指在虚继承体系中通过virtual继承而来的基类，是一种相对而言的概念

```cpp
class Base;

class Derived:public/private/protected virtual Base{
//...
};

Base称为Derived的虚基类，但是不代表Base本身是虚基类
```

### 虚拟继承时派生类对象的构造和析构

不管初始化列表中次序如何，虚基类构造函数的调用先于非基类的构造函数；同一层次的虚基类之间构造函数调用的先后顺序按照说明的次序调用

虚基类子对象必须由最新派生出的类负责初始化

派生类的构造函数的成员初始化列表中必须显式列出虚基类的构造函数，否则会使用虚基类的缺省构造函数。如果虚基类没有定义缺省构造函数，则会编译错误，因为会导致虚基类部分在可能存在的多个继承链上多次初始化

派生类对象的构造过程中虚基类的构造函数只会被距离最远的派生类的构造函数执行一次，即使该派生类有多个基类声明了该虚基类的构造函数

派生类对象的析构函数的调用顺序：

```
1、派生类的析构函数
2、派生类中成员对象的析构函数
3、普通基类的析构函数
4、虚基类的析构函数
```

### 存储布局

类之间的存储布局依次为：基类-派生类-虚基类

每个类的类内成员的布局依次为：虚函数指针(vfptr)-虚基指针(vbptr)-类自己的数据成员

#### 单个虚拟继承

##### 不带虚函数

虚继指针(vbptr)在派生类对象存储布局的起始位置，虚基类子对象在存储布局的末尾

![image-20200511101802718](D:\TyporaPic\复习笔记\image-20200511101802718.png)

##### 带虚函数

派生类在vbptr之前多一个vfptr指向派生类自己的虚函数表，基类在子对象的起始位置多一个基类的vfptr

![image-20200511101656752](D:\TyporaPic\复习笔记\image-20200511101656752.png)

#### 多重继承

##### 不使用虚拟继承

各基类按派生类定义时被声明时的顺序进行排列 ，最后是派生类自己的数据成员

![image-20200511102114025](D:\TyporaPic\复习笔记\image-20200511102114025.png)

基类中被重写的虚函数在虚表中会用goto语句跳转到第一个基类虚表相应虚函数的位置，如果派生类自己有新的虚函数，也会放到第一个基类的虚表下(不需要偏移，速度最快)

![image-20200511102436054](D:\TyporaPic\复习笔记\image-20200511102436054.png)

##### 使用虚拟继承

派生类存储布局依次为：基类-派生类-虚基类；类内成员的布局依次为：虚函数指针(vfptr)-虚基指针(vbptr)-数据成员

其中基类包含自己的虚函数指针和数据成员；派生类包含自己的虚函数指针、虚基指针和自己的数据成员；虚基类包含自己的虚函数指针和自己的数据成员

![image-20200511103207279](D:\TyporaPic\复习笔记\image-20200511103207279.png)

虚表如下：

派生类会覆盖基类的虚函数，只有第一个虚函数表中存放的是真实的被覆盖的函数的地址；其它的虚函数表中存放的并不是真实的对应的虚函数的地址，而只是一条跳转指令 (this-=number,goto Derived::function)，目的是从vbptr找到对应的vfptr

<img src="D:\TyporaPic\cppDay23\image-20200511103359690.png" alt="image-20200511103359690" style="zoom: 80%;" />



#### 菱形继承

##### 不使用虚拟继承

会造成二义性

![image-20200511103917535](D:\TyporaPic\复习笔记\image-20200511103917535.png)

虚函数表

![image-20200511104041707](D:\TyporaPic\cppDay23\image-20200511104041707.png)



##### 使用虚拟继承

![image-20200511104459133](D:\TyporaPic\复习笔记\image-20200511104459133.png)

虚函数表及虚基表

![image-20200511104609292](D:\TyporaPic\复习笔记\image-20200511104609292.png)



# day16

## 互斥锁、条件变量的封装

```
pthread_mutex_lock	加锁
pthread_mutex_unlock	解锁

pthread_cond_wait	等待条件变量
pthread_cond_signal	唤醒条件变量
pthread_cond_broadcast	唤醒所有等待的线程
```

每个类都要有构造函数和析构函数，执行锁和条件变量的初始化和销毁

互斥锁和条件变量彼此并不负责对方的生命周期，互不相干，彼此独立，MutexLock的对象以引用的形式在Condition的构造函数中作为参数传递

```
pthread_cond_wait分为上下半部
使用条件变量时一定要调用互斥锁，因为要操作临界资源

上半部：当加锁之后，调用该方法时，表示当前线程A要进入阻塞状态，但是在进入阻塞状态前会解锁，暂时不占用这把互斥锁

下半部：当线程A被激活(唤醒)时，接下来就要访问临界资源了，因此要重新获得锁并加锁，才能继续操作临界资源
```

MutexLock和Condition都属于系统资源，系统资源不能进行复制控制(拷贝构造函数或赋值运算符函数)

```cpp
ifstream(const ifstream &)=delete;	//c++11新特性，禁止执行拷贝构造函数
ifstream &operator=(const ifstream &)=delete;
```

禁止执行复制控制操作的类表达的是对象语义

允许执行复制控制操作的类表达的是值语义

vim MutexLock.hpp

```cpp
class MutexLock{
public:
    MutexLock():_isLocking(false){
        pthread_mutex_init(&_mutex,NULL);//初始化互斥锁
    }

    ~MutexLock(){
        pthread_mutex_destory(&_mutex);//销毁互斥锁
    }
    
    void lock(){
        pthread_mutex_lock(&_mutex);
        _isLocking=true;
    }
    
    void unlock(){
        pthread_mutex_unlock(&_mutex);
        _isLocking=false;
    }
    
    pthread_mutex_t *getMutexLockPtr(){
        return &_mutex;
    }
    
    bool isLocking() const{
        return _isLocking;
    }
    //对象语义
    MutexLock(const MutexLock &)=delete;
    MutexLock &operator=(const MutexLock &)=delete;
    
private:
    pthread_mutex_t _mutex;
    bool _isLocking;
};
//自动管理加解锁，利用对象生命周期和构造析构函数的关联
class MutexLockGuard{
public:
    MutexLockGuard(MutexLock &mutex):_mutex(mutex){_mutex.lock();}
    ~MutexLockGuard(){_mutex.unlock();}
private:
    MutexLock &_mutex;
};
```

vim Condition.hpp

```cpp
class Condition{
public:
    Condition(MutexLock &mutex):_mutex(mutex){
        pthread_cond_init(&_cond,NULL);
    }
    
    ~Condition(){
        pthread_cond_destory(_cond);
    }
    
    void wait(){
        pthread_cond_wait(&_cond,_mutex.getMutexLockPtr());
    }
    
    void notify(){
        pthread_cond_signal(&_cond);
    }
    
    void notifyAll(){
        pthread_cond_broadcast(&_cond);
    }
    
private:
    pthread_mutex_t &_mutex;
    pthread_cond_t _cond;
};
```

# day17

## 移动语义

```cpp
比如下列代码：
vector<string> v;
v.push_back("hello world");

依次调用了以下函数：
string(const char *);//转换为string临时对象
string(const string &);//使用临时对象构造新对象
~string();//第一步转换的对象的销毁
```

为了减少临时对象的构造和析构带来的不必要的资源拷贝，引入了`右值引用`

可以在语法层面识别出临时对象，在使用临时对象构造新对象(拷贝构造)的时候，将临时对象所持有的资源`转移`到新的对象中，就可以消除这些不必要的拷贝了。

### 引用折叠

【规则1】如果间接的创建一个引用的引用，就会发生引用折叠

只有右值引用的右值引用会折叠为右值引用

```cpp
X& &	X& &&	X&& &	都会折叠为X&
X&& &&	会折叠为X&&	
```

【规则2】当将一个左值传递给一个参数是右值引用的函数，且此右值引用指向模板类型参数(T&&)时，编译器推断模板参数类型为实参的左值引用(左值--(模板)->左值引用)

```cpp
template<typename T>
void f(T&&);

//如果传入的是左值int，则编译器推断T的类型为int &,再根据引用折叠规则void f(int & &&)会被折叠为void f(int &),因此f将被实例化为void  f<int &>(int &)
```

如果一个函数形参是一个指向模板类型的右值引用，则该参数可以绑定到一个左值上。

【规则3】虽然不能隐式的将一个左值转换为右值引用，但是可以通过`static_cast<>`显式地将一个左值转换为一个右值

### std::move

move是无条件的将传递的实参转换为右值引用，依靠`remove_reference`和`static_cast`来完成，主要用于指明转移语义，常用于传参数和返回值，主要是为了提示编译器这里可以用转移语义，而不需要保守的使用复制语义

标准库中`std::move`的定义如下：

```cpp
template <typename T>
typename remove_reference<T>::type && move(T &&t){
    return static_cast<typename remove_reference<T>::type &&>(t);
}
```

move函数的参数T &&是一个指向模板类型参数的右值引用(【规则2】)，通过引用折叠，该参数可以和任何类型的实参匹配

```cpp
//remove_reference<T>::type 引用移除
//decltype()	返回变量的类型，常用于获取变量类型
std::move(string("hello"));//右值
根据模板推导规则可得T的类型为string	
typename remove_reference<T>::type的结果为string
move的参数类型为string &&
static_cast<string &&>(t) 直接返回右值
最终move被实例化如下：
string &&move(string &&_t){
	return static_cast<string &&>(_t);
}

string s1("hello");
std::move(s1);//左值
根据模板推导规则可得T的类型为string &	【规则2】
typename remove_reference<T>::type的结果为string	去除引用
move的参数类型为string & &&,经过折叠后为string &
static_cast<string &&>(t),t是string &,经过强转后返回右值
最终move被实例化如下：
string &&move(string &_t){
	return static_cast<string &&>(_t);
}
```

需要注意的是，`std::move`本身并不会使得传入的参数的值被丢掉，`std::move`本身只是将参数转换为右值引用而已，真正的移动操作是在参数的类内部定义的移动拷贝函数，只不过移动拷贝的处理过程中常常会把右值的资源指针置为`nullptr`，此时传入的参数就不再可用；如果没有对传入的参数的资源进行处理，则原参数仍可以访问(但是不建议，因为使用move就意味着这个对象不应再被使用了)

### std::forward

forward是完美转发，即在参数传递的过程中保持其属性不变

只有当参数绑定到右值上时，才会转换它的参数到一个右值

标准库中`std::forward`实现如下：

```cpp
//constexpr 常量表达式 关键字，修饰编译期可求值的变量
//noexcept 代表该函数不会发生异常，如果被该关键字修饰的函数抛出了异常，则程序会直接终止，调用std::terminate()函数，函数内部会调用std::abort()终止程序
template <typename T>
constexpr _Tp&&
forward(typename std::remove_reference<_Tp>::type & __t)noexcept{
    return static_cast<_Tp&&>(__t);
}

template <typename T>
constexpr _Tp&&
forward(typename std::remove_reference<_Tp>::type &&)noexcept{
    static_assert(!std::is_lvalue_reference<_Tp>::value,"template argument substituting _Tp is an lvalue reference type");
    return static_cast<_Tp&&>(__t);
}
```

```cpp
std::forward(1);//右值
根据模板推导规则可得T的类型为int
typename remove_reference<_Tp>::type的结果为int
forward的参数类型为int &&
static_cast<int &&>()直接返回右值
最终forward被实例化如下：
int &&forward(int &&_t){
	return static_cast<int &&>(_t);
}

int i=1;
std::forward(i);//左值
根据模板推导规则可得T的类型为int &	【规则2】
typename remove_reference<_Tp>::type 的结果为int
forward的参数类型为int &
static_cast<int & &&>()引用折叠后返回左值
最终forward被实例化如下：
int &forward(int &_t){
    return static_cast<int &>(_t);
}
```

### 使用移动构造函数和移动赋值运算符函数改善右值拷贝的资源消耗问题

由于`const &`是万用引用，不能区分传参进来的是左值还是右值，因此可以在类中定义移动构造函数和移动赋值运算符函数对右值参数进行特化处理

如果没有定义移动拷贝函数，则会按照左值的处理调用const &的万用版本的拷贝函数

如果定义了移动拷贝函数，则会调用对应的移动拷贝函数，而不是普通版本的拷贝函数了。

拷贝构造函数、赋值运算符函数(自复制，释放左操作数，深拷贝)被称为具有复制控制语义的函数

移动构造函数、移动赋值运算符函数(自移动，释放左操作数，浅拷贝)被称为具有移动语义的函数

通常用于自定义类型

```cpp
class String{
public:
    //当执行右值拷贝时，我们希望能将临时对象直接转移到新对象里，而不是先创建临时对象，再执行拷贝
    String(String &&rhs):_pstr(rhs._pstr){//浅拷贝，移动
        rhs._pstr=nullptr;//将临时对象的pstr设置为空指针
    }
    
    String &operator(String &&rhs){
        //右值引用如果有名字，则本身应为左值
        if(this!=&rhs){//自移动	s1=std::move(s1);
            delete []_pstr;
            _pstr=rhs._pstr;//浅拷贝，移动
            rhs._pstr=nullptr;
        }
        return *this;
    }
};

//-fno-elide-constructors 把关闭编译优化的开关打开
```

# day18

## 资源管理

new：operator new分配空间->构造函数初始化对象->返回对应类型指针

delete：析构函数清理类内部申请的资源->operator delete 清理类本身

为了更安全的管理资源，建议使用智能指针借助对象的生命周期来管理资源(对象销毁时会自动调用析构函数)

特点：

```
1、申请资源时创建RAII对象来托管资源
2、当对象销毁时自动释放资源
3、提供若干访问资源的方法
4、一般情况下表达对象语义(不允许复制)
```



```cpp
template <typename T>
class RAII{
public:
    explicit	//禁止隐式转换
    RAII(T *p=nullptr):_p(p){}
    //指针访问运算符。返回的是指向对象的指针
    T* operator->(){
        return _p;
    }
    //解引用运算符，返回的是对象本身
    T& operator*(){
        return *_p;
    }
    
    T* get(){
        return _p;
    }
    
    void reset(T *p){
        if(_p){
            delete _p;
        }
        _p=p;
    }
    //禁止进行拷贝操作，即不具备复制控制语义
    RAII(const RAII &)=delete;
    RAII&operator=(const RAII &)=delete;
    
    ~RAII(){
        if(_p){
            delete _p;
        }
    }
    
private:
	T *_p;
};
```

### unique_ptr

独享所有权的智能指针

能够借助`->`和`*`等访问资源

表达对象语义，类内不提供具有复制控制语义的函数，不能进行复制或赋值

具有移动语义，可以作为右值存放在容器中(借助`std::move`)

```cpp
void test(){
    Point *pt=new Point(1,2);
    unique_ptr<Point> up(pt);
    //1、unique_ptr是独享所有权的智能指针，不具备复制控制语义(delete)
    //unique_ptr<Point> up2(up);//error
    //up3=up;//error
    //2、unique_ptr具有移动语义
    unique_ptr<Point>up4=std::move(up);//pt托管的资源交给up4管理了
    up.reset(new Point(11,12));//如果还想使用up这个变量名，就必须重新托管资源
    up4->print();
    (*up4).print();
}
//通常情况下，如果返回值类型是对象，且类中同时满足移动语义和复制控制语义，当返回的是局部对象时会调用移动构造函数，当返回的对象生命周期大于函数本身则会调用拷贝构造函数
//unique_ptr作为函数返回值时如果返回的是局部对象，会调用移动构造函数，如果返回的生命周期大于函数，会error，因为unique_ptr的拷贝构造函数被delete了，不能被调用
unique_ptr<Point> getValue(){
    unique_ptr<Point> point(new Point(1,2));//point在栈上，随函数执行完毕而销毁
    return point;//调用unique_ptr的移动构造函数，返回的是一个右值
}

void test2(){
    Point *pt=new Point(1,2);
    unique_ptr<Point> up(pt);
    vector<unique_ptr<Point>> points;
    points.push_back(std::move(up));//正确
    //points.push_back(up);//error,因为up是左值，会试图调用拷贝构造函数，但是已经被delete了
}
```

### shared_ptr

强引用智能指针

能够访问资源

共享所有权的智能指针

借助于引用计数，可以进行复制或赋值，使用`use_count`可以查看一个对象的引用计数值

当进行复制控制操作时，右操作数引用计数+1，左操作数引用计数-1(如果是赋值)

当`shared_ptr`被销毁时，先将引用计数-1，如果引用计数为0，才会真正释放资源

```cpp
void test(){
    Point *pt=new Point(1,2);
    shared_ptr<Point> sp(pt);
    sp->print();
    shared_ptr<Point> sp2(sp);//允许复制控制
    shared_ptr<Point> sp3(new Point(3,4));
    sp3=sp;//(3,4)被析构
    shared_ptr<Point> sp4=std::move(sp);
    sp.reset(new Point(11,12));
}
```

#### 提防循环引用的问题

两个类内部数据成员互相包含，导致析构时只有栈上的对象被析构，堆上的智能指针还在，导致引用计数无法归0

```cpp
struct Child;//类的前向声明
struct Parent{
    shared_ptr<Child> _pChild;
};
struct Child{
    shared_ptr<Parent> _pParent;
};
void test(){
    shared_ptr<Child> pChild(new Child());
    shared_ptr<Parent> pParent(new Parent());
    pChild._pParent=pParent;
    pParent._pChild=pChild;
}//栈上的pChild和pParent析构销毁了，但是堆空间申请的Child和Parent对象没有销毁，而是互相指向对方导致引用计数无法归0
```

### weak_ptr

弱引用智能指针

为了解决`shared_ptr`的循环引用问题出现的

当对`weak_ptr`进行复制控制操作时，不会导致引用计数的增加

没有提供访问资源的方法		没有实现`operator* operator->`

如果要访问资源，必须要使用`lock()`方法提升为`shared_ptr`，相当于延长了生命周期

可以获取引用计数

知道托管的对象是否存活

```cpp
void test(){
    weak_ptr<Point> wp;
    {
        shared_ptr<Point> sp(new Point(1,2));
        wp=sp;//引用计数不变
        cout<<sp.use_count()<<endl;
        shared_ptr<Point> sp2=wp.lock();//如果托管的对象为空(或者已经销毁了，会返回空)
        if(sp2){
            cout<<"lock提升成功"<<endl;
        }
    }//语句块内有效
    if(wp.expired()){//能知道托管的对象是否还存在
        cout<<"已被销毁"<<endl;
    }
}
```

前面`shared_ptr`的循环引用问题也可以借助`weak_ptr`来解决

```cpp
struct Child;//类的前向声明
struct Parent{
    weak_ptr<Child> _pChild;
};
struct Child{
    shared_ptr<Parent> _pParent;
};
void test(){
    shared_ptr<Child> pChild(new Child());
    shared_ptr<Parent> pParent(new Parent());
    pChild._pParent=pParent;//sp=sp,引用计数+1
    pParent._pChild=pChild;//wp=sp,引用计数不变
}//结束时pChild和pParent都销毁，Child的引用计数归0，带动Parent对象的引用结束也为0了
```

### 类内部获取本对象的shared_ptr

让类公有继承自`std::enable_shared_from_this<类名>`

### 智能指针的误用

```
1、不要将一个对象托管给多个不同的智能指针
2、一旦将一个对象托管给智能指针，之后对该对象的所有操作都要借助智能指针进行，不要再使用原生裸指针
```

### unique_ptr和shared_ptr的自定义删除器

`unique_ptr`和`shared_ptr`都可以自己指定资源删除方式，资源不一定指的是堆空间的对象

删除器具有一定的扩展性，借助自定义函数对象完成

```cpp
struct Fpcloser{
    void operator()(FILE *fp){//重载函数调用运算符
        if(fp){
            fclose(fp);
        }
    }
};

void test1(){
    unique_ptr<FILE,Fpcloser>up(fopen("test.txt","a+"));
    string msg("unique_ptr");
    fwrite(msg.c_str(),1,msg.size(),up.get());
    //fclose(up.get());//手动调用关闭把数据刷新到文件里
}

void test2(){
    shared_ptr<FILE,Fpcloser>sp(fopen("test.txt","a+"));
    string msg("shared_ptr");
    fwrite(msg.c_str(),1,msg.size(),sp.get());
}
```

# day19

## 封装线程Thread类

使用`pthread_create`创建子线程时，由于第三个参数是指向形参为void *,返回值是void  *的函数指针，为了消除普通成员函数隐含的this指针( * const的，const修饰 *表示不能改变指向 )，因此要把threadFunc定义为静态成员函数，同时为了防止通过对象直接调用，因此要放在private区域

对于不同的线程，要执行的任务也不相同，因此要设置一个纯虚函数`run()=0`让具体的线程子类重写任务函数，并在threadFunc中调用该函数，同样的，为了防止对象直接调用，需要把run函数放在private区域，为了在类内调用纯虚函数，需要借助this指针，因此`pthread_create`的第四个参数就是this指针

```cpp
class Thread{
public:
    Thread():_pthid(0),_isRunning(false){}
    
    void start(){
        pthread_create(_pthid,NULL,threadFunc,this);
        _isRunning=true;
    }
    
    void join(){
        if(_isRunning){
            pthread_join(_pthid,NULL);
        }
        _isRunning=false;
    }
    
    virtual ~Thread(){
        if(_isRunning){
            pthread_detach(_pthid);//交给系统回收
        }
    }
    
private:
    pthread_t _pthid;
    bool _isRunning;
    
    static void *threadFunc(void *arg){
        Thread *pthread=(Thread *)arg;
        pthread->run();//调用时表现动态多态特性
    }
    
    virtual void run()=0;//交由派生类实现
};

class Mythread:public Thread{
	void run(){
        cout<<"Mythread::run()"<<endl;
    }
};

void test(){
    unique_ptr<Thread> pthread(new Mythread());
    pthread->start();
    pthread->join();
}
```

# day20

## UML统一建模语言

### 继承(泛化)

A is B

空心三角箭头，派生类指向基类

<img src="D:\TyporaPic\复习笔记\image-20200506102033360.png" alt="image-20200506102033360" style="zoom:25%;" />

### 依赖

A use B

关系是偶然的、临时的，通过函数体现B与A的关系，B的对象常作为A的函数的参数、局部变量或A的成员函数内部调用B类的静态方法

虚线箭头从调用类指向被调用类

<img src="D:\TyporaPic\复习笔记\image-20200506104247569.png" alt="image-20200506104247569" style="zoom:33%;" />

### 关联

A has B

关系是固定的、单向的，彼此并不负责对方的生命周期，一般B以指针或引用的形式作为A的数据成员存在

箭头从使用类指向被使用类

<img src="D:\TyporaPic\复习笔记\image-20200506102848418.png" alt="image-20200506102848418" style="zoom:50%;" />

### 聚合

比较强的关联关系，对象间关系表现为整体和局部，但是整体不负责局部对象的销毁

空心菱形箭头从局部指向整体

<img src="D:\TyporaPic\复习笔记\image-20200506103356566.png" alt="image-20200506103356566" style="zoom:25%;" />

### 组合

更强的关联关系，相比于聚合，整体要负责局部对象的销毁，当整体部分销毁时局部部分一定已经被销毁了

实心菱形箭头从局部指向整体

<img src="D:\TyporaPic\复习笔记\image-20200506103732299.png" alt="image-20200506103732299" style="zoom:25%;" />



## 生产者消费者问题

任务队列类TaskQueue组合了互斥锁类MutexLock和条件变量类Condition，生产者类Producer和消费者类Comsumer关联了任务队列类同时还继承自Thread类，具体行为在重写的run()方法中体现

```cpp
class TaskQueue{
public:
    TaskQueue(size_t size=10):_queSize(size),_mutex(),_cond(_mutex){}
    
    bool empty(){
        if(_que.size()==0){
            return true;
        }
        return false;
    }
    
    bool full(){
        if(_que.size()==_queSize){
            return true;
        }
        return false;
    }
    
    void push(int data){
        MutexLockGuard mlg(_mutex);
        while(full()){
            _cond.wait();
        }
        _que.push(data);
        _cond.notify();
    }
    
    int pop(){
        MutexLockGuard mlg(_mutex);
        while(empty()){
            _cond.wait();
        }
        int res=_que.front();
        _que.pop();
        _cond.notify();
        return res;
    }
    
private:
    queue<int> _que;
    size_t _queSize;
    MutexLock _mutex;
    Condition _cond;
};

class Producer:public Thread{
public:
    Producer(TaskQueue &que):_que(que){}//传引用减少拷贝
private:
    void run(){
        ::srand(time(NULL));
        while(1){
            int data=::rand()%100;
            _que.push(data);
            ::sleep(1);
        }
    }
    TaskQueue &_que;
};

class Consumer:public Thread{
public:
    Consumer(TaskQueue &que):_que(que){}
private:
    void run(){
        while(1){
            int data=_que.pop();
            cout<<data<<endl;
            ::sleep(2);
        }
    }
    TaskQueue &_que;
};

void test(){
    TaskQueue que(20);
    unique_ptr<Thread> consumer(new Consumer(que));
    unique_ptr<Thread> producer(new Producer(que));
    producer->start();
    consumer->start();    
    
    producer->join();
    consumer->join();
}
```

# day22

## 工厂模式

包含静态工厂模式、工厂方法模式、抽象工厂模式

```cpp
class staticFactory{//静态工厂，不满足开闭原则(对扩展开放，对修改关闭);不满足单一职责原则(一个类只负责一种对象的创建)
public:
    static Figure* createRectangle(){
        return new Rectangle(10,20);//具体数值通常会从配置文件读取
    }
    static Figure* createCircle(){
        return new Circle(2);
    }
};

void test(){
    unique_ptr<Figure> rectangle(staticFactory::createRectangle());//静态方法通过作用域限定符访问
    unique_ptr<Figure> circle(staticFactory::createCircle());
}
```

为了解决静态工厂模式的缺点，需要把Factory类作为抽象类，继承的派生类子工厂各自负责一种对象的创建

```cpp
class Factory{
public:
    virtual Figure* create()=0;
};

class RectangleFactory:public Factory{
public:
    Figure* create(){
        return new Rectangle(10,20);
    }
};

class CircleFactory:public Factory{
public:
    Figure* create(){
        return new Circle(2);
    }
};

void test(){
    //使用智能指针托管资源，栈上的对象(智能指针)在函数执行完毕会自动调用析构
    unique_ptr<Factory> rectangleFactory(new RectangleFactory());
    unique_ptr<Factory> circleFactory(new CircleFactory());
    
    unique_ptr<Figure> rectangle(rectangleFactory->create());
    unique_ptr<Figure> circle(circleFactory->create());
}
```

## 观察者模式

主要为一个对象状态发生变化时，观察者对象也会进行相应的行为

大致流程为：被观察对象受到外界其他对象影响->触发状态变化->对观察者行为进行更新

```cpp
class Subject{
public:
    virtual void attach(Observer *obj)=0;//添加观察者
    virtual void detach(Observer *obj)=0;//去除观察者
    virtual void notify()=0;//触发状态变化，对观察者行为进行更新
};

class Ring:public Subject{
public:
    Ring():_isAlarming(false){}
    
    void attach(Observer *obj){
        auto it=std::find(_obList.begin(),_obList.end(),obj);
        if(it==_obList.end()){
            _obList.push_front(obj);
        }
    }
    
    void detach(Observer *obj){
        auto it=std::find(_obList.begin(),_obList.end(),obj);
        if(it!=_obList.end()){
            _obList.earse(it);
        }
    }
    
    void notify(){
        for(auto &ob:_obList){
            ob->update();
        }
    }
    
    void isPressed(){
        if(!_isAlarming){
            _isAlarming=true;
            notify();
        }
    }
private:
    list<Observer *> _obList;
    bool _isAlarming;
}

class Guest{
public:
    Guest(string name):_name(name){}
    
    void knock(Ring &ring){
        ring.isPressed();
    }
private:
    string _name;
};

//观察者
class Observer{
public:
    virtual void update()=0;//被观察者行为发生变化时观察者的动作
};

class Baby:public Observer{
public:
    Baby(string name):_name(name){}
    void update(){
        ::srand(::time(NULL));
        int number=rand()%100;
        if(number<70){
            cout<<_name<<" is sleeping"<<endl;
        }else{
            cout<<_name<<" is crying"<<endl;
        }
    }
private:
    string _name;
};

void test(){
    unique_ptr<Subject> ring(new Ring());
    unique_ptr<Guest> guest(new Guest("tom"));
    unique_ptr<Observer> baby1(new Baby("zhangsan"));
    unique_ptr<Observer> baby2(new Baby("lisi"));
    ring->attach(baby1.get());
    ring->attach(baby2.get());
    guest->knock(*ring.get());
    ring->detach(baby2.get());
    guest->knock(*ring.get());
}
```

# day23

## 模板

```cpp
template <class/typename T,...>
```

关键字`template`放在模板的定义与声明的最前面，其后是用逗号分隔的`参数模板表`，模板的参数有两种类型：

class或typename修饰的类型参数，代表一种类型

非类型的参数表达式，必须是整型int类型，表达式使用的必须是已知的类型符号，表达式整体代表一个常量

class 的兼容性更好

### 函数模板

函数模板实际上不是一个完整的函数定义，因为具体的类型还不确定，必须将模板参数实例化了才能使用

```cpp
template <模板参数列表>
返回类型 函数名(参数列表){
    //函数体
}
```

模板的实现原理：模板参数推导

在函数进行调用时，通过实参传递的类型进行模板参数推导，最终得到相应版本的函数并由编译器自动生成

```cpp

//		实例化
//函数模板===>模板函数
//类模板===>模板类

template <class T>
T add(T x,T y){
    return x+y;
}

//函数模板间可以重载，函数模板也可以和普通函数重载，除非显式实例化，否则普通函数优先度更高
template <class T>
T add(T x,T y,T z){
    return x+y+z;
}

void test(){
    int i1=1,i2=2;
    cout<<add(i1,i2)<<endl;//隐式实例化
    cout<<add<int>(i1,i2)<<endl;//显式实例化，此时调用的就是函数模板了
}
```

#### 如何将模板的声明和定义分离

在定义模板时，要注意：

1、一般情况下，要看到模板的全部实现，否则编译会出错

2、一般情况下，模板的声明和定义要放在一个文件中，如果分开存放，必须在声明的头文件内用include将实现文件包含进来，而不是在实现文件中include头文件

vim Add	函数模板的声明文件不加后缀

```cpp
#pargma once
//函数模板的声明
template <class T>
T add(T x,T y);
//使用include将函数模板的定义包含进来
#include "Add.tcc"
```

vim Add.tcc	t表示是模板实现的文件

```cpp
template <class T>//模板参数列表，class T是模板形参
T add(T x,T y){//函数参数列表，T x,T y是函数形参
    return x+y;
}
```

vim test.cc

```cpp
#include "Add"

void test(){
    int i1=1,i2=2;
    cout<<add(i1,i2)<<endl;
}
```

#### 模板参数列表包含非类型参数

通常如果在代码内部使用常量，如果要修改必须要修改对应的源代码，而模板参数列表的非类型参数可以避开修改源码这个过程

```cpp
template <class T=double,int kMax=10>//模板参数可以设定默认值,省略则只能从右往左省略
T multiply(T x,T y){
    return kMax*x*y;
}

void test(){
    int i1=2,i2=3;
    double d1=1.5,d2=2;
    cout<<"10*i1*i2="<<multiply(i1,i2)<<endl;//60
    cout<<"20*i1*i2="<<multiply<int,20>(i1,i2)<<endl;//120
    cout<<"10*d1*d2="<<multiply(d1,d2)<<endl;//30
    cout<<"20*d1*d2="<<multiply<double,20>(d1,d2)<<endl;//60
    cout<<"multiply<int>(d1,d2)="multiply<int>(d1,d2)<<endl;//10*1*2=20
}
```

#### 模板特化

```cpp
template <>//template后直接跟<>,里面不写类型
返回类型 函数名<特化类型>(特化类型 参数1,特化类型 参数2,...);
```

在使用模板特化时，必须要先有基础的函数模板

特化函数的函数名、参数列表、返回值要和原基础的模板函数相同

```cpp
template <>
const char *add<const char *>(const char *pstr1,const char *pstr2){
    char *p1=(char *)malloc(strlen(pstr1)+strlen(pstr2)+1);
    strcpy(p1,pstr1);
    strcat(p1,pstr2);
    return p1;
}

void test(){
    const char *p1="hello";
    const char *p2="world";
    const char *p3=add(p1,p2);
}
```

#### 普通类内部的模板函数

和正常的函数模板一样即可

#### 可变模板参数

```cpp
template <class/template... T>
void func(T ...args);
```

T被称为模板参数包，表示模板可以接收任意多个参数作为模板参数，编译器将多个模板参数打包成"单个"的模板参数包

函数形参列表的args被称为函数参数包，表示函数可以接收多个任意类型的参数，函数参数包必须唯一，且为函数的最后一个参数

当声明一个变量(或标识符)为可变参数时，省略号位于变量的左侧

当使用参数包解包时，省略号位于变量的右侧

```cpp
//递归调用的出口，这样就不会出现展开到为空的情况
template <class T>
void printElements(T t){
    cout<<t<<endl;
}

//递归打印参数
template <class T,class ...Args>
void printElements(T t,Args... args){
    cout<<t<<endl;
    //...在参数包右侧代表拆包、解包、参数展开
    printElements(args...);//递归展开
}

void test(){
    printElements(true,'a',1,3.14,"hello");
}
```



### 类模板

如果类的一些数据成员的数据类型不能确定，就必须将此类声明为模板

```cpp
template <class/typename T,...>
class 类名{
    //...
};
```

借助类模板实现一个比较通用的单例模式

```cpp
template <class T>
class Singleton{
public:
    template<class ...Args>
    static T*getInstance(Args ...);
    static void destory();
private:
    Singleton(){};
    ~Singleton(){};
    static T *_pInstance;
};
template <class T>
T *Singleton<T>_::pInstance=nullptr;

template <class T>
template <class ...Args>
T *Singleton<T>::getInstance(Args ...args){
    if(_pInstance==nullptr){
        _pInstance=new T(args...);
    }
    return _pInstance;
}

template <class T>
void Singleton<T>::destory(){
    if(_pInstance){
        delete _pInstance;
    }
}

void test(){
    Point* pt1=Singleton<Point>::getInstance(1,2);
    pt1->display();
    Point* pt2=Singleton<Point>::getInstance();
    pt2->display();
    Computer* com1=Singleton<Computer>::getInstance(1000,"xiaomi");
    com1->display();
    Computer* com2=Singleton<Computer>::getInstance(2000,"lenovo");
    com2->display();
    
    Singleton<Point>::destory();
    Singleton<Computer>::destory();
}
```

# day24

## STL

主要包含容器、迭代器、适配器、算法、函数对象(仿函数)、空间配置器六部分

容器包括序列式容器和关联式容器，关联式容器又分为红黑树实现的关联式容器和hash实现的无序关联式容器

迭代器主要作用是对容器中的元素进行访问，是一种广义的指针

适配器主要分为容器适配器和迭代器适配器，是一种接口

算法主要就是通过迭代器对容器中的元素进行操作如排序、查找、修改等

函数对象(仿函数)主要是针对容器中的元素要做定制化操作时，需要借助函数对象来完成，函数对象包括函数名、函数指针、重载了函数调用运算符的类创建的对象，通过`std::function`和`std::bind`作为基于对象的思想的精华，可以取代虚函数

空间配置器的作用是分配内存，底层实现是两层配置器，一级配置器负责分配大于128B的空间，二级配置器借助内存池分配小于128B的空间

### 容器

#### 序列式容器

`array` 静态数组，大小固定

`vector`动态数组，支持随机访问

`deque`双向队列，支持随机访问

`forward_list`单链表

`list`双向链表

```cpp
template <class T>
void display(const T &c){
    //const_iterator实际上是一个嵌套类，只是编译器不清楚这是一个类型还是一个公有的数据成员，因此需要typename指定告诉编译器这是一个嵌套类类型
    typename T::const_iterator cit=c.begin();//class和typename效果一样
    for(;cit!=c.end();++c){
        cout<<*cit<<endl;
    }
}

//vector
void test1(){
    //1、序列式容器的构造
    //points.reserve(5);//初始化容器容量为5，可以减少扩容次数
    vector<Point> points(3,Point(1,2));//初始化传递3个(1,2),但是只有第一个是默认构造，其他两个都是拷贝构造
    //Point ps[3]={Point(1,2),Point(3,4),Point(5,6)};
    //vector<Point> points(ps,ps+3);//迭代器范围构造
    //vector<Point> points{Point(1,2),Point(3,4),Point(5,6)};、
    
    //2、序列式容器的访问
    //2.1 访问头尾的元素
    cout<<points.front()<<points.back()<<endl;
    //2.2 vector支持下标访问
    cout<<points[2]<<endl;
    //2.3 vector支持随机访问迭代器
    vector<Point>::iterator it=points.begin();
    it+=2;//
    cout<<*it<<endl;
    
    //3、添加和删除元素
    //3.1 vector不支持在头部添加和删除元素，因为这样就要移动之后的所有元素，开销太大
    //points.push_front(Point(1,2));//error
    points.push_back(Point(3,4));//可以使用移动语义
    //points.emplace_back(3,4);//原地构造，不触发构造函数，不过要注意避免扩容导致的迭代器失效
    //3.2 可以在任意位置插入元素
    points.insert(points.begin(),Point(3,4));//在首元素之前插入
    it=points.end();
    --it;--it;
    points.insert(it,Point(5,6));//在倒数第三个的位置插入
    Point ps2[3]={Point(1,2),Point(3,4),Point(5,6)};
    points.insert(points.begin(),ps2,ps2+3);//迭代器范围插入
    //3.3 删除指定的元素 在vector中，remove只是移动了元素，erase才释放了空间
    points.erase(points.remove(points.begin(),points.end(),Point(3,4)),points.end());//remove将值为Point(3,4)的移动到容器的最后，返回指向这些被移动的元素的第一个元素，erase则从该元素一直删除到尾部
    //3.4 清空容器的元素
    points.clear();//清空元素，这里只是size变为0，capacity仍然不变
    points.shrink_to_fit();//回收未使用的空间。capacity变为0
    //vector<Point>.swap(points);//借助swap也可以释放
    cout<<points.size()<<points.capacity()<<endl;//只有vector有capacity方法
}

//deque
void test2(){
    //1、序列式容器的构造
    deque<Point> points={Point(1,2),Point(3,4),Point(5,6)};
    
    //2、序列式容器元素的访问
    //2.1 访问头尾的元素
    cout<<points.front()<<points.back()<<endl;
    //2.2 deque支持下标访问
    cout<<points[1]<<endl;
    //2.3 deque支持随机访问迭代器
    deque<Point>::iterator it=points.begin();
    it+=2;
    cout<<*it<<endl;
    
    //3、序列式容器添加和删除元素
    //3.1 deque支持在头部和尾部插入删除数据
    points.push_front(Point(3,4));
    points.pop_front();
    points.push_back(Point(1,2));
    points.pop_back();
    //3.2 deque支持在任意位置插入元素
    points.insert(points.begin(),Point(3,4));//在首元素之前插入
    it=points.end();
    --it;--it;
    points.insert(it,Point(5,6));//在倒数第二个之前的位置插入
    Point ps2[3]={Point(1,2),Point(3,4),Point(5,6)};
    points.insert(points.begin(),ps2,ps2+3);//迭代器范围插入
    //3.3 删除元素,deque没有remove
    points.erase(points.begin(),points.begin()+1);
    //3.4 清空元素
    points.clear();
    //points.erase(points.begin(),points.end());
    cout<<points.size();//deque没有capacity方法
}

//list
void test3(){
    //1、序列式容器的构造
    list<Point> points={Point(1,2),Point(3,4),Point(5,6)};
    
    //2、序列式容器元素的访问
    //2.1 访问头尾的元素
    cout<<points.front()<<points.back()<<endl;
    //2.2 list不支持下标访问
    //cout<<points[2]<<endl;//error
    //2.3 list只支持双向访问迭代器(只能++、--，不能+=、-=)
    it++;it--;//ok
    //it+=2;it-=2;//error
    
    //3、序列式容器添加和删除元素的操作
    //3.1 list支持在头部和尾部插入删除数据
    points.push_front(Point(3,4));
    points.pop_front();
    points.push_back(Point(1,2));
    points.pop_back();
    //3.2 list支持在任意位置插入元素
    points.insert(points.begin(),Point(3,4));//在首元素之前插入
    it=points.end();
    --it;--it;
    points.insert(it,Point(5,6));//在倒数第三个的位置插入
    Point ps2[3]={Point(1,2),Point(3,4),Point(5,6)};
    points.insert(points.begin(),ps2,ps2+3);//迭代器范围插入
    //3.3 删除元素 
    points.erase(it,points.end());//在list中，erase用于处理迭代器的场合,返回值为指向下一个元素的迭代器
    
    list<int>numbers{1,6,9,8,3,3};
    list.remove(3);//在list中，remove用于处理值的场合，返回值为空
    /*
    []捕获作用域中的变量，[&]引用捕获，[=]值捕获，[=,&foo]foo引用捕获，其他值捕获，[foo]值捕获foo，其他不捕获，捕获到的变量也可以在函数体内使用
    ()形参列表，主要是声明出来给函数体用
    {}函数体
    lambda表达式===>匿名函数(右值) 多用于异步编程，其实是一个函数对象，内部创建了一个重载()运算符的类
    */
    numbers.remove_if([](int x){return x>8;});
    
    //3.4 清空元素
    points.clear();
    //points.erase(points.begin(),points.end());
    cout<<points.size();//deque没有capacity方法
    
    //4、对元素进行排序(list特有)
    list<int> numbers{1,3,7,5,2,4,9,11};
    //4.1 默认情况下，采用升序方式排列
    //比较时默认会采用opertor< 来比较
    numbers.sort();
    //针对与内置类型的数据是无法进行运算符重载的，如果想按降序，可以使用std::greater
    std::greater<int> gt;//定制化一个函数对象，重载了operator>
    //cout<<gt(1,2)<<endl;//1大于2吗，false返回0
    numbers.sort(gt);//降序方式排列，如果需要升序可以用std::less
    numbers.unique();//去除相邻的重复元素
}
//4.2 自定义类型的排序
//定制化的比较方式有以下三种
//1、直接重载运算符<或> (使用std::less 和 std::greater也算)
//2、定义一个函数对象重载operator()
//3、定义一个普通函数(lambda表达式)

//Point重载一个list::set默认使用的<以及std::greater使用的>
bool operator<(const Point &lhs,const Point &rhs){
    return lhs.getDistance()<rhs.getDinstance();
}
bool operator>(const Point &lhs,const Point &rhs){
    return lhs.getDistance()>rhs.getDinstance();
}

//函数对象
struct PointComparator{
    bool operator()(const Point &lhs,const Point &rhs){
        return lhs.getDistance()<rhs.getDinstance();
    }
};
struct PointGreaterComparator{
    bool operator()(const Point &lhs,const Point &rhs){
    	return lhs.getDistance()>rhs.getDinstance();
	}
};

//普通函数
bool MyCompare(const Point &lhs,const Point &rhs){
    return lhs.getDistance()>rhs.getDinstance();
}

void test4(){
    list<Point> points{Point(1,2),Point(2,3),Point(3,4),Point(2,3)};
    //4.2.1、重载Point的<运算符的形式
    //points.sort();
    //4.2.2、定义函数对象的形式
    points.sort<PointComparator>(PointComparator());
    //points.sort(PointComparator());//隐式传递
    //4.2.3、普通函数的形式
    points.sort(MyCompare);
    //4.2.4、当std::greater作用于相应类型时，该类型必须重载>运算符，否则会编译出错
    points.sort(std::greater<Point>());//Point类必须重载>运算符
    
    //5、list的merge合并和reverse逆置操作
    list<int> number1{1,2,3,5,4};
    list<int> number2{6,8,7,0,9};
    number1.sort();number2.sort();
    number1.merge(number2);//必须先排序，再合并
    number1.reverse();//对list中的元素进行逆置
}

void test5(){
    //6、list的splice黏贴操作(黏贴的位置，从哪里黏贴，黏贴的范围)
    list<int> number1{1,2,3,5,4};
    list<int> number2{6,8,7,0,9};
    auto it=number1.begin();
    number1.splice(it,number2);//全部黏贴过来
    //splice可以移动其他list的某个元素过来
    it=number2.begin();
    it2=number.begin();
    ++it2;
    number2.splice(it,number1,it2);//把number1的it2指向的元素移动到number2的it的位置
    //splice还可以对list本身操作
    number2.splice(number2.begin(),number2,--number2.end());//把number2的末尾元素移到开头
    //splice可以一次一动若干元素，[)左闭右开
    it2=number.begin();
    it3=it2;
    ++it3,++it3,++it3;
    number2.splice(number2.end(),number1,it2,it3);//把number1的it2到it3的元素移到number2的起始位置
}
```

#### 底层实现

##### vector

`start`、`finish`、`end_of_storage`三个指针维护一段连续的空间，每次扩容都会重新开辟一段新空间，将原数据拷贝到新空间，因此每次扩容都会导致迭代器失效

##### deque

分片的连续空间，片内时连续的，片与片之间不一定连续，各片段的起始地址存放在中控器内，整体用`_start`和`_finish`两个指针维护，每个片段内部使用`_first`和`_last`维护，判断是否走到片段头尾

##### list

底层实现就是一个首尾相接的循环双向链表

`list`的迭代器`List_iterator`内部的运算符重载相较前两个少了很多(因为不能随机访问迭代)

#### 选取技巧

1、需要频繁的在容器中间位置增删数据：list O(1)

2、需要频繁的在容器头部位置增删数据：list/deque，因为vector不支持头部插入删除

3、需要频繁的在容器尾部位置增删数据：vector/deque/list，追求极致可以用vector，因为实现最简单

4、需要频繁的在容器的头部和尾部增删数据：deque/list，但是deque的实现开销比list要更大

5、需要频繁的随机访问：vector/deque，追求极致可以用vector，因为实现最简单，list不支持随机访问迭代器

##### 逻辑结构和物理结构

vector：逻辑结构和物理结构一致，连续空间的数组

deque：逻辑结构：连续的空间，双端开口；物理结构：由多个片段组成，片段内部连续但片段间不连续，由中控器进行操作，连结所有片段

list：逻辑结构：双向链表；物理结构：循环双向链表

# day25

## STL

### 关联式容器

关联式容器将关键字`keyword`和值`value`组成键值对存放在容器中，关键字作为索引的依据，而值用于和关键字配对

标准的STL提供了`set`、`map`、`multiset`和`multimap`四种类模板，其中

`set`只存储了关键字，没有值的概念

`map`中存放的是键值对

以上两种都不允许存在相同的关键字(自定义类型需要提供比较方法(重载运算符、函数对象、普通函数(lambda表达式))来确定是否相同)

`multiset`和`multimap`除了允许存在相同的关键字以外，其他都和`set`和`map`相同

底层实现为红黑树，查找元素使用的是二分查找，时间复杂度为`O(logN)`

容器支持双向访问迭代器，不能随机访问

#### set

```cpp
template<
	class Key,
	class Compare=std::less<Key>,//默认升序
	class Allocator=std::allocator<Key>
>
class set;
```

```cpp
void test1(){
    //1、set内部不能存放关键字相同的元素
    //2、默认情况下按升序排序(std::less)
    set<int> numbers{1,2,5,4,3,7,6};
    set<int,std::greater<int>> numbers{1,2,5,4,3,7,6};//按降序
    //3、对于自定义类型，必须确保放入set的时候该类型的对象可以比较(重载了运算符/函数对象)
    //4、在set中如何判断两个对象等价
    //!(rhs<lhs)&&!(rhs>lhs)	为真表明等价
    set<Point>points{Point(1,2),Point(3,4),Point(1,2),Point(3,2),Point(-3,2),Point(-3,-2)};//重复的会自动去除
    //set<Point,std::greater<Point>()>points;//标准库函数
    //set<Point,PointComparator>points;//函数对象
    
    //5、set不支持下标访问运算符，迭代器种类是双向访问迭代器(和list一样)
    //points[1];//error
    
    //6、可以通过迭代器访问元素，但是不能修改元素，因为set的底层实现是红黑树，一旦插入就是只读的了(因为修改元素会导致不再有序)
    //*it=Point(1,2);//error
    
    //7、添加/删除元素
    //insert的返回值是一个pair，第一个参数是迭代器，第二个是bool表示是否成功
    //std::pair<set<Point,PointComparator>::iterator,bool>
    auto ret=points3.insert(Point(10,11));
    if(ret.second){
        cout<<*ret.first<<endl;
    }
    points.erase(ret.first);
    
    //8、查找单个元素
    //count不会返回指向查找的元素的迭代器
    //find会返回指向查找元素的迭代器
    //使用count进行查找的时候如果查找方法是自定义的，需要为const版本
    size_t cnt=points.count(Point(1,2));//返回数量
    auto it2=points.find(Point(1,2));
    if(it2!=points.end()){
        cout<<*it2<<endl;
    }
    
    //9、范围查找
    auto ret2=points.equal_range(Point(1,2));//equal_range返回的是一个pair，包含迭代器范围的上下界，如果没找到满足条件的则返回的是最接近的位置，此时两个迭代器相等
    auto beg=ret2.first;
    auto end=ret2.second;
    for(;beg!=end;++beg){
        cout<<*beg<<endl;
    }
    //给定排好序的元素队列，查找某个定值
    //lower_bound从给定的下界到给定的上界二分查找第一个大于或等于value的数，返回指向其的迭代器，不存在则返回上界
    //upper_bound查找第一个小于或等于value的数，不存在返回上界
    //两者皆可重载，lower_bound(begin,end,value,greater<type>());
    auto lowerIt=points.lower_bound(Point(3,4));
    auto upperIt=points.lower_bound(Point(5,6));
    for(;lowerIt!=upperIt;++lowerIt){
        cout<<*lowerIt<<endl;
    }
    
}
```

#### multiset

除了insert操作允许插入重复值因此不需要判断是否成功外，其他和set一致

#### map

```cpp
void test1(){
    //1、map内部不能存放关键字相同的元素
    //默认情况下按升序方式排列
    map<string,string,std::greater<string>> cities{
        std::pair<string,string>("0755","深圳"),
        std::pair<string,string>("010","北京"),
        std::pair<string,string>("010","南京"),
        std::pair<string,string>("021","上海"),
        std::pair<string,string>("022","天津"),
        std::pair<string,string>("023","重庆"),
        std::pair<string,string>("028","成都"),
        std::pair<string,string>("027","武汉"),
        std::pair<string,string>("0571","杭州"),
        std::pair<string,string>("0371","随州"),
        std::pair<string,string>("020","广州")
    };
    
    //2、map支持下标访问运算符，下标是keyword,返回值是value的引用，时间复杂度为O(logN)
    //2.1 可以访问value
    cout<<cities["0755"]<<endl;
    //2.2 可以修改value的值,不能修改keyword，因为红黑树的搭建是按照keyword排序的，如果进行了修改会导致不满足有序
    cities["0755"]="郑州";
    //2.3 当查询的keyword不存在时，会直接在map中添加新纪录，value为其类型的默认值
    cities["024"]="沈阳";
    
    //3、查找单个元素
    auto it=cities.find("027");
    if(it!=cities.end()){
        cout<<it->first<<it->second<<endl;
    }else{
        cout<<"查找失败"<<endl;
    }
}
```

#### multimap

允许出现重复的键`keyword`，其他操作和map相同

# day26

## STL

### 无序关联式容器

和关联式容器采用红黑树作为存储结构不同，无序关联式容器是无序的，采用的是hash存储(桶+单链表)，主要包括`unordered_set`和`unordered_map`

查找元素的时间复杂度最好为O(1)，最坏为O(n)，空间复杂度为O(N)

针对自定义类类型，必须要给出对应的Hash函数(自定义函数对象或扩展std::hash的模板特化版本，并且要把函数调用运算符设计为const版本)，必须要重载对应类型的operator==运算符

支持前向访问迭代器，即只能`++it`

#### unordered_set

```cpp
template <class T>
void display(T c){
    for(auto &n:c){
        cout<<n<<endl;
    }
}

void test1(){
    //1、unordered_set内部不能存放关键字相同的元素，如果初始化的时候有重复的，只会存放第一次出现的关键字
    //2、内部元素是无序的
    unordered_set<int> numbers{1,5,2,3,4,7,6,1};
    
    //3、只支持前向访问迭代器，不支持下标访问运算符，不支持随机访问
    //numbers[0];//error
    unordered_set<int>::iterator it=numbers.begin();
    ++it;++it;
    //--it;//error	it+=3;//error
    cout<<*it<<endl;//通过迭代器访问元素
    
    //4、不能通过迭代器修改元素
    //底层实现是HashTable+链表，一旦存入，就变成只读的
    //*it=3;//error
    
    //5、添加/删除元素
    //std::pair<std::unordered_set<int>::iterator,bool>
    auto ret=numbers.insert(10);
    if(ret.second){
        cout<<*ret.first<<endl;
    }else{
        cout<<"insert failed"<<endl;
    }
    numbers.erase(ret.first);
    
    //6、查找单个元素
    //count不会返回指向对应元素的迭代器
    //find会返回指向对应元素的迭代器
    //使用const进行查找时如果是自定义的查找方法，需要是const的
    auto ret2=numbers.count(1);
    auto ret3=numbers.find(2);
    if(ret3!=numbers.end()){
        cout<<*ret3<<endl;
    }
}

bool operator==(const Point &lhs,const Point &rhs){//Point内部设为友元函数
    return (lhs._ix==rhs._ix&&lhs._iy==rhs._iy);
}
//自定义函数对象负责hash函数
struct PointHasher{
    size_t operator()(const Point &pt)const{
        return ((pt._ix*pt._ix+1)>>1)^((pt._iy*pt._iy+1)>>1);
    }
};
//针对Point类给出std::hash的模板特化版本
namespace std{
template<>
struct hash<Point>{
    size_t operator()(const Point &pt)const{
        return ((pt._ix*pt._ix+1)>>1)^((pt._iy*pt._iy+1)>>1);
    }
};
}

void test2(){
    //7、针对自定义类型而言，当对象放入unordered_set中时必须要指定对于自定义类型的hash函数，并且要重载对应类型的operator==函数
    unordered_set<Point,PointHasher>points{Point(1,2),Point(3,4),Point(1,2),Point(3,2),Point(-3,2),Point(-3,-2)};
    //unordered_set<Point,std::hash<Point>> points;
}
```

#### unordered_map

```cpp
bool operator==(const Point &lhs,const Point &rhs){//Point内部设为友元函数
    return (lhs._ix==rhs._ix&&lhs._iy==rhs._iy);
}
//自定义函数对象负责hash函数
struct PointHasher{
    size_t operator()(const Point &pt)const{
        return ((pt._ix*pt._ix+1)>>1)^((pt._iy*pt._iy+1)>>1);
    }
};
//针对Point类给出std::hash的模板特化版本
namespace std{
template<>
struct hash<Point>{
    size_t operator()(const Point &pt)const{
        return ((pt._ix*pt._ix+1)>>1)^((pt._iy*pt._iy+1)>>1);
    }
};
}

void test1(){
    //1、unordered_map内部不能存放关键字相同的元素
    //牺牲空间换取时间的数据结构
    //加载因子 通常为0.5
    unordered_map<Point,string,PointHasher> cities{
        make_pair(Point(1,2),"深圳"),
        make_pair(Point(10,1),"北京"),
        make_pair(Point(-1,1),"南京"),
        make_pair(Point(111,1),"上海"),
        make_pair(Point(111,1),"天津"),
        make_pair(Point(112,1),"重庆")
    };
    
    //2、unordered_map支持下标访问运算符，下标的内容是keyword,返回的是value
    //插入的时间复杂度为O(logN)
    //查找的时间复杂度为O(1)
    //2.1 可以访问value
    cout<<cities[Point(1,2)]<<endl;
    //2.2 unordered_map可以修改value的值
    cities[Point(1,2)]="郑州";
    //2.3 如果keyword不存在，会在unordered_map中直接添加新记录，value为对应类型的默认值
    cout<<cities[Point(10,10)]<<endl;
    
    //3、查找单个元素
    size_t cnt=cities.count(Point(1,2));
    auto it=cities.find(Point(1,2));
    if(it!=cities.end()){
        cout<<it->first<<it->second<<endl;
    }
}
```



### 迭代器

作用：对容器中的元素进行访问

是一种广义的指针

迭代器本身的抽象级别要高于容器

迭代器设计模式的作用：将容器的底层实现隐藏起来

#### 随机访问迭代器 RandomAccessIterator

```cpp
+ += - -= * -> ++ -- < > <= >= == != =
```

#### 双向访问迭代器 BidirectionalIterator

```cpp
++ -- * -> == != =
```

#### 前向访问迭代器 ForwardIterator

```cpp
++ * -> == != =
```

#### 输入流迭代器 InputIterator

```cpp
++ * -> == !=
```

可读，不需要关注写操作

#### 输出流迭代器 OutputIterator

```cpp
++ * =
```

```cpp
void test(){
    //可以把输出流看作一种容器，使用流迭代器操作
    //把vector中的元素拷贝到输出流中
    vector<int> numbers{1,2,3,4,5};
    
    //输出流迭代器适配器
    ostream_iterator<int> osi(cout," ");//ostream:cout												dividestring:" "
    copy(numbers.begin(),numbers.end(),osi);//赋值运算符内部会ostream<<num<<dividestring
}
```

### 适配器

#### 容器适配器

##### stack	

基础容器需要包含以下成员函数：

```cpp
empty();
size();
back();
push_back();
pop_back();
```

满足条件的基础容器有`vector`、`deque`、`list`，默认使用的基础容器为`deque`

##### queue	

基础容器需要包含以下成员函数：

```cpp
empty();
size();
front();
back();
push_front();
pop_front();
```

满足条件的基础容器有`deque`、`list`，默认使用的基础容器为`deque`

###### priority_queue	

基础容器需要包含以下成员函数：

```cpp
empty();
size();
front();
push_back();
pop_back();
```

满足条件的基础容器有`vector`、`deque`，默认使用的基础容器为`vector`

先进的不一定先出，而是按照优先级高低依次出队

```cpp
void test1(){
    //1、优先级队列默认情况下采用<比较(return lhs<rhs)
    //元素出队时采用降序方式排列，值越大的优先级越高
    
    //2、优先级队列的底层实现：堆结构存储数据(vector能以O(1)的时间复杂度访问到每个元素)
    //排序时采用堆排序算法(大顶堆)
    //特点：a、父结点的值要大于左右孩子结点
    //     b、堆顶元素的值是最大的
    
    //3、每次比较时都是拿堆顶的元素和新来的元素比较
    //返回值为true，则新元素到堆顶，原堆顶元素到堆底，调整堆
    //返回值为false，堆顶元素不变，新元素到堆底，调整堆
    vector<int> numbers{1,3,2,4,6,5};
    priority_queue<int> que;
    for(auto &number:numbers){
        que.push(number);
    }
    while(!que.empty()){
        cout<<que.top()<<endl;
        que.pop();
    }
    //存储的数据类型、使用的基础容器、使用的比较方法
    //建堆的时候默认使用大根堆，使用std::greater会变成小根堆
    //使用>进行比较，值越大的优先级越低(return lhs>rhs)
    priority_queue<int,vector<int>,std::greater<int>> que2(numbers.begin(),numbers.end());
    while(!que2.empty()){
        cout<<que2.top()<<endl;
        que2.pop();
    }
}
```



#### 迭代器适配器

##### 反向迭代器(适配器)

`reverse_iterator`

内部重新定义了`++`和`--`运算符，实现对容器的逆序遍历

```cpp
void test(){
    vector<int>numbers{1,3,2,4,5};
    //vector<int>::reverse_iterator rit;
    for(auto rit=numbers.rbegin(),rit!=numbers.rend();++rit){
        cout<<*rit<<endl;
    }
}
```



##### 插入迭代器(适配器)

拷贝操作转化为在容器的特定位置作插入操作，不能用于元素个数固定的容器(如array)

`std::insert_iterator`、`std::back_insert_iterator`、`std::front_insert_iterator`

为了使用方便，提供了`std::inserter()`、`std::back_inserter()`、`std::front_inserter()`三个函数，参数为某种具体的容器，返回值分别为三种插入迭代器

```cpp
void test(){
    vector<int> numbers{1,2,3,4,5};
    list<int> numbers2{11,12,13};
    copy(numbers.begin(),numbers.end(),std::back_insert_iterator<int>(numebrs2));//使用插入迭代器适配器std::back_insert_iterator
        copy(numbers.begin(),numbers.end(),std::back_inserter(numbers2));//使用插入迭代器std::back_insert_iterator调用容器的push_back,back_inserter是一个函数，返回值类型为back_insert_iterator，参数为一个具体的容器
        copy(numbers.begin(),numbers.end(),std::front_inserter<list<int>>(numbers2));//使用插入迭代器std::front_insert_iterator调用容器的push_front
        copy(numbers.begin(),numbers.end(),std::inserter<list<int>>(numbers2,++numbers2.begin()));//使用插入迭代器std::insert_iterator调用容器的insert
}
```



##### 流迭代器(适配器)

输入流迭代器`istream_iterator`用于从文件或者键盘读取数据

输出流迭代器`ostream_iterator`用于将数据输出到文件或者屏幕上

输入流缓冲区迭代器`istreambuf_iterator`用于从输入缓冲区中逐个读取数据

输出流缓冲区迭代器`ostreambuf_iterator`用于将数据逐个写入输出流缓冲区

```cpp
void test(){
    istream_iterator<int> isi(cin);//接收int类型的
    vector<int> numbers;
    copy(isi,istream_iterator<int>(),std::back_inserter(numbers));
    copy(numbers.begin(),numbers.end(),ostream_iterator<int>(cout," "));
}
```



##### 移动迭代器(适配器)

`move_iterator`可以将某个范围的类对象移动到目标范围，而不需要通过拷贝去移动

#### 函数适配器

##### std::bind

```cpp
int add(int x,int y){
    return x+y;
}

int add2(int x,int y,int z){
    return x+y+z;
}

void test0(){
    //bind是函数模板，返回值是一个函数对象
    
    //使用bind提前绑定两个参数的值，可以适配函数类型
    auto f=std::bind(add,1,2);
    cout<<f()<<endl;
    
    //占位符placeholder
    //只需要绑定第一个参数，第二个参数不提前绑定
    auto f1=std::bind(add,1,_1);//_1表示调用的时候的第一个参数填在这个位置
    cout<<f1(2)<<endl;//add(1,2);
    
    //在使用bind时，除了函数名，后面的参数的位置要与函数相应的形参一一对应
    //当某些参数不需要提前绑定时，必须要使用占位符
    //占位符本身所在的位置是函数形参的位置(被调用函数的形参列表的相应位置)，占位符的数字代表的是要绑定的实参的位置(调用函数时的实参列表的第几个参数)
    auto f2=std::bind(add2,1,_1,3);
    cout<<f2(10);//add2(1,10,3);
    /*
    f2=std::bind(add2,1,_2,3);
    cout<<f2(10,110);//add2(1,110,3);//第一个实参无效
    f2=std::bind(add2,1,_1,3);
    cout<<f2(10,110);//add2(1,10,3);//第二个参数无效
    */
    int n=10;
    auto f3=std::bind(add2,n,_1,10);
    cout<<f3(5,101)<<endl;//add2(10,5,10);
    n=100;
    cout<<f3(5,101)<<endl;//add2(100,5,10);
}

//结合std::function 注册回调函数
typedef int(*Function)(int,int);
//using Function=int(int,int);
typedef void*(*routine)(int,int);

int add(int x,int y){
    cout<<"int add(int,int)"<<endl;
    return x+y;
}

struct Foo{
    int add(int x,int y){
        cout<<"int Foo::add(int,int)"<<endl;
        return x+y;
    }
};

void test1(){
    //c语言的用法
    //函数类型，用一个返回值为int，两个参数都是int的函数
    //注册回调函数Callback Function
    Function f=add;
    routine f2;
    f(1,2);
}

void test2(){
    //c++的用法
    //函数容器
    //注册回调函数Callback Function
    //函数容器std::function可以放入函数指针、普通函数、成员函数
    std::function<int(int,int)>f=add;
    cout<<f(1,2)<<endl;
    using namespace std::placeholders;
    //bind绑定成员函数时需要在前面加上取地址符号
    //bind绑定实参时采用的是值传递
    //对于成员函数的第一个参数(非static情况下为this指针)，可以传递对象，也可以传递地址
    Foo foo;
    f=std::bind(&Foo::add,foo,_1,10);//Foo()临时对象也可以
    cout<<f(1,2)<<endl;//foo.add(1,10);
    f=std::bind(&Foo::add,&foo,_2,10);
    cout<<f(1,2)<<endl;//foo.add(2,10);
}

//取代虚函数
class Figure{
	using DisplayCallback=std::function<void()>;
    using AreaCallback=std::function<double()>;
public:
    Figure(DisplayCallback &&cb1,AreaCallback &&cb2):_displayCb(std::move(cb1)),_areaCb(std::move(cb2)){}
    
    void setDisplayCallback(DisplayCallback &&cb){
        _displayCb=std::move(cb);
    }
    
    void setAreaCallback(AreaCallback &&cb){
        _areaCb=std::move(cb);
    }
    
    void handleDisplayCallback(){
        if(_displayCb){
            displayCb();
        }
    }
    
    double handleAreaCallback(){
        if(_areaCb){
            return _areaCb();
        }
        return 0;
    }
    
private:
    DisplayCallback _displayCb;
    AreaCallback _areaCb;
};

//具体的图形类不需要继承Figure了
class Circle
{
public:
	Circle(double radius)
	: _radius(radius)
	{}

	void display() const
	{	cout << "circle";	}

	double area()
	{
		return 3.14159 * _radius * _radius;
	}

	~Circle() {	cout << "~Circle()" << endl;	}

private:
	double _radius;
};

class Rectangle
{
public:
	Rectangle(double length, double width)
	: _length(length)
	, _width(width)
	{}

	~Rectangle() { cout << "~Rectangle()" << endl; }

	void show() const
	{	cout << "rectangle";	}

	double calcArea()
	{	return _length * _width;	}

private:
	double _length;
	double _width;
};

void display(Figure *fig){
    fig->handleDisplayCallback();
    cout<<"的面积为："<<fig->handleAreaCallback()<<endl;
}

void test(){
    unique_ptr<Circle> circle(new Circle(4));
    unique_ptr<Rectangle> rectangle(new Rectangle(2,4));
    unique_ptr<Figure> fig(new Figure(std::bind(&Circle::display,*circle),std::bind(&Circle::area,*circle)));
    display(fig.get());
    fig->setDisplayCallback(std::bind(&Rectangle::show,*rectangle));
    fig->setAreaCallback(std::bind(&Rectangle::calcArea,*rectangle));
    display(fig.get());
}
```

##### std::mem_fn

```cpp
class Number{
public:
    explicit
    Number(size_t data):_data(data){}
    
    void display()const{
        cout<<_data<<endl;
    }
    //是否为偶数
    bool isEven() const{
        return (_data%2==0);
    }
private:
    size_t _data;
};
//当容器中存放的元素是自定义类类型对象，需要对每个元素调用相应的成员函数时，可以用函数适配器mem_fn来解决
void test(){
    vector<Number> numbers{1,2,3,4,5,6};
    for_each(numbers.begin(),numbers.end(),std::mem_fn(&Number::display));
    
    numbers.erase(remove_if(numbers.begin(),numbers.end(),std::mem_fn(&Number::isEven)),numbers.end());
}
```

# day27

## STL算法Algorithm/numeric

非修改式序列操作：不改变容器的内容，多为查找

修改式序列操作：修改容器中的内容，多为增删操作

排序和相关操作：各种排序函数

通用数字运算(numeric头文件中)：多为集合操作

内存分配相关

### for_each



```cpp
//for_each

//只要求函数的参数是一元的，不考虑函数的返回值，因为调用的时候是f(*it),不考虑返回值
bool display(int &num){
    ++num;
    cout<<num<<endl;
    return true;
}
void test1(){
    vector<int> numbers{1,2,4,3,6,5};
    for_each(numbers.begin(),numbers.end(),display);
    //使用lambda表达式
    for_each(numebrs.begin(),numbers.end(),[](int num){cout<<num<<endl;});
    copy(numbers.begin(),numbers.end(),std::ostream_iterator<int>(cout," "));
}
```

### remove

```cpp
void test1(){
    vector<int> numbers{1,3,6,7,9,33,2,5,33,8,10};
    //remove并没有把元素真正删除释放，而是用后面的元素逐个向前覆盖，再把该元素放在最后
    //返回前向访问迭代器，指向被删除的元素
    auto f=remove(numbers.begin(),numbers.end(),33);
    numbers.erase(f,numbers.end());
    //numbers.erase(remove(numbers.begin(),numbers.end(),33));//常连用
}
```



### 迭代器失效

由于插入元素，使得容器元素整体“迁移”导致存放原容器元素的空间不再有效，从而使得指向原空间的迭代器失效。

由于删除元素使得某些元素次序发生变化使得原本指向某元素的迭代器不再指向希望指向的元素。

#### vector

`push_back`操作后，如果发生了扩容，所有迭代器失效；否则只有`end()`返回的迭代器失效

`pop_back`操作后，只有`end()`返回的迭代器失效

`insert`操作后，如果发生了扩容，所有迭代器失效；否则插入点及以后的元素的迭代器失效

`erase`操作后，删除点及以后的元素的迭代器失效

#### deque

`push_back/front`由于deque要求中控器首尾时刻都各留一个位置，因此在插入时如果导致位置不够，会需要重新开辟一段空间存放map，需要把旧中控器map拷贝到新空间，由于deque的迭代器需要有一个指针指向所在段在map的node结点，因此如果进行了拷贝，所有的迭代器都会失效；同时由于只是中控器拷贝，实际各元素所在的空间没有变化，因此指针和引用不会失效

而`pop_back/front`只是简单的析构元素，即使特殊情况(当前段内正好只有一个元素)，也只需要释放该缓冲区，其他元素的迭代器没有变化

`insert`和`erase`除了在头尾操作时和上面的情况相同，其他位置都会导致内存重新分配，因此所有迭代器、指针、引用都会失效

#### list

由于是链表结构，元素间物理位置没有关系，因此只有被修改的元素的迭代器会失效，其他元素的迭代器均正常

#### set/map

由于红黑树中存放的是元素的指针，因此仅仅是红黑树顺序的变化不会影响元素实际位置的改变，只有被修改的元素的迭代器会失效，其他迭代器均正常

#### 不同容器的循环erase手法

```cpp
针对vector和deque的循环erase操作
for(it=v.begin();it!=v.end();){
	if(true){
        it=erase(it);
    }else{
        ++it;
    }
}

针对list、set、map的循环erase操作
for(it=v.begin();it!=v.end();){
	if(true){
        erase(it++);//erase(it++)的执行顺序：it自增，返回的是自增前的it指向的元素->被erase删除，it已经指向下一个元素了
    }else{
        ++it;
    }
}
```

# day28

## STL 空间配置器

作用：分配和释放内存

### 底层实现

池的技术

要解决的问题

```
1、多线程
2、内存不足的措施
3、内存碎片的问题
	外部碎片(还没有被分配出去，但是容量太小无法分配给进程的内存空闲区域)：针对堆空间，希望消除外部碎片的影响，节省内存
	内部碎片(已经被分配出去属于某个进程，但是没有被利用的内存空间)：无法优化
```

操作系统对内存的管理：页式管理(每页大小4kb)、段式管理(针对程序，分为许多段如读写段、只读段等)、段页式管理

### std::allocator

#### 特点

针对于容器来说，空间的分配和对象的创建是分开在不同的函数进行的，与new表达式不同

分配内存：`allocate(size)`

对象的创建：`construct(iterator,object)`

#### 实现方式

两级配置器

##### 一级配置器

当申请的空间大于128B时，直接调用malloc/free分配堆空间

##### 二级配置器

当申请的空间小于等于128B时，采用16个自由空闲链表+内存池进行管理

16个自由空闲链表由指针数组进行管理；内存池采用`start_free`和`end_free`两个指针管理

#### 源码

接口层std::allocator	可以感知类型

```cpp
allocate(size)//申请空间，size为元素个数，可以自动感知元素类型
deallocate(begin_iterator,size)//回收空间
construct(iterator,object)//在对应位置创建对象
destory(iterator)	//回收对象
```

实现层alloc

一级配置器：

```
如果定义了__USE_MALLOC宏，则其实是malloc_alloc_template类，成员函数全部为静态成员函数，提供一个内存不足的时候使用的 _S_oom_malloc()函数，本质上就是一级配置器，对malloc/free进行了一层封装，同时提供了内存不足的应对措施
```

二级配置器(默认)：

所有的容器最终都会调用它完成空间的分配和释放

```
如果没有定义__ USE_MALLOC宏，则是 __default_alloc_template类， 这个是二级配置器,  _S_free_list[NFREELISTS]就是空闲链表，是一个存放了16个union _Obj的指针的指针数组， _S_start_free和 _S_end_free就是内存池，由 _S_heap_size 可知二级配置器管理的空间全部都是来自于堆空间(malloc分配的)，对外提供allocate、deallocate和reallocate三个静态成员函数接口

由于数据成员全部是静态存在全局静态区的，即这个类的所有操作是唯一的，所有不同模板的该类的对象共享这些静态数据成员即可以看作是一个具体类而不是一个模板类，模板参数和alloc类无关，allocate的形参也就是单纯的字节的大小，只是对malloc进行了一层封装
```



### 优点

#### 空间换时间

只有第一次申请空间时，会调用malloc一次性申请远大于申请空间的空间，并将其进行处理，之后申请小内存时会用O(1)的时间复杂度分配内存(链表)

释放内存时只有申请的空间大小大于128B才会调用`free()`，否则会采用头插法挂靠到二级配置器的自由空闲链表上，重复使用

#### 减少系统调用malloc/free的频率

系统调用的开销要比普通函数大得多

#### 适合容器使用

容器往往操纵的是批量的数据，所以一次malloc申请多个元素大小的空间很契合

### 借助std::allocator实现一个vector的空间管理

注意到尾指针指向的是最后一个元素的下一个，因此添加新元素的时候用的是`_finish++`，删除尾元素用的是`--_finish`

```cpp
template <clasS T>
class Vector{
public:
    using value_type=T;
    using iterator=value_type*;
    using const iterator=const value_type*;
    
    Vector():_start(nullptr),_finish(nullptr),_end_of_storage(nullptr){}
    
    ~Vector(){
        while(_finish!=_start){
            _alloc.destory(--_finish);//回收对象，对象位置
        }
        if(_start){
            _alloc.deallocate(_start,capacity());//回收空间，起始位置，数量
        }
    }
    
    size_t size() const{
        return _finish-_start;
    }
    
    size_t capacity() const{
        return _end_of_storage-_start;
    }
    
    iterator begin(){
        return _start;
    }
    //如果vector对象本身具有const属性，必须返回const类型的迭代器
    const iterator begin()const{
        return _start;
    }
    
    iterator end(){
        return _finish;
    }
    
    const iterator end()const{
        return _finish;
    }
    
    void push_back(const T &t);
    void pop_back();
    
private:
    static allocator<T> _alloc;
    T *_start;
    T *_finish;
    T *_end_of_storage;
    //扩容操作
    void reallocate();
};

template<class T>
allocator<T> Vector<T>::_alloc;

template <class T>
void Vector<T>::push_back(const T &t){
    if(size()==capacity()){//需要扩容
        reallocate();
    }
    if(_finish){
        _alloc.construct(_finish++,t);//第一个参数指定存放位置，第二个参数执行拷贝构造函数在指定的位置构造对象
    }
}

template <class T>
void Vector<T>::pop_back(){
    if(size()){
        _alloc.destory(--_finish);//空间还可以继续使用，只需要销毁元素对象
    }
}

template <class T>
void Vector<T>::reallocate(){
    size_t capacity=capacity();
    //初始情况为0
    size_t newCapacity=(capacity>0)?capacity*2:1;
    
    //执行扩容操作
    //malloc(newCapacity*sizeof(T));//虽然可行，但是不够合理，应当交给_alloc进行
    //申请的是未类型化的空间，即只申请了空间没有创建对象
    T *ptmp=_alloc.allocate(newCapacity);//不用sizeof，std::allocator可以感知类型
    //复制原空间的元素到新开辟的空间
    //copy的前提条件是对象存在，而此时ptmp指向的空间上没有对象
    //copy(_start,_finish,ptmp);
    //使用algorithm函数库的uninitialized_copy，该函数内部会调用定位new表达式构造对象
    if(_start){
        std::uninitialized_copy(_start,_finish,ptmp);
        //回收原空间
        while(_finish!=_start){
            _alloc.destory(--_finish);//回收对象
        }
        _alloc.deallocate(_start,capacity);
    }
    //改变指向
    _start=ptmp;
    _finish=ptmp+capacity;
    _end_of_storage=ptmp+newCapacity;
}
```

## BO(基于对象)的生产者消费者问题

<img src="D:\TyporaPic\cppDay29\image-20200523093823097.png" alt="image-20200523093823097" style="zoom:400%;" />

不同于面向对象的继承和多态，基于对象采用`std::function`和`std::bind`，只需要提供相应的回调函数，即可满足不同对象执行不同的行为

```cpp
class Noncopyable{
protected://抽象类，构造函数和析构函数均为protected类型，Noncopyable本身不能创建对象，但是派生类可以
    Noncopyable(){}
    ~Noncopyable(){}
    //禁止复制控制操作
    Noncopyable(const Noncopyable &)=delete;
    Noncopyable &operator=(const Noncopyable &)=delete;
};

class Thread{
public:
    using ThreadCallback=std::function<void()>;//在使用bind传递的时候就绑定好参数，确保是无参的
    Thread(ThreadCallback &&cb):_pthid(0),_isRunning(false),_cb(std::move(cb)){}
    
    //不需要设为虚函数了
    ~Thread(){
        if(_isRunning){
            pthread_detach(_pthid);
        }
    }
    
    void run(){
        if(!_isRunning){
            pthread_create(&_pthid,nullptr,threadFunc,this);
        	_isRunning=true;
        }
    }
    
    void join(){
        if(_isRunning){
            pthread_join(_pthid,nullptr);
            _isRunning=false;
        }
    }

private:
    pthread_t _pthid;
    bool _isRunning;
    ThreadCallback _cb;
    
    static void *threadFunc(void *arg){
        Thread *thread=(Thread *)arg;
        if(thread){
            thread->_cb();
        }
    }
};

struct MyTask{
    void process(){
        while(1){
            cout<<"doTask()"<<endl;
        }
    }
};

void test(){
    unique_ptr<Thread> thread(new Thread(std::bind(&MyTask::process,MyTask())));//bind可以提前绑定好参数，确保传递过去以后参数是无参的符合function<void()>
    thread->run();
    thread->join();
}

class MutexLock:Noncopyable{};//表达对象语义，互斥锁不可复制
class Condition:Noncopyable{};//表达对象语义，条件变量不可复制
//bind进行的是值传递，会执行复制操作，所以如果绑定的对象含有上述对象语义的数据成员，就需要用std::ref引用包装器进行引用
```

## OO(面向对象)的线程池的搭建

![image-20200523103452958](D:\TyporaPic\复习笔记\image-20200523103452958.png)

`WorkerThread`中重写的`run()`方法会调用`Threadpool`类的`threadFunc()`方法，而`threadFunc()`主要的工作就是从`TaskQueue`中取任务并执行任务`pTask->process()`，任务都是调用`addTask()`方法将派生类`MyTask`对象加入到任务队列中的



```cpp
class Thread{
public:
    Thread():_pthid(0),_isRunning(false){}
    
    void start(){
        pthread_create(&_pthid,nullptr,threadFunc,this);
        _isRunning=true;
    }
    
    void join(){
        if(_isRunning){
            pthread_join(_pthid,nullptr);
            _isRunning=false;
        }
    }
    
    ~Thread(){
        if(_isRunning){
            pthread_detach(_pthid);
        }
    }
    
private:
    pthread_t _pthid;
    bool _isRunning;
    static void *threadFunc(void *arg){
        Thread *pthread=(Thread *)arg;
        if(pthread){
            pthread->run();
        }
    }
    virtual void run()=0;
};

class WorkerThread:public Thread{
public:
    WorkerThread(Threadpool &pool):_pool(pool){}
private:
    void run(){
        _pool.threadFunc();
    }
    Threadpool &_pool;
};

class TaskQueue{
    using ElemType=Task *;
public:
    TaskQueue(size_t size=10):_mutex(),_cond(_mutex),_queSize(size),_flag(true){}
    
    bool empty(){
        return _que.empty();
    }
    
    bool full(){
        return _que.size()==_queSize;
    }
    
    void push(ElemType data){
        MutexLockGuard guard(&_mutex);
        while(full()){
            _cond.wait();
        }
        _que.push(data);
        _cond.notify();
    }
    
    ElemType pop(){
        MutexLockGuard guard(&_mutex);
        while(_flag && empty()){//_flag通常不发挥作用，只有在结束线程池的时候用于改变可能存在的子线程的阻塞的情况，true表示正常取任务，false表示线程池关闭，任务队列也不需要存在了
            _cond.wait();
        }
        if(_flag){
            ElemType res=_que.top();
            _que.pop();
            _cond.notify();
            return res;
        }
        return nullptr;
    }
    
    void wakeup(){
        if(_flag){
            _flag=false;
        }
        _cond.notifyAll();
    }
    
private:
    MutexLock _mutex;
    Condition _cond;
    queue<ElemType> _que;
    size_t _queSize;
    bool flag;//引入flag主要是用于防止线程池的子线程无法退出，阻塞在了threadFunc的getTask调用的pop方法，在threadpool的stop方法会调用wakeup停止所有子线程阻塞在pop方法的while循环里
};

class Task{
public:
    virtual void process()=0;
};

class ThreadPool{
    friend class WorkerThread;
public:
    ThreadPool(size_t threadNum,size_t queSize):_threadNum(threadNum),_queSize(queSize),_taskQueue(_queSize),_isExit(false){
        _threads.reserve(_threadNum);
    }
    
    void start(){
        for(size_t i=0;i!=_threadNum;++i){
            unique_ptr<Thread> thread(new WorkerThread(*this));
            _threads.push_back(std::move(thread));
        }
        for(auto &c:_threads){
            c->start();
        }
    }
    
    void stop(){
        if(!_isExit){
            while(!_taskQueue.empty()){//等待任务全部完成
                
            }
            _isExit=true;//标识位置位
            _taskQueue.wakeup();//唤醒可能阻塞在getTask的子线程
            for(auto &c:_threads){
                c->join();//子线程结束
            }
        }
    }
    
    void addTask(Task *ptask){
		_taskQueue.push(ptask);//不需要在这里先判断是否已满，因为这个操作交给任务队列完成了
    }

    ~ThreadPool(){
        if(!_isExit){
            stop();
        }
    }
    
private:
    size_t _threadNum;
    size_t _queSize;
    TaskQue _taskQueue;
    vector<unique_ptr<Thread>> _threads;
    bool _isExit;
    
    Task *getTask(){
        return _taskQueue.pop();//不需要对返回值作判断，因为这个函数的任务只是取一个任务，如果为空任务队列会阻塞在while循环里的
    }
    
    void threadFunc(){
        while(!_isExit){
            Thread *p=getTask();
            if(p){
                p->process();
            }
        }
    }
};

class MyTask:public Task{
public:
    void process(){
        ::srand(time(nullptr));
        cout<<pthread_self()<<" :"<<rand()%100<<endl;
    }
};

void test(){
    unique_ptr<Task> task(new MyTask());
    ThreadPool threadpool(4,10);
    threadpool.start();
    int cnt=20;
    while(cnt--){
        threadpool.addTask(task.get());
    }
    threadpool.stop();
}
```

# day30

## BO线程池

![image-20200523131630662](D:\TyporaPic\复习笔记\image-20200523131630662.png)

`ThreadPool`的`start()`将执行回调函数的方法作为回调函数注册给了每个`Thread`对象，`Thread`对象的`threadFunc()`执行的函数对象就是`ThreadPool`的`threadFunc()`，即从任务队列取数据然后执行

threadpool将任务放入队列->子线程的threadFunc方法执行从threadpool注册的回调函数，从任务队列取任务执行

```cpp
class Thread{
    using threadCallback=std::function<void()>;
public:
    Thread(threadCallback &&cb):_pthid(0),_isRunning(false),_cb(std::move(cb)){}
    
    void start(){//开启线程
        pthread_create(&_pthid,nullptr,threadFunc,this);
        _isRunning=true;
    }
    
    void join(){//回收线程
        if(_isRunning){
            pthread_join(_pthid,nullptr);
            _isRunning=false;
        }
    }
    
    ~Thread(){
        if(_isRunning){
            pthread_detach(_pthid);
        }
    }
    
private:
    threadCallback _cb;
    pthread_t _pthid;
    bool _isRunning;
    
    static void *threadFunc(void *arg){
        Thread *pthread=(Thread *)arg;
        if(pthread){
            pthread._cb();
        }
    }
};

class ThreadPool{
    using Task=std::function<void()>;
public:
    ThreadPool(size_t threadNum,size_t queSize):_threadNum(threadNum),_queSize(queSize),_isExit(false),_taskQue(_queSize){_threads.reserve(_threadNum);}
    
    void start(){
        for(size_t idx=0;idx!=_threadNum;++idx){
            unique_ptr<Thread> thread(new Thread(std::bind(&ThreadPool::threadFunc,this)));
            _threads.push_back(std::move(thread));
        }
        for(auto &c:_threads){
            c->start();
        }
    }
    
    void stop(){
        if(!_isExit){
            while(!_taskQue.empty()){
				sleep(1);
            }
            _isExit=true;
            _taskQue.wakeup();
            for(auto &thread:_threads){
                thread->join();
            }
        }
    }
    
    void addTask(Task &&task){
        _taskQue.push(task);
    }

    ~ThreadPool(){
        if(!_isExit){
            stop();
        }
    }
    
private:
    size_t _threadNum;
    size_t _queSize;
    bool _isExit;
    vector<unique_ptr<Thread>> _threads;
    TaskQueue _taskQue;
        
    Task getTask(){
        return _taskQue.pop();
    }
    
    void threadFunc(){
        while(!_isExit){
            Task task=getTask();
            if(task){
                task();
            }
        }
    }
};

struct myTask{
    void process(){
        ::srand(::time(NULL));
    	cout<<::rand()%100<<endl;
    }
};

void test(){
    ThreadPool threadpool(4,10);
    threadpool.start();
    int cnt=20;
    while(cnt--){
        threadpool.addTask(std::bind(&myTask::process,myTask()));
    }
    threadpool.stop();
}
```

# 网络编程概览

## 计算机网络

可以类比现实生活中的物流体系

### 7层OSI模型(理论)

记忆口诀：物链网输会示用

`应用层`：HTTP/HTTPS、FTP、SMTP/POP3、DNS

`表示层`：数据的加密/解密

`会话层`：Session

`传输层`：报文(Segment)	TCP/UDP	端口号：定位到一个计算机上的唯一进程

`网络层`：分组(Packet)、IP数据报	路由器

`数据链路层`：帧(Frame)

`物理层`:比特流(bit)

传输层以上属于端到端的通信，属于资源子网

网络层以下属于点到点的通信，属于通信子网

### 4/5层TCP/IP(工业)

应用层、传输层、网络层、网际接口层(数据链路层+物理层)

### 协议

协议即一种规则，用于规定数据的传输格式，包含公有协议(TCP、UDP等)和私有协议(自己规定数据顺序标识位等)

### 为什么要分层

模块化：实现和服务进行分离

## TCP

面向连接：client和server各自有状态表示自己所处的状况，根据状态表明当前所处的情境以及各自要进行的操作

### 状态迁移图

![image-20200523205544915](D:\TyporaPic\复习笔记\image-20200523205544915.png)



```
1) LISTEN:首先服务端需要打开一个socket进行监听，状态为LISTEN.

2) SYN_SENT:客户端通过应用程序调用connect进行active open.于是客户端tcp发送一个SYN以请求建立一个连接.之后状态置为SYN_SENT.

3) SYN_RECV:服务端应发出ACK确认客户端的SYN,同时自己向客户端发送一个SYN. 之后状态置为SYN_RECV

4) ESTABLISHED: 代表一个打开的连接，双方可以进行或已经在数据交互了。

5) FIN_WAIT1:主动关闭(active close)端应用程序调用close，于是其TCP发出FIN请求主动关闭连接，之后进入FIN_WAIT1状态.（等待对本端连接的中断请求的确认）

6) CLOSE_WAIT:被动关闭(passive close)端TCP接到FIN后，就发出ACK以回应FIN请求(它的接收也作为文件结束符传递给上层应用程序),并进入CLOSE_WAIT.（等待从本地用户发来的连接中断请求）

7) FIN_WAIT2:主动关闭端接到ACK后，就进入了FIN_WAIT2（等待从远程TCP对连接的中断请求）

8) LAST_ACK:被动关闭端一段时间后，接收到文件结束符的应用程序将调用CLOSE关闭连接。这导致它的TCP也发送一个 FIN,等待对方的ACK.就进入了LAST_ACK .

9) TIME_WAIT:在主动关闭端接收到FIN后，TCP就发送ACK包，并进入TIME_WAIT状态。

10)CLOSING: 比较少见,等待远程TCP对连接中断的确认

11)CLOSED: 被动关闭端在接受到ACK包后，就进入了closed的状态。
连接结束.
```

#### 初始状态

11、CLOSED

#### 三次握手

服务器端：1、LISTEN	3、SYN_RECEIVED	4、ESTABLISHED

客户端：2、SYN_SENT	4、ESTABLISHED

类比打电话	"你能听到我说话吗"、"能听到，你能听到我说话吗"、"能听到"

##### 1、建立连接为什么要使用三次握手，两次握手可以吗？

如果是两次握手，服务器端就不会等待收到客户端的第三次握手确认再进入ESTABLISHED状态而导致资源浪费了

可能第二次握手(服务器->客户端)在发送后丢失了，此时客户端在等服务器的回复，而服务器在等客户端传输数据，会造成资源的浪费

也有可能客户端的第一次握手请求延迟了，超时重传完成传输之后才到达服务器，此时会被认为是一次新的建立连接的请求，结果就同上丢失的情况了

#### 四次挥手

客户端主动关闭

客户端：5、FIN_WAIT1	7、FIN_WAIT2	9、TIME_WAIT	11、CLOSED	10、CLOSING同时关闭时出现

服务器端：6、CLOSE_WAIT	8、LAST_ACK	11、CLOSED

##### 2、断开连接时，为什么需要四次挥手？

TCP是一个全双工的连接，客户端和服务器端都各自有发送缓冲区和接收缓冲区

关闭客户端写端->关闭服务器读端->关闭服务器写端->关闭服务器读端

以上关闭端都是针对数据报文，控制报文不包含其中(如第四次客户端向服务器端挥手或超时重传)

##### 3、一般情况下，谁应该主动断开连接？

通常是客户端主动断开连接，因为主动断开连接的一方会进入`time_wait`状态，如果服务器主动断开连接进入`time_wait`状态，会导致一段时间内无法进行其他事务的处理，严重浪费服务器资源

##### 4、time_wait状态为什么需要2MSL(1-4分钟)的超时时间？

确保第四次挥手的ACK能到达服务器端(确保第四次挥手的ACK在最极限的位置丢失，服务器的第三次挥手也能重传给客户端)

如果没有该状态，可能会造成数据窜链(如第一次连接时服务器发送数据由于网络延迟等没有全部发送给客户端，第二次连接时第一次的数据才传到客户端，如果两次连接的五元组(源/目的ip、端口号、协议类型)相同，则会视为一次连接，设立为2MSL可以确保上一次连接的数据都已经尘埃落定了)

### 首部信息



![image-20200523211241467](D:\TyporaPic\复习笔记\image-20200523211241467.png)

源端口号	目的端口号

序号：分片操作	确定数据的位置

确认号：标识位ACK为1时有效	告诉对方已经收到的序号	确认重传

数据偏移：代表首部长度	4个位bit，最大值为15(最后要乘一个基数4才是最终值)	TCP首部最大长度为60字节

窗口：告诉对方自己的接收缓冲区还能存放多少数据

校验和：对数据进行校验

紧急指针

### Linux之下进行TCP套接字编程的步骤

#### 套接字

对应物流体系的门牌号

#### 服务器端

socket	bind	listen	accept	read/recv	write/send

#### 客户端

socket	connect	write/send	read/recv

### 网络IO模型

阻塞式IO

非阻塞式IO

IO复用模型	select、poll、epoll	单线程处理多个请求

信号驱动式

异步IO	DMA

### 错误说法：阻塞就是同步，非阻塞就是异步

在处理IO的时候，阻塞和非阻塞都是同步IO，只有使用特殊API才是异步IO

IO的同步异步指的是内核态与用户态的交互关系

![image-20200803122911110](D:\TyporaPic\复习笔记\image-20200803122911110.png)

#### 同步和异步

同步和异步关注的是消息通信机制

同步指发出一个调用后直到得到结果了这个调用才会返回，需要主动读写数据

异步只需要关注操作完成的通知，并不主动读写数据，被调用者通过其他的比如状态、通知、回调函数告知调用者，由操作系统内核完成数据的读写

同步就是必须由本线程亲自主动接收调用的返回结果，而异步则是由其他线程通过某种方式被动告知调用的结果

#### 阻塞和非阻塞

阻塞与非阻塞这一对词关注的是用户态进程/线程(程序)的状态、其要访问的数据是否就绪，进程/线程是否需要等待

阻塞是指在调用结果返回前，当前线程会被挂起直到结果返回

非阻塞是指调用结果返回前，当前线程不会被挂起等待

```
老张爱喝茶，废话不说，煮开水。出场人物：老张，水壶两把（普通水壶，简称水壶；会响的水壶，简称响水壶）。
1 老张把水壶放到火上，立等水开。（同步阻塞）老张觉得自己有点傻
2 老张把水壶放到火上，去客厅看电视，时不时去厨房看看水开没有。（同步非阻塞）
老张还是觉得自己有点傻，于是变高端了，买了把会响笛的那种水壶。水开之后，能大声发出嘀~~~~的噪音。
3 老张把响水壶放到火上，立等水开。（异步阻塞）老张觉得这样傻等意义不大
4 老张把响水壶放到火上，去客厅看电视，水壶响之前不再去看它了，响了再去拿壶。（异步非阻塞）

老张觉得自己聪明了。所谓同步异步，只是对于水壶而言。普通水壶，同步；响水壶，异步。虽然都能干活，但响水壶可以在自己完工之后，提示老张水开了。这是普通水壶所不能及的。同步只能让调用者去轮询自己（情况2中），造成老张效率的低下。所谓阻塞非阻塞，仅仅对于老张而言。立等的老张，阻塞；看电视的老张，非阻塞。情况1和情况3中老张就是阻塞的，媳妇喊他都不知道。虽然3中响水壶是异步的，可对于立等的老张没有太大的意义。所以一般异步是配合非阻塞使用的，这样才能发挥异步的效用。

同步就是烧开水，要自己来看开没开；
异步就是水开了，然后水壶响了通知你水开了。
阻塞是烧开水的过程中，你不能干其他事情（即你被阻塞住了）；
非阻塞是烧开水的过程里可以干其他事情。

同步与异步说的是你获得水开了这个调用结果的方式不同，
阻塞与非阻塞说的是你得到结果之前能不能干其他事情。
```

### 如何处理一个请求

#### decode

解码	对协议进行解析	拿到真正有用的数据

#### compute

对数据进行处理

业务逻辑的编写

#### encode

对返回数据进行编码

### 创建线程数量的问题

#### 1、一个32位的系统最多可以创建多少个线程？

32位系统的能够寻址的虚拟空间为4G，其中3G-4G的空间是内核占用，剩下的0-3G才是用户态程序能操作的

如果1个栈空间的大小8M，则最多可以创建3*1024/8=384个线程

#### 2、一般情况下，一个进程要创建多少个线程？

取决于任务类型

核心思想为：线程等待时间所占比例越高，需要越多线程；线程CPU时间所占比例越高，需要越少线程

但是线程切换是存在上下文开销的，因此理论计算后还需要经过进一步的调优分析

##### CPU密集型程序

一个完整请求，I/O操作可以在很短时间内完成， CPU还有很多运算要处理，也就是说 CPU 计算的比例占很大一部分

`线程数`=`CPU核数+1`

计算密（CPU）集型的线程恰好在某时因为发生一个页错误或者因其他原因而暂停，刚好有一个“额外”的线程，可以确保在这种情况下CPU周期不会中断工作。

##### IO密集型程序

与 CPU 密集型程序相对，一个完整请求，CPU运算操作完成之后还有很多 I/O 操作要做，也就是说 I/O 操作占比很大部分，CPU大部分时间处于空闲状态，因此要最大化利用CPU，不让其处于空闲，即增加线程让CPU处于忙碌状态

<img src="D:\TyporaPic\复习笔记\image-20200803125108773.png" alt="image-20200803125108773" style="zoom: 25%;" />



`线程数`=`CPU核数*(1/CPU利用率)`=`CPU核数*(1+(IO耗时/CPU耗时))`

### 常见并发服务器模型

Reactor+threadpool 模型

#### Reactor

IO线程：处理数据的接收和发送

问题：不适合处理长链接的请求

#### threadpool

计算线程：处理业务逻辑

#### 线程间通信

eventfd	timefd定时器

### 网络编程中需要注意的三个半事件

1、新连接到来时

2、消息到达时

3、连接断开时

4、消息发送完成时

## UDP

一般会在应用层做数据可靠传输(数据校验)

# day32

## 常见服务器编程模型

![image-20200524164652075](D:\TyporaPic\复习笔记\image-20200524164652075.png)

### 反应器(reactive)服务器(reactor模式)

并发处理多个请求，实际上是在一个线程中完成，无法充分利用多核cpu

不适合执行时间比较长的服务，所以为了让客户感觉是在"并发"而不是"循环"处理，每个请求都必须在相对较短的时间内执行

由于本质也是轮询，因此如果其中一个请求卡壳了(一直在处理该请求)，其他连接请求就会一直处于等待

### reactor+threadpool(能适应密集计算)

主线程只负责请求的收发，具体的处理交由线程池的计算线程完成

### reactors+threadpool(最灵活高效的方式)

main reactor处理新连接的建立，sub reactor负责网络数据的收发，threadpool负责任务的处理，main reactor一般设置为一个线程，sub reactor一般设置和cpu核数相等的线程数

## select、poll、epoll对比

select是轮询的询问所有监听的描述符是否有请求

epoll是基于事件(event)的轮询，只有有请求的才会被监听

<img src="D:\TyporaPic\cppDay32\image-20200524201128707.png" alt="image-20200524201128707" style="zoom: 200%;" />

![image-20200524201153435](D:\TyporaPic\复习笔记\image-20200524201153435.png)



## tcp网络库的封装

<img src="D:\TyporaPic\复习笔记cpp\image-20200524213003938.png" alt="image-20200524213003938" style="zoom:200%;" />

使用Acceptor类的对象负责监听socket连接，其accept函数的返回值即为新连接的文件描述符，EventLoop的handleNewConnection函数会依照此描述符创建TcpConnection类对象，负责新连接的通信以及网络通信的事件处理(连接建立、收到数据、连接关闭)

![sequenceDiagram序列图](D:\TyporaPic\复习笔记cpp\image-20200525155157464.png)

### InetAddress网络地址类

![image-20200524103251902](D:\TyporaPic\复习笔记cpp\image-20200524103251902.png)

提供多个版本的构造函数

能得到ip地址和端口号

bind在绑定ip地址时要有一个sockaddr *类型的指针，所以要有一个get方法

```cpp
class InetAddress{
public:
    InetAddress(const string &ip,unsigned short port){
        ::bzero(&_addr,sizoef(_addr));
        _addr.sin_family=AF_INET;
        _addr.sin_port=htons(port);
        _addr.sin_addr.s_addr=inet_addr(ip.c_str());
    }
    
    explicit	//不希望通过short型数据直接获得InetAddress对象
    InetAddress(unsigned short port){
        ::bzero(&_addr,sizoef(_addr));
        _addr.sin_family=AF_INET;
        _addr.sin_port=htons(port);
        _addr.sin_addr.s_addr=INADDR_ANY;//inet_addr("0.0.0.0") 代表本机地址(一个服务器可能有多个网卡)
    }
    
    InetAddress(const struct sockaddr_in &addr)_addr(addr){}
    
    string ip() const {
        return string(::inet_ntoa(_addr.sin_addr));
    }
    
    unsigned short port() const{
        return ntohs(_addr.sin_port);
    }
    
    struct sockaddr *getInetAddressPtr(){
        return &_addr;
    }
    
private:
    struct sockaddr_in _addr;
};
```

### Socket套接字类

![image-20200524103829269](D:\TyporaPic\复习笔记cpp\image-20200524103829269.png)

套接字会用在很多地方(收发数据，连接的建立与关闭等)，我们需要一个专门的类处理套接字的创建和销毁

在析构函数中会调用close方法销毁，由于套接字相当于文件，属于资源的一种，因此需要及时进行资源回收

还需要一个提供服务器端主动关闭写端的方法

最主要的还是获取文件描述符

```cpp
class Socket{
public:
    Socket(){
        _fd=socket(AF_INET,SOCK_STREAM,nullptr);
        if(_fd==-1){
            perror("socket error");
        }
    }
    
    explicit
    Socket(int fd)_fd(fd){}
    
    void shutdownWrite(){
        ::shutdown(_fd,SHUT_WR);
    }
    
    int fd() const{
        return _fd;
    }
    
    ~Socket(){
        close(_fd);
    }
private:
    int _fd;
};
```

### Acceptor接收连接类

![image-20200524104306795](D:\TyporaPic\复习笔记cpp\image-20200524104306795.png)

数据成员包含创建的套接字类对象，服务器对外暴露的用于接收通信的网络地址类对象

构造函数需要包含ip地址和端口号用于构造_addr对象和 _listenSock对象

必不可少的操作包括bind和listen

如果需要服务器程序能够立刻重启则要提供setReuseAddr，如果需要一台物理主机同时启动多次服务器程序则要提供setReusePort

以上的bind、listen、setReuseAddr和setReusePort都是准备工作，因此可以用一个ready方法调用这些成员函数

建立新连接的accept函数会返回一个文件描述符

```cpp
class Acceptor{
public:
    explicit
    Acceptor(unsigned short port)_addr(port),_listenSock(){}
    
    Acceptor(const string &ip,unsigned short port)_addr(ip,port),_listenSock(){}
    
    void ready(){
        setReuseAddr(true);
        setReusePort(true);
        bind();
        listen();
    }
    
    int accept(){
        int peerfd=accept(_listenSock.fd(),nullptr,nullptr);
        return peerfd;
    }
    
    int fd()const{
        return _listenSock.fd();
    }
    
private:
    Socket _listenSock;
    InetAddress _addr;
    
private:
    void setReuseAddr(bool on){
        int one=on;
        setsockopt(_listenSock.fd(),SOL_SOCKET,SO_REUSEADDR,&one,sizeof(int));
    }
    
    void setReusePort(bool on){
        int one=on;
        setsockopt(_listenSock.fd(),SOL_SOCKET,SO_REUSEPORT,&one,sizeof(int));
    }
    
    void bind(){
        bind(_listenSock.fd(),_addr.getInetAddressPtr(),sizeof(struct sockaddr));
    }
    
    void listen(){
        listen(_listenSock.fd(),10);
    }
};
```

### SocketIO数据收发类

![image-20200524121406829](D:\TyporaPic\复习笔记cpp\image-20200524121406829.png)

数据传输要通过文件描述符

read的返回值一共有3种情况，0表示连接要断开，-1表示连接出错，再次读取会core dump，还有一种就是当前次数具体从接收缓冲区复制出来的数据长度

如果一次传输的数据超过一次能接收的上限，就要用readn方法固定每次读取的字符数量，返回值即为成功接收的字符数量

可以读也就意味着要可以写writen

特别的，也可以每次都读取一行数据(\n为结尾)，由于不确定这一行数据有多长，因此要设定一个最大读取字节数maxlen，如果读取的时候大于maxlen则会先截断

针对int型数据，可以提供一个专门的函数readInt32()来读取一个int型和writeInt32()来发送一个int型

```cpp
class SocketIO{
public:
    explicit
    SocketIO(int fd):_fd(fd){}
    
    //循环读取len个字节
    int readn(char *buff,int len){
        char *p=buff;
        int left=len;//剩余未读取的长度，初始为len
        while(left>0){
            int ret=read(_fd,p,left);
            if(ret==-1&&errno=EINTR){//中断
                continue;
            }else if(ret==-1){
                perror("read");
                return len-left;//返回以读取的值
            }else if(ret==0){//即将断开连接
                return len-left;
            }else{
                left-=ret;
                p+=ret;
            }
        }
        return len-left;
    }
    
    int writen(const char *buff,int len){
        int left=len;
        const char *p=buff;
        while(left>0){
            int ret=write(_fd,p,left,0);
            if(ret==-1&&errno==EINTR)
                continue;
            else if(ret==-1){
                perror("write error");
                return len-left;
            }else{//写成功
                left-=ret;
                p+=ret;
            }
        }
        return len-left;
    }
    //每一次读取一行数据
	//read不仅进行了复制，同时还移走了内核缓冲区中的数据
    int readline(char *buff,int maxlen){
        int left=maxlen-1;//防止读取完都没发现\n，留一个空放\0
        int total=0;
        char *p=buff;
        while(left>0){
            int ret=recv_peek(p,left);
            for(int i=0;i!=ret;++i){
                if(p[i]=='\n'){
                    total=i+1;//从0开始算所以要+1表示读取总数
                    readn(p,total);//读一行
                    p+=total;
                    *p='\0';
                    return total;
                }
            }
            //如果没有发现 '\n'，读取一次读取能读取的最大数量后继续循环
            readn(p,ret);
            left-=ret;
            p+=ret;
            total+=ret;
        }
        //读到上限maxlen都没有发现\n
        *p='\0';
        return total;
    }
    
private:
    int _fd;

private:
    int recvPeek(char *buff,int len){
        int ret;
        do{
            ret=recv(_fd,buf,len,MSG_PEEK);
        }while(ret==-1&&errno==EINTR);
    }
};
```



### TcpConnection连接处理类

![image-20200524213105563](D:\TyporaPic\复习笔记cpp\image-20200524213105563.png)

一个连接本质是五元组，包含源ip/port，目的ip/port以及使用的协议，因此数据成员就包含源和目的的两个InetAddress类对象local(本机)和peer(对端)，处理请求都要经过文件描述符，因此必不可少要有一个套接字Socket

对于一个连接，需要提供的服务包括

接收数据receive

发送数据send

这些具体的数据的传输会交给数据成员_sockIO专门进行

针对每个TcpConnection，都要对连接的建立与关闭、数据到达时进行一些处理(回显、日志),为了可扩展性，就不能写死在函数里，而是应当设置好相应的回调函数，因此TcpConnection内也要有三个数据成员作为回调函数，每个连接都要处理这三个事件

UML图省略了三个setCallback的形参

有set自然也会有调用handleCallback

```cpp
class TcpConnection
:Noncopyable
,public std::enable_shared_from_this<TcpConnection>{
    
    using TcpConnectionPtr=std::shared_ptr<TcpConnection>;
    using TcpConnectionCallback=std::function<void(const TcpConnectionPtr&)>;
    
public:
    explicit
    TcpConnection(int fd)_sock(fd),_sockIO(fd),_localAddr(getLocalAddr(fd)),_peerAddr(getPeerAddr(fd)),_isShutdownWrite(false){}
    
    string receive(){
        char buf[65536]={0};
        _sockIO.readline(buf,65536);
        return string(buf);
    }
    
    void send(const string &msg){
        _sockIO.sendn(msg.c_str(),msg.size());
    }
    
    string toString(){
        ostringstream oss;
        oss<<_localAddr.ip()<<":"<<_localAddr.port()<<"->"<<_peerAddr.ip()<<":"<<_peerAddr.port()<<endl;
        return oss.str();
    }
    
    void shutdown(){
        if(_isShutdownWrite){
            _isShutdownWrite=true;
            _sock.shutdownWrite();
        }
    }
    
    ~TcpConnection(){
        if(!_isShutdownWrite){
            shutdown();
        }
    }
    
    //如果这里用移动语义，则只有第一个TcpConnection对象能成功用std_move注册，之后的对象注册的都是空的了，所以要用复制
    void setConnectionCallback(const TcpConnectionCallback &cb){
        _onConnection=cb;
    }
    
    void setMessageCallback(const TcpConnectionCallback &cb){
        _onMessage=cb;
    }
    
    void setCloseCallback(const TcpConnectionCallback &cb){
        _onClose=cb;
    }
    
    void handleConnectionCallback(){
        if(_onConnection){
            _onConnection(shared_from_this());
        }
    }
    
    void handleMessageCallback(){
        if(_onMessage){
            _onMessage(shared_from_this());
        }
    }
    
    void handleCloseCallback(){
        if(_onClose){
            _onClose(shared_from_this());
        }
    }
    
private:
    Socket _sock;
    InetAddress _localAddr;
    SocketIO _sockIO;
    InetAddress _peerAddr;
    bool _isShutdownWrite;
    
    TcpConnectionCallback _onConnection;
    TcpConnectionCallback _onMessage;
    TcpConnectionCallback _onClose;
    
private:
    InetAddress getLocalAddr(int fd){
        struct sockaddr_in addr;
        socklen_t len=sizeof(struct sockaddr);
        getsockname(_sock.fd(),(struct sockaddr *)&addr,&len);
        return InetAddress(addr);
    }
    
    InetAddress getPeerAddr(int fd){
        struct sockaddr_in addr;
        socklen_t len=sizeof(struct sockaddr);
        getspeername(_sock.fd(),(struct sockaddr *)&addr,&len);
        return InetAddress(addr);
    }
};
```



### EventLoop事件循环类

![image-20200524205818444](D:\TyporaPic\复习笔记cpp\image-20200524205818444.png)

保存自己的epollfd，可以用Socket类，也可以直接用int

createEpollFd创建epoll的实例，用map保存创建的实例，key是文件描述符的id，value是TcpConnection的对象托管的智能指针(因为该对象是一个连接，不能进行复制)

为了监听Acceptor的listen文件描述符，需要一个Acceptor的引用

loop函数用来作为主体循环

unloop表示退出循环，通过标识位_isLooping控制，对于循环内部的执行体封装成waitEpollFd() 

针对要处理的连接，分为两种，一种是新的连接

handleNewConnection和旧连接handleMessage

先执行loop开始循环，在其中调用waitEpollFd

监听的集合用容器vector<struct epoll_event>存储，因为如果是和c的方式一样，则只能监听2048个，使用vector的话是可扩展的，如果返回的连接数和当前最大连接数相同，则可以继续扩展

TcpConnection是EventLoop的一部分，TcpConnection对象是在handleNewConnection函数中产生，所以是组合关系，TcpConnection中的回调函数的设置需要EventLoop设置，因此EventLoop也要有三个回调函数

```cpp
class EventLoop{
    
    using TcpConnectionPtr=std::shared_ptr<Tcpconnection>;
    using Callback=std::function<void(const TcpConnectionPtr &)>;
    
public:
    
    EventLoop(Acceptor acceptor):_acceptor(acceptor),_isLooping(false),_efd(createEpollFd()),_evtList(1024){
        addEpollRdFd(_acceptor.fd());
    }
    
    void loop(){
        if(!_isLooping){
            _isLooping=true;
        }
        while(_isLooping){
            waitEpollFd();
        }
    }
    
    void unloop(){
        if(_isLooping){
            _isLooping=false;
        }
    }
    
    void setConnectionCallback(const Callback &cb){
        _onConnection=cb;
    }
    
    void setMessageCallback(const Callback &cb){
        _onMessage=cb;
    }
    
    void setCloseCallback(const Callback &cb){
        _onClose=cb;
    }
    
private:
    int _efd;
    Acceptor &_acceptor;
    bool _isLooping;
    map<int,TcpConnectionPtr> _conns;
    vector<struct epoll_event> _events;
    Callback _onConnection;
    Callback _onMessage;
    Callback _onClose;
    
private:
    int createEpollFd(){
        int fd=epoll_create1(0);
        return fd;
    }
    
    void addEpollRdFd(int fd){//添加监听描述符
        struct epoll_event event;
        event.data.fd=fd;
        event.flag=EPOLLIN;
        epoll_ctl(_efd,EPOLL_ADD,fd,&event);
    }
    
    void delEpollRdFd(int fd){//删除监听描述符
        struct epoll_event event;
        event.data.fd=fd;
        event.flag=EPOLLIN;
        epoll_ctl(_efd,EPOLL_DEL,fd,&event);
    }
    
    void waitEpollFd(){//loop循环执行体
        int nready;
        do{
            nready=epoll_wait(_efd,&_evtList[0],_evtList.size(),5000);
        }while(nready==-1&&errno=EINTR);//如果是中断错误则继续循环
        if(nready==-1){
            perror("epoll_wait");
        }else if(nready==0){
            printf(">>>epoll_wait timeout!\n");
        }else{
            if(nready==_evtList.size()){//如果存储的待处理的连接达到当前上限
                _evtList.resize(nready*2);
            }
            
            for(int i=0;i!=nready;++i){
                int fd=_evtList[i].data.fd;
                if(fd==_acceptor.fd()&&_evtList[i].events&EPOLLIN){//有新连接且为读事件
                    handleNewConnection();
                }else{
                    if(_evtList[i].events&EPOLLIN){
                        handleMessage(fd);
                    }
                }
                
            }
        }
        
    }
    
    void handleNewConnection(){//处理新连接请求
        int peerfd=_acceptor.accept();//接收客户端描述符
        addEpollRdFd(peerfd);//加入监听
        TcpConnectionPtr conn(new TcpConnection(peerfd));
        conn->setConnectionCallback(std::move(_onConnection));
    conn->setMessageCallback(std::move(_onMessage));
    conn->setCloseCallback(std::move(_onClose));
        _conns.insert(std::make_pair(peerfd,conn));
        conn->handleConnectionCallback();
        //这里可以加日志
    }
    
    void handleMessage(int fd){//处理消息到达时的操作
        auto it=_conns.find(fd);
        if(it!=_conns.end()){
            //先判断连接是否还存在
            if(isClosed(fd)){
                it->second->handleCloseCallback();
                delEpollRdFd(fd);
                _conns.erase(it);
            }else{
                it->second->handleMessageCallback();
            }
            
        }
    }
    
    bool isClosed(int fd){//判断当前文件描述符代表的连接是否断开
        int ret;
        char buff[128]={0};
        do{
            ret=::recv(fd,buf,sizeof(buf),MSG_PEEK);
        }while(ret==-1 && errno=EINTR);
        
        return ret==0;//0表示已断开
    }
};
```

### TcpServer外部包装类

![image-20200525133625717](D:\TyporaPic\复习笔记cpp\image-20200525133625717.png)

用Acceptor类创建监听，用EventLoop处理请求

设置三个回调函数用于指定具体的建立连接、发送信息、连接关闭要执行的行为

用start封装Acceptor的ready方法

```cpp
class TcpServer{
    
    using TcpConnectionPtr=std::shared_ptr<TcpConnection>;
    using Callback=std::function<void(const TcpConnectionPtr&)>;
    
public:
    TcpServer(const string &ip,unsigned short port):_acceptor(ip,port),_loop(_acceptor){}
    
    void start(){
        _acceptor.ready();
        _loop.loop();
    }
    
    void setConnectionCallback(Callback &&cb){
        _loop.setConnectionCallback(std::move(cb));
    }
    
    void setMessageCallback(Callback && cb){
        _loop.setMessageCallback(std::move(cb));
    }
	void setCloseCallback(Callback && cb){
        _loop.setCloseCallback(std::move(cb));
    }
    
private:
    Acceptor _acceptor;
    EventLoop _loop;
};
```

### 使用网络库

```c
void onConnection(const TcpConnectionPtr &conn){
    cout<<conn->toString<<" has connected"<<endl;
    conn->send("welcome to server");
}

void onMessage(const TcpConnectionPtr &conn){
    string msg=conn->receive();
    cout<<msg<<endl;
    conn->send(msg);
}

void onClose(const TcpConnectionPtr &conn){
    cout<<conn->toString()<<"has closed"<<endl;
}

void test(){
    TcpServer server("0.0.0.0",5000);
    server.setConnectionCallback(onConnection);
	server.setMessageCallback(onMessage);
	server.setCloseCallback(onClose);
    
    server.start();
}
```

# day33

## Reactor模式



Reactor模式，又叫反应器模式，应用于同步I/O的场景。以读操作为例来看看Reactor中的具体步骤：

读取操作：

```
1、应用程序注册读就绪事件和相关联的事件处理器
2、事件分离器等待事件的发生
3、当发生读就绪事件的时候，事件分离器调用第一步注册的事件处理器
4、事件处理器首先执行实际的读取操作，然后根据读取到的内容进行进一步的处理
```

Reactor模式主要是组合关系

![image-20200525155845689](D:\TyporaPic\复习笔记cpp\image-20200525155845689.png)

## 定时器

### timerfd定时器

![image-20200525181806202](D:\TyporaPic\复习笔记cpp\image-20200525181806202.png)



timerfd是Linux提供的一个定时器接口。这个接口基于文件描述符，通过文件描述符的可读事件进行超时通知，所以能够被用于select/poll/epoll的应用场景。timerfd是linux内核2.6.25版本中加入的接口。

```c
#include <sys/timerfd.h>

int timerfd_create(int clockid, int flags);

int timerfd_settime(int fd, int flags,const struct itimerspec *new_value,struct itimerspec *old_value);
```

#### timerfd_create

功能：该函数生成一个定时器对象，返回与之关联的文件描述符。

参数详解：

clockid:可设置为

```
CLOCK_REALTIME：相对时间，从1970.1.1到目前的时间。更改系统时间 会更改获取的值，它以系统时间为坐标。

CLOCK_MONOTONIC：绝对时间，获取的时间为系统重启到现在的时间，更改系统时间对齐没有影响。
```

flags: 可设置为TFD_NONBLOCK（非阻塞），TFD_CLOEXEC（同O_CLOEXEC）

linux内核2.6.26版本以上都指定为0

#### timerfd_settime

功能：该函数能够启动和停止定时器

参数详解：

fd: timerfd对应的文件描述符

flags: 

```
0表示是相对定时器
TFD_TIMER_ABSTIME表示是绝对定时器
```

new_value:设置超时时间，如果为0则表示停止定时器。

old_value:一般设为NULL, 不为NULL,则返回定时器这次设置之前的超时时间

![image-20200525163828909](D:\TyporaPic\复习笔记cpp\image-20200525163828909.png)

#### 处理方式

read：读取缓冲区中的数据，其占据的存储空间为sizeof(uint64_t)，表示超时次数。

select/poll/epoll：当定时器超时时，会触发定时器相对应的文件描述符上的读操作，IO复用操作会返回，然后再去对该读事件进行处理。

#### Timer定时器类

![image-20200525164420242](D:\TyporaPic\复习笔记cpp\image-20200525164420242.png)

start开始定时器的运行，stop停止定时器



```cpp
class Timer{
    using TimerCallback=std::function<void()>;
    
public:
    
    Timer(TimerCallback &&cb,int initialTime,int periodicTime):_fd(createTimerFd),_cb(std::move(cb)),_initialTime(initialTime),_periodicTime(periodicTime),_isStarted(false){}
    
    void start(){
        if(!_isStarted){
            _isStarted=true;
        }
        setTimerFd(_initialTime,_periodicTime);//设置定时器
        //使用poll监听
        struct pollfd pfd;
        pfd.fd=fd;
        pfd.events=POLLIN;
        while(_isStarted){
            int nready;
            do{
                nready=poll(&pfd,1,5000);
            }while(nready==-1&&errno==EINTR);
            if(nready==-1){
                perror("poll");
            }else if(nready==0){
                cout<<">>>poll timeout\n"<<endl;
            }else{
                if(pfd.revents&POLLIN){
                    //处理定时器,否则poll会一直被触发(水平触发)
                    //水平触发：只要不处理，当poll返回时该文件描述符一直被触发
                    handleRead();
                    if（(_cb){
                        _cb();
                    }
                }
            }
        }
    }
    
    void stop(){
        setTimerFd(0,0);//将超时时间设为0，定时器停止工作
        if(_isStarted){
            _isStarted=false;
            
        }
    }
    
    ~Timer(){
        if(_isStarted){
            stop();
        }
    }
    
private:
    int _fd;//操纵的文件描述符
    int _initialTime;//第一次超时的时间
    int _periodicTime;//周期性超时的时间
    TimerCallback _cb;//设定定时器要进行的行为的回调函数
    bool _isStarted;
    
private:
    int createTimerFd(){
        int fd=timerfd_create(CLOCK_REALTIME,0);
        return fd;
    }
    
    void setTimerFd(int initialTime,int periodicTime){
        struct itimerspec value;
        value.it_value.tv_sec=initialTime;
        value.it_value.tv_nsec=0;
        value.it_interval.tv_sec=periodicTime;
        value.it_interval.tv_nsec=0;
        timerfd_settime(_fd,0,&value,nullptr);
    }
    
    void handleRead(){
        unit64_t howmany;
        //使用read处理读取超时次数，否则会一直触发(水平触发)
        int ret=read(_fd,&howmany,sizeof(howmany));
        if(ret!=sizeof(howmany)){
            perror("read");
        }
    }
    
};
```

#### TimerThread定时器子线程类

![image-20200525181739206](D:\TyporaPic\复习笔记cpp\image-20200525181739206.png)

```cpp
class TimerThread{
    using TimerCallback=std::function<void()>;
    
public:
    
    TimerThread(TimerCallback &&cb,int initicalTime,int periodicTime):_timer(std::move(cb),initicalTime,periodicTime),_thread(std::bind(&Timer::start,&_timer)){}
    
    void start(){
        _thread->start();
    }
    
    void stop(){
        _timer.stop();
        _thread->join();
    }
    
private:
    Timer _timer;
    Thread _thread;
};

void process(){
    ::srand(::time(nullptr));
    int number=::rand()%100;
    cout<<">>>number = "<<number<<endl;
}

void test(){
    TimerThread timer(process,3,6);
    timer.start();
    ::sleep(20);
    timer.stop();
}
```

## eventfd事件通知

相比于timerfd，多了一个write操作，因此定义在一个类可以实现通过读写进行线程间通信

```c
#include <sys/eventfd.h>

int eventfd(unsigned int initval, int flags);
```

initval：初始化计数器值，该值保存在内核。

flags支持以下标志位：

```
EFD_NONBLOCK      类似于使用O_NONBLOCK标志设置文件描述符。

EFD_CLOEXEC  类似open以O_CLOEXEC标志打开，O_CLOEXEC 应该表示执行exec()时，之前通过open()打开的文件描述符会自动关闭.
```

如果是2.6.26或之后版本的内核，flags 必须设置为0。

返回值：函数返回一个文件描述符，与打开的其他文件一样，可以进行读写操作。

### 处理方式

read：如果计数器A的值不为0时，读取成功，获得到该值。如果A的值为0，非阻塞模式时，会直接返回失败，并把error置为EINVAL;如果为阻塞模式，一直会阻塞到A为非0为止。

write：将缓冲区写入的8字节整形值加到内核计数器上，即会增加8字节的整数在计数器A上，如果其值达到0xfffffffffffffffe时，就会阻塞（在阻塞模式下），直到A的值被read。

因此可以用write通知其他线程阻塞read

### EventFd事件通知类

![image-20200525205944404](D:\TyporaPic\复习笔记cpp\image-20200525205944404.png)

start方法开始运行

handleRead在for循环中使用

wakeup唤醒，在其他线程执行该方法，通知开始工作

```cpp
class Eventfd{
    using EventCallback=std::function<void()>;
public:
    
    Eventfd(EventCallback &&cb):_fd(createEventfd()),_cb(std::move(cb)),_isStarted(false){}
    
    void start(){
        if(!_isStarted){
            _isStarted=true;
        }
        struct pollfd pfd;
        pfd.fd=_fd;
        pfd.flag=POLLIN;
        int nready;
        do{
            nready=poll(&pfd,1,5000);
        }while(nready==-1&&errno==EINTR);
        if(nready==-1){
            perror("poll");
        }else if(nready==0){
            cout<<">>>eventfd timeout"<<endl;
        }else{
            if(pfd.revents&POLLIN){
                handleRead();
                if(_cb){
                    _cb();
                }
            }
            
        }
    }
    
    void stop(){
        if(_isStarted){
            _isStarted=false;
        }
    }
    
    //其他线程调用
    void wakeup(){
        //每次写+1提醒要执行回调函数_cb了
        uint64_t one = 1;
        int ret = ::write(_fd, &one, sizeof(one));
        if(ret != sizeof(one)) {
            perror("write");
        }
    }
    
    ~Eventfd(){
        if(_isStarted){
            stop();
        }
    }
    
private:
    int _fd;
    EventCallback _cb;
    bool _isStarted;
    
private:
    int createEventfd(){
        int fd=eventfd(1,0);
        return fd;
    }
    
    void handleRead(){
        uint64_t howmany;
        int ret = ::read(_fd, &howmany, sizeof(howmany));
        if(ret != sizeof(howmany)) {
            perror("read");
        }
    }
};

void test(){
    Eventfd efd(process);
    Thread thread(std::bind(&Eventfd::start,&efd));
    thread->start();
    for(int i=0;i!=20;++i){
        efd.wakeup();
        ::sleep(1);
    }
    efd.stop();
    thread->join();
}
```



## 事件通知结合线程池和网络库

### 封装TcpServer

```cpp
class MyTask{
    using TcpConnectionPtr=shared_ptr<TcpConnection>;
    
public:
    
    MyTask(const string &msg,const TcpConnectionPtr &conn):_msg(msg),_conn(conn){}
    
    void process(){
        //decode解码
        //compute数据处理
        //encode加密
        string response=_msg;//返回给客户端的处理完后加密了的数据
        //_conn->send(response);//不应当由计算线程发送数据，而是注册回调函数交给IO线程
        _conn->sendInLoop(response);
    }
    
private:
    string _msg;
    TcpConnectionPtr _conn;
};

class MyServer{
public:
    
    MyServer(const string ip,unsigned short port,int threadNum,int queSize):_threadpool(threadNum,queSize),_server(ip,port){}
    
    void start(){
        _threadpool->start();
        _server.setConnectionCallback(onConnection);
        _server.setMessageCallback(onMessage);
        _server.setCloseCallback(onClose);
        _server->start();
    }
    
private:
    ThreadPool _threadpool;
    TcpServer _server;
    
private:
    void onConnection(const TcpConnectionPtr &conn){
        cout<<conn->toString()<<"has connected"<<endl;
        conn->send("welcome to server");
    }

    void onMessage(const TcpConnectionPtr &conn){
        string msg=conn->receive();
        MyTask task(msg,conn);
        //把对象封装成一个任务交给线程池
        pthreadpool->addTask(std::bind(&MyTask::process,&task));
    }

    void onClose(const TcpConnectionPtr &conn){
        cout<<conn->toString()<<"has Closed"<<endl;
    }
};

void test(){
    MyServer server("192.168.0.0",5000,5,10);
    server.start();
    
}
```

### 修改EventLoop

新增eventfd，用于分离IO线程和计算线程，计算线程得到的结果交由IO线程处理，之间的通信就需要借助eventfd

![image-20200526120212880](D:\TyporaPic\复习笔记cpp\image-20200526120212880.png)

在EventLoop中加入eventfd文件描述符

增加handleRead和wakeup函数

新增回调函数_pendingFunctiors和访问该临界资源的互斥锁 _mutex

runInLoop函数是接收TcpConnection注册来的回调函数

自此，EventLoop分为两部分，一部分是IO线程处理各种文件描述符，另一部分是TcpConnection所在的计算线程处理完毕后通知IO线程将计算结果发送出去的函数注册过来交给第一部分的文件描述符阶段进行处理

```cpp
class EventLoop{
    using Functor=std::function<void()>;
    using TcpConnectionPtr=std::shared_ptr<TcpConnection>;
    using Callback=std::function<void(const TcpConnection &)>;
    
public:
    
    EventLoop(Acceptor &acceptor):_efd(createEpollFd()),_eventfd(createEventFd()),_acceptor(acceptor),_eventList(1024),_isLooping(false){
        addEpollRdFd(_eventfd);//添加eventfd的监听，每次可以读都代表要执行回调函数
        addEpollRdFd(_acceptor.fd());
    }
    
    void loop(){
        _isLooping=true;
        while(_isLooping){
            waitEpollFd();
        }
    }
    
    void unloop(){
        if(_isLooping){
            _isLooping=false;
        }
    }
    
    void setConnectionCallback(Callback &&cb){
        _onConnection=std::move(cb);
    }
    
    void setMessageCallback(Callback &&cb){
        _onMessage=std::move(cb);
    }
    
    void setCloseCallback(Callback &&cb){
        _onClose=std::move(cb);
    }
    
    //这个函数会在TcpConnection中被调用
    void runInLoop(Functor &&cb){
        {//大括号表示语句块，这样MutexLockGuard只在语句块内部保护，减小加锁范围
            MutexLOckGuard(&_mutex);
        	_pendingFunctors.push_back(std::move(cb));
        }
        wakeup();//计算线程注册完回调函数后通知EventLoop所在的IO线程
    }
    
private:
    int _efd;
    int _eventfd;
    Acceptor &_acceptor;
    vector<struct epoll_event> _eventList;
    map<int,TcpConnectionPtr> _conns;
    bool _isLooping;
    //计算线程完成的计算结果封装成Functor函数注册回IO线程
    vector<Functor> _pendingFunctors;//临界资源，会被多个计算线程访问，因此访问需要互斥锁
    MutexLock _mutex;
    
    Callback _onConnection;
    Callback _onMessage;
    Callback _onClose;
    
private:
    int createEpollFd(){
        int efd=epoll_create1(0);
        return efd;
    }
    
    void addEpollRdFd(int fd){
        struct epoll_event event;
        event.data.fd=fd;
        event.flag=EPOLLIN;
        epoll_ctl(_efd,EPOLL_ADD,fd,&event);
    }
    
    void delEpollRdFd(int fd){
        struct epoll_event event;
        event.data.fd=fd;
        event.flag=EPOLLIN;
        epoll_ctl(_efd,EPOLL_DEL,fd,&event);
    }
    
    void waitEpollFd(){
        int nready;
        do{
            nready=epoll_wait(_efd,&*_eventList.begin(),_eventList.size(),5000);
        }while(nready==-1&&errno==EINTR);
        if(nready==-1){
            perror("epoll_wait");
            return;
        }else if(nready==0){
            cout<<"epoll_wait timeout"<<endl;
        }else{
            //满了要扩容
            if(nready==_eventList.size()){
                _eventList.resize(nready*2);
            }
            
            for(int i=0;i!=nready;++i){
                int fd=_eventList[i].data.fd;
                if(fd==_acceptor.fd()){
                    if(_eventList[i].events&EPOLLIN){
                        handleNewConnection();
                    }
                }else is(fd==_eventfd){
                    if(_eventList[i].events&EPOLLIN){
                        handleRead();
                    	doPendingFunctors();
                    }
                }else{
                    if(_eventList[i].events&EPOLLIN){
                        handleMessage(fd);
                    }
                }
                
            }
        }
    }
    
    void handleNewConnection(){
        int peerfd=_acceptor.accept();
        addEpollRdFd(peerfd);
        TcpConnectionPtr conn(new TcpConnection(peerfd,this));//多了个this，表示把回调函数注册给哪个EventLoop
        conn->setConnectionCallback(_onConnection);
        conn->setMessageCallback(_onMessage);
        conn->setCloseCallback(_onClose);
        _conns.insert(make_pair(peerfd,conn));
        conn->handleNewConnectionCallback();
    }
    
    void handleMessage(int fd){
        bool isClosed=isConnectionClosed(fd);
        auto iter=_conns.find(fd);
        assert(iter != _conns.end());//运行时断言
        if(!isClosed){
            iter->second->handleMessageCallback();
        }else{
            delEpollRdFd(fd);
            iter->second->handleCloseCallback();
            _conns.erase(iter);
        }
    }
    
    bool isConnectionClosed(int fd){//如果接收缓冲区还有数据，就表示没有关闭连接
        int ret;
        do{
            char buff[1024];
            ret = recv(fd, buff, sizeof(buff), MSG_PEEK);
        }while(ret == -1 && errno == EINTR);

        return (ret == 0);
    }
    
    int createEventFd(){
        int fd=eventfd(1,0);
        return fd;
    }
    
    void handleRead(){
        uint64_t howmany;
        read(_eventfd,&howmany,sizeof(howmany));
    }
    
    void wakeup(){
        uint64_t on=1;
        write(_eventfd,&on,sizeof(on));
    }
    
    void doPendingFunctors(){
        vector<Functor> p;
        {
            MutexLockGuard guard(_mutex);
            p.swap(_pendingFunctors);
        }
        for(auto &f:p){
            f();
        }
    }
    
};
```

### 修改TcpConnection类



![image-20200526120226685](D:\TyporaPic\复习笔记cpp\image-20200526120226685.png)

添加sendInLoop方法，给EventLoop注册回调函数，调用的时EventLoop的runInLoop

TcpConnection需要知道给哪个EventLoop对象注册，因此要加一个_loop指针

```cpp
class TcpConnection:public enable_shared_from_this<TcpConnection>{
    using TcpConnectionPtr=std::shared_ptr<TcpConnection>;
    using TcpConnectionCallback=std::function<const TcpConnectionPtr &>;
    
public:

    TcpConnection(int fd,EventLoop *loop):_sock(fd),_socketIO(fd),_localAddr(getLocalAddr(fd)),_peerAddr(getPeerLocal(fd)),_isShutDownWrite(false),_loop(loop){}
    
    ~TcpConnection(){
        if(!_isShutDownWrite){
            shutdown();
        }
    }
    
    void shutdown(){
        if(!_isShutDownWrite){
            _isShutDownWrite=true;
            _sock.shutdownWrite();
        }
    }
    
    string receive(){
        char buf[1024]={0};
        _socketIO.readline(buf,sizeof(buf));
        return string(buf);
    }
    
    void send(const string &msg){
        _socketIO.writen(msg.c_str(),msg.size());
    }
    
    string toString()const{
        string ostringstream oss;
        oss<< _localAddr.ip() << ":" << _localAddr.port() << " --> "<< _peerAddr.ip() << ":" << _peerAddr.port();
        return oss.str();
    }
    
    //延迟到IO线程执行，即把自己的send方法作为回调函数用bind打包注册给_loop代表的EventLoop
    void sendInLoop(const string &msg){
        _loop->runInLoop(std::bind(&TcpConnection::send,this,msg));
    }
    
    void setConnectionCallback(const TcpConnectionCallback &cb){
        _onConnection=cb;
    }
    
    void setMessageCallback(const TcpConnectionCallback &cb){
        _onMessage=cb;
    }
    
    void setCloseCallback(const TcpConnectionCallback &cb){
        _onClose=cb;
    }
    
    void handleConnectionCallback(){
        if(_onConnection){
            _onConnection(shared_from_this());
        }
    }
    
    void handleMessageCallback(){
        if(_onMessage){
            _onMessage(shared_from_this());
        }
    }
    
    void handleCloseCallback(){
        if(_onClose){
            _onClose(shared_from_this());
        }
    }
    
private:
    Socket _sock;
    SocketIO _socketIO;
    InetAddress _localAddr;
    InetAddress _peerAddr;
    bool _isShutDownWrite;
    TcpConnectionCallback _onConnection;
    TcpConnectionCallback _onMessage;
    TcpConnectionCallback _onClose;
    
    EventLoop *_loop;
    
private:
    InetAddress getLocalAddr(int fd){
        struct sockaddr_in addr;
        socklen_t len = sizeof(struct sockaddr);
        if(getsockname(_sock.fd(), (struct sockaddr*)&addr, &len) == -1) {
            perror("getsockname");
        }
        return InetAddress(addr);
    }
    
    InetAddress getPeerAddr(int fd){
        struct sockaddr_in addr;
        socklen_t len = sizeof(struct sockaddr);
        if(getpeername(_sock.fd(), (struct sockaddr*)&addr, &len) == -1) {
            perror("getsockname");
        }
        return InetAddress(addr);
    }
};
```

