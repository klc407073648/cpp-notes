#!/bin/bash

echo '----pull codes----'

cd /opt/tech-arch-doc/

git pull

echo '----build docs----'

vuepress build

echo '---copy to www----'

cp -rf docs/. /usr/share/nginx/html/

echo '---Nginx reload---'
nginx -s reload


