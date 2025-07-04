package cn.wolfcode.car.business.query;

import cn.wolfcode.car.common.base.query.QueryObject;
import lombok.Getter;
import lombok.Setter;
import org.springframework.format.annotation.DateTimeFormat;

import java.util.Calendar;
import java.util.Date;

@Getter
@Setter
public class AppointmentQuery extends QueryObject {
    private String customerName;
    private String customerPhone;
    private Integer status;
    // 按时间搜索
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private Date beginTime;
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private Date endTime;

    public Date getEndTime(){
        if(endTime == null){
            return null;
        }
        // 将日期变为当天的 23:59:59
        Calendar calendar = Calendar.getInstance();
        calendar.setTime(endTime);
        // +1天
        calendar.add(Calendar.DAY_OF_YEAR,1);
        // -1秒
        calendar.add(Calendar.SECOND,-1);
        return calendar.getTime();
    }
}
