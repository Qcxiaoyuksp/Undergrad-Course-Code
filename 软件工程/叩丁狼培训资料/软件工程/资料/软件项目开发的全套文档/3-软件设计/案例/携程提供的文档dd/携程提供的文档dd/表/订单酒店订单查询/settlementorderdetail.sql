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

 Date: 18/10/2023 11:01:00
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for settlementorderdetail
-- ----------------------------
DROP TABLE IF EXISTS `settlementorderdetail`;
CREATE TABLE `settlementorderdetail`  (
  `orderId` bigint(8) NULL DEFAULT NULL COMMENT '订单号',
  `employeeName` varchar(32) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '预定人名称',
  `employeeId` varchar(32) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '员工编号',
  `workCity` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '工作所在城市',
  `orderDate` varchar(32) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '预定日期',
  `roomName` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '房型中文名称',
  `roomNameEN` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '房型英文名称',
  `roomQuantity` int(10) NULL DEFAULT NULL COMMENT '房间数',
  `clientName` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '入住人姓名',
  `startTime` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '入住日期',
  `EndTime` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '离店日期',
  `postAmount` double(32, 2) NULL DEFAULT NULL COMMENT '配送费（只有会员订单有该字段）',
  `isHasSpecialInvoice` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '开票类型（增专/增普对应的值T/F)',
  `serverFrom` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '预定来源App/Online/Offline',
  `lowPriceRC` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '低价RC',
  `lowPriceRC_VV` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '预订选择的低价RC为其它时，用户自己输入的超标原\r\n因。',
  `lowPriceRCInfo` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '低价RC内容(中文)',
  `lowPriceRCInfoEN` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '低价RC内容(英文)',
  `agreementRC` varchar(32) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '协议RC',
  `agreementRC_VV` varchar(32) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '预订选择的协议RC为其它时，用户自己输入的超标原\r\n因',
  `agreementRCInfo` varchar(32) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '协议RC内容(中文)',
  `agreementRCInfoEN` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '协议RC内容(英文)',
  `costCenter` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '成本中心一',
  `costCenter2` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '成本中心二',
  `costCenter3` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '成本中心三',
  `costCenter4` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '成本中心四',
  `costCenter5` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '成本中心五',
  `costCenter6` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '成本中心六',
  `journeyReason` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '出行目的',
  `project` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '项目号',
  `defineTitleContent` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '自定义字段一',
  `defineTitleContent2` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '自定义字段二',
  `hotelRelatedJourneyNo` varchar(60) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '关联行程号',
  `remarks` varchar(60) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '补充说明',
  `payType` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '支付方式，CA：现金支付；AR：公司账户支付；\r\nCC：礼品卡；EX：信用卡；More：第三方支付，代\r\n表微信和支付宝；空代表其他支付方式',
  `balanceType` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '支付类型，Pay at check-out：前台现付；Prepay \r\nto Ctrip：预付',
  `isMixPayment` varchar(8) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '混付订单标识，T：混付订单；F：非混付订单',
  `settlementACCNTAmt` double(32, 0) NULL DEFAULT NULL COMMENT '混付公司账户支付金额，不包含后收商旅管理费，下\r\n单后不做金额更新。',
  `settlementPersonAmt` double(32, 0) NULL DEFAULT NULL COMMENT '混付个人账户支付总金额，不包含后收商旅管理费，\r\n下单后不做金额更新。',
  `couponAmount` double(32, 0) NULL DEFAULT NULL COMMENT '优惠券金额，仅在会员酒店时可能有值，协议酒店为\r\n0（优惠券金额建议使用SettlementDetail节点的\r\nCoupon字段）',
  `clientDetailList` varchar(60) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '入住人基本信息',
  `dept1` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '部门一',
  `dept2` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '部门二',
  `dept3` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '部门三',
  `dept4` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '部门四',
  `dept5` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '部门五',
  `dept6` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '部门六',
  `dept7` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '部门七',
  `dept8` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '部门八',
  `dept9` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '部门九',
  `dept10` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '部门十',
  `roomDetailList` varchar(60) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '房型信息',
  `minPriceRC` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '最低价房型RC code',
  `minPriceRC_VV` varchar(80) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '最低价房型RC原因',
  `rankName` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '预订人职级',
  `rankNameEn` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '预订人职级英文名',
  `confirmType` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '一次授权方式（不适用行程打包模式）',
  `confirmType2` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '二次授权方式（不适用行程打包模式）',
  `confirmPerson` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '一次授权人（不适用行程打包模式）',
  `confirmPerson2` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '二次授权人（不适用行程打包模式）',
  `confirmPersonCC` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '抄送一次授权人（不适用行程打包模式）',
  `confirmPersonCC2` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '抄送二次授权人（不适用行程打包模式）',
  `confirmPersonName` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '一次授权人姓名（不适用行程打包模式）',
  `confirmPersonName2` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '二次授权人姓名（不适用行程打包模式）',
  `confirmPersonCCName` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '抄送一次授权人姓名（不适用行程打包模式）',
  `confirmPersonCCName2` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '抄送二次授权人姓名（不适用行程打包模式）',
  `tPMaxPrice` double(32, 2) NULL DEFAULT NULL COMMENT '预定人差标上限',
  `roomType` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '子房型(钟点房枚举值为HourRoom，其他房型默认\r\nDefault)',
  `mealType` int(10) NULL DEFAULT NULL COMMENT '套餐类型\r\n0：无餐\r\n1：晚餐\r\n2：午餐\r\n3：午餐+晚餐\r\n4：早餐\r\n5：早餐+晚餐\r\n6：早餐+午餐\r\n7：早餐+午餐+晚餐\r\n8：可选餐\r\n9：全餐（早+午+晚餐+小食）\r\n10：午餐、晚餐二选一\r\n11：早餐、午餐（晚餐）二选一',
  `projectCode` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '项目编码',
  `cancelReason` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '取消原因Code',
  `cancelReasonDesc` varchar(60) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '取消原因描述',
  `contractRoomExistedFlag` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '是否有同名协议房型 N:无同名协议房型 T:有同名协\r\n议房型',
  `applyFormDetailList` varchar(40) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '申请单修改详情',
  `refundTime` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '退款时间',
  `repeatBookingOrderList` bigint(15) NULL DEFAULT NULL COMMENT '重复预订订单号',
  `repeatBookingRC` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '重复预订RC code',
  `repeatBookingDesc` varchar(60) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '重复预订RC描述',
  `repeatBookingRC_VV` varchar(60) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '重复预订RC用户自填内容',
  `userNamePinyin` varchar(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '入住人姓名拼音，多个逗号隔开',
  `auditList` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '夜审数据',
  `configCurrency` varchar(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '差标配置币种',
  `configExchangeToSettlement` double(20, 2) NULL DEFAULT NULL COMMENT '差标配置币种对结算币种汇率',
  `tpConfigMinPrice` double(20, 2) NULL DEFAULT NULL COMMENT '差标价格下限（差标配置币种）',
  `tpConfigMaxPrice` double(10, 2) NULL DEFAULT NULL COMMENT '差标价格上限（差标配置币种）'
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
