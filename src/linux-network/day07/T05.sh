

var=$1

case $var in
    start)
        echo "start"
        ;;
    stop|pause)
        echo "stop or pause"
        ;; # break
    *) # 其他情况
        echo "default"
esac
