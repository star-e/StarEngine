# StarEngine
An experimental rendering engine

知乎专栏：
https://zhuanlan.zhihu.com/starengine

# 系统要求
a. 良好的网络环境，能顺利连接github与microsoft。

b. Visual Studio 2019 16.3, 需要安装以下四个模块。

  1.Desktop development with C++

  2.Game development with C++

  3.Universal Windows Platform development

  4.Windows10 SDK 17763
  
  如果需要支持Unity，需要安装

  5.dotNet desktop development

  6.Game development with Unity

# 编译步骤
a. 确保网络环境良好，否则可能花费较长时间在文件下载上。

b. 按照上述系统要求安装完Visual Studio 2019

c. git clone vcpkg到本地。 https://github.com/Microsoft/vcpkg 

d. 在本地vcpkg目录打开cmd/powershell，然后在cmd/powershell中键入.\bootstrap编译vcpkg

e. 在cmd/powershell中键入，vcpkg install --triplet x64-windows boost eigen3

vcpkg会自动安装boost、eigen3和他们所需的依赖。安装时间视网络环境与机器配置而定。顺利的话，在30分钟左右。

f. 设置$(StarVcpkg)系统环境变量，目录为本地vcpkg目录。例如 c:\vcpkg。

g. 打开StarEngine目录下的Star.sln，选择x64-development即可开始编译。

h. 输出文件在build/v142/x64/Development目录下。具体路径与编译设置有关。
