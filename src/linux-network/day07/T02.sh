
# if [ expr ]
# then
#   codes1
# else
#   codes2
# fi

if [ -n "$1" ]
then
    echo "arg1 is not null"
else
    echo "arg1 is null"
    exit 1
fi

if [ $1 = 100 ]  # 判断$1是不是字符串的"100"
then 
    echo "is 100"
else
    echo "not 100"
fi

if [ $1 -ge 100 -a $1 -le 200 ]
then 
    echo "ok"
else 
    echo "not ok"
fi

if [ -d "./a.sh" ] 
then
    echo "is dir"
else
    echo "is not dir"
fi
