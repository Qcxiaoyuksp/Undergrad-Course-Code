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

 Date: 16/10/2023 16:10:40
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for standardgeoentity
-- ----------------------------
DROP TABLE IF EXISTS `standardgeoentity`;
CREATE TABLE `standardgeoentity`  (
  `countryId` bigint(5) NOT NULL COMMENT '机场所在国家id',
  `countryName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '机场所在国家名称',
  `countryEnName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '机场所在国家英文名',
  `provinceId` binary(5) NULL DEFAULT NULL COMMENT '机场所在省ID',
  `provinceName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '机场所在省名',
  `provinceEnName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '机场所在省英文名',
  `cityId` bigint(5) NULL DEFAULT NULL COMMENT '机场所在城市id',
  `cityName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '机场所在城市名',
  `cityEnName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '机场所在城市英文名',
  `districtId` binary(5) NULL DEFAULT NULL COMMENT '机场所在区县ID',
  `districtName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '机场所在区县名',
  `districtEnName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '机场所在区县英文名',
  PRIMARY KEY (`countryId`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of standardgeoentity
-- ----------------------------
INSERT INTO `standardgeoentity` VALUES (1, '张三', NULL, NULL, NULL, NULL, 1, '长春', '', NULL, '北京', NULL);

SET FOREIGN_KEY_CHECKS = 1;
