package cn.wolfcode.car.business.web.controller;

import cn.wolfcode.car.business.domain.Appointment;
import cn.wolfcode.car.business.query.AppointmentQuery;
import cn.wolfcode.car.business.service.IAppointmentService;
import cn.wolfcode.car.business.service.IStatementService;
import cn.wolfcode.car.common.base.page.TablePageInfo;
import cn.wolfcode.car.common.web.AjaxResult;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

@Controller
@RequestMapping("/business/appointment")
public class AppointmentController {
    // 模板前缀
    private static final String prefix = "/business/appointment";
    @Autowired
    private IAppointmentService appointmentService;
    @Autowired
    private IStatementService statementService;
    /**********************  进入页面 start *****************************/
    @RequestMapping("/listPage")
    public String list(){
        return prefix + "/list";
    }
    // 进入新增页面
    @RequestMapping("/addPage")
    public String addPage(){
        return prefix + "/add";
    }
    // 进入编辑页面
    @RequestMapping("/editPage")
    public String editPage(Long id, Model model){
        Appointment appointment = appointmentService.get(id);
        model.addAttribute("appointment",appointment);
        return prefix + "/edit";
    }
    /**********************  进入页面 end *****************************/
    @RequestMapping("/query")
    @ResponseBody
    public TablePageInfo<Appointment> query(AppointmentQuery qo){
        return appointmentService.query(qo);
    }
    // 新增功能实现
    @RequestMapping("/add")
    @ResponseBody
    public AjaxResult add(Appointment appointment){
        appointmentService.save(appointment);
        return AjaxResult.success();
    }
    // 编辑功能实现
    @RequestMapping("/edit")
    @ResponseBody
    public AjaxResult edit(Appointment appointment){
        appointmentService.update(appointment);
        return AjaxResult.success();
    }
    // 到店功能
    @RequestMapping("/arrival")
    @ResponseBody
    public AjaxResult arrival(Long id){
        appointmentService.arrival(id);
        return AjaxResult.success();
    }
    // 取消功能
    @RequestMapping("/cancel")
    @ResponseBody
    public AjaxResult cancel(Long id){
        appointmentService.cancel(id);
        return AjaxResult.success();
    }
    // 批量软删除
    @RequestMapping("/remove")
    @ResponseBody
    public AjaxResult remove(Long[] ids){
        appointmentService.remove(ids);
        return AjaxResult.success();
    }
    // 通过预约单生成结算单
    @RequestMapping("/generateStatement")
    @ResponseBody
    public AjaxResult generateStatement(Long appointmentId){
        Long statementId = statementService.generateStatement(appointmentId);
        return AjaxResult.success(statementId);
    }

}
