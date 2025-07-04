package cn.wolfcode.car.business.service;

import cn.wolfcode.car.business.domain.Statement;
import cn.wolfcode.car.business.domain.StatementItem;
import cn.wolfcode.car.business.query.StatementItemQuery;
import cn.wolfcode.car.business.query.StatementQuery;
import cn.wolfcode.car.common.base.page.TablePageInfo;

import java.util.List;

public interface IStatementItemService {
    //新增
    void insert(StatementItem statementItem);

    //修改
    void update(StatementItem statementItem);

    //删除
    void delete(Long id);

    //根据id查询
    StatementItem get(Long id);

    //查询全部
    List<StatementItem> listAll();

    void saveItems(List<StatementItem> items);

    TablePageInfo<StatementItem> query(StatementItemQuery qo);

}
