package cn.wolfcode.car.business.service;

import cn.wolfcode.car.business.domain.ServiceItem;
import cn.wolfcode.car.business.query.ServiceItemQuery;
import cn.wolfcode.car.common.base.page.TablePageInfo;

import java.util.List;

/**
 * 服务单项接口
 */
public interface IServiceItemService {

    /**
     * 分页
     * @param qo
     * @return
     */
    TablePageInfo<ServiceItem> query(ServiceItemQuery qo);


    /**
     * 查单个
     * @param id
     * @return
     */
    ServiceItem get(Long id);


    /**
     * 保存
     * @param serviceItem
     */
    void save(ServiceItem serviceItem);

  
    /**
     * 更新
     * @param serviceItem
     */
    void update(ServiceItem serviceItem);

    /**
     *  批量删除
     * @param ids
     */
    void deleteBatch(String ids);

    /**
     * 查询全部
     * @return
     */
    List<ServiceItem> list();

    /**
     * 上架
     * @param id
     */
    void saleOn(Long id);

    /**
     * 下架
     * @param id
     */
    void saleOff(Long id);

    /**
     * 发起审核
     * @param id
     * @param showOwnerId
     * @param financeId
     * @param info
     */
    void startAudit(Long id, Long showOwnerId, Long financeId, String info);

    /**
     * 根据服务单项 id，修改服务单项状态
     * @param serviceItemId
     * @param auditstatusInit
     */
    void changeAuditStatus(Long serviceItemId, Integer auditstatusInit);
}
