package cn.wolfcode.car.business.service.impl;

import cn.wolfcode.car.business.domain.BpmnInfo;
import cn.wolfcode.car.business.domain.CarPackageAudit;
import cn.wolfcode.car.business.domain.ServiceItem;
import cn.wolfcode.car.business.mapper.ServiceItemMapper;
import cn.wolfcode.car.business.query.ServiceItemQuery;
import cn.wolfcode.car.business.service.IBpmnInfoService;
import cn.wolfcode.car.business.service.ICarPackageAuditService;
import cn.wolfcode.car.business.service.IServiceItemService;
import cn.wolfcode.car.common.base.page.TablePageInfo;
import cn.wolfcode.car.common.exception.BusinessException;
import cn.wolfcode.car.common.util.Convert;
import cn.wolfcode.car.shiro.ShiroUtils;
import com.github.pagehelper.PageHelper;
import org.activiti.engine.RuntimeService;
import org.activiti.engine.runtime.ProcessInstance;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Lazy;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

@Service
@Transactional
public class ServiceItemServiceImpl implements IServiceItemService {

    @Autowired
    private ServiceItemMapper serviceItemMapper;
    @Autowired
    @Lazy
    private ICarPackageAuditService carPackageAuditService;
    @Autowired
    private IBpmnInfoService bpmnInfoService;
    @Autowired
    private RuntimeService runtimeService;

    @Override
    public TablePageInfo<ServiceItem> query(ServiceItemQuery qo) {
        PageHelper.startPage(qo.getPageNum(), qo.getPageSize());
        return new TablePageInfo<ServiceItem>(serviceItemMapper.selectForList(qo));
    }


    @Override
    public void save(ServiceItem serviceItem) {
        // 从安全角度考虑，前台传递过来的对象是不可以直接使用的。
        // 所以我们都新建对象。这样无论如何都不会因为前台传递了默认值而改变我们的默认值数据。
        ServiceItem newObj = new ServiceItem();
        newObj.setName(serviceItem.getName());
        newObj.setOriginalPrice(serviceItem.getOriginalPrice());
        newObj.setDiscountPrice(serviceItem.getDiscountPrice());
        newObj.setCarPackage(serviceItem.getCarPackage());
        newObj.setInfo(serviceItem.getInfo());
        newObj.setCreateTime(new Date());
        newObj.setServiceCatalog(serviceItem.getServiceCatalog());
        // 新增分为套餐和非套餐
        if (ServiceItem.CARPACKAGE_YES.equals(newObj.getCarPackage())) {
            // 是套餐默认审核状态为 -->  初始化
            newObj.setAuditStatus(ServiceItem.AUDITSTATUS_INIT);
        } else {
            // 非套餐默认审核状态为 -->  无需审核
            newObj.setAuditStatus(ServiceItem.AUDITSTATUS_NO_REQUIRED);
        }
        serviceItemMapper.insert(newObj);
    }

    @Override
    public ServiceItem get(Long id) {
        return serviceItemMapper.selectByPrimaryKey(id);
    }


    @Override
    public void update(ServiceItem serviceItem) {
        ServiceItem newObj = this.get(serviceItem.getId());
        if (ServiceItem.SALESTATUS_ON.equals(newObj.getSaleStatus())) {
            throw new BusinessException("处于上架的服务单项不允许修改");
        }
        if (ServiceItem.AUDITSTATUS_AUDITING.equals(newObj.getAuditStatus())) {
            throw new BusinessException("处于审核中的服务单项不允许修改");
        }
        // 如果是套餐，且审批通过，可以修改，但需要将状态改为初始化
        if (ServiceItem.AUDITSTATUS_APPROVED.equals(newObj.getAuditStatus())) {
            newObj.setAuditStatus(ServiceItem.AUDITSTATUS_INIT);
        }
        // 把前台用户传递的属性封装到查询出来的当前对象中。
        newObj.setName(serviceItem.getName());
        newObj.setOriginalPrice(serviceItem.getOriginalPrice());
        newObj.setDiscountPrice(serviceItem.getDiscountPrice());
        // newObj.setCarPackage(serviceItem.getCarPackage());
        newObj.setInfo(serviceItem.getInfo());
        // newObj.setCreateTime(new Date());
        newObj.setServiceCatalog(serviceItem.getServiceCatalog());
        serviceItemMapper.updateByPrimaryKey(newObj);
    }

    @Override
    public void deleteBatch(String ids) {
        Long[] dictIds = Convert.toLongArray(ids);
        for (Long dictId : dictIds) {
            serviceItemMapper.deleteByPrimaryKey(dictId);
        }
    }

    @Override
    public List<ServiceItem> list() {
        return serviceItemMapper.selectAll();
    }

