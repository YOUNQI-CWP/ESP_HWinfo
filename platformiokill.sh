#!/bin/bash

# 清理PlatformIO编译文件和目录
rm -rf .pio/build
rm -rf .pio/deps
rm -rf .pio/.cache
#保留platformio工程的第三方依赖库文件
#rm -rf .pio/libdeps

# 删除固件和中间文件
find . -name '*.elf' -delete
find . -name '*.bin' -delete
find . -name '*.hex' -delete
find . -name '*.map' -delete
find . -name '*.lst' -delete
find . -name '*.tmp' -delete

# 删除日志和缓存文件
find . -name '*.log' -delete
find . -name '*.tra' -delete
find . -name 'JLinkLog.txt' -delete

# 删除编译数据库和IDE相关文件
find . -name 'compile_commands.json' -delete
find . -name '*.gdb' -delete
find . -name 'c_cpp_properties.json' -delete

# 保留platformio.ini和核心源码文件
echo "清理完成，保留关键配置文件"
