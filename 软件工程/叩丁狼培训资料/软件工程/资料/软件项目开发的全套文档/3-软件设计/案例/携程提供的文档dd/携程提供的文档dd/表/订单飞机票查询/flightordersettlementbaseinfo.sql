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

 Date: 16/10/2023 15:44:34
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for flightordersettlementbaseinfo
-- ----------------------------
DROP TABLE IF EXISTS `flightordersettlementbaseinfo`;
CREATE TABLE `flightordersettlementbaseinfo`  (
  `recordId` int(10) NOT NULL COMMENT '结算明细ID，与OrderType字段一起共同确保数据唯一性，且仅针对当\r\n前产品类型唯一,后续将废弃，请使用NewRecordId',
  `orderId` bigint(45) NULL DEFAULT NULL COMMENT '订单号',
  `sequence` int(255) NULL DEFAULT NULL COMMENT '航程编号',
  `createTime` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '结算生成时间（格式：yyyy-MM-dd HH:mm:ss.fff）',
  `accountId` int(10) NULL DEFAULT NULL COMMENT '主账户ID',
  `corpId` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '公司编号',
  `accCheckBatchNo` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '结算批次号',
  `accBalanceBatchNo` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '付款批次号',
  `remark` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '备注',
  `unDeterminedAmount` decimal(8, 2) NULL DEFAULT NULL COMMENT '未确定金额，说明有部分费用由于未明确归属费用项，将体现在后续新\r\n的结算明细中',
  `price` decimal(8, 2) NULL DEFAULT NULL COMMENT '成交净价',
  `tax` decimal(8, 2) NULL DEFAULT NULL COMMENT '民航基金/税',
  `oilFee` decimal(8, 2) NULL DEFAULT NULL COMMENT '燃油附加费',
  `sendTicketFee` decimal(8, 2) NULL DEFAULT NULL COMMENT '快递费，原“送票费”',
  `insuranceFee` decimal(8, 2) NULL DEFAULT NULL COMMENT '保险费',
  `serviceFee` decimal(8, 2) NULL DEFAULT NULL COMMENT '商旅管理服务费，包含了基础服务费、VIP服务费、非工作时间服务\r\n费、套餐服务费、特价机票服务费、服务费赠险等',
  `coupon` decimal(8, 2) NULL DEFAULT NULL COMMENT '优惠劵，购买优惠券的金额',
  `refundServiceFee` decimal(8, 2) NULL DEFAULT NULL COMMENT '退票商旅管理服务费',
  `refund` decimal(8, 2) NULL DEFAULT NULL COMMENT '退票费',
  `rebookQueryFee` decimal(8, 2) NULL DEFAULT NULL COMMENT '改签费',
  `reBookingServiceFee` decimal(8, 2) NULL DEFAULT NULL COMMENT '改签商旅管理服务费',
  `itineraryFee` decimal(8, 2) NULL DEFAULT NULL COMMENT '前收行程单管理服务费，该管理服务费不包含在ServiceFee中，但计入\r\nAmount',
  `amount` decimal(8, 2) NULL DEFAULT NULL COMMENT ' 应收金额（Amount）= 成交净价（Price）+民航基金/税（Tax）+\r\n燃油附加费（OilFee）+商旅管理服务费（ServiceFee）+保险费\r\n（InsuranceFee）+优惠券（Coupon）+前收行程单管理服务费\r\n（ItineraryFee）+快递费（SendticketFee）+改签费\r\n（RebookQueryFee）+退票费（Refund）+退票管理服务费\r\n（RefundServiceFee）+改签管理服务费（ReBookingServiceFee）+\r\n服务包金额（ServicePackagePrice）',
  `postServiceFee` decimal(8, 2) NULL DEFAULT NULL COMMENT '后收商旅管理服务费，包含ServiceFee,RefundServiceFee,\r\nReBookingServiceFee,ItineraryFee,postBookServiceFee,\r\nsettItineraryFee,postReBookingServiceFee,\r\npostRefundServiceFee，若管理服务费收取方式为结算时统一收\r\n取，则管理服务费体现在该字段，具体管理服务费类型通过\r\nPostServiceFeedesc可查看。\r\nPostServiceFee不包含在Amount中，该条流水结算总金额\r\n=Amount+PostServiceFee\r\n后收商旅管理服务费：预订过程中不展示，仅在结算数据中体现。',
  `postServiceFeedesc` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '后收商旅管理服务费类型描述：预订、退票、改签、配送',
  `baseServiceFee` decimal(8, 2) NULL DEFAULT NULL COMMENT '基础服务费，已包含在ServiceFee。注：当订单为国际机票改签新增订\r\n单时，包含在ReBookingServiceFee，而非ServiceFee。',
  `unWorkTimeServiceFee` decimal(8, 2) NULL DEFAULT NULL COMMENT '非工作时间商旅管理服务费，已包含在ServiceFee',
  `vipServiceFee` decimal(8, 2) NULL DEFAULT NULL COMMENT 'VIP商旅管理服务费，已包含在ServiceFee',
  `bindServiceFee` decimal(8, 2) NULL DEFAULT NULL COMMENT '特价机票商旅管理服务费，已包含在ServiceFee',
  `orderDetailType` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '退改签类型（出票改签退票取消调整）',
  `orderType` int(10) NULL DEFAULT NULL COMMENT '订单类型，1：月结机票，2：现付机票',
  `subAccCheckBatchNo` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '结算子批次号',
  `tripId` bigint(8) NULL DEFAULT NULL COMMENT '行程号，又名“行程打包单号”',
  `settlementCurrency` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '结算币种',
  `dateChangeFee` decimal(8, 2) NULL DEFAULT NULL COMMENT '更改费',
  `priceDifferential` decimal(8, 2) NULL DEFAULT NULL COMMENT '改签差价',
  `isChecked` int(10) NULL DEFAULT NULL COMMENT '是否已被客户核对(确认状态)，true 已确认 ，false 未确认',
  `deductibleTax` decimal(8, 2) NULL DEFAULT NULL COMMENT '可抵扣税额',
  `nonDeductibleTax` decimal(8, 2) NULL DEFAULT NULL COMMENT '不可抵扣税额',
  `subsidy` decimal(8, 2) NULL DEFAULT NULL COMMENT '飞享金',
  `invoiceIds` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '携程发票集合',
  `batchStartDate` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '批次开始时间,yyyyMMdd',
  `batchEndDate` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '批次结束时间,yyyyMMdd',
  `deductionAmount` decimal(8, 2) NULL DEFAULT NULL COMMENT '抵扣金额，负数，抵扣金额已经在对应的费用项里扣减，仅作展示，无\r\n需重复计算',
  `servicePackagePrice` decimal(8, 2) NULL DEFAULT NULL COMMENT '服务包金额',
  `newRecordId` bigint(8) NULL DEFAULT NULL COMMENT '结算明细ID，未来将替换RecordId',
  `taxFeeDifferential` decimal(8, 2) NULL DEFAULT NULL COMMENT '改签税费',
  `postBookServiceFee` decimal(8, 2) NULL DEFAULT NULL COMMENT '后收预订商旅管理服务费',
  `settItineraryFee` decimal(8, 2) NULL DEFAULT NULL COMMENT '后收行程单管理服务费',
  `postReBookingServiceFee` decimal(8, 2) NULL DEFAULT NULL COMMENT '后收改签商旅管理服务费',
  `postRefundServiceFee` decimal(8, 2) NULL DEFAULT NULL COMMENT '后收退票商旅管理服务费',
  `payMixFlag` int(8) NULL DEFAULT NULL COMMENT '混付标识',
  `personalPayTicketFee` decimal(8, 2) NULL DEFAULT NULL COMMENT '个付-票款',
  `personalPayOilFee` decimal(8, 2) NULL DEFAULT NULL COMMENT '个付-燃油税',
  `personalPayBaseServiceFee` decimal(8, 2) NULL DEFAULT NULL COMMENT '个付-预订服务费',
  `personalPayRefundServiceFee` decimal(8, 2) NULL DEFAULT NULL COMMENT '个付-退票费',
  `personalPayTax` decimal(8, 2) NULL DEFAULT NULL COMMENT '个付-机票税费',
  `rebookInsuranceFee` decimal(8, 2) NULL DEFAULT NULL COMMENT '个付-保险费'
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
