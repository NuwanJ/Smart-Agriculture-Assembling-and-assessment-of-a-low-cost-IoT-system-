-- phpMyAdmin SQL Dump
-- version 4.6.6deb5ubuntu0.5
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Generation Time: Nov 16, 2022 at 07:03 PM
-- Server version: 5.7.40-0ubuntu0.18.04.1
-- PHP Version: 7.2.24-0ubuntu0.18.04.15

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `agri_iot`
--

-- --------------------------------------------------------

--
-- Table structure for table `agri_data`
--

CREATE TABLE `agri_data` (
  `id` int(11) NOT NULL,
  `dKey` text NOT NULL,
  `dValue` text NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `agri_data`
--

INSERT INTO `agri_data` (`id`, `dKey`, `dValue`) VALUES
(1, 'serverIP', '127.0.0.1'),
(4, 'apiEndpoint', 'http://localhost:8080/v1/'),
(5, 'serviceMessage', ''),
(6, 'seqNo', '0'),
(7, 'apiPHPEndpoint', 'http://example.com/dashboard/api/');

-- --------------------------------------------------------

--
-- Table structure for table `agri_services`
--

CREATE TABLE `agri_services` (
  `id` int(6) NOT NULL,
  `serviceCode` varchar(16) NOT NULL,
  `serviceName` text NOT NULL,
  `serviceIcon` text NOT NULL,
  `serviceURL` text NOT NULL,
  `servicePermission` int(3) NOT NULL,
  `serviceData` text NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `agri_services`
--

INSERT INTO `agri_services` (`id`, `serviceCode`, `serviceName`, `serviceIcon`, `serviceURL`, `servicePermission`, `serviceData`) VALUES
(1001, 'admin', 'Admin', '', './', 2, ''),
(1002, 'dev', 'Developer', '', './', 2, ''),
(1003, 'betaTest', 'Beta Tester', '', './', 1, ''),
(1000, 'sudo', 'Super Admin', '', './', 2, ''),
(1007, 'service', 'Service Manager', '', './', 2, '');

-- --------------------------------------------------------

--
-- Table structure for table `agri_users`
--

CREATE TABLE `agri_users` (
  `id` int(6) NOT NULL,
  `email` text NOT NULL,
  `password` varchar(255) NOT NULL,
  `userStatus` enum('ACTIVE','PENDING','REJECTED') NOT NULL DEFAULT 'PENDING',
  `honorific` int(1) NOT NULL,
  `firstName` text NOT NULL,
  `lastName` text NOT NULL,
  `role` int(1) NOT NULL,
  `loginType` int(1) NOT NULL,
  `lastAccess` datetime NOT NULL,
  `imageURL` text,
  `profilePage` int(1) NOT NULL DEFAULT '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `agri_user_services`
--

CREATE TABLE `agri_user_services` (
  `id` int(8) NOT NULL,
  `userId` int(5) NOT NULL,
  `serviceCode` varchar(16) NOT NULL,
  `enabledOn` date NOT NULL,
  `enabledBy` int(5) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `agri_user_services`
--

-- INSERT INTO `agri_user_services` (`id`, `userId`, `serviceCode`, `enabledOn`, `enabledBy`) VALUES

-- --------------------------------------------------------

--
-- Table structure for table `controller_history`
--

CREATE TABLE `controller_history` (
  `id` int(11) NOT NULL,
  `siteId` int(5) NOT NULL,
  `parameter` enum('BLOWER','MIST','WATER','CURTAIN') NOT NULL,
  `value` int(2) NOT NULL,
  `created_at` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `sensor_data`
--

CREATE TABLE `sensor_data` (
  `id` int(9) UNSIGNED NOT NULL,
  `siteId` int(4) UNSIGNED DEFAULT NULL,
  `x` int(3) UNSIGNED DEFAULT NULL,
  `y` int(3) UNSIGNED DEFAULT NULL,
  `state` enum('ACTIVE','DEACTIVE','NULL') DEFAULT NULL,
  `firmwareVersion` int(2) UNSIGNED DEFAULT NULL,
  `notes` text NOT NULL,
  `createdAt` datetime NOT NULL,
  `lastUpdate` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `sensor_data`
--

-- INSERT INTO `sensor_data` (`id`, `siteId`, `x`, `y`, `state`, `firmwareVersion`, `notes`, `createdAt`, `lastUpdate`) VALUES

-- --------------------------------------------------------

--
-- Table structure for table `sensor_log`
--

CREATE TABLE `sensor_log` (
  `id` int(16) UNSIGNED NOT NULL,
  `sensorId` int(5) UNSIGNED DEFAULT NULL,
  `seqNo` int(4) NOT NULL,
  `temp1` float DEFAULT NULL,
  `temp2` float DEFAULT NULL,
  `temp3` float DEFAULT NULL,
  `humidity1` float DEFAULT NULL,
  `humidity2` float DEFAULT NULL,
  `humidity3` float DEFAULT NULL,
  `light` float DEFAULT NULL,
  `soilMoisture` float DEFAULT NULL,
  `version` int(2) UNSIGNED DEFAULT NULL,
  `createdAt` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `sensor_log_0`
--

CREATE TABLE `sensor_log_0` (
  `id` int(16) UNSIGNED NOT NULL,
  `sensorId` int(5) UNSIGNED DEFAULT NULL,
  `seqNo` int(4) NOT NULL,
  `temp1` float DEFAULT NULL,
  `temp2` float DEFAULT NULL,
  `temp3` float DEFAULT NULL,
  `humidity1` float DEFAULT NULL,
  `humidity2` float DEFAULT NULL,
  `humidity3` float DEFAULT NULL,
  `light` float DEFAULT NULL,
  `soilMoisture` float DEFAULT NULL,
  `version` int(2) UNSIGNED DEFAULT NULL,
  `createdAt` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `sensor_log_t1`
--

CREATE TABLE `sensor_log_t1` (
  `id` int(10) UNSIGNED NOT NULL,
  `sensorId` int(5) UNSIGNED DEFAULT NULL,
  `seqNo` int(4) NOT NULL,
  `temp1` float DEFAULT NULL,
  `temp2` float DEFAULT NULL,
  `temp3` float DEFAULT NULL,
  `humidity1` float DEFAULT NULL,
  `humidity2` float DEFAULT NULL,
  `humidity3` float DEFAULT NULL,
  `light` float DEFAULT NULL,
  `soilMoisture` float DEFAULT NULL,
  `version` int(2) UNSIGNED DEFAULT NULL,
  `createdAt` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `setvalues`
--

CREATE TABLE `setvalues` (
  `id` int(5) UNSIGNED NOT NULL,
  `siteId` int(5) NOT NULL,
  `parameter` text NOT NULL,
  `value` float NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `setvalues`
--

INSERT INTO `setvalues` (`id`, `siteId`, `parameter`, `value`) VALUES
(1000, 1000, 'fanTempLow', 30),
(1001, 1000, 'fanTempHigh', 32),
(1002, 1000, 'mistTempHigh', 34),
(1003, 1000, 'mistTempLow', 33),
(1004, 1004, 'fanTempHigh', 30),
(1005, 1004, 'fanTempLow', 28),
(1006, 1004, 'mistTempHigh', 32),
(1007, 1004, 'mistTempLow', 28);

-- --------------------------------------------------------

--
-- Table structure for table `set_values`
--

CREATE TABLE `set_values` (
  `siteId` int(5) UNSIGNED NOT NULL,
  `temp` float DEFAULT NULL,
  `humidity` float DEFAULT NULL,
  `light` float DEFAULT NULL,
  `version` int(2) UNSIGNED DEFAULT NULL,
  `createdAt` datetime NOT NULL,
  `lastUpdate` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `sites`
--

CREATE TABLE `sites` (
  `id` int(4) UNSIGNED NOT NULL,
  `title` text,
  `status` enum('ACTIVE','DEACTIVE','TEST') DEFAULT NULL,
  `controllerId` int(5) NOT NULL,
  `width` int(4) UNSIGNED DEFAULT NULL,
  `length` int(4) UNSIGNED DEFAULT NULL,
  `notes` text,
  `createdAt` datetime NOT NULL,
  `lastUpdate` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `sites`
--

-- INSERT INTO `sites` (`id`, `title`, `status`, `controllerId`, `width`, `length`, `notes`, `createdAt`, `lastUpdate`) VALUES

-- --------------------------------------------------------

--
-- Table structure for table `system_log`
--

CREATE TABLE `system_log` (
  `id` int(11) UNSIGNED NOT NULL,
  `type` enum('CONTROLLER','SENSOR','WEB','OTHER') DEFAULT NULL,
  `priority` int(2) UNSIGNED DEFAULT NULL,
  `message` text,
  `createdAt` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `agri_data`
--
ALTER TABLE `agri_data`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `agri_services`
--
ALTER TABLE `agri_services`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `agri_users`
--
ALTER TABLE `agri_users`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `agri_user_services`
--
ALTER TABLE `agri_user_services`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `controller_history`
--
ALTER TABLE `controller_history`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `sensor_data`
--
ALTER TABLE `sensor_data`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `sensor_log`
--
ALTER TABLE `sensor_log`
  ADD PRIMARY KEY (`id`),
  ADD KEY `idx_seqNo` (`seqNo`);

--
-- Indexes for table `sensor_log_0`
--
ALTER TABLE `sensor_log_0`
  ADD PRIMARY KEY (`id`),
  ADD KEY `idx_seqNo` (`seqNo`);

--
-- Indexes for table `sensor_log_t1`
--
ALTER TABLE `sensor_log_t1`
  ADD PRIMARY KEY (`id`),
  ADD KEY `idx_seqNo` (`seqNo`);

--
-- Indexes for table `setvalues`
--
ALTER TABLE `setvalues`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `set_values`
--
ALTER TABLE `set_values`
  ADD PRIMARY KEY (`siteId`);

--
-- Indexes for table `sites`
--
ALTER TABLE `sites`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `system_log`
--
ALTER TABLE `system_log`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `agri_data`
--
ALTER TABLE `agri_data`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;
--
-- AUTO_INCREMENT for table `agri_services`
--
ALTER TABLE `agri_services`
  MODIFY `id` int(6) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=1008;
--
-- AUTO_INCREMENT for table `agri_users`
--
ALTER TABLE `agri_users`
  MODIFY `id` int(6) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=100021;
--
-- AUTO_INCREMENT for table `agri_user_services`
--
ALTER TABLE `agri_user_services`
  MODIFY `id` int(8) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=10050;
--
-- AUTO_INCREMENT for table `controller_history`
--
ALTER TABLE `controller_history`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=14431;
--
-- AUTO_INCREMENT for table `sensor_data`
--
ALTER TABLE `sensor_data`
  MODIFY `id` int(9) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=10041;
--
-- AUTO_INCREMENT for table `sensor_log`
--
ALTER TABLE `sensor_log`
  MODIFY `id` int(16) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=19682553;
--
-- AUTO_INCREMENT for table `sensor_log_0`
--
ALTER TABLE `sensor_log_0`
  MODIFY `id` int(16) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=18136426;
--
-- AUTO_INCREMENT for table `sensor_log_t1`
--
ALTER TABLE `sensor_log_t1`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=9133450;
--
-- AUTO_INCREMENT for table `setvalues`
--
ALTER TABLE `setvalues`
  MODIFY `id` int(5) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=1008;
--
-- AUTO_INCREMENT for table `system_log`
--
ALTER TABLE `system_log`
  MODIFY `id` int(11) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=1070;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
