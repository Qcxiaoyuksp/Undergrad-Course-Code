/*
 Navicat Premium Data Transfer

 Source Server         : localhost_mysql
 Source Server Type    : MySQL
 Source Server Version : 50728
 Source Host           : localhost:3306
 Source Schema         : crm

 Target Server Type    : MySQL
 Target Server Version : 50728
 File Encoding         : 65001

 Date: 13/04/2020 10:06:16
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for customer
-- ----------------------------
DROP TABLE IF EXISTS `customer`;
CREATE TABLE `customer`  (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `age` int(11) NULL DEFAULT NULL,
  `gender` int(11) NULL DEFAULT NULL,
  `tel` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `qq` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `job_id` bigint(20) NULL DEFAULT NULL,
  `source_id` bigint(20) NULL DEFAULT NULL,
  `seller_id` bigint(20) NULL DEFAULT NULL,
  `input_user_id` bigint(20) NULL DEFAULT NULL,
  `input_time` datetime NULL DEFAULT NULL,
  `status` int(11) NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 8 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of customer
-- ----------------------------
INSERT INTO `customer` VALUES (1, '王五', 22, 0, '1370000000', '10086', 54, 5, 5, 1, '2018-07-01 15:41:42', 0);
INSERT INTO `customer` VALUES (2, '张三', 18, 0, '1570000000', '10087', 3, 33, 4, 1, '2018-08-03 15:17:57', 1);
INSERT INTO `customer` VALUES (3, '周粥', 25, 0, '1770000000', '10088', 2, 34, 5, 1, '2018-08-03 15:56:30', 3);
INSERT INTO `customer` VALUES (4, '李四', 17, 1, '1880000000', '10089', 2, 34, 6, 1, '2018-08-03 16:24:09', 4);
INSERT INTO `customer` VALUES (5, '大飞', 1, 1, '1600000000', '11008', 2, 5, 5, 1, '2018-09-28 10:53:52', 0);
INSERT INTO `customer` VALUES (6, '逍遥', 10, 1, '1340000000', '11009', 1, 33, 1, 1, '2018-09-28 10:53:48', 2);
INSERT INTO `customer` VALUES (7, '12', 22, 1, '12', '12', 2, 5, 3, 1, '2019-02-01 15:44:20', 3);

-- ----------------------------
-- Table structure for customertracehistory
-- ----------------------------
DROP TABLE IF EXISTS `customertracehistory`;
CREATE TABLE `customertracehistory`  (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `trace_time` date NULL DEFAULT NULL,
  `trace_details` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `trace_type_id` bigint(20) NULL DEFAULT NULL,
  `trace_result` int(255) NULL DEFAULT NULL,
  `customer_id` bigint(20) NULL DEFAULT NULL,
  `input_user_id` bigint(20) NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 10 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of customertracehistory
-- ----------------------------
INSERT INTO `customertracehistory` VALUES (1, '2018-08-02', '无人接听电话，联系不上', 67, 2, 1, 1);
INSERT INTO `customertracehistory` VALUES (2, '2018-08-04', '考虑中', 68, 2, 4, 1);
INSERT INTO `customertracehistory` VALUES (3, '2018-08-04', '了解使用感受', 65, 3, 4, 1);
INSERT INTO `customertracehistory` VALUES (4, '2018-08-04', '暂无培训想法', 65, 3, 3, 2);
INSERT INTO `customertracehistory` VALUES (5, '2018-09-27', '电话接通就挂掉，待跟进中', 65, 3, 6, 1);
INSERT INTO `customertracehistory` VALUES (6, '2018-09-19', '表示不认识，打错了', 65, 2, 6, 1);
INSERT INTO `customertracehistory` VALUES (7, '2019-02-11', '说要和家里人先商量', 67, 3, 1, 1);
INSERT INTO `customertracehistory` VALUES (8, '2019-02-01', '还在纠结中', 65, 3, 7, 1);
INSERT INTO `customertracehistory` VALUES (9, '2019-05-04', '准备购买，下午付款', 65, 2, 1, 1);

-- ----------------------------
-- Table structure for customertransfer
-- ----------------------------
DROP TABLE IF EXISTS `customertransfer`;
CREATE TABLE `customertransfer`  (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `customer_id` bigint(20) NULL DEFAULT NULL,
  `operator_id` bigint(20) NULL DEFAULT NULL,
  `operate_time` datetime NULL DEFAULT NULL,
  `old_seller_id` bigint(20) NULL DEFAULT NULL,
  `new_seller_id` bigint(20) NULL DEFAULT NULL,
  `reason` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 26 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of customertransfer
-- ----------------------------
INSERT INTO `customertransfer` VALUES (1, 1, 1, '2018-08-04 16:44:11', 2, 1, '离职资源移交');
INSERT INTO `customertransfer` VALUES (2, 1, 1, '2018-08-04 17:13:38', 2, 1, '休产假移交');
INSERT INTO `customertransfer` VALUES (3, 1, 1, '2018-08-04 17:19:54', 2, 1, '离职资源移交');
INSERT INTO `customertransfer` VALUES (4, 1, 1, '2018-08-04 17:45:38', 1, 1, '调岗移交');
INSERT INTO `customertransfer` VALUES (5, 1, 1, '2018-08-04 17:53:03', 1, 1, '离职资源移交');
INSERT INTO `customertransfer` VALUES (6, 1, 1, '2018-08-04 17:54:58', 1, 1, '离职资源移交');
INSERT INTO `customertransfer` VALUES (7, 2, 1, '2018-08-04 18:41:51', 1, 1, '工作调配移交');
INSERT INTO `customertransfer` VALUES (8, 6, 1, '2018-09-28 14:36:46', 5, 3, '离职资源移交');
INSERT INTO `customertransfer` VALUES (9, 5, 1, '2018-09-28 14:37:08', 3, 5, '工作调配移交');
INSERT INTO `customertransfer` VALUES (10, 5, 1, '2018-09-28 14:41:39', 5, 3, '离职资源移交');
INSERT INTO `customertransfer` VALUES (16, 6, 1, '2018-09-28 16:21:30', 3, 1, '工作调配移交');
INSERT INTO `customertransfer` VALUES (17, 5, 1, '2018-09-29 09:47:15', 3, 1, '离职资源移交');
INSERT INTO `customertransfer` VALUES (18, 5, 1, '2018-09-29 09:47:30', 1, 5, '调岗移交');

-- ----------------------------
-- Table structure for department
-- ----------------------------
DROP TABLE IF EXISTS `department`;
CREATE TABLE `department`  (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `sn` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 7 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of department
-- ----------------------------
INSERT INTO `department` VALUES (1, '总经办2', 'General Deparment2');
INSERT INTO `department` VALUES (2, '人力资源部', 'Human Resources Department');
INSERT INTO `department` VALUES (3, '采购部', 'Order Department');
INSERT INTO `department` VALUES (4, '仓储部', 'Warehousing Department');
INSERT INTO `department` VALUES (6, '技术部', 'Technolog Department ');

-- ----------------------------
-- Table structure for employee
-- ----------------------------
DROP TABLE IF EXISTS `employee`;
CREATE TABLE `employee`  (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `password` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `email` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `age` int(11) NULL DEFAULT NULL,
  `admin` bit(1) NULL DEFAULT NULL,
  `dept_id` bigint(20) NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 26 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of employee
-- ----------------------------
INSERT INTO `employee` VALUES (1, 'admin', '1', 'admin@abc.com', 20, b'1', 2);
INSERT INTO `employee` VALUES (2, '赵总', '1', 'zhaoz@wolfcode.cn', 35, b'0', 1);
INSERT INTO `employee` VALUES (3, '赵一明', '1', 'zhaoym@wolfcode.cn', 25, b'0', 1);
INSERT INTO `employee` VALUES (4, '钱总', '1', 'qianz@wolfcode.cn', 35, b'0', 2);
INSERT INTO `employee` VALUES (5, '钱二明', '1', 'qianem@wolfcode.cn', 25, b'0', 2);
INSERT INTO `employee` VALUES (6, '孙总', '1', 'sunz@wolfcode.cn', 35, b'0', 3);
INSERT INTO `employee` VALUES (7, '孙三明', '1', 'sunsm@wolfcode.cn', 25, b'0', 3);
INSERT INTO `employee` VALUES (9, '李四明', '1', 'lism@wolfcode.cn', 25, b'0', 4);
INSERT INTO `employee` VALUES (10, '周总', '1', 'zhouz@wolfcode.cn', 35, b'0', 5);
INSERT INTO `employee` VALUES (11, '周五明', '1', 'zhouwm@wolfcode.cn', 25, b'0', 5);
INSERT INTO `employee` VALUES (12, '吴总', '1', 'wuz@wolfcode.cn', 35, b'0', 6);
INSERT INTO `employee` VALUES (13, '吴六明', '1', 'wulm@wolfcode.cn', 25, b'0', 6);
INSERT INTO `employee` VALUES (14, '郑总', '1', 'zhengz@wolfcode.cn', 35, b'0', 7);
INSERT INTO `employee` VALUES (15, '郑七明', '1', 'zhengqm@wolfcode.cn', 25, b'0', 7);
INSERT INTO `employee` VALUES (16, '孙四明', '1', 'sunsim@wolfcode.cn', 25, b'0', 3);
INSERT INTO `employee` VALUES (17, '孙五明2', '1', 'sunwm@wolfcode.cn', 25, b'0', 1);
INSERT INTO `employee` VALUES (18, '李五明', '1', 'liwm@wolfcode.cn', 25, b'0', 4);
INSERT INTO `employee` VALUES (19, '李六明', '1', 'lilm@wolfcode.cn', 25, b'0', 4);

-- ----------------------------
-- Table structure for employee_role
-- ----------------------------
DROP TABLE IF EXISTS `employee_role`;
CREATE TABLE `employee_role`  (
  `employee_id` bigint(20) NULL DEFAULT NULL,
  `role_id` bigint(20) NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of employee_role
-- ----------------------------
INSERT INTO `employee_role` VALUES (2, 1);
INSERT INTO `employee_role` VALUES (3, 12);
INSERT INTO `employee_role` VALUES (5, 11);
INSERT INTO `employee_role` VALUES (22, 11);
INSERT INTO `employee_role` VALUES (22, 12);
INSERT INTO `employee_role` VALUES (23, 3);
INSERT INTO `employee_role` VALUES (23, 4);
INSERT INTO `employee_role` VALUES (23, 11);
INSERT INTO `employee_role` VALUES (23, 12);
INSERT INTO `employee_role` VALUES (17, 1);
INSERT INTO `employee_role` VALUES (17, 2);
INSERT INTO `employee_role` VALUES (17, 3);
INSERT INTO `employee_role` VALUES (17, 4);
INSERT INTO `employee_role` VALUES (17, 11);
INSERT INTO `employee_role` VALUES (17, 12);
INSERT INTO `employee_role` VALUES (17, 13);

-- ----------------------------
-- Table structure for permission
-- ----------------------------
DROP TABLE IF EXISTS `permission`;
CREATE TABLE `permission`  (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `expression` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 36 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of permission
-- ----------------------------
INSERT INTO `permission` VALUES (4, '客户状态修改', 'customer:updateStatus');
INSERT INTO `permission` VALUES (5, '潜在客户列表', 'customer:potentialList');
INSERT INTO `permission` VALUES (6, '客户池列表', 'customer:poolList');
INSERT INTO `permission` VALUES (7, '失败客户列表', 'customer:failList');
INSERT INTO `permission` VALUES (8, '客户添加/更新', 'customer:saveOrUpdate');
INSERT INTO `permission` VALUES (9, '客户报表列表', 'customerReport:list');
INSERT INTO `permission` VALUES (10, '客户报表条形图', 'customerReport:chartByBar');
INSERT INTO `permission` VALUES (11, '客户报表饼图', 'customerReport:chartByPie');
INSERT INTO `permission` VALUES (12, '客户跟进历史列表', 'customerTraceHistory:list');
INSERT INTO `permission` VALUES (13, '客户跟进历史添加/更新', 'customerTraceHistory:saveOrUpdate');
INSERT INTO `permission` VALUES (14, '客户移交列表', 'customerTransfer:list');
INSERT INTO `permission` VALUES (15, '客户吸纳', 'customerTransfer:absorb');
INSERT INTO `permission` VALUES (16, '客户移交添加/更新', 'customerTransfer:saveOrUpdate');
INSERT INTO `permission` VALUES (17, '部门列表', 'department:list');
INSERT INTO `permission` VALUES (18, '部门编辑', 'department:input');
INSERT INTO `permission` VALUES (19, '部门删除', 'department:delete');
INSERT INTO `permission` VALUES (20, '部门添加/更新', 'department:saveOrUpdate');
INSERT INTO `permission` VALUES (21, '员工删除', 'employee:delete');
INSERT INTO `permission` VALUES (22, '员工列表', 'employee:list');
INSERT INTO `permission` VALUES (23, '员工编辑', 'employee:input');
INSERT INTO `permission` VALUES (24, '员工导入', 'employee:importXls');
INSERT INTO `permission` VALUES (25, '员工批量删除', 'employee:batchDelete');
INSERT INTO `permission` VALUES (26, '员工导出', 'employee:exportXls');
INSERT INTO `permission` VALUES (27, '员工添加/更新', 'employee:saveOrUpdate');
INSERT INTO `permission` VALUES (28, '权限删除', 'permission:delete');
INSERT INTO `permission` VALUES (29, '权限列表', 'permission:list');
INSERT INTO `permission` VALUES (30, '权限加载', 'permission:reload');
INSERT INTO `permission` VALUES (31, '角色删除', 'role:delete');
INSERT INTO `permission` VALUES (32, '角色列表', 'role:list');
INSERT INTO `permission` VALUES (33, '角色编辑', 'role:input');
INSERT INTO `permission` VALUES (34, '角色添加/更新', 'role:saveOrUpdate');
INSERT INTO `permission` VALUES (35, '数据字典字典列表', 'systemDictionary:list');

-- ----------------------------
-- Table structure for role
-- ----------------------------
DROP TABLE IF EXISTS `role`;
CREATE TABLE `role`  (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `sn` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 15 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of role
-- ----------------------------
INSERT INTO `role` VALUES (1, '人事管理', 'HR_MGR');
INSERT INTO `role` VALUES (2, '采购管理', 'ORDER_MGR');
INSERT INTO `role` VALUES (3, '仓储管理', 'WAREHOUSING_MGR');
INSERT INTO `role` VALUES (4, '行政部管理', 'Admin_MGR');
INSERT INTO `role` VALUES (11, '市场经理', 'Market_Manager');
INSERT INTO `role` VALUES (12, '市场专员', 'Market');
INSERT INTO `role` VALUES (13, '2222222', '22222222');
INSERT INTO `role` VALUES (14, '1231', '3132');

-- ----------------------------
-- Table structure for role_permission
-- ----------------------------
DROP TABLE IF EXISTS `role_permission`;
CREATE TABLE `role_permission`  (
  `role_id` bigint(20) NULL DEFAULT NULL,
  `permission_id` bigint(20) NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of role_permission
-- ----------------------------
INSERT INTO `role_permission` VALUES (1, 5);
INSERT INTO `role_permission` VALUES (1, 6);
INSERT INTO `role_permission` VALUES (1, 7);
INSERT INTO `role_permission` VALUES (1, 8);
INSERT INTO `role_permission` VALUES (1, 11);
INSERT INTO `role_permission` VALUES (14, 4);
INSERT INTO `role_permission` VALUES (14, 5);
INSERT INTO `role_permission` VALUES (14, 6);
INSERT INTO `role_permission` VALUES (14, 7);
INSERT INTO `role_permission` VALUES (14, 8);
INSERT INTO `role_permission` VALUES (14, 9);
INSERT INTO `role_permission` VALUES (14, 10);
INSERT INTO `role_permission` VALUES (14, 11);

-- ----------------------------
-- Table structure for systemdictionary
-- ----------------------------
DROP TABLE IF EXISTS `systemdictionary`;
CREATE TABLE `systemdictionary`  (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `sn` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `title` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `intro` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 33 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of systemdictionary
-- ----------------------------
INSERT INTO `systemdictionary` VALUES (1, 'job', '职业', '客户职业');
INSERT INTO `systemdictionary` VALUES (2, 'source', '来源', '客户来源渠道');
INSERT INTO `systemdictionary` VALUES (3, 'intentionDegree', '意向程度', '客户意向，用★表示');
INSERT INTO `systemdictionary` VALUES (4, 'subject', '学科', '学科分类');
INSERT INTO `systemdictionary` VALUES (5, 'payment', '收款类型', '学费收款方式');
INSERT INTO `systemdictionary` VALUES (6, 'property', '办学性质', '公办/民办');
INSERT INTO `systemdictionary` VALUES (7, 'importance', '客户重要程度', '');
INSERT INTO `systemdictionary` VALUES (14, 'foreignLangLevel', '外语水平', '各类考证');
INSERT INTO `systemdictionary` VALUES (15, 'clientType', '客户类型', '');
INSERT INTO `systemdictionary` VALUES (16, 'source', '客户来源', '');
INSERT INTO `systemdictionary` VALUES (19, 'education', '学历', '学校的办学层次');
INSERT INTO `systemdictionary` VALUES (26, 'communicationMethod', '交流方式', '跟踪潜在学员的方式');
INSERT INTO `systemdictionary` VALUES (27, 'tracePurpose', '跟进目的', '营销要达到目标');
INSERT INTO `systemdictionary` VALUES (28, 'wantedLevel', '意向程度', '客户意向，用★表示');
INSERT INTO `systemdictionary` VALUES (31, 'score', '评分', '客户跟踪评审分数');

-- ----------------------------
-- Table structure for systemdictionaryitem
-- ----------------------------
DROP TABLE IF EXISTS `systemdictionaryitem`;
CREATE TABLE `systemdictionaryitem`  (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `parent_id` bigint(20) NOT NULL,
  `title` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `sequence` int(255) NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `parent_id`(`parent_id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 83 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of systemdictionaryitem
-- ----------------------------
INSERT INTO `systemdictionaryitem` VALUES (1, 1, '老师', 2);
INSERT INTO `systemdictionaryitem` VALUES (2, 1, '司机', 1);
INSERT INTO `systemdictionaryitem` VALUES (3, 1, '老板', 1);
INSERT INTO `systemdictionaryitem` VALUES (4, 2, '自身途径', 1);
INSERT INTO `systemdictionaryitem` VALUES (5, 2, '营销广告', 4);
INSERT INTO `systemdictionaryitem` VALUES (6, 2, '老学员推荐', 1);
INSERT INTO `systemdictionaryitem` VALUES (7, 3, '★', 1);
INSERT INTO `systemdictionaryitem` VALUES (9, 3, '★★', 1);
INSERT INTO `systemdictionaryitem` VALUES (13, 4, 'java', 1);
INSERT INTO `systemdictionaryitem` VALUES (14, 4, 'ios', 1);
INSERT INTO `systemdictionaryitem` VALUES (15, 4, 'c#', 1);
INSERT INTO `systemdictionaryitem` VALUES (16, 5, '信用卡', 1);
INSERT INTO `systemdictionaryitem` VALUES (17, 5, '贷款', 1);
INSERT INTO `systemdictionaryitem` VALUES (18, 5, '银行卡', 1);
INSERT INTO `systemdictionaryitem` VALUES (19, 5, '支付宝', 1);
INSERT INTO `systemdictionaryitem` VALUES (20, 6, '公办', 1);
INSERT INTO `systemdictionaryitem` VALUES (21, 6, '民办', 1);
INSERT INTO `systemdictionaryitem` VALUES (22, 6, '独立院校', 1);
INSERT INTO `systemdictionaryitem` VALUES (23, 6, '其他', 1);
INSERT INTO `systemdictionaryitem` VALUES (28, 14, 'CET4', 1);
INSERT INTO `systemdictionaryitem` VALUES (29, 14, 'CET6', 1);
INSERT INTO `systemdictionaryitem` VALUES (30, 14, '专八', 1);
INSERT INTO `systemdictionaryitem` VALUES (31, 15, '线上', 1);
INSERT INTO `systemdictionaryitem` VALUES (32, 15, '线下', 1);
INSERT INTO `systemdictionaryitem` VALUES (33, 16, 'QQ', 1);
INSERT INTO `systemdictionaryitem` VALUES (34, 16, '微信', 1);
INSERT INTO `systemdictionaryitem` VALUES (35, 17, '广州校区', 1);
INSERT INTO `systemdictionaryitem` VALUES (36, 17, '西安校区', 1);
INSERT INTO `systemdictionaryitem` VALUES (37, 17, '上海校区', 1);
INSERT INTO `systemdictionaryitem` VALUES (38, 17, '北京校区', 1);
INSERT INTO `systemdictionaryitem` VALUES (39, 17, '深圳校区', 1);
INSERT INTO `systemdictionaryitem` VALUES (40, 7, '★', 1);
INSERT INTO `systemdictionaryitem` VALUES (41, 7, '★★', 1);
INSERT INTO `systemdictionaryitem` VALUES (42, 7, '★★★', 1);
INSERT INTO `systemdictionaryitem` VALUES (43, 7, '★★★★', 1);
INSERT INTO `systemdictionaryitem` VALUES (44, 7, '★★★★★', 1);
INSERT INTO `systemdictionaryitem` VALUES (45, 7, '★★★★★★', 1);
INSERT INTO `systemdictionaryitem` VALUES (46, 7, '★★★★★★★', 1);
INSERT INTO `systemdictionaryitem` VALUES (47, 3, '★★★', 1);
INSERT INTO `systemdictionaryitem` VALUES (48, 3, '★★★★', 1);
INSERT INTO `systemdictionaryitem` VALUES (49, 3, '★★★★★', 1);
INSERT INTO `systemdictionaryitem` VALUES (50, 19, '高中', 1);
INSERT INTO `systemdictionaryitem` VALUES (51, 19, '大专', 1);
INSERT INTO `systemdictionaryitem` VALUES (52, 19, '本科', 1);
INSERT INTO `systemdictionaryitem` VALUES (53, 19, '研究生', 1);
INSERT INTO `systemdictionaryitem` VALUES (54, 1, '学生', 1);
INSERT INTO `systemdictionaryitem` VALUES (55, 20, '高中', 1);
INSERT INTO `systemdictionaryitem` VALUES (56, 20, '大专', 1);
INSERT INTO `systemdictionaryitem` VALUES (57, 20, '本科', 1);
INSERT INTO `systemdictionaryitem` VALUES (58, 20, '研究生', 1);
INSERT INTO `systemdictionaryitem` VALUES (59, 24, '正常', 1);
INSERT INTO `systemdictionaryitem` VALUES (60, 24, '正式学员', 1);
INSERT INTO `systemdictionaryitem` VALUES (61, 25, 'java学院', 1);
INSERT INTO `systemdictionaryitem` VALUES (62, 25, 'IOS学院', 1);
INSERT INTO `systemdictionaryitem` VALUES (63, 25, 'UI学院', 1);
INSERT INTO `systemdictionaryitem` VALUES (64, 25, 'Python学院', 1);
INSERT INTO `systemdictionaryitem` VALUES (65, 26, '营销QQ', 1);
INSERT INTO `systemdictionaryitem` VALUES (66, 26, '来电咨询', 1);
INSERT INTO `systemdictionaryitem` VALUES (67, 26, '去电跟踪', 1);
INSERT INTO `systemdictionaryitem` VALUES (68, 26, '短信', 1);
INSERT INTO `systemdictionaryitem` VALUES (69, 27, '潜在客户跟进', 1);
INSERT INTO `systemdictionaryitem` VALUES (70, 27, '常规跟进', 1);
INSERT INTO `systemdictionaryitem` VALUES (71, 27, '正式客户跟进', 1);
INSERT INTO `systemdictionaryitem` VALUES (72, 27, '其他', 1);
INSERT INTO `systemdictionaryitem` VALUES (73, 28, '★', 1);
INSERT INTO `systemdictionaryitem` VALUES (74, 28, '★★', 1);
INSERT INTO `systemdictionaryitem` VALUES (75, 28, '★★★', 1);
INSERT INTO `systemdictionaryitem` VALUES (76, 29, '高中', 1);
INSERT INTO `systemdictionaryitem` VALUES (77, 29, '大专', 1);
INSERT INTO `systemdictionaryitem` VALUES (78, 29, '本科', 1);
INSERT INTO `systemdictionaryitem` VALUES (79, 31, '差', 1);
INSERT INTO `systemdictionaryitem` VALUES (80, 31, '良', 1);
INSERT INTO `systemdictionaryitem` VALUES (81, 31, '优', 1);

SET FOREIGN_KEY_CHECKS = 1;
