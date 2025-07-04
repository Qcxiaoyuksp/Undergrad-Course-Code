package cn.wolfcode.car.business.domain;

import com.fasterxml.jackson.annotation.JsonFormat;
import lombok.Getter;
import lombok.Setter;

import java.util.Date;

@Getter
@Setter
public class BpmnInfo {
    /** 主键*/
    private Long id;

    /** 流程名称-数据字典label*/
    private String bpmnLabel;

    /** 流程类型-数据字典value*/
    private String bpmnType;

    /** activity流程定义生成的key*/
    private String processDefinitionKey;

    /** 部署时间*/
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    private Date deployTime;

    /** 版本号*/
    private Integer version;

    /** 描述信息*/
    private String info;
}