#!/bin/bash

echo '
CREATE DATABASE IF NOT EXISTS `documents_2012`;
CREATE TABLE IF NOT EXISTS `documents_2012`.`20120709` (
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
) ENGINE=MyISAM DEFAULT CHARSET=latin1;'
