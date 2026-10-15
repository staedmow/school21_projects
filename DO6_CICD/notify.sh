#!/bin/bash


TOKEN="7813048483:AAHv8tc51oqD9p0AdMytrzP8R4my1PzJ2SM"
ID="1226030133"
URL="https://api.telegram.org/bot$TOKEN/sendMessage"
TEXT="$CI_JOB_NAME $CI_JOB_STATUS"

curl -s -d "chat_id=$ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null
