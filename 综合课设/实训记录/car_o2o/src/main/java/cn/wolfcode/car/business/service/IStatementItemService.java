package cn.wolfcode.car.business.service;

import cn.wolfcode.car.business.domain.StatementItem;
import cn.wolfcode.car.business.query.StatementItemQuery;
import cn.wolfcode.car.common.base.page.TablePageInfo;

import java.util.List;

/**
 * 结算单明细接口
 */
public interface IStatementItemService {

    /**
     * 分页
     * @param qo
     * @return
     */
    TablePageInfo<StatementItem> query(StatementItemQuery qo);


    /**
     * 查单个
     * @param id
     * @return
     */
    StatementItem get(Long id);


    /**
     * 保存
     * @param
     */
    void save(StatementItem statementItem);

  
    /**
     * 更新
     * @param
     */
    void update(StatementItem statementItem);

    /**
     *  批量删除
     * @param ids
     */
    void deleteBatch(String ids);

    /**
     * 查询全部
     * @return
     */
    List<StatementItem> list();

    /**
     * 批量添加结算单明细
     * @param list
     */
    void saveItems(List<StatementItem> list);

}
