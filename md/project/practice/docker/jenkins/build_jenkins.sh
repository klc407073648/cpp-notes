#/bin/bash
prj_name='stibel'
container_name='jenkins'
full_name="${prj_name}_${container_name}"
cur_path=`pwd`

function build_environment()
{
    echo "begin to build environment in ${cur_path}"

    rm -rf ${cur_path}/data

    if [ ! -d ${cur_path}/data ]; then
        echo "$cur_path/data"
        mkdir -p ${cur_path}/data/jenkins_home
        chown -R 1000:1000 ${cur_path}/data/jenkins_home
    fi

    echo "end to build environment in ${cur_path}"
}

function clean_container() 
{
    echo "begin to clear ${full_name}"

    cnt=`docker ps -a | grep ${full_name} | wc -l`

    if [ "$cnt"x != "0"x ]; then
      docker stop ${full_name}
      docker rm $(docker ps -q -f status=exited)
    fi

    echo "end to clear ${full_name}"
}

function build_jenkins()
{
    echo "begin to build ${full_name}"

    CONTAINER_NAME=${full_name}
    MOUNT_PATH=${cur_path}/data/jenkins_home/
    echo "before $MOUNT_PATH"
    MOUNT_PATH=`echo ${MOUNT_PATH//\//\\\/}`
    echo "after $MOUNT_PATH"

    sed -i "s/\$CONTAINER_NAME/${CONTAINER_NAME}/g"   ./docker-compose.yml
    sed -i "s/\$MOUNT_PATH/${MOUNT_PATH}/g"           ./docker-compose.yml
    #sed -i 's#\$MOUNT_PATH#${MOUNT_PATH}#g'   ./docker-compose.yml
    # 带'/',需要进行转义
    #sed -i "s/\$MOUNT_PATH/${MOUNT_PATH}/g"           ./docker-compose.yml

    docker-compose up -d

    echo "end to build ${full_name}"
}

function MAIN()
{
    echo "begin to MAIN"

    build_environment
    clean_container
    build_jenkins

    echo "end to MAIN"
}

MAIN
