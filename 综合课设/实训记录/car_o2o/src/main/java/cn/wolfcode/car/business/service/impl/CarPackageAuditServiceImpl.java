package cn.wolfcode.car.business.service.impl;

import cn.wolfcode.car.business.domain.BpmnInfo;
import cn.wolfcode.car.business.domain.CarPackageAudit;
import cn.wolfcode.car.business.domain.HistoricComment;
import cn.wolfcode.car.business.domain.ServiceItem;
import cn.wolfcode.car.business.mapper.CarPackageAuditMapper;
import cn.wolfcode.car.business.query.CarPackageAuditQuery;
import cn.wolfcode.car.business.service.IBpmnInfoService;
import cn.wolfcode.car.business.service.ICarPackageAuditService;
import cn.wolfcode.car.business.service.IServiceItemService;
import cn.wolfcode.car.common.base.page.TablePageInfo;
import cn.wolfcode.car.common.exception.BusinessException;
import cn.wolfcode.car.common.util.Convert;
import cn.wolfcode.car.shiro.ShiroUtils;
import com.github.pagehelper.PageHelper;
import org.activiti.bpmn.model.BpmnModel;
import org.activiti.engine.HistoryService;
import org.activiti.engine.RepositoryService;
import org.activiti.engine.RuntimeService;
import org.activiti.engine.TaskService;
import org.activiti.engine.history.HistoricProcessInstance;
import org.activiti.engine.history.HistoricTaskInstance;
import org.activiti.engine.runtime.ProcessInstance;
import org.activiti.engine.task.Comment;
import org.activiti.engine.task.Task;
import org.activiti.image.impl.DefaultProcessDiagramGenerator;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Lazy;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.io.InputStream;
import java.text.SimpleDateFormat;
import java.util.*;

@Service
@Transactional
public class CarPackageAuditServiceImpl implements ICarPackageAuditService {

    @Autowired
    private CarPackageAuditMapper carPackageAuditMapper;
    @Autowired
    private RepositoryService repositoryService;
    @Autowired
    private RuntimeService runtimeService;
    @Autowired
    @Lazy
    private IServiceItemService serviceItemService;
    @Autowired
    private TaskService taskService;
    @Autowired
    private IBpmnInfoService bpmnInfoService;
    @Autowired
    private HistoryService historyService;


    @Override
    public TablePageInfo<CarPackageAudit> query(CarPackageAuditQuery qo) {
        PageHelper.startPage(qo.getPageNum(), qo.getPageSize());
        return new TablePageInfo<CarPackageAudit>(carPackageAuditMapper.selectForList(qo));
    }


    @Override
    public void save(CarPackageAudit carPackageAudit) {
        // 从安全角度考虑，前台传递过来的对象是不可以直接使用的。
        // 所以我们都新建对象。这样无论如何都不会因为前台传递了默认值而改变我们的默认值数据。
        /*CarPackageAudit obj = new CarPackageAudit();
        obj.setServiceItemId(carPackageAudit.getServiceItemId());
        obj.setServiceItemName(carPackageAudit.getServiceItemName());
        obj.setServiceItemInfo(carPackageAudit.getServiceItemInfo());
        obj.setServiceItemPrice(carPackageAudit.getServiceItemPrice());
        obj.setInstanceId(carPackageAudit.getInstanceId());
        obj.setCreatorId(String.valueOf(ShiroUtils.getUserId()));
        obj.setCreateTime(new Date());
        obj.setInfo(carPackageAudit.getInfo());*/

        carPackageAuditMapper.insert(carPackageAudit);
    }

    @Override
    public CarPackageAudit get(Long id) {
        return carPackageAuditMapper.selectByPrimaryKey(id);
    }


    @Override
    public void update(CarPackageAudit carPackageAudit) {
        CarPackageAudit obj = this.get(carPackageAudit.getId());
        // 只有状态为预约中才可以点击编辑按钮。其他都不可以。
        obj.setServiceItemId(carPackageAudit.getServiceItemId());
        obj.setServiceItemName(carPackageAudit.getServiceItemName());
        obj.setServiceItemInfo(carPackageAudit.getServiceItemInfo());
        obj.setServiceItemPrice(carPackageAudit.getServiceItemPrice());
        obj.setInstanceId(carPackageAudit.getInstanceId());
        obj.setCreatorId(String.valueOf(ShiroUtils.getUserId()));
        obj.setInfo(carPackageAudit.getInfo());
        carPackageAuditMapper.updateByPrimaryKey(obj);
    }

    @Override
    public void deleteBatch(String ids) {
        Long[] dictIds = Convert.toLongArray(ids);
        for (Long dictId : dictIds) {
            carPackageAuditMapper.deleteByPrimaryKey(dictId);
        }
    }

