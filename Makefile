# 编译器设置
CC = gcc
CFLAGS = -Wall -Wextra -g -std=c11
INCLUDES = -Iinclude
LDFLAGS = 

# 目录设置
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/object
ASM_DIR = $(BUILD_DIR)/assemble
OBJDUMP_DIR = $(BUILD_DIR)/objump

# 源文件和目标文件
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
ASSEMBLY = $(SOURCES:$(SRC_DIR)/%.c=$(ASM_DIR)/%.s)
OBJDUMP_FILES = $(SOURCES:$(SRC_DIR)/%.c=$(OBJDUMP_DIR)/%.dump)

# 最终可执行文件
TARGET = demo

# 默认目标
all: $(TARGET)

# 创建目录
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(ASM_DIR):
	mkdir -p $(ASM_DIR)

$(OBJDUMP_DIR):
	mkdir -p $(OBJDUMP_DIR)

# 编译可执行文件
$(TARGET): $(OBJECTS) | $(OBJ_DIR)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo "构建完成: $(TARGET)"

# 编译目标文件
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# 生成汇编文件
$(ASM_DIR)/%.s: $(SRC_DIR)/%.c | $(ASM_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -S $< -o $@

# 生成反汇编文件
$(OBJDUMP_DIR)/%.dump: $(OBJ_DIR)/%.o | $(OBJDUMP_DIR)
	objdump -d -S $< > $@

# 生成所有汇编文件
assembly: $(ASSEMBLY)
	@echo "汇编文件已生成到 $(ASM_DIR)"

# 生成所有反汇编文件
objdump: $(OBJDUMP_DIR) $(OBJECTS) $(OBJDUMP_FILES)
	@echo "反汇编文件已生成到 $(OBJDUMP_DIR)"

# 清理
clean:
	rm -rf $(BUILD_DIR) $(TARGET)
	@echo "清理完成"

# 完全清理（包括可执行文件）
distclean: clean
	rm -f $(TARGET)

# 显示符号表
symbols: $(TARGET)
	@echo "=== 可执行文件符号表 ==="
	nm $(TARGET)
	@echo "\n=== 使用readelf查看符号 ==="
	readelf -s $(TARGET)

# 显示目标文件符号
obj-symbols: $(OBJECTS)
	@echo "=== 目标文件符号表 ==="
	@for obj in $(OBJECTS); do \
		echo "\n--- $$obj ---"; \
		nm $$obj; \
	done

# 帮助信息
help:
	@echo "可用的make目标:"
	@echo "  all          - 编译项目（默认）"
	@echo "  assembly     - 生成汇编文件到 $(ASM_DIR)"
	@echo "  objdump      - 生成反汇编文件到 $(OBJDUMP_DIR)"
	@echo "  symbols      - 显示可执行文件的符号表"
	@echo "  obj-symbols  - 显示所有目标文件的符号表"
	@echo "  clean        - 清理构建文件"
	@echo "  distclean    - 完全清理（包括可执行文件）"
	@echo "  help         - 显示此帮助信息"

.PHONY: all clean distclean assembly objdump symbols obj-symbols help

