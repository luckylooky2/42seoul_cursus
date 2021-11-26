#!/bin/bash
make fclean
echo -e “\033[32;1m”NORM”\033[m”
read $a
norminette ./*.c ./*.h
echo -e “\033[32;1m”LIBFT TEST”\033[m”
read $a
git clone https://github.com/jtoty/Libftest
cd Libftest/
./grademe.sh
sed -i “” ‘s/~\/libft/..\//’ my_config.sh
cd Libftest/
./grademe.sh -n
cd ..
echo -e “\033[32;1m”WAR MACHINE”\033[m”
read $a
git clone https://github.com/ska42/libft-war-machine
cd libft-war-machine/
bash grademe.sh
bash grademe.sh -n
cd ..
echo -e “\033[32;1m”unit-test”\033[m”
read $a
git clone https://github.com/alelievr/libft-unit-test.git
cd libft-unit-test/
sed -i “” ‘s/LIBFTDIR	=	..\/libft/LIBFTDIR	=	..\//’ Makefile
cd ..
make all
sleep .5
make bonus
cd libft-unit-test/
make f
cd ..
make fclean
echo -e “\033[32;1m”libftTester”\033[m”
read $a
git clone https://github.com/Tripouille/libftTester.git
cd libftTester/
make m
make b
cd ..
rm -rf Libftest/ libft-war-machine/ libft-unit-test/ libftTester/
echo -e “\033[32;1m”make fclean”\033[m”
read $a
make
make fclean
ls
echo -e “\033[32;1m”make clean”\033[m”
read $a
make
make clean
ls
echo -e “\033[32;1m”make all”\033[m”
read $a
make all
ls
echo -e “\033[32;1m”make bonus”\033[m”
read $a
make bonus
ls
echo -e “\033[32;1m”relink”\033[m”
read $a
make
make bonus
echo -e “\033[32;1m”DONE”\033[m”