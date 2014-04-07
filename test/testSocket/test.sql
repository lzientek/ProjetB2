-- phpMyAdmin SQL Dump
-- version 3.4.11.1deb2
-- http://www.phpmyadmin.net
--
-- Client: localhost
-- Généré le: Dim 02 Mars 2014 à 18:45
-- Version du serveur: 5.5.35
-- Version de PHP: 5.4.4-14+deb7u7

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Base de données: `test`
--
CREATE DATABASE `test` DEFAULT CHARACTER SET ascii COLLATE ascii_general_ci;
USE `test`;

-- --------------------------------------------------------

--
-- Structure de la table `files`
--

CREATE TABLE IF NOT EXISTS `files` (
  `titre` varchar(256) CHARACTER SET ascii COLLATE ascii_bin NOT NULL COMMENT 'titre voir nom du fichier',
  `url` varchar(512) CHARACTER SET ascii NOT NULL,
  `type` int(1) NOT NULL DEFAULT '0' COMMENT 'type du fichier bin txt ou html...',
  `txt` longtext CHARACTER SET ascii NOT NULL COMMENT 'text complet du fichier',
  `motImportant` text CHARACTER SET ascii COLLATE ascii_bin NOT NULL COMMENT 'mot important généré par l''algo',
  `lastcrawl` int(11) NOT NULL COMMENT 'timestamp du dernier crawl',
  UNIQUE KEY `url` (`url`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;


/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
