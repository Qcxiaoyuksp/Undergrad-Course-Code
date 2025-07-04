package cn.wolfcode.car.business.service;

import cn.wolfcode.car.business.domain.ServiceItem;
import cn.wolfcode.car.business.domain.Statement;
import cn.wolfcode.car.business.query.StatementQuery;
import cn.wolfcode.car.common.base.page.TablePageInfo;

import java.math.BigDecimal;
import java.util.List;

public interface IStatementService {
    //新增
    void insert(Statement statement);

    //修改
    void update(Statement statement);

    //删除
    void delete(Long id);

    //根据id查询
    Statement get(Long id);

    //查询全部
    List<Statement> listAll();

    TablePageInfo<Statement> selectForList(StatementQuery qo);

    void edit(Statement statement);

    void remove(Long[] id);

    void updateAmount(Long statementId, BigDecimal totalAmount, BigDecimal totalQuantity, BigDecimal disCountPrice);

}
