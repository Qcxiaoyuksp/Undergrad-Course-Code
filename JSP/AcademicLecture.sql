-- MySQL dump 10.13  Distrib 8.0.35, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: academiclecture
-- ------------------------------------------------------
-- Server version	8.0.35

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `lecture`
--

DROP TABLE IF EXISTS `lecture`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `lecture` (
  `id` int NOT NULL AUTO_INCREMENT,
  `title` varchar(50) DEFAULT NULL,
  `summary` text,
  `department_undertake` varchar(50) DEFAULT NULL,
  `speaker` varchar(50) DEFAULT NULL,
  `department_speaker` varchar(20) DEFAULT NULL,
  `title_speaker` varchar(50) DEFAULT NULL,
  `inviter` varchar(50) DEFAULT NULL,
  `number_participants` varchar(50) DEFAULT NULL,
  `data_lecture` varchar(20) DEFAULT NULL,
  `time` varchar(20) DEFAULT NULL,
  `address` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `lecture`
--

LOCK TABLES `lecture` WRITE;
/*!40000 ALTER TABLE `lecture` DISABLE KEYS */;
INSERT INTO `lecture` VALUES (1,'智能机器人操作系统核心技术','分类众多的智能机器人是智能时代的重要体现与重点发展，对未来社会与经济具有深远影响；智能机器人操作系统（iROS）是智能机器人的核心软件平台，是软件定义智能机器人的具体体现；在简介iROS发展历程与现状基础上;重点论述iROS的嵌入式实时资源管理、OODA行为管理、丰富应用开发支持等功能与结构及其技术挑战；给出云边端融合结构、集群自主协同、人与智能机器人共融以及具身智能支持等iROS发展趋势；结合承担的国家项目，介绍所在团队智能机器人操作系统研发实践。','计算机科学与工程学院','周兴社','西北工业大学计算机学院','教授','陈志列','300','2023-10-26','15:00:00','实验楼8楼'),(2,'培育创新精神，提升创业能力','孟繁宇，沈阳云创未来科技有限公司总经理。2002年获东北大学计算机科学与技术专业学士学位，2005年获沈阳建筑大学计算机科学与技术硕士学位，当前从事教育信息化相关工作。\n\n','计算机科学与工程学院','孟繁宇','沈阳云创未来科技有限公司','总经理','孙焕良','100','2023-09-21','10:30:00','C1-205'),(3,'66666666',NULL,'33','33','3333','教授',NULL,NULL,'2023-12-17','01:04','33333'),(4,'计算机就业指导',NULL,'计算机','许老师','计算机','教授',NULL,NULL,'2023-12-02','20:13','丙一'),(5,'JSP1',NULL,'计算机','许老师','计算机学院','教授',NULL,NULL,'2023-12-11','08:54','丙1403');
/*!40000 ALTER TABLE `lecture` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user`
--

DROP TABLE IF EXISTS `user`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `user` (
  `id` int NOT NULL AUTO_INCREMENT,
  `userID` varchar(20) DEFAULT NULL,
  `password` varchar(20) DEFAULT NULL,
  `name` varchar(50) DEFAULT NULL,
  `gender` varchar(20) DEFAULT NULL,
  `birth_date` varchar(20) DEFAULT NULL,
  `nation` varchar(20) DEFAULT NULL,
  `department` varchar(50) DEFAULT NULL,
  `address` varchar(50) DEFAULT NULL,
  `phone_work` varchar(20) DEFAULT NULL,
  `phone_home` varchar(20) DEFAULT NULL,
  `email` varchar(20) DEFAULT NULL,
  `education` varchar(20) DEFAULT NULL,
  `degree` varchar(20) DEFAULT NULL,
  `title` varchar(20) DEFAULT NULL,
  `major` varchar(20) DEFAULT NULL,
  `graduation_university` varchar(20) DEFAULT NULL,
  `graduation_date` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user`
--

LOCK TABLES `user` WRITE;
/*!40000 ALTER TABLE `user` DISABLE KEYS */;
INSERT INTO `user` VALUES (1,'2104230414','2104230414','张清晨','男','2004-02-16','汉族','计算机科学与工程学院','辽宁省沈阳市浑南区','15139497674','15139497674','1904977351@qq.com','大学本科','学士学位','学生','计算机科学与技术','沈阳建筑大学','2025-06-01'),(2,'2103200423','2103200423','徐心雨','女','2003-12-12','汉族','计算机科学与工程学院','辽宁省沈阳市浑南区浑南中路25号','15759991508','15759991508','2692592495@qq.com','大学本科','学士学位','助教','计算机科学与技术','沈阳建筑大学','2025-06-01'),(3,'admin','admin','1','男','2023-12-11','汉族','1','1','1','1','1','研究生','学士学位','教授','1','1','2023-12-11'),(4,'1','1','张清晨','男','2023-12-11','汉族','1','1','1','1','1','研究生','学士学位','教授','1','1','2023-12-11'),(5,'1','1','1','男','2023-12-11','汉族','1','1','1','1','1','研究生','学士学位','教授','1','1','2023-12-12');
/*!40000 ALTER TABLE `user` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-12-20 22:02:14
