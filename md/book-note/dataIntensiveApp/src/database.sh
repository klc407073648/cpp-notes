#!/bin/bash

function db_set()
{
    echo "$1,$2" >> database
}

function db_get()
{
    grep "^$1," database | sed -e "s/^$1,//" |tail -n 1
}

function testfun()
{
  db_set "name" "Jason"
  db_set "age" "16"
  db_get "name"
  db_set "name" "Helen"
  db_get "name"
  db_get "age"
}

testfun