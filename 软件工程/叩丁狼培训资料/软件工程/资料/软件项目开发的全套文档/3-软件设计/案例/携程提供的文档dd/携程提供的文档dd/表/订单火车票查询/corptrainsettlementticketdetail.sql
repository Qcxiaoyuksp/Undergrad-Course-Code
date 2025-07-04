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

 Date: 16/10/2023 14:58:50
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for corptrainsettlementticketdetail
-- ----------------------------
DROP TABLE IF EXISTS `corptrainsettlementticketdetail`;
CREATE TABLE `corptrainsettlementticketdetail`  (
  `ticketInfoId` bigint(20) NOT NULL COMMENT '车次编号',
  `trainName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '车次名',
  `firstSeatTypeName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '首选座席名称',
  `trainType` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '列车类型id(D,G,K,T)',
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
  `changeStatus` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '改签状态，P/改签处理中；S/改签成功；F/改签失败',
  `dealTicketPrice` decimal(8, 2) NULL DEFAULT NULL COMMENT '出票实际票价',
  `rebRefEstimateAmount` decimal(8, 2) NULL DEFAULT NULL COMMENT '退改预估手续费',
  `departureCityId` int(10) NULL DEFAULT NULL COMMENT '出发城市ID',
  `departureDistrictCode` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '出发城市行政编码',
  `arrivalCityId` int(10) NULL DEFAULT NULL COMMENT '到达城市ID',
  `arrivalDistrictCode` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '到达城市行政编码',
  `changeCode` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '改签原因Code',
  `dealSeatNo` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '出票座位号',
  `dealSeatName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT ' 出票座\r\n位号描\r\n述',
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
  `refundreasonCodeDesc` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '退票原因说明',
  `issueTicketTime` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '出票时间',
  `rebookTicketSuccessTime` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '改签时间',
  `refundTicketSuccessTime` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '退票时间',
  `changePreApprovalId` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '改签审批单号',
  `refundApprovalId` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '退票审批单号',
  `standardGeoInfo` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '标准地理信息'
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
