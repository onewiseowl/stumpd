#!/bin/bash

if [ ! -z $DEBUG_MODE ]
then
  set -x
fi

if [ -z "${STUMP_USER}" ]
then
  STUMP_USER='admin'
fi

if [ -z "${STUMP_PASS}" ]
then
  STUMP_PASS='admin'
fi

if [ -z "${STUMP_URI}" ]
then
  STUMP_URI="http://127.0.0.1:8081/api"
fi

COOKIE_JAR="/tmp/stump-$$.cookie"

INPUT_FILE="${1}"

function LOGCMD
{
  RETURN_CODE=$?
  read LOG_LINE
  echo "$(date '+%b %d %H:%m:%S') : stump_agent : $$ : ${LOG_LINE}" | tee -a "${LOG_FILE}"
  return ${RETURN_CODE}
}

curl -X GET -H 'x-stump-action: login' -u "${STUMP_USER}:${STUMP_PASS}" --cookie-jar "${COOKIE_JAR}" "${STUMP_URI}"

if [ $? -eq 0 ]
then
  echo "Loading file ${INPUT_FILE}" | ${LOGCMD}
else
  echo "CuRL error...exiting" | ${LOGCMD} 
  exit 1
fi

while read INPUT_LINE
do
  #INPUT_DATE=$(date --date $(echo ${INPUT_LINE} | awk -F '{$1" "$2" "$3}') +%s)
  INPUT_DATE=$(date --date "$(echo ${INPUT_LINE} | awk '{print $1" "$2" "$3}'
)" +%s)
  #echo $INPUT_DATE
  curl -X POST -H 'x-stump-action: insert' --data-urlencode 'documents=[{"date":"'${INPUT_DATE}'","host":"'$(hostname -f)'","input":"'${INPUT_FILE}'","content":"'$(echo -n ${INPUT_LINE} | openssl enc -e -base64 -A)'"}]' -u "${STUMP_USER}:${STUMP_PASS}" "${STUMP_URI}"
done < <(tail -n $(wc -c ${INPUT_FILE} | awk '{print $1}') -f ${INPUT_FILE})

