--
-- Table `local_tbl_lusin`
--

CREATE TABLE IF NOT EXISTS `local_tbl_lusin` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `tr_amount` double NOT NULL DEFAULT '0',
  `client_start_ts` bigint(20) NOT NULL,
  `timestamp` bigint(20) NOT NULL,
  `srcip` varchar(16) DEFAULT NULL,
  `senderip` varchar(16) DEFAULT NULL,
  `ident` varchar(16) DEFAULT NULL,
  `rules` varchar(255) DEFAULT NULL,
  `description` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=0 ;
