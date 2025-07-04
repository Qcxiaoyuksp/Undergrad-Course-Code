package cn.wolfcode.car.business.service;

import cn.wolfcode.car.business.domain.Statement;
import cn.wolfcode.car.business.query.StatementQuery;
import cn.wolfcode.car.common.base.page.TablePageInfo;

import java.util.List;

/**
 * 结算单接口
 */
public interface IStatementService {

    /**
     * 分页
     * @param qo
     * @return
     */
    TablePageInfo<Statement> query(StatementQuery qo);


    /**
     * 查单个
     * @param id
     * @return
     */
    Statement get(Long id);


    /**
     * 保存
     * @param Statement
     */
    void save(Statement statement);

  
    /**
     * 更新
     * @param Statement
     */
    void update(Statement statement);

    /**
     *  批量删除
     * @param ids
     */
    void deleteBatch(String ids);

    /**
     * 查询全部结算单
     * @return
     */
    List<Statement> list();

    /**
     * 批量软删除
     * @param ids
     */
    void remove(Long[] ids);

    /**
     * 结算单支付
     * @param statementId
     */
    void pay(Long statementId);

    /**
     * 通过预约单生成结算单
     */
    Long generateStatement(Long appointmentId);
}
