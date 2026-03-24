# 🐾 Qt Desktop Pet（桌面宠物）

一个基于 Qt Widgets 实现的轻量级桌面宠物应用，支持多动画状态切换、透明窗口、无边框拖拽以及右键菜单交互。

---

## ✨ Features

- 🪟 **无边框透明窗口**  
  使用 `Qt::FramelessWindowHint` + `WA_TranslucentBackground`

- 🎞️ **帧动画播放**  
  基于 `QTimer` 实现逐帧动画切换

- 🖱️ **可拖拽移动**  
  自定义 `EventFilter` 实现桌面拖动

- 📋 **右键菜单控制**  
  支持多种行为切换：  
  - SayHello 👋  
  - Swing 🎈  
  - Sleep 😴  

- 🔄 **动态资源加载**  
  使用资源路径批量加载动画帧

- 🧩 **枚举驱动行为系统**  
  利用 `QMetaEnum` 实现字符串到枚举的映射

---

## 📸 Preview
### 🐾 SayHello

![SayHello](aseets/SayHello.gif)

### 🎈 Swing

![Swing](aseets/Swing.gif)

### 😴 Sleep

![Sleep](aseets/Sleep.gif)

---

## 🛠️ Tech Stack

- C++
- Qt 6 (Qt Widgets)
- QTimer / QPainter / QPixmap
- Qt Resource System（.qrc）

---

## 📂 Project Structure

```bash
.
├── widget.cpp        # 主逻辑（动画、绘制、菜单）
├── widget.h
├── DragFilter        # 拖拽事件过滤器
├── resources.qrc     # 图片资源
└── img/
    ├── sayHello/
    ├── swing/
    └── sleep/
```
---
## 🚀 How It Works
1️⃣ 动画实现原理

通过 QTimer 定时切换图片帧：
```bash
connect(timer, &QTimer::timeout, [this]() {
    static int index = 0;
    auto paths = this->action_map.value(this->cur_role_act);
    this->cur_role_pix = paths[index++ % paths.size()];
    this->update();
});
```
2️⃣ 绘制机制

在 paintEvent 中绘制当前帧：
```bash
QPainter painter(this);
QPixmap pix;
pix.load(this->cur_role_pix.toLocalFile());
painter.drawPixmap(0, 0, pix);
```
3️⃣ 动作切换

通过菜单触发 + 枚举反射实现：
```bash
QMetaEnum me = QMetaEnum::fromType<RoleAct>();
int k = me.keyToValue(action->text().toStdString().c_str(), &ok);
```
---
## 🎮 Usage

运行后：

- **🖱️ 拖动宠物：** 鼠标拖拽
- **🖱️ 右键菜单：**
  切换动作（SayHello / Sleep / Swing）
  隐藏窗口
📦 Resource Format

动画资源命名格式如下：
```bash
sayHello_%d.png
swing_%d.png
sleep_%d.png
```
示例：
```bash
sayHello_0.png
sayHello_1.png
...
```
---
## ⚙️ Build

使用 Qt Creator 打开 .pro 或 CMakeLists.txt：

# Qt 6 + CMake 示例
```bash
mkdir build
cd build
cmake ..
make
```
---
## 🔮 Future Work
- **🎤 添加语音交互**
- **🧠 接入 AI（如 OpenAI / 本地大模型）**
- **🐱 多角色切换**
- **💬 气泡对话系统**
- **⏰ 定时提醒功能**
---
## 🙌 Acknowledgements
- **Qt 官方文档**
- **桌面宠物灵感来源于经典 Windows 桌宠应用**
---
## ⭐ Star This Project

如果你觉得这个项目有意思，欢迎点个 ⭐！

