package cn.wolfcode.car.business.controller;

import cn.wolfcode.car.business.domain.ServiceItem;
import cn.wolfcode.car.business.query.ServiceItemQuery;
import cn.wolfcode.car.business.service.IServiceItemService;
import cn.wolfcode.car.common.base.page.TablePageInfo;
import cn.wolfcode.car.common.base.query.QueryObject;
import cn.wolfcode.car.common.web.AjaxResult;

import org.apache.shiro.authz.annotation.RequiresPermissions;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.Banner;
import org.springframework.stereotype.Controller;
import org.springframework.stereotype.Repository;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

import javax.jws.WebParam;
import javax.xml.ws.Service;

@Controller
@RequestMapping("/business/serviceItem")
public class ServiceItemController {
    //去页面前缀
    private final String prefix = "/business/serviceItem/";
    @Autowired
    private IServiceItemService service;

    //服务单项列表请求 http://localhost/business/serviceItem/listPage
    @RequiresPermissions("business:serviceItem:view")
    @GetMapping("/listPage")
    public String list(){
        //分页展示
        return prefix + "list";
    }

    //请求列表数据
    @RequiresPermissions("business:serviceItem:list")
    @RequestMapping("/query")
    @ResponseBody
    public TablePageInfo<ServiceItem> query(ServiceItemQuery qo){
        //该类存放分页信息和数据
        TablePageInfo<ServiceItem> tablePageInfo =
                service.selectForList(qo);
        return tablePageInfo;
    }

    //新增
    @RequestMapping("/addPage")
    public String addPage(){
        return prefix + "add";
    }

    //插入数据
    @RequestMapping("/add")
    @ResponseBody
    public AjaxResult add(ServiceItem serviceItem){
        service.insert(serviceItem);
        return AjaxResult.success();
    }

    //编辑页面
    @RequestMapping("/editPage")
    public String editPage(Long id, Model model){
        ServiceItem serviceItem = service.get(id);
        model.addAttribute("serviceItem",serviceItem);
        return prefix + "/edit";
    }


    //编辑数据
    @RequestMapping("/edit")
    @ResponseBody
    public AjaxResult edit(ServiceItem serviceItem){
        service.edit(serviceItem);
        return AjaxResult.success();
    }

    @RequestMapping("/saleOn")
    @ResponseBody
    public AjaxResult saleOn(Long id){
        service.saleOn(id);
        return AjaxResult.success();
    }

    //下架方法
    @RequestMapping("/saleOff")
    @ResponseBody
    public AjaxResult saleOff(Long id){
        service.saleOff(id);
        return AjaxResult.success();
    }
}
