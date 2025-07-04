package cn.wolfcode.car.business.web.controller;

import cn.wolfcode.car.business.domain.Statement;
import cn.wolfcode.car.business.query.StatementQuery;
import cn.wolfcode.car.business.service.IStatementService;
import cn.wolfcode.car.common.base.page.TablePageInfo;
import cn.wolfcode.car.common.web.AjaxResult;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

@Controller
@RequestMapping("/business/statement")
public class StatementController {
    // 模板前缀
    private static final String prefix = "/business/statement";
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
        model.addAttribute("statement",statementService.get(id));
        return prefix + "/edit";
    }
    /**********************  进入页面 end *****************************/
    @RequestMapping("/query")
    @ResponseBody
    public TablePageInfo<Statement> query(StatementQuery qo){
        return statementService.query(qo);
    }
    // 新增功能
    @RequestMapping("/add")
    @ResponseBody
    public AjaxResult add(Statement statement){
        statementService.save(statement);
        return AjaxResult.success();
    }
    // 编辑功能
    @RequestMapping("/edit")
    @ResponseBody
    public AjaxResult edit(Statement statement){
        statementService.update(statement);
        return AjaxResult.success();
    }
    // 删除功能
    @RequestMapping("/remove")
    @ResponseBody
    public AjaxResult remove(Long[] id){
        statementService.remove(id);
        return AjaxResult.success();
    }

}
