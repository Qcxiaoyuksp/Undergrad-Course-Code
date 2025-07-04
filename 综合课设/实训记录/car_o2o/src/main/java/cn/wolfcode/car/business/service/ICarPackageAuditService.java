package cn.wolfcode.car.business.service;

import cn.wolfcode.car.business.domain.CarPackageAudit;
import cn.wolfcode.car.business.domain.HistoricComment;
import cn.wolfcode.car.business.query.CarPackageAuditQuery;
import cn.wolfcode.car.common.base.page.TablePageInfo;

import java.io.InputStream;

/**
 * 业务接口
 */
public interface ICarPackageAuditService {

    /**
     * 分页
     * @param qo
     * @return
     */
    TablePageInfo<CarPackageAudit> query(CarPackageAuditQuery qo);


    /**
     * 查单个
     * @param id
     * @return
     */
    CarPackageAudit get(Long id);


    /**
     * 保存
     * @param C
     */
    void save(CarPackageAudit carPackageAudit);

  
    /**
     * 更新
     * @param
     */
    void update(CarPackageAudit carPackageAudit);

    /**
     *  批量删除
     * @param ids
     */
    void deleteBatch(String ids);

    /**
     * 流程查看
     * @param id
     * @return
     */
    InputStream processImg(Long id);

    /**
     * 撤销流程
     * @param id
     */
    void cancelApply(Long id);

    /**
     * 查询代办任务列表（有分页）
     * @param qo
     * @return
     */
    TablePageInfo<CarPackageAudit> todoQuery(CarPackageAuditQuery qo);

    /**
     * 审批功能
     * @param id
     * @param auditStatus
     * @param info
     */
    void audit(Long id, String auditStatus, String info);

    /**
     * 我的已办列表
     * @param qo
     * @return
     */
    TablePageInfo<CarPackageAudit> doneQuery(CarPackageAuditQuery qo);

    /**
     * 查询审批历史列表
     * @param instanceId
     * @return
     */
    TablePageInfo<HistoricComment> listHistoryQuery(String instanceId);
}
