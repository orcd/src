
echo $#

# 定义函数的方法
func1()
{
    echo $0
    echo $#
    echo "func1, $1, $2, $3"

    var=100

    return 11 # return 0 ~ 255
}

# 后面两种定义函数的方法，了解即可
#function func2
#{
#    echo "func2"   
#}

#function func3()
#{
#    echo "func3"
#}

# 调用函数和C语言不一样，不需要括号
echo "before var is: $var"
func1 aaa bbb ccc
echo "after var is: $var"
echo $?
#func2
#func3

