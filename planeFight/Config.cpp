#include "Config.h"
#include "QFile"
#include "QJsonDocument"
#include "QJsonObject"

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
		//从文件中读取
		f.open(QIODevice::ReadOnly);
		QByteArray temp = f.readAll();
		f.close();

		//从json中获取相应的属性
		QJsonDocument jsonDocument = QJsonDocument::fromJson(temp);
		QJsonObject jsonObject = jsonDocument.object();
		fps_ = jsonObject.value("Fps").toInt(); //读取帧数
		//控制帧数范围
		if (fps_ > 60)
		{
			fps_ = 60;
		}
		else if (fps_ < 30)
		{
			fps_ = 30;
		}
		highestScore_ = jsonObject.value("HighestScore").toInt(); //读取最高分
		highestScorePlayer_ = jsonObject.value("HighestScorePlayer").toString(); //读取最高分保持者
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
	//json格式保存入文件之中
	QJsonObject json;
	json.insert("Fps", fps_); //写入保存fps值
	json.insert("HighestScore", highestScore_); //写入保存最高分
	json.insert("HighestScorePlayer", highestScorePlayer_); //写入保存最高分保持者

	QJsonDocument jsonDocument;
	jsonDocument.setObject(json);
	QByteArray byteArray = jsonDocument.toJson();

	//写入文件
	QFile f("config.ini");
	f.open(QIODevice::WriteOnly | QIODevice::Truncate);
	f.write(byteArray);
	f.close();
}