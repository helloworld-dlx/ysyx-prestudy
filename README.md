# ysyx-prestudy

个人的 ysyx 预学习/记录仓库：

目标是方便自己随时打开、复习、回滚版本，不追求“项目化/可发布”。



## 目录结构

- `Resource/`
  - `F_phase/`：数字逻辑 / 电路相关（Logisim `.circ`、配套资源）
  - `E_phase/`：后续新增（C / Verilog / 环境 / ISA 等内容按阶段整理）
- `docs/`：学习笔记/整理（Markdown）
- `.gitignore`：忽略临时文件/输出文件
- `README.md`：本说明



## F_phase 说明

`F_phase/` 下会按阶段分子目录，例如：

- `F_phase/F3/`：数字逻辑基础（门电路、编码器/译码器、多路复用、加法器、触发器/锁存器等）
- `F_phase/F5_sCPU/`：简单 CPU / 存储（如 RAM/ROM、小 CPU 组合）
- `F_phase/F6_minirv/`：迷你 RISC-V / minirv 相关电路

如果后续新增 `E_phase/`，同样按阶段拆目录即可。



## E_phase（预留）

`Resource/E_phase/` 计划按主题/阶段整理，例如：

- `E1/`：C 语言练习
- `E2/`：Verilog/HDL
- `E3/`：Linux / 环境配置 / 笔记
- `E4/`：从 C 到二进制 / ISA 模拟
- `E5/`：RTL 仿真 / 综合 / 物理设计入门
- `E6/`：PA1



## 使用方式

### 打开电路
1. 安装 Logisim-evolution
2. 直接打开 `.circ` 文件即可

### 查看文档
- `docs/` 下的 `.md` 直接用 VS Code / Typora / Obsidian 等打开



## Git 使用习惯

- 每次完成一个小目标就提交一次：  
  `feat: ...` / `fix: ...` / `chore: ...`  
- 不在仓库里保留临时恢复产物、缓存、输出文件（靠 `.gitignore` 管住）。

常用命令：

```bash
git status
git add -A
git commit -m "chore: update circuits"
git push
