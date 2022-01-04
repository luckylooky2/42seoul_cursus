#!/bin/bash
echo -e "\033[32;1m"NORM"\033[m"
read $a
norminette ./g*.c ./g*.h
echo -e "\033[32;1m"printfTester"\033[m"
read $a
git clone https://github.com/Tripouille/printfTester.git
cd printfTester/
make b
cd ..
rm -rf printfTester/
echo -e "\033[32;1m"DONE"\033[m"