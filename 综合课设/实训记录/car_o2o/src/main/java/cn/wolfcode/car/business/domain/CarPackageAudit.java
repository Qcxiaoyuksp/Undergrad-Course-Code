package cn.wolfcode.car.business.domain;

import com.fasterxml.jackson.annotation.JsonFormat;
import lombok.Getter;
import lombok.Setter;

import java.math.BigDecimal;
import java.util.Date;

/**
 * 套餐审核对象
 */
@Setter
@Getter
public class CarPackageAudit {
    public static final String AUDIT_TYPE = "car_package";//数据字典的value
    public static final Integer STATUS_IN_ROGRESS = 0;//审核中
    public static final Integer STATUS_REJECT = 1;//审核拒绝
    public static final Integer STATUS_PASS = 2;//审核通过
    public static final Integer STATUS_CANCEL = 3;//审核撤销
    private static final long serialVersionUID = 1L;
    /** 主键*/
    private Long id;
    /** 服务单项id*/
    private Long serviceItemId;
    /** */
    private String serviceItemName;
    /** 服务单项备注*/
    private String serviceItemInfo;
    /** 服务单项审核价格*/
    private BigDecimal serviceItemPrice;
    /** 流程实例id*/
    private String instanceId;
    /** 创建者*/
    private String creatorId;
    /** 创建时间*/
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss",timezone = "GMT+8")
    private Date createTime;
    /** 备注*/
    private String info;
    /** 状态【进行中0/审核拒绝1/审核通过2/审核撤销3】*/
    private Integer status= STATUS_IN_ROGRESS;;
}