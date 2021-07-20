# CoLoR应用层
&emsp;&emsp;color的应用层都应通过`colorSocket`与网络层模块建立连接,通过接口函数生成GET包、注册DATA包。具体方式请参考实现应用中的实例。
&emsp;&emsp;这里主要实现了两类应用，一是最简单的无重传请求-应答应用，具体实现见`SimpleApp`和`SimpleProvider`类型，一个是请求者，一个是内容提供者，具体实现参看代码。使用方式非常简单，设置好DATA的包长度、数量还有请求者的请求间隔后就可以使用。需要注意的是，使用时请求者需要设置端口号，并且设置`destAddr`为内容提供者模块的`index`。
&emsp;&emsp;第二类是文件传输应用，分别为请求端的`fileTransApp`、内容提供者端的`fileTransProvider`。文件传输应用提供了重传确认机制，在请求者端由三个参数控制。
``` cpp
// 最大超时时间
double limit @unit(s) = default(0.5s);

// 重传间隔
double retransTimer @unit(s) = default(0.1s);

// 模式
bool greedy = default(false); 
```
重传间隔到了如果文件如果不完整会重传GET包，如果最大超时时间到了直接请求下一个文件。如果开启了greedy模式，在收到完整文件后就立即请求下一个文件；否则即使当前文件完整，也要等到最大超时时间到了再请求下一个文件。
&emsp;&emsp;`LFBL_file`是专用于LFBL的文件传输应用，模拟NDN中一个GET（interest)对应一个DATA的情况。每次请求文件时，请求者需要一次发送多个GET包。
&emsp;&emsp;用于比较的IP架构的应用在`/cmpUdpApp`文件夹下，基于UDP实现了请求应答和文件传输应用，对应流传输可以直接使用INET原生提供的`UdpVideoStream`应用。