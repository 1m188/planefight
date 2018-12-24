#include "Config.h"
#include "QFile"

Config *Config::instance = nullptr; //初始化单例指针

Config::Config()
{
}

Config::~Config()
{
}

Config * Config::getInstance()
{
	if (!instance)
	{
		instance = new Config();
	}
	return instance;
}

void Config::init()
{
	QFile f("config.ini");
	//如果设置文件存在则读取数据
	if (f.exists())
	{
		f.open(QIODevice::ReadOnly);

		QString temp;

		//读取fps值
		temp = f.readLine();
		temp.chop(1);
		fps_ = temp.toInt();

		f.close();
	}
	//否则创建一个新的文件
	else
	{
		f.open(QIODevice::WriteOnly);
		f.close();
	}
}

void Config::uninit()
{
	QFile f("config.ini");
	f.open(QIODevice::WriteOnly | QIODevice::Truncate);
	//写入保存fps值
	f.write((QString::number(fps_) + "\n").toStdString().c_str());
	f.close();
}