
var=xiao

echo ${var}ming

#PATH='haha'
#echo $PATH


echo $0
echo $1
echo $2
echo $3
echo $4
echo $5
echo "\$10 is " ${10}
echo $# 

var=100
var="100"
var='100'

var="hello world"
var=hello\ world

files=`ls`

echo $files

abc=100
export abc
#export abc=100

echo ${abc}

a=100
b=200

c=`expr $a + $b`
echo $c






