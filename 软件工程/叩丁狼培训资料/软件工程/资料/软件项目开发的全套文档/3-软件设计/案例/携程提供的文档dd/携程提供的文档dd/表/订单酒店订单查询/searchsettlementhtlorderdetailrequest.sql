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

 Date: 17/10/2023 14:26:17
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for searchsettlementhtlorderdetailrequest
-- ----------------------------
DROP TABLE IF EXISTS `searchsettlementhtlorderdetailrequest`;
CREATE TABLE `searchsettlementhtlorderdetailrequest`  (
  `auth` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '接入账号',
  `accountId` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '主账户Id',
  `dateFrom` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '开始时间',
  `dateTo` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '结束时间',
  `hotelType` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '酒店类型',
  `payType` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '结算类型',
  `batchNo` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '结算批次\r\n号',
  `recordId` int(10) NULL DEFAULT NULL COMMENT '流水号',
  `orderId` bigint(8) NULL DEFAULT NULL COMMENT '订单号',
  `journeyNoList` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '关联行程\r\n号',
  `isCompensation` int(10) NULL DEFAULT NULL COMMENT '是否补偿\r\n获取',
  `pageIndex` int(10) NULL DEFAULT NULL COMMENT '分页页码',
  `pageSize` int(10) NULL DEFAULT NULL COMMENT '分页大小',
  `subBatchNoList` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '“主账户ID”_\"子批次配置ID\"_\"结算周期的开始日期\"\r\n其中子批次配置ID，按客户需求配置后提供\r\n例：主账户ID=4113，按成本中心1维度配置子批次号，其中成本\r\n中心值为A，对应子批次ID=CC1_01，结算周期为自然月则子批次\r\n号=4113_CC1_01_20230401'
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
