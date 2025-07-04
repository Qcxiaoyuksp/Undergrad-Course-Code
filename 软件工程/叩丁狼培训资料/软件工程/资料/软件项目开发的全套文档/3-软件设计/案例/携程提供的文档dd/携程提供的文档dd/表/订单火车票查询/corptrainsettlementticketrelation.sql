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

 Date: 16/10/2023 16:47:04
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for corptrainsettlementticketrelation
-- ----------------------------
DROP TABLE IF EXISTS `corptrainsettlementticketrelation`;
CREATE TABLE `corptrainsettlementticketrelation`  (
  `orderId` bigint(8) NOT NULL COMMENT '车票类型（D原车次车票；C改签车次车票）',
  `passengerNo` bigint(8) NULL DEFAULT NULL COMMENT '出行人编号',
  `ticketInfoId` bigint(8) NULL DEFAULT NULL COMMENT '车次编号',
  `orderTicketId` bigint(8) NULL DEFAULT NULL COMMENT '车票编号',
  `refundTicketStatusDesc` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '退票状态描述',
  `refundAmountStatus` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '退款状态(T:已退款，默认为空)',
  `changeStatus` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '改签状态（P/改签处理中；S/改签成功；F/改签失败）',
  `ticketType` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '车票类型（D原车次车票；C改签车次车票）'
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
