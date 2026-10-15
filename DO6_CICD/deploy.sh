#!/bin/bash

cd src/cat && make && cd ../grep && make && cd ../..
if scp src/cat/s21_cat src/grep/s21_grep staedmow@10.0.0.2:/usr/local/bin; then
	echo "artifacts copied successfully!"
else
	echo "artifacts wasn't copied!!!"
	exit 1
fi
