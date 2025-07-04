package cn.wolfcode.car.business.controller;

import cn.wolfcode.car.business.domain.ServiceItem;
import cn.wolfcode.car.business.domain.Statement;
import cn.wolfcode.car.business.query.ServiceItemQuery;
import cn.wolfcode.car.business.query.StatementQuery;
import cn.wolfcode.car.business.service.IServiceItemService;
import cn.wolfcode.car.business.service.IStatementService;
import cn.wolfcode.car.common.base.page.TablePageInfo;
import cn.wolfcode.car.common.web.AjaxResult;
import org.apache.shiro.authz.annotation.RequiresPermissions;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

@Controller
@RequestMapping("/business/statement")
public class StatementController {
    //去页面前缀
    private final String prefix = "/business/statement/";
    @Autowired
    private IStatementService service;

    //删除
    @RequestMapping("/remove")
    @ResponseBody
    public AjaxResult remove(Long[] id){
        service.remove(id);
        return AjaxResult.success();
    }

    @GetMapping("/listPage")
    public String list(){
        //分页展示
        return prefix + "list";
    }
    //新增
    @RequestMapping("/addPage")
    public String addPage(){
        return prefix + "add";
    }
    //插入数据
    @RequestMapping("/add")
    @ResponseBody
    public AjaxResult add(Statement statement){
        service.insert(statement);
        return AjaxResult.success();
    }

    //请求列表数据
    @RequestMapping("/query")
    @ResponseBody
    public TablePageInfo<Statement> query(StatementQuery qo){
        //该类存放分页信息和数据
        TablePageInfo<Statement> tablePageInfo =
                service.selectForList(qo);
        System.out.println(qo.getStartTime());
        System.out.println(qo.getEndTime());
        return tablePageInfo;
    }

    //编辑页面
    @RequestMapping("/editPage")
    public String editPage(Long id, Model model){
        Statement statement = service.get(id);
        model.addAttribute("statement",statement);
        return prefix + "/edit";
    }

    //编辑数据
    @RequestMapping("/edit")
    @ResponseBody
    public AjaxResult edit(Statement statement){
        service.edit(statement);
        return AjaxResult.success();
    }
}
