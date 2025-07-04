package cn.wolfcode.car.business.query;

import cn.wolfcode.car.common.base.query.QueryObject;
import lombok.Getter;
import lombok.Setter;

@Getter
@Setter
public class StatementItemQuery extends QueryObject {
    // 高级查询条件为 结算单 ID
    private Long statementId;
}
