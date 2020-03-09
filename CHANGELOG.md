# StarEngine Changelog #

## 2020.1: 2020-03-09  ##
### ShaderGraph ###
* 添加了shader全局状态的支持
* 重构了descriptor table的构筑算法
* 支持VS、PS的构建，放弃DS、HS、TS、GS。用Mesh Shader替代
### RenderGraph ###
* 添加了桌面端RenderGraph的构建
* 添加了Forward、Deferred渲染管线的demo
### AssetFactory ###
* 添加了png的导入、dxt的导出
* 添加了fbx的导入
### DX12Engine ###
* 添加了静态场景的渲染
* 添加了调试渲染流水线
