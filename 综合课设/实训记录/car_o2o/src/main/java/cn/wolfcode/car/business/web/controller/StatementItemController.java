package cn.wolfcode.car.business.web.controller;

import cn.wolfcode.car.business.domain.Statement;
import cn.wolfcode.car.business.domain.StatementItem;
import cn.wolfcode.car.business.query.StatementItemQuery;
import cn.wolfcode.car.business.service.IStatementItemService;
import cn.wolfcode.car.business.service.IStatementService;
import cn.wolfcode.car.common.base.page.TablePageInfo;
import cn.wolfcode.car.common.web.AjaxResult;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

import java.util.List;

@Controller
@RequestMapping("/business/statementItem")
public class StatementItemController {
    // 模板前缀
    private static final String prefix = "/business/statementItem/";

    @Autowired
    private IStatementService statementService;
    @Autowired
    private IStatementItemService statementItemService;
    /**********************  进入页面 start *****************************/

    /**********************  进入页面 end *****************************/
    // 根据不同状态进入不同的 结算单明细页面
    @RequestMapping("/itemDetail")
    public String itemDetail(Long statementId, Model model){
        // 查询当前结算单 并共享
        Statement statement = statementService.get(statementId);
        model.addAttribute("statement",statement);
        if(Statement.STATUS_CONSUME.equals(statement.getStatus())){
            // 消费中
            return prefix + "itemEdit.html";
        } else {
            // 已支付
            return prefix + "itemDetail.html";
        }
    }
    // 查询页面数据
    @RequestMapping("/query")
    @ResponseBody
    public TablePageInfo<StatementItem> query(StatementItemQuery qo){
        return statementItemService.query(qo);
    }

    @RequestMapping("/saveItems")
    @ResponseBody
    public AjaxResult saveItems(@RequestBody List<StatementItem> list){
        statementItemService.saveItems(list);
        return AjaxResult.success();
    }

    @RequestMapping("/pay")
    @ResponseBody
    public AjaxResult pay(Long statementId){
        statementService.pay(statementId);
        return AjaxResult.success();
    }
}