    @Override
    public InputStream processImg(Long id) {
        // 需要高亮的节点
        List<String> highLightedActivities = new ArrayList<>();
        // 需要高亮的连线
        List<String> highLightedFlows = new ArrayList<>();
        // 根据 id 查询 CarpackageAudit 对象
        CarPackageAudit audit = this.get(id);
        // 当前 CarPackageAudit 对象中只有流程实例 id。 根据流程实例 id 查询流程实例对象
        ProcessInstance processInstance = runtimeService.createProcessInstanceQuery()
                .processInstanceId(audit.getInstanceId())
                .singleResult();
        // 若已取消的流程图，那我们查看时就默认给其空的高亮节点即可
        if(processInstance == null){
            throw new BusinessException("没有正在运行的任务");
        }
        // 获取当前活动的节点 (新方法)
        highLightedActivities = runtimeService.getActiveActivityIds(processInstance.getId());
        // 根据流程实例获取 流程定义的 Id
        // 流程定义 Id
        String processDefinitionId = processInstance.getProcessDefinitionId();
        // 生成 png 流程图
        BpmnModel model = repositoryService.getBpmnModel(processDefinitionId);
        DefaultProcessDiagramGenerator generator = new DefaultProcessDiagramGenerator();
        return generator.generateDiagram(model,highLightedActivities,highLightedFlows,
                "宋体","宋体","宋体");
    }

    @Override
    @Transactional
    public void cancelApply(Long id) {
        // 合理化校验：必须状态是 审批中 才可以进行撤销操作
        CarPackageAudit audit = this.get(id);
        if(!CarPackageAudit.STATUS_IN_ROGRESS.equals(audit.getStatus())){
            throw new BusinessException("只有审核中的流程才可以进行撤销操作");
        }
        // 1. 审核记录状态 --> 流程撤销
        audit.setStatus(CarPackageAudit.STATUS_CANCEL);
        carPackageAuditMapper.updateByPrimaryKey(audit);
        // 2. 通过服务单项 id --> 找到服务单项对象，把状态改为初始化
        serviceItemService.changeAuditStatus(audit.getServiceItemId(), ServiceItem.AUDITSTATUS_INIT);
        // 3. 删除流程实例
        runtimeService.deleteProcessInstance(audit.getInstanceId(),"流程撤销");
    }

    @Override
    public TablePageInfo<CarPackageAudit> todoQuery(CarPackageAuditQuery qo) {
        BpmnInfo bpmnInfo = bpmnInfoService.getByBpmnType(CarPackageAudit.AUDIT_TYPE);
        String processDefinitionKey =  bpmnInfo.getProcessDefinitionKey(); // 流程定义的 Key（套餐审批的 Key）
        List<String> businessKeyList = new ArrayList<>();
        // 需要分页
        // 查询总条数
        long count = taskService.createTaskQuery()
                .processDefinitionKey(processDefinitionKey)
                .taskAssignee(String.valueOf(ShiroUtils.getUserId()))
                .count();
        if(count == 0){
            return new TablePageInfo<CarPackageAudit>(count, Collections.EMPTY_LIST);
        }
        // - 根据用户（当前登录用户）查询已办任务集合。
        List<Task> tasks = taskService.createTaskQuery()
                .processDefinitionKey(processDefinitionKey)
                .taskAssignee(String.valueOf(ShiroUtils.getUserId()))
                .listPage((qo.getPageNum() - 1) * qo.getPageSize(), qo.getPageSize());
        // - 遍历任务集合，拿到每一个待办任务。
        for (Task task : tasks) {
            // - 根据任务查询对应的流程实例。
            ProcessInstance processInstance = runtimeService.createProcessInstanceQuery()
                    .processInstanceId(task.getProcessInstanceId())
                    .singleResult();
            // - 通过流程实例拿到 BusinessKey （每一个任务有自己对应的 BusinessKey）。
            String businessKey = processInstance.getBusinessKey();
            // - 我们可以将所有的 BusinessKey 存入到一个集合中。
            businessKeyList.add(businessKey);
        }
        // - 最后通过 MyBatis 批量查询这些 Key 对应的 CarPackageAudit 的业务数据。
        List<CarPackageAudit> carPackageAuditList = carPackageAuditMapper.queryTodoList(businessKeyList);
        return new TablePageInfo<CarPackageAudit>(count,carPackageAuditList);
    }

