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

 Date: 16/10/2023 14:49:40
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for corptrainsettlementdetail
-- ----------------------------
DROP TABLE IF EXISTS `corptrainsettlementdetail`;
CREATE TABLE `corptrainsettlementdetail`  (
  `recordId` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '结算明细ID，与OrderType字段一起共同确保数据唯一性，且仅针\r\n对当前产品类型唯一\r\n备注：如是补偿数据，可以通过RecordId进行去重',
  `orderId` bigint(8) NULL DEFAULT NULL COMMENT '订单号',
  `corpId` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '公司编号',
  `accountId` int(10) NULL DEFAULT NULL COMMENT '主账户ID',
  `uid` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '携程卡号',
  `detailType` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '订单明细类型：出票--O 退票--R 改签--A',
  `passengerName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '乘客姓名',
  `price` decimal(8, 2) NULL DEFAULT NULL COMMENT '票面价',
  `serverFee` decimal(8, 2) NULL DEFAULT NULL COMMENT '商旅管理服务费',
  `cancelFee` decimal(8, 2) NULL DEFAULT NULL COMMENT '退票费（新接入客户请使用TrainChangePrice、TrainOtherFee进\r\n行计算）',
  `insureFee` decimal(8, 2) NULL DEFAULT NULL COMMENT '保险费',
  `paperTicketFee` decimal(8, 2) NULL DEFAULT NULL COMMENT '纸质票出票费',
  `deliverFee` decimal(8, 2) NULL DEFAULT NULL COMMENT '快递费',
  `reBookingServiceFee` decimal(8, 2) NULL DEFAULT NULL COMMENT '改签商旅管理服务费',
  `realAmount` decimal(8, 2) NULL DEFAULT NULL COMMENT '费用合计=票面价+商旅管理服务费+退票费+保险费+抢票费+纸质\r\n出票费+快递费+改签商旅管理服务费+免关联购票',
  `batchNo` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '结算批次号',
  `settlementType` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '月结M/现付N',
  `createtime` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '结算生成时间（格式：yyyy-MM-dd HH:mm:ss.fff）',
  `changeLasttime` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '结算最晚更新时间（格式：yyyy-MM-dd HH:mm:ss.fff）',
  `orderType` int(10) NULL DEFAULT NULL COMMENT '订单类型 7：月结火车票8：现付火车票',
  `subAccCheckBatchNo` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '结算子批次号',
  `tripId` bigint(8) NULL DEFAULT NULL COMMENT '行程号，又名“行程打包单号”',
  `settlementCurrency` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '结算币种',
  `grabServiceFee` decimal(8, 0) NULL DEFAULT NULL COMMENT '抢票费，使用抢票功能支付的服务费',
  `postServiceFee` decimal(8, 0) NULL DEFAULT NULL COMMENT '后收商旅管理服务费\r\n后收商旅管理服务费：指预订过程中不展示，仅在结算数据中体\r\n现。',
  `realAmountHasPost` decimal(8, 0) NULL DEFAULT NULL COMMENT '实收实付（含后收商旅管理服务费）',
  `isChecked` int(10) NULL DEFAULT NULL COMMENT '是否已被客户核对(确认状态)，true 已确认，false 未确认',
  `subDetailType` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '(T出票、C订单取消、TF出票失败、BF购票失败(配送票)、RT退票、RI退保险、RB退差额、RD票张金额差价退款(配送费)、CT改签收费、CS收取改签商旅管理服务费、CB退改签差额、CR改签退款、CD改签原票张关系、RA退代取票费、SP扣服务费、SR、 退服务费)',
  `invoiceIds` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '携程发票ID集合',
  `batchStartDate` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '批次起始日期,yyyyMMdd',
  `batchEndDate` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '批次结束日期,yyyyMMdd',
  `afterTakeTicketFee` decimal(8, 2) NULL DEFAULT NULL COMMENT '代取人工费，6位小数精度，本字段只做展示使用，该值已经包在\r\n商旅管理服务费里面，前收的话包在前收里面，后收包在后收里面',
  `estimatePrice` decimal(8, 2) NULL DEFAULT NULL COMMENT '预估票面价，6位小数精度，本字段只做展示使用',
  `estimaAmount` decimal(8, 2) NULL DEFAULT NULL COMMENT '预估手续费（改签手续费/退票手续费），6位小数精度，本字段只\r\n做展示使用',
  `purchaseFee` decimal(8, 2) NULL DEFAULT NULL COMMENT '免关联购票费',
  `payMixFlag` int(5) NULL DEFAULT NULL COMMENT '是否混付，true是，false不是',
  `personalPayTicketFee` decimal(8, 2) NULL DEFAULT NULL COMMENT '个人支付-票款，下单后不做金额更新。',
  `personalPayServiceFee` decimal(8, 2) NULL DEFAULT NULL COMMENT '个人支付-服务费，下单后不做金额更新。',
  `personalPayOtherFee` decimal(8, 2) NULL DEFAULT NULL COMMENT '个人支付-其他费用，下单后不做金额更新。',
  `trainChangePrice` decimal(8, 2) NULL DEFAULT NULL COMMENT '新票面金额（不包含手续费）',
  `trainOtherFee` decimal(8, 0) NULL DEFAULT NULL COMMENT '包含12306收取的改签手续费、退票手续费和线下退改的费用',
  `dealTime` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '交易时间',
  `productType` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '产品类型I：国际：N：国内',
  `departureCountry` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '出发国家',
  `arrivalCountry` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '到达国家',
  `sequence` int(10) NULL DEFAULT NULL COMMENT '行程序号',
  `loanServiceFee` decimal(8, 2) NULL DEFAULT NULL COMMENT '垫资服务费',
  `intlIssueTicketFee` decimal(8, 2) NULL DEFAULT NULL COMMENT '境外出票费'
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
