#!/bin/bash

echo "----arm app compile start----"

current_date=$(date +%Y-%m-%d-%H-%M-%S) # 获取当前日期，格式为YYYY-MM-DD-HH-MM-SS

echo -e "\033[1;41m compile date $current_date \033[0m"

current_path=$(pwd)

make clean

make

cd release

if [ -f arm_app ] 
then
    echo "arm app compile success !!!"
else
    echo "arm app compile failed !!!"
fi   