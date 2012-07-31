#!/bin/bash

if [[ $1 =~ 20[0-9][0-9] ]]
then

  echo $1

else
  echo doesnt work
fi
YEAR=$(date +%Y);

i=0;

echo '
CREATE DATABASE IF NOT EXISTS `stump`;
CREATE TABLE IF NOT EXISTS `stump`.`filters` (
  `id` int(10) unsigned not null auto_increment,
  `alias` varchar(32) default null,
  `filter` text,
  KEY `id` (`id`),
  KEY `alias_index` (`alias`))
  ENGINE=InnoDB DEFAULT CHARSET=latin1;' | mysql -uroot

while [ $i -lt 365 ]
do

echo '
CREATE DATABASE IF NOT EXISTS `documents_'$YEAR'`;
CREATE TABLE IF NOT EXISTS `documents_'$YEAR'`.`'$(date -d "01/01/$YEAR $i days" +%Y%m%d)'` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `date` datetime DEFAULT NULL,
  `host` varchar(64) DEFAULT NULL,
  `source` varchar(256) DEFAULT NULL,
  `content` text,
  KEY `id` (`id`),
  KEY `date_index` (`date`),
  KEY `host_index` (`host`(10)),
  KEY `source_index` (`source`(40)),
  FULLTEXT KEY `content_index` (`content`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;'|mysql -uroot

  ((i++))
done
