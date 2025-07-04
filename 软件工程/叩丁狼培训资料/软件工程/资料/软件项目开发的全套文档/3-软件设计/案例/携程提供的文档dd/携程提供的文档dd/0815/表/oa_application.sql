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

 Date: 28/09/2023 14:01:14
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for oa_application
-- ----------------------------
DROP TABLE IF EXISTS `oa_application`;
CREATE TABLE `oa_application`  (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '院外出差人',
  `depart_name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '部门',
  `create_time` datetime(0) NULL DEFAULT NULL COMMENT '填表时间',
  `normal_name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '出差人用户名',
  `business_trip_name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '院外出差人',
  `Origin` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '出发地',
  `Destination` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '目的地',
  `departure_time` datetime(6) NULL DEFAULT NULL COMMENT '出发时间',
  `vehicle` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '交通工具',
  `source_of_funding` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '经费来源',
  `budget_department` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '预算部门',
  `project_ leader` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '项目负责人',
  `business_trip_reasons` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '出差事由',
  `residing_in_the_city` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '入住城市',
  `opinions_of_department_head` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '部门负责人意见',
  `manager_approved` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '主管院领导审批',
  `approval_by_chie_ Accountant` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '总会计师审批',
  `dean_ approval` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '院长审批',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
