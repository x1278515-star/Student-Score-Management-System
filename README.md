# 学生成绩管理系统

[![Language](https://img.shields.io/badge/language-C%2B%2B-blue.svg)](https://isocpp.org/)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/platform-Windows-lightgrey.svg)](https://visualstudio.microsoft.com/)

一个基于 C++ 的控制台学生成绩管理系统，使用**单链表**作为核心数据结构，适合数据结构或程序设计课程设计项目。

## 📁 项目结构

```
Student-Score-Management-System/
├── .gitattributes
├── .gitignore
├── LICENSE                 # MIT 开源许可证
├── README.md
├── 学生管理系统.sln          # Visual Studio 解决方案
├── 学生管理系统.vcxproj       # Visual Studio 项目文件
├── 学生管理系统.vcxproj.filters
└── src/
    ├── 学生管理系统.cpp       # 基础版本
    └── 学生管理系统_改进版.cpp  # 改进版本（推荐）
```

## ✨ 功能说明

| 功能 | 基础版 | 改进版 |
|------|:------:|:------:|
| 登记学生成绩 | ✅ | ✅ |
| 查询学生成绩 | ✅ | ✅ |
| 插入新学生 | ✅ | ✅ |
| 删除学生信息 | ✅ | ✅ |
| 显示全部学生 | ✅ | ✅ |
| 更新学生成绩 | ❌ | ✅ |
| 统计（总数/平均/最高/最低） | ❌ | ✅ |
| 按成绩排序显示 | ❌ | ✅ |
| 文件保存与读取 | ❌ | ✅ |
| 输入合法性校验 | ❌ | ✅ |

## 🧱 数据结构设计

采用**单链表**存储学生信息，每个结点包含：

- 学号（`char[20]`）
- 姓名（`char[20]`）
- 成绩（`float`）
- 指向下一结点的指针

**选择链表的原因：** 便于动态插入和删除结点，体现数据结构课程中链式存储的应用。

## 🚀 运行方法

### 环境要求

- **操作系统：** Windows
- **编译器：** Visual Studio 或任意支持 C++ 的编译器（GCC / MSVC / Clang）

### 方法一：Visual Studio 运行

```bash
# 打开解决方案文件
git clone https://github.com/x1278515-star/Student-Score-Management-System.git
cd Student-Score-Management-System
start 学生管理系统.sln
```

### 方法二：直接编译

```bash
g++ src/学生管理系统_改进版.cpp -o student_manager
./student_manager
```

## 🖥️ 运行示例

```text
========== 学生成绩管理系统 ==========
1. 登记学生成绩(覆盖)    2. 查询学生成绩
3. 插入新学生          4. 更新学生成绩
5. 删除学生            6. 显示所有学生
7. 显示统计信息        8. 按成绩排序显示
9. 保存到文件          0. 退出
=====================================
请选择操作 (0-9):
```

## 📝 改进方向

- [ ] 图形界面（Qt / MFC）
- [ ] 数据库存储（SQLite / MySQL）
- [ ] 按姓名模糊查询
- [ ] 多条件组合统计
- [ ] 代码模块化拆分（.h / .cpp 分离）

## 📄 许可证

本项目采用 [MIT License](LICENSE) 开源许可。

## 🙋 说明

本项目为控制台程序，适合课程设计、实验作业或 C++ 基础项目练习。
