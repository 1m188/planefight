#ifndef CONFIG_H
#define CONFIG_H

//设置类
class Config
{
private:
	Config(); //禁止自动默认构造

	static Config *instance; //单例指针

	//帧数
	int fps_ = 0;

public:
	Config(const Config &) = delete;
	Config &operator=(const Config &) = delete;
	~Config();

	static Config *getInstance(); //获取单例指针

	//初始化
	void init();
	//保存数据
	void uninit();

	//获取帧数
	const int fps() const { return fps_; }
	//获取帧数的引用
	int &rfps() { return fps_; }
};

#endif // !CONFIG_H
