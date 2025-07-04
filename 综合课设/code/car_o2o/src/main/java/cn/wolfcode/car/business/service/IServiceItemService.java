package cn.wolfcode.car.business.service;

import cn.wolfcode.car.business.domain.ServiceItem;
import cn.wolfcode.car.business.query.ServiceItemQuery;
import cn.wolfcode.car.common.base.page.TablePageInfo;
import cn.wolfcode.car.common.base.query.QueryObject;

import java.util.List;

/**
 * 服务单项接口
 */
public interface IServiceItemService {
    //新增
    void insert(ServiceItem item);

    //修改
    void update(ServiceItem item);

    //删除
    void delete(Long id);

    //根据id查询
    ServiceItem get(Long id);

    //查询全部
    List<ServiceItem> listAll();

    TablePageInfo<ServiceItem> selectForList(ServiceItemQuery qo);

    void edit(ServiceItem serviceItem);

    void saleOn(Long id);

    void saleOff(Long id);
}
