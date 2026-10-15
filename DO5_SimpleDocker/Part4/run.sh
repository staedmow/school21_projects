#!/bin/bash

gcc -o my_server my_server.c -lfcgi
spawn-fcgi -p 8080 ./my_server
service nginx start
/bin/bash