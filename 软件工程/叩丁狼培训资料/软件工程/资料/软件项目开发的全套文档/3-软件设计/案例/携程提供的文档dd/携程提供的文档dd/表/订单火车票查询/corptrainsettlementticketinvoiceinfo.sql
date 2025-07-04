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

 Date: 17/10/2023 09:50:46
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for corptrainsettlementticketinvoiceinfo
-- ----------------------------
DROP TABLE IF EXISTS `corptrainsettlementticketinvoiceinfo`;
CREATE TABLE `corptrainsettlementticketinvoiceinfo`  (
  `orderTicketInvoiceId` bigint(8) NOT NULL COMMENT '票张发票情况主键',
  `orderTicketId` bigint(8) NULL DEFAULT NULL COMMENT '车次编号，用于关联票张',
  `invoiceAmount` decimal(8, 0) NULL DEFAULT NULL COMMENT '发票金额',
  `invoiceStatus` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '发票状态(W待上传;P审核中;S已审核;E已完成;A无需上传)',
  PRIMARY KEY (`orderTicketInvoiceId`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
