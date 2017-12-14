# LM项目

LM软件全称为Local Message，用于局域网通信的聊天软件。

## 模块
- cli
- gui 滞后实现
- ctrl
- ft

### cli模块
获取用户输入，将用户输入转化为数据交换格式（json）发送给ctrl模块

### ctrl模块
向其他用户发送控制信息，向ft传输模块发送控制信息，同时接收其他用户发送过来的控制信息。

### ft模块
ctrl发送来的文件传输任务
其他用户发送来文件请求
cli/gui发送过来的文件传输情况请求



## 流程图

- 设置名字的流程图

```{mermaid}
sequenceDiagram
cli/gui->>ctrl: 设置名字
ctrl->>其他用户:设置名字
其他用户->>ctrl:设置名字的相应
```

设置名字ui->ctrl：
```json
{
  cmd: "setname",
  name: "xxxx"
}
```

ctrl->other
```json
{
  cmd: "setname",
  name: "xxxx",
}
```

other->ctrl
``` json
{
  cmd: "setname_ack",
  name: "yyyy"
}
```

- 聊天流程图

发送
```{mermaid}
sequenceDiagram
cli/gui->>ctrl: 发送聊天信息
ctrl->>其他用户:发送聊天信息
```

接收
```{mermaid}
sequenceDiagram
其他用户->>ctrl: 发送聊天信息
ctrl->>cli/gui:发送聊天信息
```

- 发送文件
发送文件的总图

```{mermaid}
sequenceDiagram
cli1->>ctrl1:发送文件
ctrl1->>ft1:创建发送任务
ctrl1->>ctrl1:sleep
ctrl1->>ctrl2:发送接收文件通知
ctrl2->>cli2:通知有文件来了
cli2->>ctrl2:确认接收文件
ctrl2->>ft2:创建接收文件任务
ft2->>ft1:发送TCP连接，接收文件
```
发送
```{mermaid}
sequenceDiagram
cli/gui->>ctrl: 发送文件1
ctrl->>ft: 创建发送文件任务2
ctrl->>其他用户: 发送文件3
其他用户->>ft: 接收文件4
ft->>其他用户: 发送文件内容5
```
报文：
ui --> ctrl
```json
{
  cmd:"sendfile",
  path:"/home/xueguoliang/test.file"
  to:"192.168.11.20",
}
```
ctrl-->ft
``` json
{
  cmd:"ft",
  filepath:"/home/xueguoliang/test.file"
  recv:"192.168.11.20",
  type:"send",
  token:"1123103123"
}
```
ctrl-->Other(ctrl)
```json
{
  cmd:"ft",
  path:"/home/xueguoliang/test.file",
  fromuser: "xxxx",
  filelen: 123456,
  token:"1123103123"
}
```



接收
```{mermaid}
sequenceDiagram
其他用户->>ctrl: 发送文件
ctrl->>cli/gui: 发送文件请求
ctrl->>ft: 创建接收文件任务
ft->>其他用户: 接收文件请求
其他用户->>ft: 发送文件
```

- 获取用户信息
```{mermaid}
sequenceDiagram
cli/gui->>ctrl: 用户列表请求
ctrl->>cli/gui: 用户列表相应
```

-  获取文件传输信息
```{mermaid}
sequenceDiagram
cli/gui->>ft: 文件列表请求
ft->>cli/gui: 文件列表相应
```

![Snip20170303_24](/assets/Snip20170303_24.png)

v0.01: 搭建好环境
v0.02: UI发送setname OK
v0.03: ctrl recv setname
v0.05: chat ok
v0.06: 传输文件之前，准备实现文件传输
