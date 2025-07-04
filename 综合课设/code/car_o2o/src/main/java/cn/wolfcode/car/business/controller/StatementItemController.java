package cn.wolfcode.car.business.controller;

import cn.wolfcode.car.business.domain.Statement;
import cn.wolfcode.car.business.domain.StatementItem;
import cn.wolfcode.car.business.query.StatementItemQuery;
import cn.wolfcode.car.business.query.StatementQuery;
import cn.wolfcode.car.business.service.IStatementItemService;
import cn.wolfcode.car.business.service.IStatementService;
import cn.wolfcode.car.common.base.page.TablePageInfo;
import cn.wolfcode.car.common.base.query.QueryObject;
import cn.wolfcode.car.common.web.AjaxResult;
import org.apache.shiro.authz.annotation.RequiresPermissions;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

import java.util.List;

@Controller
@RequestMapping("/business/statementItem")
public class StatementItemController {
    //去页面前缀
    private final String prefix = "/business/statementItem/";
    @Autowired
    private IStatementItemService statementItemService;

    @Autowired
    private IStatementService statementService;


    @GetMapping("/itemDetail")
    public String list(Long statementId,Model model){
        Statement statement = statementService.get(statementId);
        model.addAttribute("statement",statement);
        if (Statement.STATUS_CONSUME.equals(statement.getStatus())){
            //消费中
            return prefix + "itemEdit";
        }
        return prefix + "itemDetail";
    }

    //请求列表数据
    @RequestMapping("/query")
    @ResponseBody
    public TablePageInfo<StatementItem> query(StatementItemQuery qo){
        //该类存放分页信息和数据
        TablePageInfo<StatementItem> tablePageInfo =
                statementItemService.query(qo);
        return tablePageInfo;
    }

    @RequiresPermissions("business:statementItem:saveItems")
    @RequestMapping("/saveItems")
    @ResponseBody
    public AjaxResult saveItems(@RequestBody List<StatementItem> items){
        statementItemService.saveItems(items);
        return AjaxResult.success();
    }

}
