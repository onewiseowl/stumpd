#!/bin/bash

if [[ $1 =~ 20[0-9][0-9] ]]
then

  YEAR=$1

else
  echo doesnt work >&2
  YEAR=$(date +%Y);
fi
i=0;

while [ $i -le 364 ]
do
echo '
TRUNCATE TABLE `documents_'$YEAR'`.`'$(date -d "01/01/$YEAR $i days" +%Y%m%d)'`;'

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
