package cn.wolfcode.car.business.domain;

import lombok.Getter;
import lombok.Setter;

@Setter
@Getter
public class HistoricComment {
    private String taskName;//任务名称
    private String comment;//批注信息
    private String startTime;//开始时间
    private String endTime;//结束时间
    private String durationInMillis;//耗时
}