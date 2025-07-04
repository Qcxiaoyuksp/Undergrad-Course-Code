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

 Date: 17/10/2023 15:59:17
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for settlementdetail
-- ----------------------------
DROP TABLE IF EXISTS `settlementdetail`;
CREATE TABLE `settlementdetail`  (
  `recordId` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '结算明细ID，与OrderType字段一起共同确保数据唯一\r\n性，且仅针对当前产品类型唯一\r\n备注：如是补偿数据，可以通过RecordId进行去重',
  `orderId` bigint(8) NULL DEFAULT NULL COMMENT '订单号',
  `accountId` int(10) NULL DEFAULT NULL COMMENT '主账户ID',
  `uid` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '携程卡号',
  `detailType` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '订单明细类型：出--O；退--R',
  `payType` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '结算类型：员工现付--X；公司月结--Y',
  `hotelType` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '酒店类型：会员酒店--H；协议酒店--X',
  `price` double(32, 2) NULL DEFAULT NULL COMMENT '单价 ，间夜单价= 金额amount/间夜数quantity',
  `quantity` int(10) NULL DEFAULT NULL COMMENT '间夜数',
  `amount` double(32, 0) NULL DEFAULT NULL COMMENT '金额\r\n（Amount = 公司账户支付的房费 + \r\nFrontendServiceFee + ExpressFee - Coupon ）\r\n说明：\r\n1. amount计算公式为携程商旅输出逻辑，不含后收费\r\n用\r\n2. 若订单为全部公司账户支付时，公司账户支付的房费 = \r\nPrice * Quantity；若是混合支付，则公司账户支付的房费 \r\n＜ Price * Quantity\r\n3. 随新增费用项，计算方式可能发生变化\r\n4.订单总价=Amount+Servicefee+ExtraCharge',
  `servicefee` double(32, 0) NULL DEFAULT NULL COMMENT '后收商旅管理服务费',
  `extraCharge` double(32, 0) NULL DEFAULT NULL COMMENT '手续费（加收税额），后收',
  `accCheckBatchNo` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '结算批次号',
  `createtime` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '明细生成时间',
  `datachange_Lasttime` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '明细最晚更新时间',
  `orderType` int(10) NULL DEFAULT NULL COMMENT '订单类型：3-月结会员酒店；4-月结协议酒店；5-现付会\r\n员酒店；6-现付协议酒店',
  `subAccCheckBatchNo` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '结算子批次号',
  `tripId` bigint(8) NULL DEFAULT NULL COMMENT '行程号，又名“行程打包单号”',
  `settlementCurrency` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '结算币种',
  `isChecked` int(10) NULL DEFAULT NULL COMMENT '是否已被客户核对(确认状态)，ture 已确认，false 未确认',
  `dailyAvgPriceInfo` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '每日均价',
  `invoiceIds` int(15) NULL DEFAULT NULL COMMENT '携程发票集合',
  `batchStartDate` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '批次起始日期，yyyyMMdd',
  `batchEndDate` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '批次结束日期，yyyyMMdd',
  `frontendServiceFee` double(32, 0) NULL DEFAULT NULL COMMENT '前收商旅管理服务费，保留6位小数',
  `expressFee` double(32, 0) NULL DEFAULT NULL COMMENT '快递费，保留6位小数',
  `coupon` double(32, 0) NULL DEFAULT NULL COMMENT '优惠券抵扣金额，正数，保留6位小数',
  `relatedCostsId` bigint(8) NULL DEFAULT NULL COMMENT '支付BillNo',
  `apportionMode` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '分摊类型, NONE：不分摊;ORDER：按订单;ROOM：按\r\n房间;TRAVEL_CONTROL：按差标',
  `orderRoomMode` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '订房模式, NORMAL:普通; ROOM_TOGETHER:同住; \r\nTRAVEL_TOGETHER:同行',
  `clientApprovalNo` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '入住人审批单号 注:此字段仅开通同住时会有审批单号，\r\n未开通拼房则只会下发姓名',
  `fellowApprovalNo` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '同行人审批单号 注:此字段仅开通同住时会有审批单号',
  `loanServiceFee` double(32, 0) NULL DEFAULT NULL COMMENT '垫资服务费',
  `clientName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '入住人姓名，没做人程拆分时，clientName 是多个的，用英文逗号隔开',
  `employeeId` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '入住人eid',
  `insuranceAmount` double(32, 0) NULL DEFAULT NULL COMMENT '保险费',
  `personAmount` double(32, 0) NULL DEFAULT NULL COMMENT '个人支付房费',
  PRIMARY KEY (`recordId`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
