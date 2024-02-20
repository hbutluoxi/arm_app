#! /bin/bash

echo "hello world ! this is a test shell..."


function compare()
{
	echo this is a function test
}

var1=$[1+5]
var2=10
var3=$[$var1 + $var2]

APP_IN=luoxi11

echo var1 result is $var1
echo var3 result is $var3

tesetuser=liqiong
echo USER result is $USER

compare
if [ $USER = $tesetuser ]
then
	echo welcome user....
	echo we will start app_test...
	./app_test
fi

for test in one tow three four
do
	echo state is $test
done

for ((a=1; a<5; a++))
do
	echo avalue is $a
done

case $1 in 
$APP_IN )
	echo this is csae test
;;
esac