    @Override
    public void saleOn(Long id) {
        // 根据服务单项 id 查询当前服务单项对象
        ServiceItem serviceItem = this.get(id);
        // 处于下架状态才可以上架
        if (ServiceItem.SALESTATUS_ON.equals(serviceItem.getSaleStatus())) {
            throw new BusinessException("目前该商品已经在上架，无需重复操作");
        }
        // 若是套餐必须是审核通过状态才可以上架
        if (ServiceItem.CARPACKAGE_YES.equals(serviceItem.getCarPackage())
                && !ServiceItem.AUDITSTATUS_APPROVED.equals(serviceItem.getAuditStatus())) {
            throw new BusinessException("套裁服务单项必须审核通过才可以上架");
        }
        // 下架 && (非套餐 || 审核通过)  ==> 把状态改为上架
        // 不建议使用原始编辑。因为原始的编辑方法只是为了更新前台传递的数据。
        serviceItemMapper.updateSaleStatusById(serviceItem.getId(), ServiceItem.SALESTATUS_ON);
    }

    @Override
    public void saleOff(Long id) {
        // 根据服务单项 id 查询当前服务单项对象
        ServiceItem serviceItem = this.get(id);
        // 处于上架状态才可以下架
        if (ServiceItem.SALESTATUS_OFF.equals(serviceItem.getSaleStatus())) {
            throw new BusinessException("目前该商品已经下架，无需重复操作");
        }
        serviceItemMapper.updateSaleStatusById(serviceItem.getId(), ServiceItem.SALESTATUS_OFF);
    }

    @Override
    @Transactional
    public void startAudit(Long id, Long showOwnerId, Long financeId, String info) {
        // 有什么样的限制条件，就是前台校验的后台也要校验。
        // 根据服务单项 id 查询该服务单项，判断是否为套餐且状态处于初始化或重新调整
        ServiceItem serviceItem = this.get(id);
        if (!(ServiceItem.CARPACKAGE_YES.equals(serviceItem.getCarPackage()) &&
                (ServiceItem.AUDITSTATUS_INIT.equals(serviceItem.getAuditStatus())
                        || ServiceItem.AUDITSTATUS_REPLY.equals(serviceItem.getAuditStatus())))) {
            throw new BusinessException("非法操作");
        }
        // 需要封装 CarPackageAudit 封装对象信息。
        // 获取插入数据库中的CarPackageAudit的id 值，这样就拿到了 BusinessKey
        CarPackageAudit audit = new CarPackageAudit();
        audit.setServiceItemId(serviceItem.getId());
        audit.setServiceItemName(serviceItem.getName());
        audit.setServiceItemInfo(serviceItem.getInfo());
        audit.setServiceItemPrice(serviceItem.getDiscountPrice());
        audit.setCreatorId(String.valueOf(ShiroUtils.getUserId()));
        audit.setCreateTime(new Date());
        audit.setInfo(info);    // 发起审核的被著信息
        carPackageAuditService.save(audit);
        String businessKey = String.valueOf(audit.getId());
        // 如何能找到对应的流程定义，发起流程实例 （也就是我们发起的流程）
        // 通过 CarpackageAudit.AUDIT_TYPE 属性去 bpmnInfo 表中查询对应的 流程定义 Key
        // 若查询结果为 Null,说明没有上传该流程定义。
        // 若查询到多个，按部署时间最近的那个（版本号最高的）
        BpmnInfo bpmnInfo = bpmnInfoService.getByBpmnType(CarPackageAudit.AUDIT_TYPE);
        if (bpmnInfo == null) {
            throw new BusinessException("缺少对应的流程定义，请联系管理员");
        }
        String processDefinitionKey = bpmnInfo.getProcessDefinitionKey();
        // 发起流程时我们需要携带什么样的参数到流程中（给连线和节点上的流程变量赋值）
        // 需要定义一个 Map 集合，存储任务负责人相关 id (店长、财务)，折扣金额
        // 启动流程实例，在启动的同时绑定 Businesskey 与 流程变量的 Map 一并传入
        Map<String, Object> params = new HashMap<>();
        params.put("shopOwnerId", showOwnerId);  // 店长
        params.put("financeId", financeId);      // 财务
        params.put("disCountPrice", serviceItem.getDiscountPrice().longValue()); // 折扣金额
        ProcessInstance processInstance = runtimeService.startProcessInstanceByKey(processDefinitionKey, businessKey, params);
        // 为 CarPackageAudit 插入流程实例 id。
        audit.setInstanceId(processInstance.getProcessInstanceId());
        carPackageAuditService.update(audit);
        // 服务单项中的状态改编为 审核中。
        serviceItemMapper.changeAuditStatus(serviceItem.getId(), ServiceItem.AUDITSTATUS_AUDITING);
    }

    @Override
    public void changeAuditStatus(Long serviceItemId, Integer auditstatusInit) {
        serviceItemMapper.changeAuditStatus(serviceItemId, auditstatusInit);
    }
}
