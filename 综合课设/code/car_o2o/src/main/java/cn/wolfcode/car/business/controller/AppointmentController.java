package cn.wolfcode.car.business.controller;

import cn.wolfcode.car.business.domain.Appointment;
import cn.wolfcode.car.business.query.AppointmentQuery;
import cn.wolfcode.car.business.service.IAppointmentService;
import cn.wolfcode.car.common.base.page.TablePageInfo;
import cn.wolfcode.car.common.web.AjaxResult;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Bean;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

import java.util.ArrayList;
import java.util.List;

@Controller
@RequestMapping("/business/appointment")
public class AppointmentController {
    //去页面前缀
    private final String prefix = "/business/appointment/";
    //服务层
    @Autowired
    private IAppointmentService service;

    @RequestMapping("/listPage")
    public String listPage(){
        return prefix + "/list";
    }

    @RequestMapping("/query")
    @ResponseBody
    public TablePageInfo<Appointment> query(AppointmentQuery qo){
        TablePageInfo<Appointment> tablePageInfo = service.query(qo);
        return tablePageInfo;
    }

    @RequestMapping("/addPage")
    public String addPage(){
        return prefix + "/add";
    }

    @RequestMapping("/add")
    @ResponseBody
    public AjaxResult add(Appointment appointment){
        service.save(appointment);
        return AjaxResult.success();
    }

    //编辑页面
    @RequestMapping("/editPage")
    public String editPage(Long id,Model model){
        Appointment appointment = service.get(id);
        model.addAttribute("appointment",appointment);
        return prefix + "edit";
    }

    @RequestMapping("/edit")
    @ResponseBody
    public AjaxResult edit(Appointment appointment){
        service.update(appointment);
        return AjaxResult.success();
    }

    //取消
    @RequestMapping("/cancel")
    @ResponseBody
    public AjaxResult cancel(Long id){
        service.cancel(id);
        return AjaxResult.success();
    }

    //删除
    @RequestMapping("/remove")
    @ResponseBody
    public AjaxResult remove(Long[] ids){
        service.remove(ids);
        return AjaxResult.success();
    }

    //到店
    @RequestMapping("/arrival")
    @ResponseBody
    public AjaxResult arrival(Long id){
        service.arrival(id);
        return AjaxResult.success();
    }
}
