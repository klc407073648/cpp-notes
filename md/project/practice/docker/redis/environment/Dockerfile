FROM redis:6.2.0

#docker-compose.yml的构建参数
ARG REDIS_PORT
ARG REDIS_PASSWORD

COPY ./conf/redis-simple.conf /usr/local/etc/redis/redis.conf

RUN chmod 777  /usr/local/etc/redis/redis.conf

RUN sed -i "s/\$REDIS_PORT/$REDIS_PORT/g"                     /usr/local/etc/redis/redis.conf
RUN sed -i "s/\$REDIS_PASSWORD/$REDIS_PASSWORD/g"             /usr/local/etc/redis/redis.conf

CMD [ "redis-server", "/usr/local/etc/redis/redis.conf" ]