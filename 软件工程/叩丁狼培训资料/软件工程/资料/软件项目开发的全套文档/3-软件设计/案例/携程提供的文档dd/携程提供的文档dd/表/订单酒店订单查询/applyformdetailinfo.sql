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

 Date: 18/10/2023 11:16:18
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for applyformdetailinfo
-- ----------------------------
DROP TABLE IF EXISTS `applyformdetailinfo`;
CREATE TABLE `applyformdetailinfo`  (
  `reasonCode` varchar(60) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '修改原因',
  `reasonDesc` varchar(60) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '原因说明',
  `sceneList` varchar(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '修改单场景\r\n1:修改酒店\r\n2：修改房型-金额变化\r\n3：提前入住 \r\n4：推出入住 \r\n5：中段取消 \r\n6：提前离店 \r\n7：推迟离店 \r\n8：新入离时间和原单完全没有重叠 \r\n9：减少间数 \r\n10：增加间数 \r\n11：修改最晚抵店时间 \r\n12：修改入住人姓名 \r\n13：修改房型：金额无变化 \r\n14：修改联系人'
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