    @Override
    public void audit(Long id, String auditStatus, String info) {
        // 只有状态为审核中才可以进行审批
        CarPackageAudit audit = this.get(id);
        if(!CarPackageAudit.STATUS_IN_ROGRESS.equals(audit.getStatus())){
            throw new BusinessException("只有状态为审核中才可以进行审批操作");
        }
        // 将同意或者拒绝转换为 Boolean 类型
        Boolean status = Boolean.valueOf(auditStatus);
        // 通过流程实例 Id 查询对应当前正在活动的任务
        String instanceId = audit.getInstanceId();
        Task task = taskService.createTaskQuery()
                .processInstanceId(instanceId)
                .singleResult();
        // 设置批注信息
        String msg = ShiroUtils.getUser().getUserName() + (status?"[同意]":"[拒绝]") +
                ",审批意见:" + info;
        taskService.addComment(task.getId(),instanceId,msg);
        // 设置流程变量
        // task.getTaskDefinitionKey() 获取到节点在流程图中定义的  id
        String taskDefinitionKey = task.getTaskDefinitionKey();
        Map<String,Object> params = new HashMap<>();
        params.put(taskDefinitionKey,status);
        // 完成任务
        taskService.complete(task.getId(),params);
        // ************************************************************************
        if(status){
            // 同意
            Task nextTask = taskService.createTaskQuery()
                    .processInstanceId(instanceId)
                    .singleResult();
            if(nextTask == null){
                // 流程走完了
                // CarPackageAudit 对象 -->  状态修改为 审批通过   （快照）
                audit.setStatus(CarPackageAudit.STATUS_PASS);
                carPackageAuditMapper.updateByPrimaryKey(audit);
                // ServiceItem 对象 -->  状态修改为 审批通过   （服务单项）
                serviceItemService.changeAuditStatus(audit.getServiceItemId(),ServiceItem.AUDITSTATUS_APPROVED);
            }
        } else {
            // 拒绝
            //  CarPackageAudit 对象 -->  状态修改为 审批拒绝   （快照）
            audit.setStatus(CarPackageAudit.STATUS_REJECT);
            carPackageAuditMapper.updateByPrimaryKey(audit);
            //  ServiceItem 对象 -->  状态修改为 重新调整   （服务单项）
            serviceItemService.changeAuditStatus(audit.getServiceItemId(),ServiceItem.AUDITSTATUS_REPLY);
        }
    }

    @Override
    public TablePageInfo<CarPackageAudit> doneQuery(CarPackageAuditQuery qo) {
        BpmnInfo bpmnInfo = bpmnInfoService.getByBpmnType(CarPackageAudit.AUDIT_TYPE);
        String processDefinitionKey =  bpmnInfo.getProcessDefinitionKey(); // 流程定义的 Key（套餐审批的 Key）
        
        List<String> businessKeyList = new ArrayList<>();
        // 需要分页
        // 查询总条数
        long count = historyService.createHistoricTaskInstanceQuery()
                .processDefinitionKey(processDefinitionKey)
                .taskAssignee(String.valueOf(ShiroUtils.getUserId()))
                .finished() // 已完成任务
                .count();
        if(count == 0){
            return new TablePageInfo<CarPackageAudit>(count, Collections.EMPTY_LIST);
        }
        // - 根据用户（当前登录用户）查询已办任务集合。
        List<HistoricTaskInstance> historicTaskInstances = historyService.createHistoricTaskInstanceQuery()
                .processDefinitionKey(processDefinitionKey)
                .taskAssignee(String.valueOf(ShiroUtils.getUserId()))
                .finished() // 已完成任务
                .listPage((qo.getPageNum() - 1) * qo.getPageSize(), qo.getPageSize());
        // - 遍历任务集合，拿到每一个已办任务。
        for (HistoricTaskInstance task : historicTaskInstances) {
            // - 根据任务查询对应的流程实例。
            HistoricProcessInstance historicProcessInstance = historyService.createHistoricProcessInstanceQuery()
                    .processInstanceId(task.getProcessInstanceId())
                    .singleResult();
            // - 通过流程实例拿到 BusinessKey （每一个任务有自己对应的 BusinessKey）。
            String businessKey = historicProcessInstance.getBusinessKey();
            // - 我们可以将所有的 BusinessKey 存入到一个集合中。
            businessKeyList.add(businessKey);
        }
        // - 最后通过 MyBatis 批量查询这些 Key 对应的 CarPackageAudit 的业务数据。
        List<CarPackageAudit> carPackageAuditList = carPackageAuditMapper.queryHistoryTaskList(businessKeyList);
        return new TablePageInfo<CarPackageAudit>(count,carPackageAuditList);
    }

    @Override
    public TablePageInfo<HistoricComment> listHistoryQuery(String instanceId) {
        List<HistoricComment> commentList = new ArrayList<>();
        List<HistoricTaskInstance> taskList = historyService.createHistoricTaskInstanceQuery()
                .processInstanceId(instanceId)
                .finished() // 已完成任务
                .orderByTaskCreateTime()    // 按照任务开始时间排序
                .desc() // 倒序排序
                .list();
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        for (HistoricTaskInstance task : taskList) {
            HistoricComment comment = new HistoricComment();
            comment.setTaskName(task.getName());
            comment.setStartTime(sdf.format(task.getStartTime()));
            comment.setEndTime(sdf.format(task.getEndTime()));
            comment.setDurationInMillis(String.valueOf(task.getDurationInMillis()));
            // 拿到每个任务的的批注集合
            List<Comment> taskComments = taskService.getTaskComments(task.getId());
            if(taskComments.size() > 0){
                // 说明存在批注信息
                comment.setComment(taskComments.get(0).getFullMessage());
            }
            commentList.add(comment);
        }
        return new TablePageInfo<HistoricComment>(Long.valueOf(commentList.size()),commentList);
    }
}
