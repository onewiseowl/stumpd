#!/bin/bash

if [[ $1 =~ 20[0-9][0-9] ]]
then

  YEAR=$1

else
  echo doesnt work >&2
  YEAR=$(date +%Y);
fi
i=0;

echo '
CREATE DATABASE IF NOT EXISTS `stump`;
CREATE TABLE IF NOT EXISTS `stump`.`filters` (
  `id` int(10) unsigned not null auto_increment,
  `alias` varchar(32) default null,
  `filter` text,
  INDEX `id_index` (`id`),
  INDEX `alias_index` (`alias`))
  ENGINE=InnoDB DEFAULT CHARSET=latin1;'

echo "CREATE DATABASE IF NOT EXISTS documents_$YEAR;"
while [ $i -le 364 ]
do
echo '
DROP TABLE IF EXISTS `documents_'$YEAR'`.`'$(date -d "01/01/$YEAR $i days" +%Y%m%d)'`;
CREATE TABLE `documents_'$YEAR'`.`'$(date -d "01/01/$YEAR $i days" +%Y%m%d)'` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT PRIMARY KEY,
  `date` datetime DEFAULT NULL,
  `host` varchar(64) DEFAULT NULL,
  `input` varchar(256) DEFAULT NULL,
  `content` text,
  KEY `id_index` (`id`),
  KEY `date_index` (`date`),
  KEY `host_index` (`host`(10)),
  KEY `input_index` (`input`(40))
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
CREATE FULLTEXT INDEX `content_index` on `documents_'$YEAR'`.`'$(date -d "01/01/$YEAR $i days" +%Y%m%d)'` (`content`);
'

#echo '
#CREATE TABLE `documents_'$YEAR'`.`'$(date -d "01/01/$YEAR $i days" +%Y%m%d)'` (
#  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
#  `date` datetime DEFAULT NULL,
#  `host` varchar(64) DEFAULT NULL,
#  `source` varchar(256) DEFAULT NULL,
#  `content` text,
#  KEY `id` (`id`),
#  KEY `date_index` (`date`),
#  KEY `host_index` (`host`(10)),
#  KEY `source_index` (`source`(40)),
#  FULLTEXT KEY `content` (`content`)
#) ENGINE=InnoDB DEFAULT CHARSET=latin1;'

  ((i++))
done
