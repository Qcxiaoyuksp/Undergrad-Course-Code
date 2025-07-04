package cn.wolfcode.car.business.web.controller;

import cn.wolfcode.car.business.domain.CarPackageAudit;
import cn.wolfcode.car.business.domain.HistoricComment;
import cn.wolfcode.car.business.query.CarPackageAuditQuery;
import cn.wolfcode.car.business.service.ICarPackageAuditService;
import cn.wolfcode.car.common.base.page.TablePageInfo;
import cn.wolfcode.car.common.web.AjaxResult;
import org.apache.commons.io.IOUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.InputStream;

@Controller
@RequestMapping("/business/carPackageAudit")
public class CarPackageAuditController {
    // 模板前缀
    private static final String prefix = "/business/carPackageAudit";
    @Autowired
    private ICarPackageAuditService carPackageAuditService;

    /**********************  进入页面 start *****************************/
    @RequestMapping("/listPage")
    public String list(){
        return prefix + "/list";
    }
    @RequestMapping("/todoPage")
    public String todoPage(){
        return prefix + "/todoPage";
    }
    // 进入审批页面
    @RequestMapping("/auditPage")
    public String auditPage(Long id, Model model){
        model.addAttribute("id",id);
        return prefix + "/auditPage";
    }
    // 进入我的已办任务
    @RequestMapping("/donePage")
    public String donePage(){
        return prefix + "/donePage";
    }
    /**
     * 进入查看审批历史
     */
    @RequestMapping("/historyList")
    public String historyList(String instanceId,Model model){
        model.addAttribute("instanceId",instanceId);
        return prefix + "/historyList";
    }
    /**********************  进入页面 end *****************************/
    @RequestMapping("/query")
    @ResponseBody
    public TablePageInfo<CarPackageAudit> query(CarPackageAuditQuery qo){
        return carPackageAuditService.query(qo);
    }

    /**
     * 查看流程图
     * @param id
     * @param response
     * @throws IOException
     */
    @RequestMapping("/processImg")
    @ResponseBody
    public void processImg(Long id, HttpServletResponse response) throws IOException {
        InputStream is = carPackageAuditService.processImg(id);
        IOUtils.copy(is,response.getOutputStream());
    }
    /**
     * 撤销流程
     */
    @RequestMapping("/cancelApply")
    @ResponseBody
    public AjaxResult cancelApply(Long id){
        carPackageAuditService.cancelApply(id);
        return AjaxResult.success();
    }
    /**
     * 我的代办列表
     */
    @RequestMapping("/todoQuery")
    @ResponseBody
    public TablePageInfo<CarPackageAudit> todoQuery(CarPackageAuditQuery qo){
        return carPackageAuditService.todoQuery(qo);
    }
    /**
     * 审批功能
     */
    @RequestMapping("/audit")
    @ResponseBody
    public AjaxResult audit(Long id,String auditStatus,String info){
        carPackageAuditService.audit(id,auditStatus,info);
        return AjaxResult.success();
    }
    /**
     * 我的已办列表
     */
    @RequestMapping("/doneQuery")
    @ResponseBody
    public TablePageInfo<CarPackageAudit> doneQuery(CarPackageAuditQuery qo){
        return carPackageAuditService.doneQuery(qo);
    }
    /**
     * 查看审批历史
     */
    @RequestMapping("/listHistory")
    @ResponseBody
    public TablePageInfo<HistoricComment> listHistory(String instanceId){
        return carPackageAuditService.listHistoryQuery(instanceId);
    }

}
