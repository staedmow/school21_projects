#!/bin/bash

gcc -o my_server my_server.c -lfcgi
service nginx start
nginx -s reload
spawn-fcgi -p 8080 -n my_server