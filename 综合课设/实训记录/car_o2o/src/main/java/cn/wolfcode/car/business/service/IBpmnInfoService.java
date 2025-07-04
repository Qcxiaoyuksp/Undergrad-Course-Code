package cn.wolfcode.car.business.service;

import cn.wolfcode.car.business.domain.BpmnInfo;
import cn.wolfcode.car.business.query.BpmnInfoQuery;
import cn.wolfcode.car.common.base.page.TablePageInfo;
import org.springframework.web.multipart.MultipartFile;

import java.io.IOException;
import java.io.InputStream;
import java.util.List;

/**
 * 审核流程定义接口
 */
public interface IBpmnInfoService {

    /**
     * 分页
     * @param qo
     * @return
     */
    TablePageInfo<BpmnInfo> query(BpmnInfoQuery qo);


    /**
     * 查单个
     * @param id
     * @return
     */
    BpmnInfo get(Long id);


    /**
     * 保存
     * @param
     */
    void save(BpmnInfo bpmnInfo);

  
    /**
     * 更新
     * @param
     */
    void update(BpmnInfo bpmnInfo);

    /**
     *  批量删除
     * @param ids
     */
    void deleteBatch(String ids);

    /**
     * 查询全部
     * @return
     */
    List<BpmnInfo> list();

    /**
     * 流程定义部署
     * @param bpmnFile
     * @param bpmnType
     * @param bpmnLabel
     * @param info
     */
    void deploy(MultipartFile bpmnFile, String bpmnType, String bpmnLabel, String info) throws IOException;

    /**
     * 根据类型获取资源文件输入流（XML、PNG）
     * @param id
     * @param type
     * @return
     */
    InputStream getInputStreamByType(Long id, String type);

    /**
     * 删除流程定义
     * @param id
     */
    void delete(Long id);

    // bpmnType 查询 流程定义的Key
    BpmnInfo getByBpmnType(String auditType);
}
