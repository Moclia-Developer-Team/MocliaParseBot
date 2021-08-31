## MocliaParseBot —— 一个基于Mirai-Api-Http和Mirai-Cpp的网络服务群解析程序

MocliaParseBot 跨平台的网易云音乐、B站视频、ascii2d图片查找等解析程序。

本程序基于Mirai-Cpp制作，通过Mirai-Api-Http与Mirai连接，请确保在`[yourBot]/config/net.mamoe.mirai-api-http/setting.yml`中进行正确配置。  
~~~yaml
adapters: 
  - http
  - ws    # 此处ws必须填写

# 省略非必要部分

adapterSettings: 
  http:
    host: localhost
    port: 5036
  
  # 必须填写ws相关设置，建议和http保持一致
  ws:
    host: localhost
    port: 5036
    reservedSyncId: -1
~~~

### 程序配置

本程序采用json配置文件，配置文件不会自动创建，需手动在程序同目录下新建`config.json`，内容示例如下：
~~~json
{
    "hostname": "127.0.0.1",
    "port": 8080,
    "botQQ": 10000,
    "verifyKey": "Hello",
    "enableVerify": false,
    "singleMode": true,
    "threadPoolSize": 4
}
~~~

由于json不支持注释，相关解释呈现在下表：

|json键|说明|类型|示例内容|
|:-:|:-:|:-:|:-:|
|hostname|MiraiApiHttp的IP地址|string|127.0.0.1|
|port|MiraiApiHttp开放的端口|int|8080|
|botQQ|要连接的机器人账号|int|10000|
|verifykey|MiraiApiHttp配置文件中定义的验证密钥|string|hello|
|enableVerify|MiraiApiHttp是否开启验证模式|bool|true|
|singleMode|MiraiApiHttp是否开启单账号模式|bool|true|
|threadPoolSize|程序使用的线程池大小|int|4|

更多配置文件选项请参阅[MiraiCPP文档](https://github.com/cyanray/mirai-cpp/blob/master/doc/Documentation.md#%E5%A6%82%E4%BD%95%E4%B8%8Emirai-api-http%E5%BB%BA%E7%AB%8B%E8%BF%9E%E6%8E%A5)

配置完成json，打开机器人后，等待屏幕出现`bot working……`即可使用。

### 群命令列表
* 关于点歌 —— 本程序暂时的帮助列表
* 点歌[歌名] —— 进行网易云点歌  

### 控制台命令列表
* exit —— 结束程序（如正常使用退出需使用本命令，否则会导致机器人程序内存泄漏）  

### 功能

网易云点歌  
网易云链接解析（未实现）  
BiliBili视频解析（未实现）   
Acfun视频解析（未实现）  
Ascii2d识图（未实现）    

### todo

网易云链接解析  
B站视频解析  
A站视频解析  
搜图  
彩色控制台页面  
指令优化  

## 如何编译

### 需要的库

submdule:  
> cyanray/mirai-cpp

vcpkg:  
> nlohmann/json (json for modern c++)
> whoshuu/cpr
> fmtlib/fmt

ps:如不想使用vcpkg，需要自己编译上述的vcpkg库或将其变成submodule  

### 需要的软件

windows:
> cmake
> visual studio 构建工具（msvc）

linux:
> cmake
> gcc
> make

### visual studio编译
配置好CMakeSettings.json，随后根据提示更新缓存，完全正确后点击生成-全部生成即可。可在out下找到需要的程序。  

### visual studio code windows编译
安装cmake插件后配置好vcpkg，选择构建工具和Release/debug，在底部找到按钮进行构建。

### visual studio code linux编译
todo

### linux命令行编译
todo