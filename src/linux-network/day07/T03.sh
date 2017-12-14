
sum=0
var=1

while [ $var -le 100 ]
do
    sum=`expr $sum + $var`
    var=`expr $var + 1`
done

echo $sum

