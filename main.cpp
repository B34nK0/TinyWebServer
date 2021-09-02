#include "config.h"

int main(int argc, char *argv[])
{
    //需要修改的数据库信息,登录名,密码,库名
    string user = "root";
    string passwd = "root";
    string databasename = "qgydb";

    //命令行解析 后期可以写一个类，读取项目配置文件
    Config config;
    config.parse_arg(argc, argv);

    //栈上构造 初始化 httpconns timers
    WebServer server;

    //初始化 数据库配置、链接池配置、线程池配置
    server.init(config.PORT, user, passwd, databasename, config.LOGWrite, 
                config.OPT_LINGER, config.TRIGMode,  config.sql_num,  config.thread_num, 
                config.close_log, config.actor_model);
    

/////////////以下服务器的动作 不应该是在init里么？应该是伴随着server的声明周期且不会被单独调用的
    //日志
    server.log_write();

    //数据库
    server.sql_pool();

    //线程池
    server.thread_pool();

    //触发模式
    server.trig_mode();

    //监听
    server.eventListen();

/////////////////////////////////////////

    //运行启动
    server.eventLoop();

    return 0;
}