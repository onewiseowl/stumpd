#!/bin/bash

echo -n "Username: "
read HT_USERNAME
echo -en "\nPassword: "
read HT_PASSWORD

echo ${HT_USERNAME}:$(echo -n "${HT_PASSWORD}"|md5sum|awk '{print $1}')|openssl enc -e -base64 -A >> /tmp/stumpd.htpasswd
exit 0
