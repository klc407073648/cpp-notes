./zhx_server &
./client1 &
./client2 &

function protect {
    # PRO_NAME = $1   
    #用ps获取$PRO_NAME进程数量
    NUM=`ps aux | grep -w $1 | grep -v grep |wc -l`
    #echo $NUM
    #少于1，重启进程
    if [ "${NUM}" -lt "1" ];then
        echo "[main.sh] $1 was killed"
        ./$1 &
    #大于1，杀掉所有进程，重启
    elif [ "${NUM}" -gt "1" ];then
        echo "[main.sh] more than 1 $1,killall $1"
        killall -9 $PRO_NAME
        ./$1 &
    fi
    #kill僵尸进程
    NUM_STAT=`ps aux | grep -w $1 | grep T | grep -v grep | wc -l`
    if [ "${NUM_STAT}" -gt "0" ];then
        killall -9 $1
        ./$1 &
    fi
    # sleep 1s
}

# NAME="client1"
while true ; do
    protect "zhx_server"
    protect "client1"
    protect "client2"
done
exit 0
