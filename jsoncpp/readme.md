## 0、安装background插件(插件商店搜索安装)



## 1、在全局settings.json中添加如下background的配置

```json
  "background.customImages" : 
	[
		"file:///F:/vscodebackground/1.png"//图片路径
	],
	"background.style" : 
	{
		"background-position" : "center",
		"background-size" : "100%,100%", //图片大小
		"background.repeat" : "no-repeat",
		"content" : "''",
		"height" : "100%",
		"opacity" : 0.2, //透明度
		"pointer-events" : "none",
		"position" : "absolute", //图片位置
		"width" : "100%",
		"z-index" : "99999"
	},
	"background.useDefault" : false,
	"background.useFront" : true,
	"extensions.ignoreRecommendations" : false,
	"maxPlus.DefaultGame" : "lol",
	"powermode.enabled" : true,
	"powermode.shakeIntensity" : 0, //是否使用默认图片
	//background 的相关配置
	"update.enableWindowsBackgroundUpdates" : true,
	"window.zoomLevel" : 2,
```

## 2、修改changeVscodeBackground.cpp中全局变量jsonPath变成自己的vscode的全局settings.json的位置



## 3、修改parseJson中i的大小，使其满足遍历到最后一张图片的id后回到第一张



## 4、修改parseJson中拼接的图片路径字符串sprintf



## 5、按需修改main函数中的startNum和sleepSecond



## 6、运行程序

    如：changeVscodeBackground.exe 1 10
    从1.png开始，每10s切换到下一张



## 7、到时间了点击右下角弹窗刷新vscode