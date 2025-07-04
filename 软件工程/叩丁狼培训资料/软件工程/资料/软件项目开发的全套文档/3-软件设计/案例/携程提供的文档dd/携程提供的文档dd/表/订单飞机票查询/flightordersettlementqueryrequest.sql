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

 Date: 16/10/2023 15:47:42
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for flightordersettlementqueryrequest
-- ----------------------------
DROP TABLE IF EXISTS `flightordersettlementqueryrequest`;
CREATE TABLE `flightordersettlementqueryrequest`  (
  `auth` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '接入账号、ticket，用作身份验证',
  `accountId` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '主账户ID(请联系实施经理获取,主账户ID为空，则按照接入账号\r\nAppKey对应的CorpId查询公司下所有账户的结算数据)',
  `dateFrom` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '开始时间',
  `dateTo` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '结束时间',
  `batchNo` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '结算批次号',
  `recordId` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '多个RecordID以,号隔开，最多1000个。',
  `orderId` bigint(255) NULL DEFAULT NULL COMMENT '订单号(仅支持单个订单号，如果流水号存在时，以流水号为准)',
  `journeyNoList` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '关联行程号(单次查询最多支持20个，且只能查询当前一年内的数\r\n据)',
  `isCompensation` int(10) NULL DEFAULT NULL COMMENT '是否补偿获取(默认为false，建议设置为true，在获取正常数据的同\r\n时，我们也会将最近更新的数据一起推送)',
  `payType` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '结算类型(默认Y，Y（月结）,X（现付）,All（全部）)',
  `pageIndex` int(10) NULL DEFAULT NULL COMMENT '分页页码(仅针对时间段、批次号查询\r\n注意事项：1、分页不考虑补偿数据；2、如果配置了\r\n改签数据屏蔽，返回的数据可能小于PageSize的大\r\n小；3、PageIndex超过总页数不返回数据)',
  `pageSize` int(10) NULL DEFAULT NULL COMMENT '分页大小',
  `subBatchNoList` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '子批次号(“主账户ID”_\"子批次配置ID\"_\"结算周期的开始日期\"其中子批次配置ID，按客户需求配置后提供\r\n例：主账户ID=4113，按成本中心1维度配置子批次号，其中成本中心\r\n值为A，对应子批次ID=CC1_01，结算周期为自然月则子批次号\r\n=4113_CC1_01_20230401)'
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
