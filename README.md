# StarEngine
An experimental rendering engine

知乎专栏：
https://zhuanlan.zhihu.com/starengine

# 系统要求
良好的网络环境，能顺利连接github与microsoft。

## Visual Studio 2019 16.4, 需要安装以下模块。

1.Desktop development with C++

2.Game development with C++

3.Universal Windows Platform development

4.Windows10 SDK 18362

5.dotNet desktop development (可选，为了支持Unity)

6.Game development with Unity (可选，为了支持Unity）

## Visual Studio安装完成后，需要安装以下插件

1.C++/WinRT

# 编译步骤
1. 确保网络环境良好，否则可能花费较长时间在文件下载上。

2. 按照上述系统要求安装完Visual Studio 2019

3. git clone vcpkg到本地。 https://github.com/Microsoft/vcpkg 

4. 在本地vcpkg目录打开cmd，然后在cmd中键入.\bootstrap编译vcpkg

5. 在cmd中键入，vcpkg install --triplet x64-windows eigen3 boost libjpeg-turbo libpng tiff rxcpp directxtex ms-gsl。vcpkg会自动安装boost、eigen3等依赖。安装时间视网络环境与机器配置而定。顺利的话，在30分钟左右。

6. 设置$(StarVcpkg)系统环境变量，目录为本地vcpkg目录。例如 C:\vcpkg。

7. 设置$(StarFbx)系统环境变量，目录为本地fbxsdk目录。例如 C:\fbxsdk\2019.5

8. 打开StarEngine目录下的Star.sln，选择x64-Development即可开始编译。

9. 输出文件在build/v142/x64/Development目录下。具体路径与编译设置有关。
