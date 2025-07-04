package cn.wolfcode.car.business.query;

import cn.wolfcode.car.common.base.query.QueryObject;
import com.fasterxml.jackson.annotation.JsonFormat;
import lombok.Data;
import org.springframework.format.annotation.DateTimeFormat;

import java.util.Calendar;
import java.util.Date;

@Data
public class StatementItemQuery extends QueryObject {
    private Long statementId;
}
