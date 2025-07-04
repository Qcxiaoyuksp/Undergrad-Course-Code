package cn.wolfcode.car.business.web.controller;

import cn.wolfcode.car.business.domain.BpmnInfo;
import cn.wolfcode.car.business.query.BpmnInfoQuery;
import cn.wolfcode.car.business.service.IBpmnInfoService;
import cn.wolfcode.car.common.base.page.TablePageInfo;
import cn.wolfcode.car.common.web.AjaxResult;
import org.apache.commons.io.IOUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.multipart.MultipartFile;

import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.InputStream;

@Controller
@RequestMapping("/business/bpmnInfo")
public class BpmnInfoController {
    // 模板前缀
    private static final String prefix = "/business/bpmnInfo";
    @Autowired
    private IBpmnInfoService bpmnInfoService;

    /**********************  进入页面 start *****************************/
    @RequestMapping("/listPage")
    public String list(){
        return prefix + "/list";
    }
    // 进入流程部署页面
    @RequestMapping("/deployPage")
    public String deployPage(){
        return prefix + "/deploy";
    }

    /**********************  进入页面 end *****************************/
    @RequestMapping("/query")
    @ResponseBody
    public TablePageInfo<BpmnInfo> query(BpmnInfoQuery qo){
        return bpmnInfoService.query(qo);
    }
    // 部署
    @RequestMapping("/deploy")
    @ResponseBody
    public AjaxResult deploy(MultipartFile bpmnFile,String bpmnType,String bpmnLabel,String info) throws IOException {
        bpmnInfoService.deploy(bpmnFile,bpmnType,bpmnLabel,info);
        return AjaxResult.success();
    }

    // 查看流程资源
    @RequestMapping("/readResource")
    @ResponseBody
    public void readResource(HttpServletResponse response,Long id,String type) throws Exception {
        // 根据类型去找对应的 一个流
        InputStream is = bpmnInfoService.getInputStreamByType(id,type);
        IOUtils.copy(is,response.getOutputStream());
    }

    // 流程删除
    @RequestMapping("/delete")
    @ResponseBody
    public AjaxResult delete(Long id){
        bpmnInfoService.delete(id);
        return AjaxResult.success();
    }
}
