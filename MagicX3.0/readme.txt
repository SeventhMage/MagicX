Magic3.0引擎

学习图形学过程中Magic引擎的第三次重构
由于时间紧迫及个人能力尚且有且，本引擎只实现了最基本的功能

本目录下所有代码及资源已经上传到git地址https://github.com/SeventhMage/MagicX.git/trunk/MagicX3.0
并将持续更新进行完善

引擎代码渲染器采用最新OpenGL标准，以可编程渲染管线方式编写

目录说明：
bin：所有生成的程序文件，直接运行目录下的文件需要将.exe文件拷至resource目录下或将resource下所有文件拷贝到.exe同目录下
doc: 相关文档
examples：通过引擎实现的几个例子
	Cube目录下实现了基本的箱子功能，鼠标左键以虚拟跟踪球方式旋转箱子，鼠标右键旋转摄像机
	SceneRoam：通过立方体映射实现天空盒及环境映射，鼠标右键旋转摄像机，ADWS控制球体移动
	Shadow：通过创建深度阴影贴图，两次渲染场景，实现基本阴影效果，鼠标右键旋转摄像机，鼠标滚轮拉近拉远摄像机。
	FlyingGreedySnoke：能过前面功能的组合，实现了一个简单的游戏贪吃蛇Demo，鼠标右键控制摄像机旋转，AD键控制蛇的转向。
include：引擎头文件
lib：引擎生成及依赖库文件
project：引擎工程目录
resource：游戏资源包括了纹理、模型、shader等
source：引擎源文件

	