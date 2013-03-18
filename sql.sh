#!/bin/bash

#if [[ $1 =~ 20[0-9][0-9] ]]
#then
#
#  echo $1 >&2
#
#else
#  echo doesnt work >&2
#fi
#YEAR=$(date +%Y);
if [ ! -z "${1}" ]
then
  if [[ $1 =~ 20[0-9][0-9] ]]
  then
    YEAR="${1}"
  else
    echo "Bad year format '${1}'...use 20xx, ie $(date +%Y)" >&2
    exit 1
  fi
else
  YEAR="$(date +%Y)"
fi

if [ ! -z "${2}" ]
then
  DB_ENGINE="${2}"
else
  DB_ENGINE="MyISAM"
fi

i=0;

echo '
CREATE DATABASE IF NOT EXISTS `stump`;
CREATE TABLE IF NOT EXISTS `stump`.`hosts` (
  `id` int(10) unsigned not null auto_increment,
  `hostname` varchar(64) default null,
  KEY `id` (`id`))
  ENGINE='${DB_ENGINE}' DEFAULT CHARSET=latin1;
CREATE TABLE IF NOT EXISTS `stump`.`filters` (
  `id` int(10) unsigned not null auto_increment,
  `alias` varchar(32) default null,
  `filter` text,
  KEY `id` (`id`),
  KEY `alias_index` (`alias`))
  ENGINE='${DB_ENGINE}' DEFAULT CHARSET=latin1;
CREATE TABLE IF NOT EXISTS `stump`.`inputs` (
  `id` int(10) unsigned not null auto_increment,
  `alias` varchar(32) default null,
  `input` text,
  KEY `id` (`id`))
  ENGINE='${DB_ENGINE}' DEFAULT CHARSET=latin1;'
#
echo "CREATE DATABASE IF NOT EXISTS documents_$YEAR;"
while [ $i -le 364 ]
do

echo '
DROP TABLE IF EXISTS `documents_'$YEAR'`.`'$(date -d "01/01/$YEAR $i days" +%Y%m%d)'`;
CREATE TABLE IF NOT EXISTS `documents_'$YEAR'`.`'$(date -d "01/01/$YEAR $i days" +%Y%m%d)'` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `date` datetime DEFAULT NULL,
  `host` varchar(64) DEFAULT NULL,
  `input` varchar(256) DEFAULT NULL,
  `content` text,
  KEY `id` (`id`),
  KEY `date_index` (`date`),
  KEY `host_index` (`host`(10)),
  KEY `input_index` (`input`(40)),
  FULLTEXT KEY `content_index` (`content`)
) ENGINE='${DB_ENGINE}' DEFAULT CHARSET=latin1;'

  ((i++))
done
