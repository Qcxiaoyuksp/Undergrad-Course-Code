package cn.wolfcode.car.business.service.impl;

import cn.wolfcode.car.business.domain.ServiceItem;
import cn.wolfcode.car.business.mapper.ServiceItemMapper;
import cn.wolfcode.car.business.query.ServiceItemQuery;
import cn.wolfcode.car.business.service.IServiceItemService;
import cn.wolfcode.car.common.base.page.TablePageInfo;
import cn.wolfcode.car.common.base.query.QueryObject;
import cn.wolfcode.car.common.exception.BusinessException;
import com.github.pagehelper.PageHelper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.context.properties.ConfigurationProperties;
import org.springframework.stereotype.Service;

import java.util.Date;
import java.util.List;

/**
 * 服务单项接口
 */
@Service
public class ServiceItemServiceImpl implements IServiceItemService {

    //注入mapper
    @Autowired
    private ServiceItemMapper serviceItemmapper;

    @Override
    public void insert(ServiceItem item) {
        item.setCreateTime(new Date());
        serviceItemmapper.insert(item);
    }

    @Override
    public void update(ServiceItem item) {
        serviceItemmapper.updateByPrimaryKey(item);
    }

    @Override
    public void delete(Long id) {
        serviceItemmapper.deleteByPrimaryKey(id);
    }

    @Override
    public ServiceItem get(Long id) {

        return serviceItemmapper.selectByPrimaryKey(id);
    }

    @Override
    public List<ServiceItem> listAll() {
        return serviceItemmapper.selectAll();
    }



    @Override
    public TablePageInfo<ServiceItem> selectForList(ServiceItemQuery qo) {
        //使用分页框架实现分页功能PageHelper
        PageHelper.startPage(qo.getPageNum(),qo.getPageSize());
        TablePageInfo<ServiceItem> tablePageInfo = new TablePageInfo<ServiceItem>(serviceItemmapper.selectForList(qo));
        return tablePageInfo;
    }

    //下架业务逻辑书写
    @Override
    public void saleOff(Long id) {
        //书写业务逻辑
        ServiceItem serviceItem = this.get(id);
        //上架才可下架
        if (!ServiceItem.SALESTATUS_ON.equals(serviceItem.getSaleStatus())){
            throw new BusinessException("必须为上架商品才可以下架");
        }
        //修改为下架状态
        serviceItemmapper.changeSaleStatus(id,ServiceItem.SALESTATUS_OFF);
    }

    //上架方法
    @Override
    public void saleOn(Long id) {
        //书写业务逻辑
        ServiceItem serviceItem = this.get(id);
        //下架才可上架
        if (ServiceItem.SALESTATUS_ON.equals(serviceItem.getSaleStatus())){
            throw new BusinessException("必须为下架商品才可以上架");
        }
        //是套餐且为审核通过才能上架
        if (
                !(ServiceItem.CARPACKAGE_YES.equals(serviceItem.getCarPackage())
        && ServiceItem.AUDITSTATUS_APPROVED.equals(serviceItem.getAuditStatus())

        || ServiceItem.AUDITSTATUS_NO_REQUIRED.equals(serviceItem.getAuditStatus()))){
            throw new BusinessException("套餐状态必须为审核通过才可以进行上架");
        }
        serviceItemmapper.changeSaleStatus(id,ServiceItem.SALESTATUS_ON);
    }

    //编辑方法
    @Override
    public void edit(ServiceItem serviceItem) {
        //书写业务逻辑
        ServiceItem oldServiceItem = this.get(serviceItem.getId());
        //上架不可修改
        if (ServiceItem.SALESTATUS_ON.equals(oldServiceItem.getSaleStatus())){
            throw new BusinessException("上架状态不能修改");
        }
        //是套餐且状态为审核不修改
        if (ServiceItem.CARPACKAGE_YES.equals(oldServiceItem.getCarPackage())
            && ServiceItem.AUDITSTATUS_AUDITING.equals(oldServiceItem.getAuditStatus())){
            throw new BusinessException("审核中的订单不能修改");
        }
        //是套餐且状态为审核通过，可修改，但是设置为初始化
        if (ServiceItem.CARPACKAGE_YES.equals(oldServiceItem.getCarPackage())
        && ServiceItem.AUDITSTATUS_APPROVED.equals(oldServiceItem.getAuditStatus())){
            //设置为初始化
            serviceItem.setAuditStatus(ServiceItem.AUDITSTATUS_INIT);
        }
        serviceItemmapper.edit(serviceItem);
    }
}
