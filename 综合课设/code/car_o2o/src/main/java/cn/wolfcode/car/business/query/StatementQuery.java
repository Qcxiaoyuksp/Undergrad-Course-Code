package cn.wolfcode.car.business.query;

import cn.wolfcode.car.common.base.query.QueryObject;
import com.fasterxml.jackson.annotation.JsonFormat;
import lombok.Data;
import org.springframework.format.annotation.DateTimeFormat;

import java.util.Calendar;
import java.util.Date;

@Data
public class StatementQuery extends QueryObject {

    @DateTimeFormat(pattern = "yyyy-MM-dd")
    @JsonFormat(pattern = "yyyy-MM-dd")
    private Date startTime;

    @DateTimeFormat(pattern = "yyyy-MM-dd")
    @JsonFormat(pattern = "yyyy-MM-dd")
    private Date endTime;

    public Date getEndTime(){
        if (endTime != null){
            Calendar calendar = Calendar.getInstance();
            calendar.setTime(endTime);
            calendar.add(Calendar.DAY_OF_YEAR,1);
            calendar.add(Calendar.SECOND,-1);
            return calendar.getTime();
        }
        return endTime;
    }
}
