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

 Date: 16/10/2023 14:59:55
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for searchsettlementtrainorderdetailrequest
-- ----------------------------
DROP TABLE IF EXISTS `searchsettlementtrainorderdetailrequest`;
CREATE TABLE `searchsettlementtrainorderdetailrequest`  (
  `auth` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '接入账号、ticket，用作身份验证',
  `accountId` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '主账户Id',
  `dateFrom` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '开始时间',
  `dateTo` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '结束时间',
  `batchNo` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '结算批次号',
  `settlementType` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '结算类型(月结：M；现付：N 默认是所有)',
  `recordId` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '流水号',
  `orderId` bigint(8) NULL DEFAULT NULL COMMENT '订单号',
  `journeyNoList` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '关联行程号',
  `isCompensation` int(10) NULL DEFAULT NULL COMMENT '是否补偿获\r\n取(默认为false，建议设置为true，在获取\r\n正常数据的同时，我们也会将最近更新\r\n的数据一起推送)',
  `pageIndex` int(10) NULL DEFAULT NULL COMMENT '分页页码(仅针对时间段、批次号查询)',
  `pageSize` int(10) NULL DEFAULT NULL COMMENT '分页大小',
  `subBatchNoList` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '子批次号'
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
