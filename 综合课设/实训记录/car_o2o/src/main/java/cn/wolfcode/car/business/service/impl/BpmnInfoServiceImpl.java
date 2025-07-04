package cn.wolfcode.car.business.service.impl;

import cn.wolfcode.car.business.domain.BpmnInfo;
import cn.wolfcode.car.business.mapper.BpmnInfoMapper;
import cn.wolfcode.car.business.query.BpmnInfoQuery;
import cn.wolfcode.car.business.service.IBpmnInfoService;
import cn.wolfcode.car.common.base.page.TablePageInfo;
import cn.wolfcode.car.common.exception.BusinessException;
import cn.wolfcode.car.common.util.Convert;
import com.github.pagehelper.PageHelper;
import org.activiti.bpmn.model.BpmnModel;
import org.activiti.engine.RepositoryService;
import org.activiti.engine.RuntimeService;
import org.activiti.engine.repository.Deployment;
import org.activiti.engine.repository.ProcessDefinition;
import org.activiti.engine.runtime.ProcessInstance;
import org.activiti.image.impl.DefaultProcessDiagramGenerator;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.web.multipart.MultipartFile;

import java.io.IOException;
import java.io.InputStream;
import java.util.Collections;
import java.util.List;

@Service
@Transactional
public class BpmnInfoServiceImpl implements IBpmnInfoService {

    @Autowired
    private BpmnInfoMapper bpmnInfoMapper;
    @Autowired
    private RepositoryService repositoryService;
    @Autowired
    private RuntimeService runtimeService;


    @Override
    public TablePageInfo<BpmnInfo> query(BpmnInfoQuery qo) {
        PageHelper.startPage(qo.getPageNum(), qo.getPageSize());

        return new TablePageInfo<BpmnInfo>(bpmnInfoMapper.selectForList(qo));
    }


    @Override
    public void save(BpmnInfo bpmnInfo) {

        bpmnInfoMapper.insert(bpmnInfo);
    }

    @Override
    public BpmnInfo get(Long id) {
        return bpmnInfoMapper.selectByPrimaryKey(id);
    }


    @Override
    public void update(BpmnInfo bpmnInfo) {

        bpmnInfoMapper.updateByPrimaryKey(bpmnInfo);
    }

    @Override
    public void deleteBatch(String ids) {
        Long[] dictIds = Convert.toLongArray(ids);
        for (Long dictId : dictIds) {
            bpmnInfoMapper.deleteByPrimaryKey(dictId);
        }
    }

    @Override
    public List<BpmnInfo> list() {
        return bpmnInfoMapper.selectAll();
    }

    @Override
    @Transactional
    public void deploy(MultipartFile bpmnFile, String bpmnType, String bpmnLabel, String info) throws IOException {
        // 获取原始名字 bus_service_car_package.bpmn
        String originalFilename = bpmnFile.getOriginalFilename();
        // 获取文件后缀名  bpmn
        String subName = originalFilename.substring(originalFilename.lastIndexOf(".") + 1);
        // 需要验证传入的参数必须为 bpmn 格式。
        if(!"bpmn".equalsIgnoreCase(subName)){
            throw new BusinessException("流程文件必须是 bpmn 格式！");
        }
        // 进行部署
        Deployment deploy = repositoryService.createDeployment()
                .addInputStream(originalFilename, bpmnFile.getInputStream())
                .deploy();
        // 根据部署对象查询流程定义对象     一次部署 --> 一个流程定义
        ProcessDefinition processDefinition = repositoryService.createProcessDefinitionQuery()
                .deploymentId(deploy.getId())
                .singleResult();
        // 获取流程定义对象 获取到 流程定义的Key 和 version
        BpmnInfo bpmnInfo = new BpmnInfo();
        bpmnInfo.setBpmnType(bpmnType);
        bpmnInfo.setBpmnLabel(bpmnLabel);
        bpmnInfo.setInfo(info);
        bpmnInfo.setDeployTime(deploy.getDeploymentTime());
        bpmnInfo.setProcessDefinitionKey(processDefinition.getKey());
        bpmnInfo.setVersion(processDefinition.getVersion());
        // 插入到 bpmnInfo 中
        bpmnInfoMapper.insert(bpmnInfo);
    }

    @Override
    public InputStream getInputStreamByType(Long id, String type) {
        // 通过 id 查询 bpmnInfo 对象。就可以该对象中对应的 流程定义的 Key 和 Version 了
        BpmnInfo bpmnInfo = this.get(id);
        String processDefinitionKey = bpmnInfo.getProcessDefinitionKey();
        Integer version = bpmnInfo.getVersion();
        // 就可以通过 流程定义的 Key 和 Version 查询出当前流程定义对象。
        ProcessDefinition processDefinition = repositoryService.createProcessDefinitionQuery()
                .processDefinitionKey(processDefinitionKey)
                .processDefinitionVersion(version)
                .singleResult();
        String deploymentId = processDefinition.getDeploymentId();
        String xmlName = processDefinition.getResourceName();
        InputStream is = null;
        // 根据类型判断需要哪种输入流
        if("xml".equalsIgnoreCase(type)){
            // 需要有 xml 的文件名称
            is = repositoryService.getResourceAsStream(deploymentId,xmlName); // 获取 XML 方式。
        } else if("png".equalsIgnoreCase(type)){
            // 流程图对象模型
            BpmnModel model = repositoryService.getBpmnModel(processDefinition.getId());
            // 流程文件图片生成器
            DefaultProcessDiagramGenerator generator = new DefaultProcessDiagramGenerator();
            // generator.generateDiagram(bpmn模型，需要高亮节点的id集合，需要高亮的链接id集合，字体，字体，字体)
            is = generator.generateDiagram(model, Collections.EMPTY_LIST,Collections.EMPTY_LIST,
                    "宋体","宋体","宋体");
        } else {
            throw new BusinessException("请传递正确类型格式");
        }
        return is;
    }

    @Override
    @Transactional
    public void delete(Long id) {
        BpmnInfo bpmnInfo = this.get(id);
        // 查询当前流程定义有哪些流程实例
        List<ProcessInstance> processInstanceList = runtimeService.createProcessInstanceQuery()
                .processDefinitionKey(bpmnInfo.getProcessDefinitionKey())
                .list();
        // 找到所有对应的业务标识，通过业务标识更新其状态为（初始化）
        for(ProcessInstance processInstance : processInstanceList){
            String businessKey = processInstance.getBusinessKey();
            // TODO  后续待完成...
        }
        // 级联删除流程定义
        ProcessDefinition processDefinition = repositoryService.createProcessDefinitionQuery()
                .processDefinitionKey(bpmnInfo.getProcessDefinitionKey())
                .processDefinitionVersion(bpmnInfo.getVersion())
                .singleResult();
        repositoryService.deleteDeployment(processDefinition.getDeploymentId(),true);
        // 删除业务表数据
        bpmnInfoMapper.deleteByPrimaryKey(id);
    }

    @Override
    public BpmnInfo getByBpmnType(String auditType) {
        return bpmnInfoMapper.getByBpmnType(auditType);
    }
}
