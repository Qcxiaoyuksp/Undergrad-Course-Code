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

 Date: 18/10/2023 13:26:19
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for settlementroomdetail
-- ----------------------------
DROP TABLE IF EXISTS `settlementroomdetail`;
CREATE TABLE `settlementroomdetail`  (
  `basicRoomTypeName` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '基础房型(中文)',
  `basicRoomTypeEnName` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '基础房型(英文)',
  `breakfast` int(10) NULL DEFAULT NULL COMMENT '早餐',
  `addBreakfast` int(10) NULL DEFAULT NULL COMMENT '加早',
  `meals` int(10) NULL DEFAULT NULL COMMENT '餐食份数',
  `eta` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '入住时间（格式：yyyy-MM-dd HH:mm:ss，默认为空，\r\n历史数据为空）',
  `etd` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '离店时间（格式：yyyy-MM-dd HH:mm:ss，默认为空，\r\n历史数据为空）',
  `price` double(8, 2) NULL DEFAULT NULL COMMENT '每间夜价格（默认为0，历史数据为0）',
  `remainQuantity` int(10) NULL DEFAULT NULL COMMENT '剩余房间数',
  `refundQuantity` int(10) NULL DEFAULT NULL COMMENT '退款房间数'
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
