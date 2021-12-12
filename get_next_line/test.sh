#!/bin/bash
echo -e "\033[32;1m"NORM"\033[m"
read $a
norminette ./*.c ./*.h
echo -e "\033[32;1m"gnlTester"\033[m"
read $a
git clone https://github.com/Tripouille/gnlTester.git
cd gnlTester/
make m
cd ..
rm -rf gnlTester/
echo -e "\033[32;1m"DONE"\033[m"