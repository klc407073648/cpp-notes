#/bin/bash
project_name='stibel'
EUREKA_SERVICE_HOST='1.1.1.1'

function modify_env_var() 
{
    echo "begin to modify_env_var"

    sed -i "s/\$EUREKA_SERVICE_HOST/${EUREKA_SERVICE_HOST}/g" ./environment/mysql.env

    echo "end to modify_env_var"
}

function build_docker_project()
{
    docker_name=$1
    docker_name_tar=$2
    echo "begin to clear environment ${project_name}_${docker_name}"

    docker stop $(docker ps |grep ${project_name}_${docker_name}_0 |awk '{print $1}')
    docker rm $(docker ps -q -f status=exited)
    docker rmi ${project_name}_${docker_name}:${docker_name_tar}

    echo "end to clear environment ${project_name}_${docker_name}"

    echo "begin to build ${project_name}_${docker_name}"

    cp ./environment/${docker_name}.env .env

    docker-compose up -d

    echo "end to build ${project_name}_${docker_name}"
}

modify_env_var
build_docker_project "mysql" "v1.0"