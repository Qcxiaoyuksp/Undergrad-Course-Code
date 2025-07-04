/*
 Navicat Premium Data Transfer

 Source Server         : jeecg-boot
 Source Server Type    : MySQL
 Source Server Version : 80017
 Source Host           : 172.16.1.121:3306
 Source Schema         : jeecg-boot

 Target Server Type    : MySQL
 Target Server Version : 80017
 File Encoding         : 65001

 Date: 16/10/2023 15:59:15
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for  flighttriprecordinfo
-- ----------------------------
DROP TABLE IF EXISTS ` flighttriprecordinfo`;
CREATE TABLE ` flighttriprecordinfo`  (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `tripId` bigint(255) NULL DEFAULT NULL COMMENT '携程最终行程id',
  `sectorId` int(10) NULL DEFAULT NULL COMMENT '航程',
  `passengerName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '乘机人姓名',
  `recordStatus` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '行程状态（R退票 S成功 C删除）',
  `validFlag` bigint(255) NULL DEFAULT NULL COMMENT '最终行程是否有效',
  `flightClass` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '航班类型(经济舱和商务舱、包机航班、联程航班、直达航班、中转航班)',
  `flight` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '航班号',
  `classGrade` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '舱等(经济舱、商务舱、头等舱)',
  `subClass` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '子舱位',
  `takeOffTime` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '起飞时间',
  `arrivalTime` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '到达时间',
  `dCity` int(10) NULL DEFAULT NULL COMMENT '出发城市ID',
  `departureDistrictCode` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '出发城市行政编码',
  `dPort` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '出发机场三字码',
  `dPortBuilding` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '出发航站楼',
  `dPortBuildingId` int(10) NULL DEFAULT NULL COMMENT '出发航站楼ID',
  `aCity` int(255) NULL DEFAULT NULL COMMENT '到达城市ID',
  `arrivalDistrictCode` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '到达城市行政编码',
  `aPort` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '到达机场三字码',
  `aPortBuilding` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '到达航站楼',
  `aPortBuildingId` int(10) NULL DEFAULT NULL COMMENT '到达航站楼ID',
  `openTranFlag` int(10) NULL DEFAULT NULL COMMENT '是否open程',
  `printPrice` decimal(16, 2) NULL DEFAULT NULL COMMENT '票面价',
  `oil` decimal(16, 0) NULL DEFAULT NULL COMMENT '燃油费',
  `tax` decimal(16, 0) NULL DEFAULT NULL COMMENT '民航基金/税',
  `recordNo` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '记录编号',
  `airlineRecordNo` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '航司大记录编号',
  `sharedFlag` int(10) NULL DEFAULT NULL COMMENT '是否共享航班',
  `sharedFlight` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '共享航班号',
  `surfaceFlag` int(10) NULL DEFAULT NULL COMMENT '是否地面程',
  `airLineCode` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '航司代码',
  `ticketNo` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '票号（以后改签退签凭证）',
  `ticketNoStatus` int(255) NULL DEFAULT NULL COMMENT '票号状态(未使用、使用中、取消、转让、改签、退票)',
  `dCityName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '出发城市名称',
  `dPortName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '出发机场名称',
  `aCityName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '到达城市名称',
  `aPortName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '到达机场名称',
  `standardGeoInfo` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '标准地理信息',
  `classTypeName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '舱等名',
  `airlineName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '航司名',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 2 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of  flighttriprecordinfo
-- ----------------------------
INSERT INTO ` flighttriprecordinfo` VALUES (1, 1, NULL, '张三', 'S', 1, '国内航班', NULL, '经济舱', 'Y', '2023-10-8', '2023-10-9', 1, NULL, NULL, NULL, NULL, 2, NULL, NULL, NULL, NULL, NULL, 900.00, 50, 0, NULL, NULL, NULL, NULL, NULL, NULL, 'QR1234567890', 1, '长春', '长春龙嘉国际机场', '北京', '北京大兴国际机场', NULL, NULL, '中国国际航空公司');

SET FOREIGN_KEY_CHECKS = 1;
