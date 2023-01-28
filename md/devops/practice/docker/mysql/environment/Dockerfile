FROM mysql:5.7
 
#docker-compose.yml的构建参数
ARG MYSQL_ROOT_PASSWORD
ARG MYSQL_USER
ARG MYSQL_PASSWORD
ARG MYSQL_DATABASE
ARG EUREKA_SERVICE_HOST

#设置免密登录
ENV MYSQL_ALLOW_EMPTY_PASSWORD yes

#创建文件目录
RUN mkdir -p /home/mysql   \
    &&  mkdir -p /mysql/sql/docker_mysql   \
    &&  mkdir -p /mysql/sql/student   \
    &&  mkdir -p /mysql/sql/privileges \
    &&  mkdir -p /mysql/sql/apollo      \
    &&  mkdir -p /mysql/sql/usercenter
 
#将所需文件放到容器中
COPY setup.sh /mysql/setup.sh

COPY ./sql/docker_mysql/create_table.sql    /mysql/sql/docker_mysql
COPY ./sql/docker_mysql/init_data.sql       /mysql/sql/docker_mysql
COPY ./sql/docker_mysql/update_data.sql     /mysql/sql/docker_mysql

COPY ./sql/student/create_table.sql         /mysql/sql/student
COPY ./sql/student/init_data.sql            /mysql/sql/student
COPY ./sql/student/update_data.sql          /mysql/sql/student

COPY ./sql/privileges/privileges.sql        /mysql/sql/privileges

COPY ./sql/apollo/apolloconfigdb.sql        /mysql/sql/apollo
COPY ./sql/apollo/apolloportaldb.sql        /mysql/sql/apollo

COPY ./sql/usercenter/create_table.sql         /mysql/sql/usercenter
COPY ./sql/usercenter/init_data.sql          /mysql/sql/usercenter

RUN sed -i "s/\$MYSQL_ROOT_PASSWORD/$MYSQL_ROOT_PASSWORD/g"         /mysql/sql/privileges/privileges.sql   \
    &&  sed -i "s/\$MYSQL_USER/$MYSQL_USER/g"                       /mysql/sql/privileges/privileges.sql   \ 
    &&  sed -i "s/\$MYSQL_PASSWORD/$MYSQL_PASSWORD/g"               /mysql/sql/privileges/privileges.sql   \ 
    &&  sed -i "s/\$MYSQL_DATABASE/$MYSQL_DATABASE/g"               /mysql/sql/privileges/privileges.sql    \
    &&  sed -i "s/\$EUREKA_SERVICE_HOST/$EUREKA_SERVICE_HOST/g"     /mysql/sql/apollo/apolloconfigdb.sql    

#设置容器启动时执行的命令
CMD ["sh", "/mysql/setup.sh"]