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

 Date: 16/10/2023 15:10:54
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for flightorderchangeinfo
-- ----------------------------
DROP TABLE IF EXISTS `flightorderchangeinfo`;
CREATE TABLE `flightorderchangeinfo`  (
  `sequence` int(10) NOT NULL COMMENT '航程',
  `passengerName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '出行人姓名',
  `createTime` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '航变订单生成时间yyyy-MM-dd HH:mm:ss',
  `finishTime` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '航变订单完成时间yyyy-MM-dd HH:mm:ss',
  `flightChangeReason` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '航变原因',
  `protectDepartureDate` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '航变后出发时间yyyy-MM-dd HH:mm:ss',
  `protectArrivalDate` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '航变后到达时间yyyy-MM-dd HH:mm:ss',
  `protectClass` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '航变后舱等',
  `protectSubClass` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '航变后舱位',
  `protectFlight` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '航变后航班号',
  `ticketNo` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '票号（不含三字码）',
  `airline` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '航变后航司二字码',
  `protectDepartureAirPortCode` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '出发机场三字码',
  `protectArrivalAirPortCode` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '到达机场三字码',
  `protectClassDesc` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '航变后舱等描述'
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of flightorderchangeinfo
-- ----------------------------
INSERT INTO `flightorderchangeinfo` VALUES (500, '李四', '2023-10-12 10:48:23:23', '2023-10-13 10:48:23:23', NULL, NULL, NULL, NULL, NULL, NULL, '123456', NULL, NULL, NULL, NULL);

SET FOREIGN_KEY_CHECKS = 1;
