package cn.wolfcode.car.business.query;

import cn.wolfcode.car.common.base.query.QueryObject;
import lombok.Data;

@Data
public class ServiceItemQuery extends QueryObject {
    private String name;//姓名
    private Integer carPackage;//是否套餐
    private Integer serviceCatalog;//服务分类
    private Integer auditStatus;//是否审核
    private Integer saleStatus;//上架状态
}
