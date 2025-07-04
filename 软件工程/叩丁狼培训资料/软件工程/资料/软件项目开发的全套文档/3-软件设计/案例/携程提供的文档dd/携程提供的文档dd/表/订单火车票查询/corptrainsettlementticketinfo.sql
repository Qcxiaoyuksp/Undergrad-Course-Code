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

 Date: 17/10/2023 09:34:17
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for corptrainsettlementticketinfo
-- ----------------------------
DROP TABLE IF EXISTS `corptrainsettlementticketinfo`;
CREATE TABLE `corptrainsettlementticketinfo`  (
  `ticketInfoId` bigint(8) NOT NULL COMMENT '车次编号',
  `trainName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '车次名',
  `firstSeatTypeName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '首选座席名称',
  `trainType` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '列车类型id(D：动车,G：高铁|城际,K：普通,T：特快列车)',
  `departureCityName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '出发城市名称',
  `departureDate` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '出发时间（格式：yyyy-MM-dd HH:mm:ss.fff）',
  `departureStationName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '出发车站名',
  `departureStationEn` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '出发车站英文名',
  `arrivalCityName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '到达城市名称',
  `arrivalDate` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '到达时间（格式：yyyy-MM-dd HH:mm:ss.fff）',
  `arrivalStationName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '到达车站名',
  `arrivalStationEn` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '到达车站英文名',
  `electronicOrderNo` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '12306电子订单号',
  `customType` int(10) NULL DEFAULT NULL COMMENT '订制类型',
  `customDetail` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '具体定制内容',
  `trainTicketType` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '车票类型（D原车次车票；C改签车次车票）',
  `trainSeatPriceData` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '车次坐席价格数据',
  `orderTicketId` bigint(8) NULL DEFAULT NULL COMMENT '订单出票车票ID',
  `refundTicketStatusDesc` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '车票状态',
  `refundAmountStatus` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '退款状态(T:已退款，默认为空)',
  `changeStatus` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '改签状态（P/改签处理中；S/改签成功；F/改签失败）',
  `ticketType` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '车票类型（D原车次车票；C改签车次车票）',
  `dealTicketPrice` decimal(8, 2) NULL DEFAULT NULL COMMENT '出票实际票价',
  `departureCityId` int(10) NULL DEFAULT NULL COMMENT '出发城市ID',
  `departureDistrictCode` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '出发城市行政编码',
  `arrivalCityId` int(10) NULL DEFAULT NULL COMMENT '到达城市ID',
  `arrivalDistrictCode` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '到达城市行政编码',
  `changeCode` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT ' 改签原因Code',
  `takeTicketStatus` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '取票状态(N，无；W，待取票；P，取票中；S，取票成\r\n功；F，取票失败)',
  `failReason` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '取票失败原因',
  `departureProvinceId` bigint(8) NULL DEFAULT NULL COMMENT '出发站省份id',
  `departureProvinceName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '出发站省份名',
  `departureLocationId` bigint(8) NULL DEFAULT NULL COMMENT '出发站区县ID',
  `departureLocationName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '出发站区县名',
  `departureLocationCategoryId` int(10) NULL DEFAULT NULL COMMENT '出发站区/县ID类别',
  `arrivalProvinceId` bigint(8) NULL DEFAULT NULL COMMENT '到达站省份id',
  `arrivalProvinceName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '到达站省份名',
  `arrivalLocationId` bigint(8) NULL DEFAULT NULL COMMENT '到达站区县ID',
  `arrivalLocationName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '到达站区县名',
  `arrivalLocationCategoryId` int(10) NULL DEFAULT NULL COMMENT '到达站区/县ID类别',
  `sequence` int(10) NULL DEFAULT NULL COMMENT '行程序号',
  `refundreasonCode` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '退票原因Code',
  `issueTicketTime` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '出票时间',
  `rebookTicketSuccessTime` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '改签时间',
  `refundTicketSuccessTime` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '退票时间',
  `originalDealSeatName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '原始坐席描述（改签时才有）',
  `changePreApprovalId` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '改签审批单号',
  `refundApprovalId` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '退票审批单号',
  `standardGeoInfo` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '标准地理信息'
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
